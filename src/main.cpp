#include "stm32g0xx_hal.h"

extern "C" void SysTick_Handler(void);
void GPIO_PA4_Init();

int main() {
  HAL_Init();
  GPIO_PA4_Init();

  while (1) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    HAL_Delay(100);
  }
  return 0;
}

void SysTick_Handler(void) { HAL_IncTick(); }

void GPIO_PA4_Init() {
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
