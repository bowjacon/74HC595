/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-21 15:04:41
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-22 21:01:17
 * @FilePath: /74HC595/Core/Inc/i2c.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _I2C_H
#define _I2C_H
#include "gpio.h"
#include <stdint.h>
#define SlaveAddress 0x21
static void I2C_config(void);
static void I2Cdev_writeByte(uint8_t dev_addr, uint8_t REG_Address, uint8_t REG_data);
static void I2Cdev_readByte(uint8_t dev_addr, uint8_t REG_Address, uint8_t *data);
static void I2Cdev_writeBit(uint8_t dev_addr, uint8_t reg_addr, uint8_t bit_n,
                     uint8_t data);
static void I2Cdev_readBit(uint8_t dev_addr, uint8_t reg_addr, uint8_t bitn,
                    uint8_t *data);
static void I2Cdev_writeBits(uint8_t dev_addr, uint8_t reg_addr, uint8_t start_bit,
                      uint8_t len, uint8_t data);
static void I2Cdev_readBits(uint8_t dev_addr, uint8_t reg_addr, uint8_t start_bit,
                     uint8_t len, uint8_t *data);
#endif