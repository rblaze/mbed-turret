#pragma once

#include <limits>

struct Sample {
  uint16_t mean{0};
  uint16_t stddev{0};
};

class CalibrationData {
public:
  void add_sample(uint16_t value) {
    count_ += 1;
    float v = value;
    auto delta = v - mean_;
    mean_ += delta / count_;
    auto delta2 = v - mean_;
    m2_ += delta * delta2;
  }

  Sample finalize() {
    MBED_ASSERT(count_ > 1);
    auto stddev = std::sqrt(m2_ / (count_ - 1));

    MBED_ASSERT(mean_ >= 0);
    MBED_ASSERT(mean_ <= std::numeric_limits<uint16_t>::max());
    MBED_ASSERT(stddev <= mean_);

    return Sample{(uint16_t)std::lround(mean_), (uint16_t)std::lround(stddev)};
  }

private:
  int count_{0};
  float mean_{0};
  float m2_{0};
};
