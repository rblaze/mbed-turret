#pragma once

#include "LaserSensor.h"
#include <FastServo.h>
#include <vector>

class RangingScanner {
public:
  using TargetEvent = Event<void(float)>;

  RangingScanner(FastServo &servo, LaserSensor &sensor, size_t numSteps,
                 float nSigma, uint16_t minDiff);

  void search(size_t minLockPoints, size_t maxBreakPoints, TargetEvent &ev);

private:
  static constexpr int kStepDelay = 100; // 0.1s
  static constexpr int kNumCalibrations = 5;

  void scan(bool scanForward, size_t minLockPoints, size_t maxBreakPoints,
            TargetEvent &ev);

  FastServo &servo_;
  LaserSensor &sensor_;
  std::vector<uint16_t> baseline_;
};
