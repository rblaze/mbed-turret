#include "AudioPlayer.h"
#include "PCM_I_see_you.h"
#include "PCM_are_you_still_there.h"
#include "PCM_deploying.h"
#include "PCM_hello_friend.h"
#include "PCM_sfx_active.h"
#include "PCM_sfx_deploy.h"
#include "PCM_sfx_retract.h"
#include "PCM_target_lost.h"

const std::unordered_map<AudioPlayer::Clip, AudioPlayer::Data>
    AudioPlayer::clips_{
        {Clip::ARE_YOU_STILL_THERE, Data(Turret_are_you_still_there_raw,
                                         Turret_are_you_still_there_raw_len)},
        {Clip::DEPLOYING, Data(Turret_deploying_raw, Turret_deploying_raw_len)},
        {Clip::HELLO_FRIEND,
         Data(Turret_hello_friend_raw, Turret_hello_friend_raw_len)},
        {Clip::I_SEE_YOU, Data(Turret_I_see_you_raw, Turret_I_see_you_raw_len)},
        {Clip::SFX_ACTIVE, Data(Turret_active_raw, Turret_active_raw_len)},
        {Clip::SFX_DEPLOY, Data(Turret_deploy_raw, Turret_deploy_raw_len)},
        {Clip::SFX_RETRACT, Data(Turret_retract_raw, Turret_retract_raw_len)},
        {Clip::TARGET_LOST,
         Data(Turret_target_lost_raw, Turret_target_lost_raw_len)},
    };

AudioPlayer::AudioPlayer(PinName pin)
    : sharedQueue_{mbed_event_queue()},
      playEvent_{sharedQueue_->event(this, &AudioPlayer::playClip)}, pwm_{pin} {
  // Audio samples are at 16KHz.
  // Set PWM to 4x this frequency.
  pwm_.period(1.0 / (kFreq * 4.0));
}

// clip_ only changed from event queue, no synchronization necessary.
// Until it is single-threaded, that is.

void AudioPlayer::playClip(Clip clip) {
  if (!clip_) {
    auto p = clips_.find(clip);

    if (p != clips_.end()) {
      clip_ = p->second;
      position_ = 0;
      ticker_.attach_us(callback(this, &AudioPlayer::nextSample),
                        1000000 / kFreq);
    }
  }
}

void AudioPlayer::clipFinished() { clip_ = std::experimental::nullopt; }

void AudioPlayer::nextSample() {
  MBED_ASSERT(clip_);

  if (position_ >= clip_->size()) {
    ticker_.detach();
    sharedQueue_->call(this, &AudioPlayer::clipFinished);
  } else {
    pwm_.write((double)(*clip_)[position_] / 255.0);
    position_ += 1;
  }
}
