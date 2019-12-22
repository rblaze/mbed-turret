#include "Audio.h"
#include "mbed.h"

Ticker ticker;

void tick() {
  /* no-op */
}

int main() {
  printf("Starting\n");

  // Break sleep every 10ms.
  ticker.attach_us(&tick, 10000);

  Audio::init();
  Audio::play(Audio::Clip::STARTUP);
  for (;;) {
    Audio::tick();
    sleep();
  }
}
