#pragma once

#include "LaserSensor.h"
#include "Servo.h"
#include <vector>

class RangingScanner {
public:
  using TargetCenterCallback = mbed::Callback<void(float)>;

  RangingScanner(Servo &servo, LaserSensor &sensor, size_t numSteps,
                 float nSigma, uint16_t minDiff);

  void search(size_t minLockPoints, size_t maxBreakPoints,
              TargetCenterCallback cb);

private:
  static constexpr int kStepDelay = 100; // 0.1s
  static constexpr int kNumCalibrations = 5;

  void scan(bool scanForward, size_t minLockPoints, size_t maxBreakPoints,
            TargetCenterCallback cb);

  Servo &servo_;
  LaserSensor &sensor_;
  std::vector<uint16_t> baseline_;
};
