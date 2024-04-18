/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-12 13:54:15
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-18 12:57:10
 * @FilePath: /74HC595/Core/Src/gpio.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "gpio.h"
#include "stm32f10x_gpio.h"

void My_GPIO_Init(void) {
  // Configure LCD data pins as output
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = HC_STCP | HC_SHCP | HC_DS | BUSY_PIN | HC_MR;
  GPIO_Init(HC_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN | LCD_EN_PIN | LCD_RW_PIN;
  GPIO_Init(LCD_SIGNAL_PORT, &GPIO_InitStructure);
}