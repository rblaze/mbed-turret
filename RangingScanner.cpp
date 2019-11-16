#include "RangingScanner.h"

void RangingScanner::baseline_scan() {
  if (!sensor_.setLongDistanceMode()) {
    printf("set mode failed\n");
  }

  if (!sensor_.setTimings(500, 600)) {
    printf("set timing failed\n");
  }

  if (auto b = sensor_.getBudget()) {
    printf("budget %hd\n", *b);
  }

  if (auto p = sensor_.getPeriod()) {
    printf("period %hd\n", *p);
  }

  servo_.write(0);
  ThisThread::sleep_for(1000);

  for (size_t i = 0; i < kNumSteps; i++) {
    // Move sensor.
    servo_.write(i * kRotationStep);
    ThisThread::sleep_for(kStepDelay);

    CalibrationData calibration;
    for (int n = 0; n < kNumCalibrations; n++) {
      if (sensor_.measureOnce()) {
        auto status = sensor_.getStatus();
        auto distance = sensor_.getDistance();

        calibration.add_sample(distance);
        printf("%d: %d %hd\n", i, (int)status, distance);
      } else {
        printf("%d: scan failed\n", i);
      }
    }
  }
}
