/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-21 15:04:41
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-21 15:07:01
 * @FilePath: /74HC595/Core/Inc/i2c.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _I2C_H
#define _I2C_H
#include "gpio.h"
#define SlaveAddress 0x21
void I2C_config(void);
#endif