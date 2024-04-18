/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-17 22:12:10
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-17 22:29:08
 * @FilePath: /74HC595/Core/Inc/74HC595.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AEd

 */
#ifndef _74HC595_H
#define _74HC595_H
#include "gpio.h"
#define SCK(x) GPIO_WriteBit(GPIOA, HC_SHCP, x)
#define RCK(x) GPIO_WriteBit(GPIOA, HC_STCP, x)
#define SDA(x) GPIO_WriteBit(GPIOA, HC_DS, x)
#define MR(x) GPIO_WriteBit(GPIOA, HC_MR, x)
void SendByte(uint8_t byte);
void DataClear(void);
#endif