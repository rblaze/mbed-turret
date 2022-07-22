#include "Ranging.h"

#include <LaserSensor.h>
#include <mbed.h>

#include "Audio.h"
#include "Calibration.h"
#include "Servo.h"
#include "Targeting.h"

namespace {
// Ranging settings
constexpr int kNumCalibrations{3};
constexpr int kNumSigma{2};
constexpr float kMinDiff{100};

// Hardware
DigitalOut led{MBED_CONF_APP_CONTACT_LED, 0};
Servo servo{MBED_CONF_APP_SENSOR_SERVO_PWM};
I2C i2c{MBED_CONF_APP_SENSOR_SDA, MBED_CONF_APP_SENSOR_SCL};
uint16_t sensorId;

// FSM
enum class Direction {
  CALIBRATION,
  DOWNSCAN,
  UPSCAN,
} direction{Direction::CALIBRATION};

// Timings
// Force milliseconds here because some APIs expect this.
using duration = std::chrono::milliseconds;
constexpr duration kSensorTimingBudget{100ms};
constexpr duration kSensorTimingInterval{200ms};
constexpr duration kServoResetWaitTime{500ms};
constexpr duration kServoStepWaitTime{100ms};

// Ranging data
constexpr size_t kMaxSteps{180};
uint16_t baseline[kMaxSteps];

size_t numSteps;  // Actual number of steps in scanning.
size_t currentStep;
float rotationStep;  // Angle increment on each step.

CalibrationData cal;

void beginScan();
void readSensor();
void rereadSensor();

auto queue{mbed_event_queue()};
auto beginScanEvent{queue->make_user_allocated_event(beginScan)};
auto readSensorEvent{queue->make_user_allocated_event(readSensor)};
auto rereadSensorEvent{queue->make_user_allocated_event(rereadSensor)};

void setServo(size_t pos) {
  printf("setting position %u\n", pos);
  servo.write(pos * rotationStep);
  currentStep = pos;
}

void processCalibration(uint16_t distance) {
  cal.add_sample(distance);

  if (cal.count() < kNumCalibrations) {
    // Wait for another measurment.
    rereadSensorEvent.delay(kSensorTimingInterval.count());
    rereadSensorEvent.call();
  } else {
    // Done with this sensor position.
    auto result = cal.finalize();
    auto threshold = std::max(result.stddev * kNumSigma, kMinDiff);

    baseline[currentStep] =
        std::lround(result.mean > threshold ? result.mean - threshold : 0);
    printf("value: %hu\n", baseline[currentStep]);

    if (currentStep == numSteps - 1) {
      // Re-Init PRNG
      srandom(random() ^ Kernel::Clock::now().time_since_epoch().count());
      Audio::play(Audio::Clip::BEGIN_SCAN);

      // Done calibrating, start scanning.
      direction = Direction::DOWNSCAN;
      rereadSensorEvent.delay(kSensorTimingInterval.count());
      rereadSensorEvent.call();
    } else {
      // Next calibration step
      VL53L1X_StopRanging(sensorId);
      setServo(currentStep + 1);
      beginScanEvent.delay(kServoStepWaitTime.count());
      beginScanEvent.call();
    }
  }
}

void processScan(uint16_t distance) {
  auto hasContact{distance < baseline[currentStep]};
  led.write(hasContact);
  Targeting::report(currentStep, hasContact);

  ssize_t step = 0;

  if (direction == Direction::DOWNSCAN) {
    if (currentStep == 0) {
      direction = Direction::UPSCAN;
    } else {
      step = -1;
    }
  } else {
    if (currentStep == numSteps - 1) {
      direction = Direction::DOWNSCAN;
    } else {
      step = 1;
    }
  }

  if (step != 0) {
    VL53L1X_StopRanging(sensorId);
    setServo(currentStep + step);
    beginScanEvent.call();
  } else {
    Targeting::resetState();
    rereadSensorEvent.delay(kSensorTimingInterval.count());
    rereadSensorEvent.call();
  }
}

// Sensor positioned, start scanning
void beginScan() {
  VL53L1X_StartRanging(sensorId);
  cal = CalibrationData();

  // Check sensor soon.
  readSensorEvent.delay(kSensorTimingBudget.count());
  readSensorEvent.call();
}

// Check if sensor data is ready.
void readSensor() {
  uint8_t ready{0};

  VL53L1X_CheckForDataReady(sensorId, &ready);
  if (!ready) {
    printf("sensor not ready\n");
    // Try again real soon.
    // XXX check how often this happens, maybe adjust initial delay.
    rereadSensorEvent.delay(10 /*ms*/);
    rereadSensorEvent.call();
    return;
  }

  VL53L1X_Result_t result;
  VL53L1X_GetResult(sensorId, &result);
  VL53L1X_ClearInterrupt(sensorId);

  printf("sample: %hu\n", result.Distance);

  if (direction == Direction::CALIBRATION) {
    processCalibration(result.Distance);
  } else {
    processScan(result.Distance);
  }
}

void rereadSensor() {
  // This is a workaround for recursive event scheduling.
  // Call next exent immediately.
  readSensorEvent.delay(0);
  readSensorEvent.call();
}

}  // namespace

void Ranging::init(float range, float angle) {
  numSteps = angle * 2;
  MBED_ASSERT(numSteps <= kMaxSteps);
  MBED_ASSERT(numSteps > 1);

  rotationStep = 1.0 / (numSteps - 1);

  // Set servo parameters
  servo.calibrate(range, angle);
  // Reset servo position
  setServo(0);

  sensorId = VL53L1_RegisterDevice(&i2c, LaserSensor::ADDR_DEFAULT);

  // Wait for sensor to boot.
  for (uint8_t bootState = 0; bootState == 0; /**/) {
    VL53L1X_BootState(sensorId, &bootState);
    if (bootState == 0) {
      // Wait for 1ms. Expected boot time is 1.2ms.
      ThisThread::sleep_for(1ms);
    }
  }

  // Init device.
  VL53L1X_SensorInit(sensorId);
  // Set long distance mode.
  VL53L1X_SetDistanceMode(sensorId, 2);
  // Set timings.
  VL53L1X_SetTimingBudgetInMs(sensorId, kSensorTimingBudget.count());
  VL53L1X_SetInterMeasurementInMs(sensorId, kSensorTimingInterval.count());

  // Wait 0.5 second for servo to get to position.
  // XXX duration not yet implemented for UserAllocatedEvent.
  beginScanEvent.delay(kServoResetWaitTime.count());
  beginScanEvent.call();
}
