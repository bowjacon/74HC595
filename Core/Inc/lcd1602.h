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
 * @LastEditTime: 2024-04-18 16:21:49
 * @FilePath: /74HC595/Core/Inc/lcd1602.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-13 15:09:11
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-18 13:41:44
 * @FilePath: /74HC595/Core/Inc/lcd1602.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _LCD1602_H_
#define _LCD1602_H_
#include "74HC595.h"
#include "delay.h"
#include "gpio.h"

#define LCD_Delay 1
#define LCD_TIMEOUT 100
#define RS(X) GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_RS_PIN, X)
#define RW(X) GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_RW_PIN, X)
#define EN(X) GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, X)
void LCD_Init(void);
void LCD_DisplayString(uint8_t x, uint8_t y, char *str);
void LCD_WriteData(uint8_t data);
void LCD_WriteCommand(uint8_t command);
void LCD_ShowNum_16(uint8_t x, uint8_t y, int num);
void LCD_ShowNum_10(uint8_t x, uint8_t y, int num);
#endif