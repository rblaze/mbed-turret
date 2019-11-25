#pragma once
#include <FastPWM.h>
#include <Span.h>
#include <experimental/optional>
#include <unordered_map>

class AudioPlayer {
public:
  AudioPlayer(PinName pin);

  enum class Clip {
    ARE_YOU_STILL_THERE,
    DEPLOYING,
    HELLO_FRIEND,
    I_SEE_YOU,
    SFX_ACTIVE,
    SFX_DEPLOY,
    SFX_RETRACT,
    TARGET_LOST,
  };

  Event<void(Clip)> &playEvent() { return playEvent_; }

private:
  // Clips are 8 bit, 16 KHz.
  using Data = Span<const uint8_t>;
  static constexpr uint32_t kFreq = 16000;
  static const std::unordered_map<Clip, Data> clips_;

  void playClip(Clip);
  void clipFinished();
  void nextSample();

  EventQueue *sharedQueue_;
  Event<void(Clip)> playEvent_;
  FastPWM pwm_;
  Ticker ticker_;
  std::experimental::optional<Data> clip_;
  int position_{0};
};
