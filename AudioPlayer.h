#pragma once
#include "mbed.h"
#include <FastPWM.h>
#include <Span.h>
#include <memory>
#include <unordered_map>
#include <vector>

class AudioPlayer {
public:
  AudioPlayer(PinName pin);

  enum class Clip {
    STARTUP,
    BEGIN_SCAN,
    TARGET_ACQUIRED,
    CONTACT_LOST,
    CONTACT_RESTORED,
    TARGET_LOST,
    PICKED_UP,
  };

  Event<void(Clip)> &playEvent() { return playEvent_; }

private:
  // Clips are signed 16 bit, 44.1 KHz.
  static constexpr uint32_t kFreq = 44100;
  static constexpr size_t kBlockSize = 1024;

  void scanDir(Clip, const std::string &);
  void playClip(Clip);
  void nextSample();
  void readNextBuffer();
  void endClip();

  std::unordered_map<Clip, std::vector<string>> clips_;
  EventQueue *sharedQueue_;
  Event<void(Clip)> playEvent_;
  FastPWM pwm_;
  Ticker ticker_;
  std::array<uint8_t, kBlockSize * 5> buf_;
  std::unique_ptr<File> file_;
  size_t lastSample_{0};
  size_t position_{0};
};
