#include "RangingScanner.h"
#include "Calibration.h"

RangingScanner::RangingScanner(Servo &servo, LaserSensor &sensor,
                               size_t numSteps, float nSigma, uint16_t minDiff)
    : servo_{servo}, sensor_{sensor}, baseline_(numSteps) {
  MBED_ASSERT(numSteps > 1);
  const float rotationStep = 1.0 / (float)(numSteps - 1);

  if (!sensor_.setLongDistanceMode()) {
    printf("set mode failed\n");
  }

  if (!sensor_.setTimings(100, 200)) {
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

  for (size_t i = 0; i < baseline_.size(); i++) {
    // Move sensor.
    servo_.write(i * rotationStep);
    ThisThread::sleep_for(kStepDelay);

    CalibrationData calibration;
    for (int n = 0; n < kNumCalibrations; n++) {
      if (sensor_.measureOnce()) {
        // auto status = sensor_.getStatus();
        auto distance = sensor_.getDistance();

        calibration.add_sample(distance);
      } else {
        printf("%d: scan failed\n", i);
      }
    }

    auto result = calibration.finalize();
    auto threshold = std::max(result.stddev * nSigma, (float)minDiff);

    baseline_[i] =
        std::lround(result.mean > threshold ? result.mean - threshold : 0);

    printf("%d -> %0.2f %0.2f -> %hd\n", i, result.mean, result.stddev,
           baseline_[i]);
  }
}

void RangingScanner::search(size_t minLockPoints, size_t maxBreakPoints,
                            mbed::Callback<void(float)> cb) {
  const float rotationStep = 1.0 / (float)(baseline_.size() - 1);

  servo_.write(0);
  ThisThread::sleep_for(1000);

  size_t firstLock = 0;
  size_t lastLock = 0;
  size_t gap = 0;
  bool inLock = false;

  for (size_t i = 0; i < baseline_.size(); i++) {
    if (baseline_[i] == 0) {
      // Nothing to scan here.
      continue;
    }

    // Move sensor.
    servo_.write(i * rotationStep);
    ThisThread::sleep_for(kStepDelay);

    if (sensor_.measureOnce()) {
      auto status = sensor_.getStatus();
      auto distance = sensor_.getDistance();

      printf("%d: %d %hd\n", i, (int)status, distance);

      if (distance < baseline_[i]) {
        // Got contact.
        if (inLock) {
          // Keeping contact.
          lastLock = i;
          gap = 0;
        } else {
          // Initial contact.
          inLock = true;
          firstLock = i;
          lastLock = i;
          gap = 0;
        }

        auto diff = lastLock - firstLock;
        if (diff + 1 >= minLockPoints) {
          // Target found.
          cb((lastLock - diff / 2) * rotationStep);
        }
      } else {
        // No contact.
        if (inLock) {
          gap += 1;
          if (gap > maxBreakPoints) {
            // Reset lock data.
            inLock = false;
            gap = 0;
            firstLock = 0;
            lastLock = 0;
          }
        } else {
          // No contact, no cry.
        }
      }
    } else {
      printf("%d: scan failed\n", i);
    }
  }
}
