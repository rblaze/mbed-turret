#include "Audio.h"

#include <LittleFileSystem.h>
#include <SPIFBlockDevice.h>
#include <mbed.h>

#include "AudioGen.h"

namespace {

// Hardware
DigitalOut enable{MBED_CONF_APP_AUDIO_ENABLE, 0};
SPIFBlockDevice spif{
    MBED_CONF_SPIF_DRIVER_SPI_MOSI, MBED_CONF_SPIF_DRIVER_SPI_MISO,
    MBED_CONF_SPIF_DRIVER_SPI_CLK, MBED_CONF_SPIF_DRIVER_SPI_CS};
LittleFileSystem fs{"fs", &spif};

struct ClipList {
  size_t count;
  const char **files;
};

enum class State {
  IDLE,
  PLAYING,
  DRAINING,
};

// Clips are unsigned 8 bit, 16 KHz.
// TODO extend to 10 bits?
using SampleType = uint8_t;
constexpr unsigned int kFreq = 16000;
constexpr unsigned int kBufSize = 1024;

const char *startup[] = {
    "Turret_sfx_deploy.raw",
    "Turret_sfx_active.raw",
};
const char *begin_scan[] = {
    "Turret_searching.raw",
    "Turret_activated.raw",
    "Turret_sentry_mode_activated.raw",
    "Turret_could_you_come_over_here.raw",
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

File file;

SampleType buf1[kBufSize];
size_t buf1len;
SampleType buf2[kBufSize];
size_t buf2len;
int activeBuffer;
State state{State::IDLE};

void startClip() {
  enable = 1;

  if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3) != HAL_OK) {
    MBED_ERROR(
        MBED_MAKE_ERROR(
            MBED_MODULE_APPLICATION, MBED_ERROR_CODE_FAILED_OPERATION),
        "HAL_TIM_PWM_Start()");
  }

  if (HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_1) != HAL_OK) {
    MBED_ERROR(
        MBED_MAKE_ERROR(
            MBED_MODULE_APPLICATION, MBED_ERROR_CODE_FAILED_OPERATION),
        "HAL_TIM_OC_Start()");
  }

  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC1);
}

void playBuffer(SampleType *buffer, size_t len) {
  if (HAL_DMA_Start_IT(
          &hdma_tim2_ch1, (uint32_t)buffer, (uint32_t)(&htim3.Instance->CCR3),
          len) != HAL_OK) {
    MBED_ERROR(
        MBED_MAKE_ERROR(
            MBED_MODULE_APPLICATION, MBED_ERROR_CODE_FAILED_OPERATION),
        "HAL_DMA_Start_IT()");
  }
}

void endClip() {
  __HAL_TIM_DISABLE_DMA(&htim2, TIM_DMA_CC1);

  if (HAL_TIM_OC_Stop(&htim2, TIM_CHANNEL_1) != HAL_OK) {
    MBED_ERROR(
        MBED_MAKE_ERROR(MBED_MODULE_HAL, MBED_ERROR_CODE_INITIALIZATION_FAILED),
        "HAL_TIM_OC_Stop()");
  }

  if (HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3) != HAL_OK) {
    MBED_ERROR(
        MBED_MAKE_ERROR(MBED_MODULE_HAL, MBED_ERROR_CODE_INITIALIZATION_FAILED),
        "HAL_TIM_PWM_Stop()");
  }
  htim3.Instance->CCR3 = 0;

  enable = 0;
  file.close();
  state = State::IDLE;

  printf("done\n");
}

void playNextBlock() {
  if (state == State::DRAINING) {
    endClip();
  } else {
    SampleType *playbuf;
    size_t playlen;
    SampleType *rdbuf;
    size_t *rdlen;

    if (activeBuffer == 0) {
      playbuf = buf2;
      playlen = buf2len;
      rdbuf = buf1;
      rdlen = &buf1len;
      activeBuffer = 1;
    } else {
      playbuf = buf1;
      playlen = buf1len;
      rdbuf = buf2;
      rdlen = &buf2len;
      activeBuffer = 0;
    }

    playBuffer(playbuf, playlen);
    ssize_t rd = file.read(rdbuf, kBufSize * sizeof(SampleType));
    if (rd > 0) {
      *rdlen = rd / sizeof(SampleType);
    } else {
      // End of data, wait for current buffer to finish and stop.
      state = State::DRAINING;
    }
  }
}

auto queue{mbed_event_queue()};
auto playNextBlockEvent{queue->make_user_allocated_event(playNextBlock)};

void dmaCompleteCallback(DMA_HandleTypeDef *_hdma) {
  playNextBlockEvent.call();
}

void dmaErrorCallback(DMA_HandleTypeDef *_hdma) {
  MBED_ERROR(
      MBED_MAKE_ERROR(
          MBED_MODULE_APPLICATION, MBED_ERROR_CODE_FAILED_OPERATION),
      "DMA transfer error");
}

}  // namespace

void Audio::init() {
  Audio_HW_Init(kFreq);

  // Register end-of-transfer callbacks
  if (HAL_DMA_RegisterCallback(
          &hdma_tim2_ch1, HAL_DMA_XFER_CPLT_CB_ID, &dmaCompleteCallback) !=
      HAL_OK) {
    MBED_ERROR(
        MBED_MAKE_ERROR(MBED_MODULE_HAL, MBED_ERROR_CODE_INITIALIZATION_FAILED),
        "HAL_DMA_RegisterCallback()");
  }

  if (HAL_DMA_RegisterCallback(
          &hdma_tim2_ch1, HAL_DMA_XFER_ERROR_CB_ID, &dmaErrorCallback) !=
      HAL_OK) {
    MBED_ERROR(
        MBED_MAKE_ERROR(MBED_MODULE_HAL, MBED_ERROR_CODE_INITIALIZATION_FAILED),
        "HAL_DMA_RegisterCallback()");
  }

  if (HAL_DMA_RegisterCallback(
          &hdma_tim2_ch1, HAL_DMA_XFER_ABORT_CB_ID, &dmaErrorCallback) !=
      HAL_OK) {
    MBED_ERROR(
        MBED_MAKE_ERROR(MBED_MODULE_HAL, MBED_ERROR_CODE_INITIALIZATION_FAILED),
        "HAL_DMA_RegisterCallback()");
  }
}

void Audio::play(Audio::Clip clip) {
  printf("play %d %d\n", (int)clip, (int)state);

  if (state == State::IDLE) {
    auto list = clips[(int)clip];
    size_t index = random() % list.count;
    auto path = list.files[index];

    int status = file.open(&fs, path, O_RDONLY);
    if (status == 0) {
      ssize_t rd = file.read(buf1, sizeof(buf1));
      if (rd > 0) {
        buf1len = rd / sizeof(SampleType);
        state = State::PLAYING;
        activeBuffer = 1;

        startClip();
        playNextBlock();
      } else {
        file.close();
      }
    } else {
      printf("open failed %d\n", status);
    }
  }
}
