#pragma once

#include "LaserSensor.h"
#include "Servo.h"
#include <vector>

class RangingScanner {
public:
  RangingScanner(Servo &servo, LaserSensor &sensor, size_t numSteps,
                 float nSigma, uint16_t minDiff);

  void search(size_t minLockPoints, size_t maxBreakPoints,
              mbed::Callback<void(float)> cb);

private:
  static constexpr int kStepDelay = 100; // 0.1s
  static constexpr int kNumCalibrations = 5;

  Servo &servo_;
  LaserSensor &sensor_;
  std::vector<uint16_t> baseline_;
};
