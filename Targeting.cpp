#include "Targeting.h"
#include "Audio.h"
#include "FastServo.h"
#include "mbed.h"

namespace {

DigitalOut laser{MBED_CONF_APP_LASER_POWER, 0};
FastServo servo{MBED_CONF_APP_LASER_SERVO};

constexpr int kMinLockPoints{8};
constexpr int kMaxBreakPoints{4};
constexpr int kLaserOffDelayMs{5000};
constexpr uint64_t kTargetAcquiredInterval{30000};
constexpr uint64_t kTargetLostInterval{60000};

float rotationStep;

bool hasLock;
size_t contactStart;
size_t contactEnd;
int contactGap;

uint64_t lastSeenAtMs{0};
uint64_t eventTimeMs{0};
enum class DelayedEvent {
  LASER_OFF,
  PLAY_TARGET_LOST,
} event;

}  // namespace

void Targeting::init(float range, float angle) {
  // Set servo parameters
  servo.calibrate(range, angle);
  resetState();

  size_t numSteps = angle * 2;
  MBED_ASSERT(numSteps > 1);
  rotationStep = 1.0 / (numSteps - 1);
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
        if (Kernel::get_ms_count() - lastSeenAtMs > kTargetAcquiredInterval) {
          Audio::play(Audio::Clip::TARGET_ACQUIRED);
        } else {
          Audio::play(Audio::Clip::CONTACT_RESTORED);
        }
      }

      // Turn on laser.
      laser = 1;
      
      // Schedule laser off.
      eventTimeMs = Kernel::get_ms_count() + kLaserOffDelayMs;
      event = DelayedEvent::LASER_OFF;
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

void Targeting::tick() {
  if (eventTimeMs != 0) {
    auto now = Kernel::get_ms_count();
    if (now >= eventTimeMs) {
      switch (event) {
        case DelayedEvent::LASER_OFF:
          lastSeenAtMs = now;
          laser = 0;
          Audio::play(Audio::Clip::CONTACT_LOST);
          eventTimeMs = now + kTargetLostInterval;
          event = DelayedEvent::PLAY_TARGET_LOST;
          break;
        case DelayedEvent::PLAY_TARGET_LOST:
          Audio::play(Audio::Clip::TARGET_LOST);
          eventTimeMs = 0;
          break;
      }
    }
  }
}
