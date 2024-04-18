/*
 * _______________#########_______________________
 * ______________############_____________________
 * ______________#############____________________
 * _____________##__###########___________________
 * ____________###__######_#####__________________
 * ____________###_#######___####_________________
 * ___________###__##########_####________________
 * __________####__###########_####_______________
 * ________#####___###########__#####_____________
 * _______######___###_########___#####___________
 * _______#####___###___########___######_________
 * ______######___###__###########___######_______
 * _____######___####_##############__######______
 * ____#######__#####################_#######_____
 * ____#######__##############################____
 * ___#######__######_#################_#######___
 * ___#######__######_######_#########___######___
 * ___#######____##__######___######_____######___
 * ___#######________######____#####_____#####____
 * ____######________#####_____#####_____####_____
 * _____#####________####______#####_____###______
 * ______#####______;###________###______#________
 * ________##_______####________####______________
 *
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-13 15:09:00
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-18 14:14:24
 * @FilePath: /74HC595/Core/Src/lcd1602.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "lcd1602.h"
#include "delay.h"
#include <stdint.h>

/**
 * @description:
 * @return {*}
 */
voO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = BUSY_PIN;
  GPIO_Init(HC_PORT, &GPIO_InitStructure);
  int counter = 0;
  while (GPIO_ReadInputDataBit(HC_PORT, BUSY_PIN)) {
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
  // GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, 0);
  EN(Bit_RESET);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(HC_PORT, &GPIO_InitStructure);
}id LCD_CheckBusy(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPI

/**
 * @description:
 * @param {uint8_t} command
 * @return {*}
 */
void LCD_WriteCommand(uint8_t command) {
  DataClear();
  // SendByte(0);
  // LCD_CheckBusy();
  // Delay_ms(10);
  RS(Bit_RESET);
  // RW(Bit_RESET);
  SendByte(command);
  // GPIO_Write(LCD_DATA_PORT, command);
  EN(Bit_SET);
  Delay_ms(LCD_Delay);
  EN(Bit_RESET);
}

void LCD_WriteData(uint8_t data) {
  DataClear();
  // SendByte(0);
  // LCD_CheckBusy();
  // Delay_ms(10);
  RS(Bit_SET);
  // RW(Bit_RESET);
  // GPIO_Write(LCD_DATA_PORT, data);
  SendByte(data);
  EN(Bit_SET);
  Delay_ms(LCD_Delay);
  EN(Bit_RESET);
}

/**
 * @description:
 * @return {*}
 */
void LCD_Init(void) {

  LCD_WriteCommand(0x38); // 8-bit mode, 2 lines, 5x8 dots/character
  LCD_WriteCommand(0x0C); // Display on, cursor off
  LCD_WriteCommand(0x01); // Clear display
  LCD_WriteCommand(0x06); // Entry mode: increment address, no shift
  // LCD_WriteCommand(0x80);
}

/**
 * @description:
 * @param {uint8_t} x
 * @param {uint8_t} y
 * @return {*}
 */
void LCD_SetCursor(uint8_t x, uint8_t y) {
  uint8_t address = (y == 1) ? (0xC0 + x) : (0x80 + x);
  LCD_WriteCommand(address);
}
/**
 * @description:
 * @param {uint8_t} x
 * @param {uint8_t} y
 * @param {char} *str
 * @return {*}
 */
void LCD_DisplayString(uint8_t x, uint8_t y, char *str) {
  LCD_WriteCommand(0x40 + x + y * 64);
  while (*str > 0) {
    LCD_WriteData(*str++);
  }
}
