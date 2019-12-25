#include "Ranging.h"
#include "Audio.h"
#include "Calibration.h"
#include "FastServo.h"
#include "LaserSensor.h"
#include "Targeting.h"
#include "mbed.h"

namespace {
// Ranging settings
constexpr int kNumCalibrations{3};
constexpr int kNumSigma{2};
constexpr float kMinDiff{100};

// Hardware
FastServo servo{MBED_CONF_APP_SENSOR_SERVO};
I2C i2c{MBED_CONF_APP_SENSOR_SDA, MBED_CONF_APP_SENSOR_SCL};
uint16_t sensorId;

// FSM
enum class State {
  CALIBRATION_MOVE,
  CALIBRATION_MEASURE,
  DOWNSCAN_MOVE,
  DOWNSCAN_MEASURE,
  UPSCAN_MOVE,
  UPSCAN_MEASURE,
} state;

// Timings
constexpr uint64_t kServoResetWaitMs{500};
constexpr uint64_t kServoStepWaitMs{100};

// Ranging data
constexpr size_t kMaxSteps{180};
uint16_t baseline[kMaxSteps];

size_t numSteps;  // Actual number of steps in scanning.
size_t currentStep;
float rotationStep;  // Angle increment on each step.

// End time for *_WAIT
uint64_t wait_until{0};

CalibrationData cal;

void setServo(size_t pos) {
  printf("position %u\n", pos);
  servo.write(pos * rotationStep);
  currentStep = pos;
}

bool waitMove(State nextState) {
  bool expired = Kernel::get_ms_count() < wait_until;

  if (expired) {
    state = nextState;
    VL53L1X_StartRanging(sensorId);
  }

  return expired;
}

void calibration_step() {
  uint8_t ready{0};

  VL53L1X_CheckForDataReady(sensorId, &ready);
  if (!ready) {
    // Try again
    return;
  }

  VL53L1X_Result_t result;
  VL53L1X_GetResult(sensorId, &result);
  VL53L1X_ClearInterrupt(sensorId);

  // printf("sample: %hu\n", result.Distance);
  cal.add_sample(result.Distance);

  if (cal.count() == kNumCalibrations) {
    auto result = cal.finalize();
    auto threshold = std::max(result.stddev * kNumSigma, kMinDiff);

    baseline[currentStep] =
        std::lround(result.mean > threshold ? result.mean - threshold : 0);
    // printf("value: %hu\n", baseline[currentStep]);

    if (currentStep == numSteps - 1) {
      // Done calibrating, start scanning.
      state = State::DOWNSCAN_MEASURE;
      Audio::play(Audio::Clip::BEGIN_SCAN);
    } else {
      VL53L1X_StopRanging(sensorId);
      setServo(currentStep + 1);
      wait_until = Kernel::get_ms_count() + kServoStepWaitMs;
      state = State::CALIBRATION_MOVE;
    }
  }
}

void scan_step(int step, size_t border, State nextState, State switchState) {
  uint8_t ready{0};

  VL53L1X_CheckForDataReady(sensorId, &ready);
  if (!ready) {
    // Try again
    return;
  }

  VL53L1X_Result_t result;
  VL53L1X_GetResult(sensorId, &result);
  VL53L1X_ClearInterrupt(sensorId);

  // printf("sample: %hu\n", result.Distance);

  Targeting::report(currentStep,
                    result.Distance < baseline[currentStep]);

  if (currentStep == border) {
    // Switch direction
    Targeting::resetState();
    state = switchState;
  } else {
    VL53L1X_StopRanging(sensorId);
    setServo(currentStep + step);
    wait_until = Kernel::get_ms_count() + kServoStepWaitMs;
    state = nextState;
  }
}

}  // namespace

void Ranging::init(float range, float angle) {
  numSteps = angle * 2;
  MBED_ASSERT(numSteps <= kMaxSteps);
  MBED_ASSERT(numSteps > 1);

  rotationStep = 1.0 / (numSteps - 1);

  // Set servo parameters
  servo.calibrate(range, angle);
  setServo(0);
  // Wait 0.5 second for servo to get to position
  wait_until = Kernel::get_ms_count() + kServoResetWaitMs;
  state = State::CALIBRATION_MOVE;

  sensorId = VL53L1_RegisterDevice(&i2c, LaserSensor::ADDR_DEFAULT);

  // Wait for sensor to boot.
  for (uint8_t bootState = 0; bootState == 0; /**/) {
    VL53L1X_BootState(sensorId, &bootState);
    if (bootState == 0) {
      // Wait for 1ms. Expected boot time is 1.2ms.
      ThisThread::sleep_for(1);
    }
  }

  // Init device.
  VL53L1X_SensorInit(sensorId);
  // Set long distance mode.
  VL53L1X_SetDistanceMode(sensorId, 2);
  // Set timings.
  VL53L1X_SetTimingBudgetInMs(sensorId, 100);
  VL53L1X_SetInterMeasurementInMs(sensorId, 200);

  // SFX
  Audio::play(Audio::Clip::STARTUP);
}

void Ranging::tick() {
  switch (state) {
    case State::CALIBRATION_MOVE:
      if (waitMove(State::CALIBRATION_MEASURE)) {
        // Reset calibration data collector.
        cal = CalibrationData();
      }
      break;
    case State::CALIBRATION_MEASURE:
      calibration_step();
      break;
    case State::DOWNSCAN_MOVE:
      waitMove(State::DOWNSCAN_MEASURE);
      break;
    case State::DOWNSCAN_MEASURE:
      scan_step(-1, 0, State::DOWNSCAN_MOVE, State::UPSCAN_MEASURE);
      break;
    case State::UPSCAN_MOVE:
      waitMove(State::UPSCAN_MEASURE);
      break;
    case State::UPSCAN_MEASURE:
      scan_step(1, numSteps - 1, State::UPSCAN_MOVE, State::DOWNSCAN_MEASURE);
      break;
  }
}
