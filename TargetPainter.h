#pragma once
#include "AudioPlayer.h"
#include <FastServo.h>

class TargetPainter {
public:
  TargetPainter(FastServo &servo, DigitalOut &laser, AudioPlayer &audio)
      : servo_{servo}, laser_{laser}, audio_{audio} {}

  void targetAt(float);

private:
  void turnOffLaser();
  void targetLost();

  FastServo &servo_;
  DigitalOut &laser_;
  AudioPlayer &audio_;
  LowPowerTimeout timeout_;
  time_t lastContact_{0};

  static constexpr time_t recentContactThreshold{30};
  static constexpr us_timestamp_t laserOffDelay{5000000};
  static constexpr us_timestamp_t targetLostAudioDelay{30000000};
};
