#include "LaserSensor.h"
#include "Servo.h"
#include "RangingScanner.h"
#include "mbed.h"

PinName SENSOR_SDA{I2C_SDA};
PinName SENSOR_SCL{I2C_SCL};
PinName SENSOR_SERVO{D6};

constexpr float sensorServoRange{0.0009};
constexpr float sensorServoAngle{90};

int main() {
  I2C i2c{SENSOR_SDA, SENSOR_SCL};
  LaserSensor sensor{i2c, LaserSensor::ADDR_DEFAULT};
  Servo sensorServo{SENSOR_SERVO};

  while (true) {
    RangingScanner scanner(sensorServo, sensor);
  }
}
