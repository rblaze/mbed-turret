#include "Audio.h"
#include "mbed.h"

int main() {
  printf("Starting\n");

  Audio::init();
  Audio::play(Audio::Clip::TARGET_ACQUIRED);
  for (;;) {
    Audio::tick();
    ThisThread::sleep_for(10);
  }
}
