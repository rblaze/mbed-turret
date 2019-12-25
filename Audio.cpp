#include "Audio.h"
#include <LittleFileSystem.h>
#include <SPIFBlockDevice.h>
#include "FastPWM.h"
#include "mbed.h"

namespace {

struct ClipList {
  size_t count;
  const char **files;
};

enum class State {
  IDLE,
  PLAYING,
  PLAYING_READING,
  DRAINING,
  STOPPED,
};

// Clips are unsigned 8 bit, 16 KHz.
constexpr uint32_t kFreq = 16000;
constexpr size_t kBlockSize = 1024;

const char *startup[] = {
    "Turret_sfx_deploy.raw",
    "Turret_sfx_active.raw",
};
const char *begin_scan[] = {
    "Turret_searching.raw",
    "Turret_activated.raw",
    "Turret_sentry_mode_activated.raw",
    "Turret_would_you_come_over_here.raw",
    "Turret_deploying.raw",
};
const char *target_acquired[] = {
    "Turret_hello_friend.raw",    "Turret_who_is_there.raw",
    "Turret_target_acquired.raw", "Turret_gotcha.raw",
    "Turret_I_see_you.raw",       "Turret_there_you_are.raw",
};
const char *contact_lost[] = {"Turret_sfx_retract.raw"};
const char *contact_restored[] = {
    "Turret_sfx_ping.raw",
    "Turret_hi.raw",
    "Turret_sfx_alert.raw",
};
const char *target_lost[] = {
    "Turret_is_anyone_there.raw",
    "Turret_hellooooo.raw",
    "Turret_are_you_still_there.raw",
    "Turret_target_lost.raw",
};
const char *picked_up[] = {
    "Turret_malfunctioning.raw",
    "Turret_put_me_down.raw",
    "Turret_who_are_you.raw",
    "Turret_please_put_me_down.raw",
};

constexpr ClipList clips[] = {
    {sizeof(startup) / sizeof(const char *), startup},
    {sizeof(begin_scan) / sizeof(const char *), begin_scan},
    {sizeof(target_acquired) / sizeof(const char *), target_acquired},
    {sizeof(contact_lost) / sizeof(const char *), contact_lost},
    {sizeof(contact_restored) / sizeof(const char *), contact_restored},
    {sizeof(target_lost) / sizeof(const char *), target_lost},
    {sizeof(picked_up) / sizeof(const char *), picked_up}};

FastPWM pwm{MBED_CONF_APP_AUDIO_PWM};
SPIFBlockDevice spif{
    MBED_CONF_SPIF_DRIVER_SPI_MOSI, MBED_CONF_SPIF_DRIVER_SPI_MISO,
    MBED_CONF_SPIF_DRIVER_SPI_CLK, MBED_CONF_SPIF_DRIVER_SPI_CS};
LittleFileSystem fs{"fs", &spif};

Ticker ticker;
File file;

uint8_t buf[kBlockSize * 2];
size_t position;
size_t lastSample;
State state{State::IDLE};

// Play single sample from buffer
void playSample() {
  // precondition - there is sample to play
  double sample = buf[position];
  pwm.write(sample / 256.0);
  position += 1;

  if (position == lastSample) {
    ticker.detach();
    pwm.write(0);
    state = State::STOPPED;
  } else {
    if (position % kBlockSize == 0 && state == State::PLAYING) {
      state = State::PLAYING_READING;
    }

    if (position >= sizeof(buf)) {
      position = 0;
    }
  }
}

}  // namespace

void Audio::init() {
  pwm.period_us(4);
}

void Audio::play(Audio::Clip clip) {
  if (state == State::IDLE) {
    auto list = clips[(int)clip];
    size_t index = random() % list.count;
    auto path = list.files[index];

    int status = file.open(&fs, path, O_RDONLY);
    if (status == 0) {
      ssize_t read = file.read(buf, sizeof(buf));
      if (read > 0) {
        position = 0;
        lastSample = read;
        state = State::PLAYING;
        ticker.attach_us(&playSample, 1000000 / kFreq);
      } else {
        file.close();
      }
    }
  }
}

void Audio::tick() {
  switch (state) {
    case State::IDLE:
    case State::PLAYING:
    case State::DRAINING:
      break;
    case State::PLAYING_READING: {
      ssize_t readPos = lastSample >= sizeof(buf) ? 0 : lastSample;
      ssize_t rd = file.read(buf + readPos, kBlockSize);

      state = State::PLAYING;

      if (rd > 0) {
        lastSample = readPos + rd;
      }

      if (rd != kBlockSize) {
        state = State::DRAINING;
      }

      break;
    }
    case State::STOPPED:
      printf("done %d %d\n", position, lastSample);
      file.close();
      state = State::IDLE;
      break;
  }
}
