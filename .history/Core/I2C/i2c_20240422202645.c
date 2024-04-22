/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-21 20:22:42
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-21 20:24:10
 * @FilePath: /74HC595/Core/I2C/i2c.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "i2c.h"
#define I2C_PORT GPIOA
#define I2C_SCL GPIO_Pin_1
#define I2C_SDA GPIO_Pin_0

void I2C_Init(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = I2C_SCL | I2C_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(I2C_PORT, &GPIO_InitStructure);
  I2C_SCL_1;
  I2C_SDA_1;
}