#include "TargetPainter.h"

TargetPainter::TargetPainter(FastServo &servo, DigitalOut &laser,
                             Event<void(AudioPlayer::Clip)> &player)
    : sharedQueue_{mbed_event_queue()}, targetEvent_{sharedQueue_->event(
                                            this, &TargetPainter::turnOnLaser)},
      servo_{servo}, laser_{laser}, player_{player} {}

// All methods are called from shared event queue.
// This removes the need for synchronization.

void TargetPainter::targetLost() {
  player_.post(AudioPlayer::Clip::TARGET_LOST);
  timeoutEventId_ = 0;
}

void TargetPainter::turnOffLaser() {
  laser_.write(0);
  player_.post(AudioPlayer::Clip::CONTACT_LOST);
  timeoutEventId_ =
      sharedQueue_->call_in(targetLostDelay, this, &TargetPainter::targetLost);
}

void TargetPainter::turnOnLaser(float pos) {
  time_t now = time(nullptr);

  if (laser_.read() == 0) {
    if (now - lastContact_ > recentContactThreshold || lastContact_ == 0) {
      player_.post(AudioPlayer::Clip::TARGET_ACQUIRED);
    } else {
      player_.post(AudioPlayer::Clip::CONTACT_RESTORED);
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
