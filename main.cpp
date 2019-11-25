#include "AudioPlayer.h"
#include "FastServo.h"
#include "LaserSensor.h"
#include "RangingScanner.h"
#include "TargetPainter.h"
#include "mbed.h"

PinName SENSOR_SDA{I2C_SDA};
PinName SENSOR_SCL{I2C_SCL};
PinName SENSOR_SERVO{D6};
PinName LASER_SERVO{D5};
PinName LASER_POWER{D4};
PinName AUDIO_OUT{PB_11};
// PinName SERVO_RANGE_POT{A0};

constexpr float sensorServoRange{0.0009};
constexpr float sensorServoAngle{90};

constexpr float laserServoRange{0.0009};
constexpr float laserServoAngle{90};

int main() {
  I2C i2c{SENSOR_SDA, SENSOR_SCL};
  LaserSensor sensor{i2c, LaserSensor::ADDR_DEFAULT};
  FastServo sensorServo{SENSOR_SERVO};
  FastServo laserServo{LASER_SERVO};
  DigitalOut laser{LASER_POWER, 0};
  AudioPlayer audio{AUDIO_OUT};
  TargetPainter painter{laserServo, laser, audio};

  //  sensorServo.calibrate(sensorServoRange, sensorServoAngle);
  //  laserServo.calibrate(laserServoRange, laserServoAngle);

  audio.play(AudioPlayer::Clip::DEPLOYING);
  RangingScanner scanner(sensorServo, sensor, 90, 2, 100);

  audio.play(AudioPlayer::Clip::SFX_DEPLOY);
  for (;;) {
    scanner.search(
        8, 4,
        RangingScanner::TargetCallback(&painter, &TargetPainter::targetAt));
  }
}
