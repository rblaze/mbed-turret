#pragma once
#include "AudioPlayer.h"
#include <FastServo.h>

class TargetPainter {
public:
  TargetPainter(FastServo &servo, DigitalOut &laser,
                Event<void(AudioPlayer::Clip)> &player);

  Event<void(float)> &targetEvent() { return targetEvent_; }

private:
  static constexpr time_t recentContactThreshold{30};
  static constexpr int laserOffDelay{5000};
  static constexpr int targetLostDelay{30000};

  void turnOnLaser(float);
  void turnOffLaser();
  void targetLost();

  EventQueue *sharedQueue_;
  Event<void(float)> targetEvent_;
  time_t lastContact_{0};
  int timeoutEventId_{0};
  FastServo &servo_;
  DigitalOut &laser_;
  Event<void(AudioPlayer::Clip)> &player_;
};
