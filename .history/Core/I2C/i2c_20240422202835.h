/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-21 20:22:48
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-22 20:27:54
 * @FilePath: /74HC595/Core/I2C/i2c.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef I2C_H
#define I2C_H
#include "gpio.h"
#define I2C_PORT GPIOA
#define I2C_SCL GPIO_Pin_1
#define I2C_SDA GPIO_Pin_0
#define I2C_SCL_ GPIO_SetBits(I2C_PORT, x)
void M_I2C_Init(void);
#endif