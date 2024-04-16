#ifndef _LCD1602_H_
#define _LCD1602_H_
#include "delay.h"
#include "gpio.h"

#define LCD_DATA_PORT GPIOA
#define LCD_DATA_PIN                                                           \
  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |             \
      GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
#define LCD_SIGNAL_PORT GPIOB
#define LCD_RS_PIN GPIO_Pin_0
#define LCD_RW_PIN GPIO_Pin_1
#define LCD_EN_PIN GPIO_Pin_10
#define LCD_CHECK_PIN GPIO_Pin_6
#define LCD_Delay 1
#define LCD_TIMEOUT 10000
#define RS(X) GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_RS_PIN, X)
#define RW(X) GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_RW_PIN, X)
#define EN(X) GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, X)
void LCD_Init(void);
void LCD_DisplayString(char *str);

#endif