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
 * @Date: 2024-04-18 15:17:21
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-18 16:21:52
 * @FilePath: /74HC595/Core/Inc/gpio.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-12 13:51:11
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-18 12:10:33
 * @FilePath: /74HC595/Core/Inc/gpio.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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

// #define HC_STCP GPIO_Pin_7
// #define HC_SHCP GPIO_Pin_6
#define HC_STCP GPIO_Pin_2
#define HC_SHCP GPIO_Pin_3
// #define HC_DS GPIO_Pin_5
#define HC_DS GPIO_Pin_0
#define HC_PORT GPIOA
#define HC_MR GPIO_Pin_3
#define BUSY_PIN GPIO_Pin_4
#define LCD_DATA_PORT GPIOA
#define LCD_DATA_PIN                                                           \
  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |             \
      GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
#define HC_PORT GPIOA
#define LCD_SIGNAL_PORT GPIOB
#define LCD_RS_PIN GPIO_Pin_0
#define LCD_RW_PIN GPIO_Pin_1
#define LCD_EN_PIN GPIO_Pin_10
#define LCD_CHECK_PIN GPIO_Pin_6
#define LOW 0
#define HIGH 1
// #define 
#define LCD_PORT GPIOA
// #define RS(x) GPIO_WriteBit(GPIOB, LCD_RS, x)
// #define EN(x) GPIO_WriteBit(GPIOB, LCD_EN, x)
void My_GPIO_Init(void);

#endif