/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-21 20:22:48
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-22 20:41:54
 * @FilePath: /74HC595/Core/I2C/i2c.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   写"1":在SCL高电平期间，SDA的电平不能发生变化，保持为高电平，并且在SCL的下降沿到来时，数据生效
   写"0":在SCL高电平期间，SDA的电平不能发生变化，保持为低电平，并且在SCL的下降沿到来时，数据生效
 */
#ifndef I2C_H
#define I2C_H
#include "gpio.h"
#define I2C_PORT GPIOA
#define I2C_SCL_Pin GPIO_Pin_1
#define I2C_SDA_Pin GPIO_Pin_0
#define I2C_SCL(x)                                                             \
    do {                                                                       \
        if (x)                                                                 \
            GPIO_SetBits(I2C_PORT, I2C_SCL_Pin);                               \
        else                                                                   \
            GPIO_ResetBits(I2C_PORT, I2C_SCL_Pin);                             \
    } while (0)
#define I2C_SDA(x)                                                             \
    do {                                                                       \
        if (x)                                                                 \
            GPIO_SetBits(I2C_PORT, I2C_SDA_Pin);                               \
        else                                                                   \
            GPIO_ResetBits(I2C_PORT, I2C_SDA_Pin);                             \
    } while (0)

void M_I2C_Init(void);

#endif