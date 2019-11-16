#pragma once

#include "LaserSensor.h"
#include "Servo.h"
#include "ranging.h"

class RangingScanner {
public:
  RangingScanner(Servo &servo, LaserSensor &sensor)
      : servo_{servo}, sensor_{sensor} {
    baseline_scan();
  }

private:
  void baseline_scan();

  static constexpr size_t kNumSteps = 180;
  static constexpr float kRotationStep = 1.0 / (float)(kNumSteps - 1);
  static constexpr int kStepDelay = 100;    // 0.1s
  static constexpr int kNumCalibrations = 5;

  Servo &servo_;
  LaserSensor &sensor_;
  // std::array<Sample, kNumSteps> baseline_;
};
