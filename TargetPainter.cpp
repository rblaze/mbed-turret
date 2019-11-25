#include "TargetPainter.h"

TargetPainter::TargetPainter(FastServo &servo, DigitalOut &laser,
                             AudioPlayer &audio)
    : sharedQueue_{mbed_event_queue()}, targetEvent_{sharedQueue_->event(
                                            this, &TargetPainter::turnOnLaser)},
      servo_{servo}, laser_{laser}, audio_{audio} {}

// All methods are called from shared event queue.
// This removes the need for synchronization.

void TargetPainter::targetLost() {
  if ((random() % 2) == 0) {
    audio_.play(AudioPlayer::Clip::TARGET_LOST);
  } else {
    audio_.play(AudioPlayer::Clip::ARE_YOU_STILL_THERE);
  }
  timeoutEventId_ = 0;
}

void TargetPainter::turnOffLaser() {
  laser_.write(0);
  audio_.play(AudioPlayer::Clip::SFX_RETRACT);
  timeoutEventId_ =
      sharedQueue_->call_in(targetLostDelay, this, &TargetPainter::targetLost);
}

void TargetPainter::turnOnLaser(float pos) {
  time_t now = time(nullptr);

  if (laser_.read() == 0) {
    if (now - lastContact_ > recentContactThreshold || lastContact_ == 0) {
      if ((random() % 2) == 0) {
        audio_.play(AudioPlayer::Clip::HELLO_FRIEND);
      } else {
        audio_.play(AudioPlayer::Clip::I_SEE_YOU);
      }
    } else {
      audio_.play(AudioPlayer::Clip::SFX_ACTIVE);
    }
  }

  lastContact_ = now;

  servo_.write(pos);
  laser_.write(1);

  // Forget old timeout, set a new one in 5 seconds.
  if (timeoutEventId_ != 0) {
    sharedQueue_->cancel(timeoutEventId_);
  }

  timeoutEventId_ =
      sharedQueue_->call_in(laserOffDelay, this, &TargetPainter::turnOffLaser);
}
