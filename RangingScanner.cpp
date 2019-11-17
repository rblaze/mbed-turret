#include "RangingScanner.h"
#include "Calibration.h"

namespace {

class TargetTracker {
public:
  TargetTracker(size_t minTargetWidth, size_t maxContactGap)
      : minTargetWidth_{minTargetWidth}, maxContactGap_{maxContactGap} {}

  std::experimental::optional<size_t> update(size_t position, bool hasContact) {
    std::experimental::optional<size_t> targetCenter{
        std::experimental::nullopt};

    if (hasContact) {
      if (!hasLock_) {
        // This is initial contact.
        hasLock_ = true;
        firstLock_ = position;
      }

      lastLock_ = position;
      gapInContact_ = 0;

      auto leftSide = std::min(firstLock_, lastLock_);
      auto rightSide = std::max(firstLock_, lastLock_);
      auto targetSize = rightSide - leftSide;

      if (targetSize + 1 >= minTargetWidth_) {
        // Target found.
        targetCenter = leftSide + targetSize / 2;
      }
    } else if (hasLock_) {
      // Target disappeared.
      gapInContact_ += 1;

      if (gapInContact_ > maxContactGap_) {
        // Target lost.
        hasLock_ = false;
        gapInContact_ = 0;
        firstLock_ = 0;
        lastLock_ = 0;
      }
    }

    return targetCenter;
  }

private:
  size_t minTargetWidth_;
  size_t maxContactGap_;
  size_t firstLock_{0};
  size_t lastLock_{0};
  size_t gapInContact_{0};
  bool hasLock_{false};
};

} // namespace

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
  ThisThread::sleep_for(500);

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

void RangingScanner::scan(bool scanForward, size_t minLockPoints,
                          size_t maxBreakPoints,
                          mbed::Callback<void(float)> cb) {
  const int numSteps = baseline_.size();

  auto start = scanForward ? 0 : numSteps - 1;
  auto stop = scanForward ? numSteps : -1;
  auto step = scanForward ? 1 : -1;

  const float rotationStep = 1.0 / (float)(numSteps - 1);
  TargetTracker tracker{minLockPoints, maxBreakPoints};

  for (int i = start; i != stop; i += step) {
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

      if (auto center = tracker.update(i, distance < baseline_[i])) {
        cb(*center * rotationStep);
      }
    } else {
      printf("%d: scan failed\n", i);
    }
  }
}

void RangingScanner::search(size_t minLockPoints, size_t maxBreakPoints,
                            mbed::Callback<void(float)> cb) {
  scan(false, minLockPoints, maxBreakPoints, cb);
  scan(true, minLockPoints, maxBreakPoints, cb);
}
