#include "AudioPlayer.h"
//#include "FastServo.h"
//#include "LaserSensor.h"
//#include "RangingScanner.h"
//#include "TargetPainter.h"
#include "mbed.h"

PinName SENSOR_SDA{I2C_SDA};
PinName SENSOR_SCL{I2C_SCL};
PinName SENSOR_SERVO{D6};
PinName LASER_SERVO{D5};
PinName LASER_POWER{D4};
PinName AUDIO_OUT{MBED_CONF_APP_AUDIO_PWM};
PinName SERVO_RANGE_POT{A0};

constexpr float servoRangeMin{0.0003};
constexpr size_t servoAngleMin{30};

constexpr float servoRangeMax{0.0009};
constexpr size_t servoAngleMax{90};

#if 0
size_t calibrateServos(FastServo &sensor, FastServo &laser) {
  AnalogIn pot{SERVO_RANGE_POT};
  float pct{pot.read()};

  // Force end values.
  if (pct > 0.99) {
    pct = 1;
  } else if (pct < 0.01) {
    pct = 0;
  }

  float range = servoRangeMin + (servoRangeMax - servoRangeMin) * pct;
  float angle = servoAngleMin + (servoAngleMax - servoAngleMin) * pct;

  printf("calibration %f -> %f %f\n", pct, range, angle);

  sensor.calibrate(range, angle);
  laser.calibrate(range, angle);

  return angle;
}
#endif

AudioPlayer audio{AUDIO_OUT};

int main() {
#if 0
  I2C i2c{SENSOR_SDA, SENSOR_SCL};
  LaserSensor sensor{i2c, LaserSensor::ADDR_DEFAULT};
  FastServo sensorServo{SENSOR_SERVO};
  FastServo laserServo{LASER_SERVO};
  DigitalOut laser{LASER_POWER, 0};
#endif

#if 0
  TargetPainter painter{laserServo, laser, audio.playEvent()};
  auto numSteps{calibrateServos(sensorServo, laserServo) * 2};
#endif
  printf("Starting\n");
  audio.playEvent().post(AudioPlayer::Clip::TARGET_LOST);
  mbed_event_queue()->dispatch_forever();
#if 0
  RangingScanner scanner(sensorServo, sensor, numSteps, 2, 100);

  audio.playEvent().post(AudioPlayer::Clip::SFX_DEPLOY);
  for (;;) {
    scanner.search(8, 4, painter.targetEvent());
  }
#endif
}
