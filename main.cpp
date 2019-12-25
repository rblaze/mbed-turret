#include "Audio.h"
#include "Ranging.h"
#include "mbed.h"

constexpr float servoRangeMin{0.0003};
constexpr size_t servoAngleMin{30};

constexpr float servoRangeMax{0.0009};
constexpr size_t servoAngleMax{90};

int main() {
  printf("Starting\n");

  Audio::init();
  {
    AnalogIn pot{MBED_CONF_APP_SENSOR_ANGLE_POT};
    float pct{pot.read()};

    // Force end values.
    if (pct > 0.99) {
      pct = 1;
    } else if (pct < 0.01) {
      pct = 0;
    }

    float range = servoRangeMin + (servoRangeMax - servoRangeMin) * pct;
    float angle = servoAngleMin + (servoAngleMax - servoAngleMin) * pct;

    printf("calibrate %f %f %f\n", pct, range, angle);
    Ranging::init(range, angle);
  }

  Audio::play(Audio::Clip::TARGET_ACQUIRED);

  for (;;) {
    Audio::tick();
    Ranging::tick();
    ThisThread::sleep_for(10);
  }
}
