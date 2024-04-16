#include "lcd1602.h"

void LCD_CheckBusy(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(LCD_DATA_PORT, &GPIO_InitStructure);
  int counter = 0;
  while (GPIO_ReadInputDataBit(LCD_DATA_PORT, GPIO_Pin_7)) {
    if (counter++ > LCD_TIMEOUT) { //防止死循环
      return;
    }
    GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, 0);
    GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_RS_PIN, 0);
    GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_RW_PIN, 1);
    Delay_ms(LCD_Delay);
    GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, 1);
    Delay_ms(LCD_Delay);
  }

  GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, 0);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_DATA_PORT, &GPIO_InitStructure);
}
void LCD_WriteCommand(uint8_t command) {
  LCD_CheckBusy();
  RS(Bit_RESET);
  // GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_RW_PIN, 0);
  RW(Bit_RESET);
  GPIO_Write(LCD_DATA_PORT, command);
  // GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, 1);
  EN(Bit_SET);
  Delay_ms(LCD_Delay);
  // GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, 0);
  EN(Bit_RESET);
}

void LCD_WriteData(uint8_t data) {
  LCD_CheckBusy();
  RS(Bit_SET);
  RW(Bit_RESET);
  GPIO_Write(LCD_DATA_PORT, data);
  EN(Bit_SET);
  Delay_ms(LCD_Delay);
  EN(Bit_RESET);
}

void LCD_Init(void) {
  // Configure LCD data pins as output
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = LCD_DATA_PIN;
  GPIO_Init(LCD_DATA_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin =
      LCD_RS_PIN | LCD_EN_PIN | LCD_RW_PIN | LCD_CHECK_PIN;
  GPIO_Init(LCD_SIGNAL_PORT, &GPIO_InitStructure);
  LCD_WriteCommand(0x38); // 8-bit mode, 2 lines, 5x8 dots/character
  LCD_WriteCommand(0x0C); // Display on, cursor off
  LCD_WriteCommand(0x01); // Clear display
  LCD_WriteCommand(0x06); // Entry mode: increment address, no shift
  LCD_WriteCommand(0x80);
}

void LCD_DisplayString(char *str) {
  while (*str) {
    LCD_WriteData(*str++);
  }
}
