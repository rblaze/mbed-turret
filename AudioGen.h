#pragma once

#include <stm32f1xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim2_ch1;
extern TIM_HandleTypeDef htim3;

void Audio_HW_Init(uint32_t sampleFreq);

#ifdef __cplusplus
}
#endif
