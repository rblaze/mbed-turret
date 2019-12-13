#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(PinName pin)
    : sharedQueue_{mbed_event_queue()},
      playEvent_{sharedQueue_->event(this, &AudioPlayer::playClip)}, pwm_{pin} {
  // Audio samples are at 16KHz.
  // Set PWM to 4x this frequency.
  pwm_.period(1.0 / (kFreq * 4.0));

  scanDir(Clip::STARTUP, "startup");
  scanDir(Clip::BEGIN_SCAN, "begin_scan");
  scanDir(Clip::TARGET_ACQUIRED, "target_acquired");
  scanDir(Clip::CONTACT_LOST, "contact_lost");
  scanDir(Clip::CONTACT_RESTORED, "contact_restored");
  scanDir(Clip::TARGET_LOST, "target_lost");
  scanDir(Clip::PICKED_UP, "picked_up");
}

void AudioPlayer::scanDir(Clip clip, const std::string &path) {
  Dir dir(FileSystem::get_default_instance(), path.c_str());
  struct dirent entry;

  printf("clip %d\n", (int)clip);
  while (dir.read(&entry) == 1) {
    if (entry.d_type != DT_REG) {
      continue;
    }

    printf("file %s\n", entry.d_name);
    clips_[clip].push_back(path + "/" + entry.d_name);
  }
}

void AudioPlayer::playClip(Clip clip) {
  if (file_ == nullptr) {
    size_t numClips = clips_[clip].size();

    if (numClips > 0) {
      size_t index = time(nullptr) % numClips;
      auto path = clips_[clip][index];

      file_ = std::make_unique<File>(FileSystem::get_default_instance(), path.c_str(), O_RDONLY);
      if (file_) {
        printf("playing %s\n", path.c_str());
        ssize_t read = file_->read(buf_.data(), buf_.size());
        if (read > 0) {
          position_ = 0;
          lastSample_ = buf_.size();
          ticker_.attach_us(callback(this, &AudioPlayer::nextSample),
                            1000000 / kFreq);
        } else {
          sharedQueue_->call(this, &AudioPlayer::endClip);
        }
      }
    }
  }
}

void AudioPlayer::endClip() {
  pwm_.write(0);
  file_.reset();
  printf("done %d\n", position_);
}

void AudioPlayer::readNextBuffer() {
  ssize_t readPos = lastSample_ >= buf_.size() ? 0 : lastSample_;
  ssize_t readSize = std::min(kBlockSize, buf_.size() - readPos);
  ssize_t read = file_->read(buf_.data() + readPos, readSize);
  if (read > 0) {
    lastSample_ = readPos + read;
  }
//  printf("read %d %d %d %d\n", readPos, readSize, position_, lastSample_);
}

void AudioPlayer::nextSample() {
  uint16_t sample = buf_[position_];
  sample <<= 8;
  sample += buf_[position_ + 1];
  // Shift from signed to unsigned 16-bit.
  sample += 0x8000;
  pwm_.write((double)(sample) / 65536.0);
  position_ += sizeof(int16_t);

  if (position_ == lastSample_) {
    ticker_.detach();
    sharedQueue_->call(this, &AudioPlayer::endClip);
  } else {
    if (position_ % kBlockSize == 0) {
      sharedQueue_->call(this, &AudioPlayer::readNextBuffer);
    }

    if (position_ >= buf_.size()) {
      position_ = 0;
    }
  }
}
