#include "main.h"

int main(void) {
  My_GPIO_Init();
  while (1) {
    GPIO_SetBits(GPIOA, GPIO_Pin_6);
    Delay_ms(500);
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);
  }
}