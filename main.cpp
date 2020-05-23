#include <mbed.h>

#include "Audio.h"
#include "Ranging.h"
#include "Targeting.h"

void init() {
  constexpr float servoRangeMin{0.0003};
  constexpr size_t servoAngleMin{30};

  constexpr float servoRangeMax{0.0009};
  constexpr size_t servoAngleMax{90};

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

  // Init PRGN
  srandom(pot.read_u16());

  // Init modules.
  Audio::init();
  Ranging::init(range, angle);
  Targeting::init(range, angle);
}

int main() {
  printf("Starting\n");
  init();

  // SFX
  Audio::play(Audio::Clip::STARTUP);

  auto queue = mbed_event_queue();
  queue->dispatch_forever();

  return 0;
}
