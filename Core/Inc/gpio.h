#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f10x_conf.h"
#define LCD_D0 GPIO_Pin_0
#define LCD_D1 GPIO_Pin_1
#define LCD_D2 GPIO_Pin_2
#define LCD_D3 GPIO_Pin_3
#define LCD_D4 GPIO_Pin_4
#define LCD_D5 GPIO_Pin_5
#define LCD_D6 GPIO_Pin_6
#define LCD_D7 GPIO_Pin_7

#define LCD_RS GPIO_Pin_0
#define LCD_EN GPIO_Pin_1

#define LOW 0
#define HIGH 1

#define LCD_PORT GPIOA
#define RS(x) GPIO_WriteBit(GPIOB, LCD_RS, x)
#define EN(x) GPIO_WriteBit(GPIOB, LCD_EN, x)
void My_GPIO_Init(void);

#endif