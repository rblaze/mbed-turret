#include "LaserSensor.h"
#include "RangingScanner.h"
#include "Servo.h"
#include "mbed.h"

PinName SENSOR_SDA{I2C_SDA};
PinName SENSOR_SCL{I2C_SCL};
PinName SENSOR_SERVO{D6};
PinName LASER_SERVO{D5};
PinName LASER_POWER{D4};

constexpr float sensorServoRange{0.0009};
constexpr float sensorServoAngle{90};

constexpr float laserServoRange{0.0009};
constexpr float laserServoAngle{90};

Servo laserServo{LASER_SERVO};
DigitalOut laser{LASER_POWER, 0};
Timeout laserOff;

void turnOffLaser() { laser.write(0); }

void pointLaser(float pos) {
  printf("*** LOCK %f\n", pos);
  laserServo.write(pos);
  laser.write(1);
  laserOff.detach();
  laserOff.attach_us(turnOffLaser, 5000000);
}

int main() {
  I2C i2c{SENSOR_SDA, SENSOR_SCL};
  LaserSensor sensor{i2c, LaserSensor::ADDR_DEFAULT};
  Servo sensorServo{SENSOR_SERVO};

//  sensorServo.calibrate(sensorServoRange, sensorServoAngle);
//  laserServo.calibrate(laserServoRange, laserServoAngle);

  RangingScanner scanner(sensorServo, sensor, 90, 2, 100);

  for (;;) {
    scanner.search(8, 4, pointLaser);
  }
}
