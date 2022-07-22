#include "Targeting.h"
#include "Audio.h"
#include "Servo.h"

#include <mbed.h>

namespace {

DigitalOut laser{MBED_CONF_APP_LASER_POWER, 0};
Servo servo{MBED_CONF_APP_LASER_SERVO_PWM};

constexpr int kMinLockPoints{8};
constexpr int kMaxBreakPoints{4};

// Force milliseconds here because some APIs expect this.
using duration = std::chrono::milliseconds;
constexpr duration kLaserOffDelay{5s};
constexpr duration kTargetAcquiredInterval{30s};
constexpr duration kTargetLostInterval{60s};

float rotationStep;

bool hasLock;
size_t contactStart;
size_t contactEnd;
int contactGap;

Kernel::Clock::time_point lastSeenAt{Kernel::Clock::time_point::min()};

void laserOff();
void targetLost();

auto queue{mbed_event_queue()};
auto laserOffEvent{queue->make_user_allocated_event(laserOff)};
auto targetLostEvent{queue->make_user_allocated_event(targetLost)};

void laserOff() {
  laser = 0;
  lastSeenAt = Kernel::Clock::now();
  Audio::play(Audio::Clip::CONTACT_LOST);
  targetLostEvent.call();
}

void targetLost() {
  Audio::play(Audio::Clip::TARGET_LOST);
}

}  // namespace

void Targeting::init(float range, float angle) {
  // Set servo parameters
  servo.calibrate(range, angle);
  resetState();

  size_t numSteps = angle * 2;
  MBED_ASSERT(numSteps > 1);
  rotationStep = 1.0 / (numSteps - 1);
  laserOffEvent.delay(kLaserOffDelay.count());
  targetLostEvent.delay(kTargetLostInterval.count());
}

void Targeting::resetState() {
  hasLock = false;
  contactStart = 0;
  contactEnd = 0;
  contactGap = 0;
}

void Targeting::report(size_t currentStep, bool hasContact) {
  if (hasContact) {
    if (!hasLock) {
      // This is initial contact.
      hasLock = true;
      contactStart = currentStep;
    }

    contactEnd = currentStep;
    contactGap = 0;

    auto leftSide = std::min(contactStart, contactEnd);
    auto rightSide = std::max(contactStart, contactEnd);
    auto targetSize = rightSide - leftSide;

    if (targetSize + 1 >= kMinLockPoints) {
      // Target found.
      auto targetCenter = leftSide + targetSize / 2;
      servo.write(targetCenter * rotationStep);

      // SFX
      if (laser.read() == 0) {
        if (Kernel::Clock::now() - lastSeenAt > kTargetAcquiredInterval) {
          Audio::play(Audio::Clip::TARGET_ACQUIRED);
        } else {
          Audio::play(Audio::Clip::CONTACT_RESTORED);
        }
      }

      // Turn on laser.
      laser = 1;

      // [Re]Schedule laser off.
      targetLostEvent.cancel();
      laserOffEvent.cancel();
      laserOffEvent.call();
    }
  } else if (hasLock) {
    // Target disappeared.
    contactGap += 1;

    if (contactGap > kMaxBreakPoints) {
      // Target lost.
      resetState();
    }
  }
}
