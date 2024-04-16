// #include "stm32c8t6.h"
#include "main.h"
int main(void) {
  LCD_Init();
  LCD_DisplayString("Hello World");
  while (1) {
  }
}
