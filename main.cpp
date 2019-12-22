#include "AudioPlayer.h"
#include "mbed.h"

int main() {
  printf("Starting\n");

  Audio::init();
  Audio::play(Audio::Clip::STARTUP);
  for (;;) {
    Audio::tick();
    sleep();
  }
}
