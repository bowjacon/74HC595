#include "lcd1602.h"
#include <stdint.h>

void LCD_CheckBusy(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = BUSY_PIN;
  GPIO_Init(LCD_DATA_PORT, &GPIO_InitStructure);
  int counter = 0;
  while (GPIO_ReadInputDataBit(LCD_DATA_PORT, GPIO_Pin_7)) {
    if (counter++ > LCD_TIMEOUT) { //防止死循环
      return;
    }
    EN(Bit_RESET);
    RS(Bit_RESET);
    RW(Bit_SET);
    Delay_ms(LCD_Delay);
    EN(Bit_SET);
    Delay_ms(LCD_Delay);
  }
  GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, 0);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_DATA_PORT, &GPIO_InitStructure);
}
void LCD_WriteCommand(uint8_t command) {
  LCD_CheckBusy();
  RS(Bit_RESET);
  RW(Bit_RESET);
  GPIO_Write(LCD_DATA_PORT, command);
  EN(Bit_SET);
  Delay_ms(LCD_Delay);
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
  // LCD_WriteCommand(0x80);
}
void LCD_SetCursor(uint8_t x, uint8_t y) {
  uint8_t address = (y == 1) ? (0xC0 + x) : (0x80 + x);
  LCD_WriteCommand(address);
}
void LCD_DisplayString(uint8_t x, uint8_t y, char *str) {
  LCD_WriteCommand(0x40 + x + y * 64);
  // LCD_WriteCommand(0x81);
  // LCD_WriteData('A');
  while (*str>0) {
  //   //   // LCD_SetCursor(x,y);

    LCD_WriteData(*str++);
  }
}
