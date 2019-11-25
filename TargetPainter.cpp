#include "TargetPainter.h"

void TargetPainter::targetLost() {
  if ((random() % 2) == 0) {
    audio_.play(AudioPlayer::Clip::TARGET_LOST);
  } else {
    audio_.play(AudioPlayer::Clip::ARE_YOU_STILL_THERE);
  }
}

void TargetPainter::turnOffLaser() {
  laser_.write(0);
  audio_.play(AudioPlayer::Clip::SFX_RETRACT);
  // schedule audio effect in 30 seconds.
  timeout_.attach_us(callback(this, &TargetPainter::targetLost),
                     targetLostAudioDelay);
}

void TargetPainter::targetAt(float pos) {
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
  timeout_.detach();
  timeout_.attach_us(callback(this, &TargetPainter::turnOffLaser),
                     laserOffDelay);
}
