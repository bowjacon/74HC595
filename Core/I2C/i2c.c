/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-21 20:22:42
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-24 19:43:39
 * @FilePath: /74HC595/Core/I2C/i2c.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
开始信号：在SCL为高电平时，SDA由高电平转为低电平
结束信号：在SCL为高电平时，SDA由低电平转为高电平
写"1":
    在SCL高电平期间，SDA的电平不能发生变化，保持为高电平，并且在SCL的下降沿到来时，数据生效
写"0":
    在SCL高电平期间，SDA的电平不能发生变化，保持为低电平，并且在SCL的下降沿到来时，数据生效
写命令：
    [开始信号]-->[写入器件地址+应答]-->[写入寄存器地址+应答]-->[写入数据+应答...写入数据+应答]-->[停止信号]
读命令:
    [开始信号]-->[写入器件地址+应答]-->[写入寄存器地址+应答]-->
    [写入器件地址+应答]-->[读取数据+应答...读取数据+应答]-->[最后数据+无应答]-->[停止信号]
 */
#include "i2c.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>
#include <string.h>

/**
 * @brief
 * 开始信号
 */
void M_I2C_Start(void) {
    I2C_SDA(1);
    I2C_SCL(1);
    I2C_SDA(0);
}

/**
 * @brief 停止信号
 */

void M_I2C_Stop(void) {
    I2C_SDA(0);
    I2C_SCL(1);
    I2C_SDA(1);
}
/**
 * @brief 脉冲信号
 *
 */
void M_I2C_Clock(void) {
    I2C_SCL(0);
    I2C_SCL(1);
    I2C_SCL(0);
}
/**
 * 发送一个字节数据
 */
void M_I2C_Transmit_Byte(uint8_t byte) {
    I2C_SCL(0);
    for (uint8_t j = 0; j < 8; j++) {
        I2C_SDA((byte & (0x80 >> j)));
        I2C_SCL(1);
        I2C_SCL(0);
    }
}

/**
 * 发送n个数据(中间层)
 */
void M_I2C_Transmit(const uint8_t *data, uint8_t n) {
    for (uint8_t i = 0; i < n; i++) {
        M_I2C_Transmit_Byte(data[i]);
        M_I2C_Clock();
    }
}

/**
 * 接收一个字节数据
 */
void M_I2C_Receive_Byte(uint8_t *data) {
    uint8_t byte = 0;
    I2C_SCL(0);
    I2C_SDA(1);
    for (uint8_t j = 0; j < 8; j++) {
        I2C_SCL(1);
        if (Read_SDA() == 1) {
            byte |= (0x80 >> j);
        }
        I2C_SCL(0);
    }
    *data = byte;
}

/**
 * 接受n个数据(中间层)
 */
void M_I2C_Reicive(uint8_t reg_adress, uint8_t *data, uint8_t n) {
    for (uint8_t i = 0; i < n; i++) {
        M_I2C_Receive_Byte(&data[i]);
        M_I2C_Clock();
        reg_adress++;
    }
}
/**
 * 写入指定个数数据
 */
void M_I2C_Transmit_Data(uint8_t reg_adress, const uint8_t *data, uint8_t n) {
    uint8_t length = 2 + n;
    uint8_t send_packet[length];
    uint8_t adress[2] = {MPU6050_ADDRESS, reg_adress};
    M_I2C_Start();
    Connect_Array(send_packet, adress, 2, data, n);
    M_I2C_Transmit(send_packet, length);
    M_I2C_Stop();
}

/**
 * 读取指定个数数据
 */
void M_I2C_ReiciveByte_Data(uint8_t reg_adress, uint8_t *data, uint8_t n) {
    M_I2C_Start();
    uint8_t adress[2] = {MPU6050_ADDRESS, reg_adress};
    M_I2C_Transmit(adress, 2);
    M_I2C_Start();
    uint8_t send_data[] = {MPU6050_ADDRESS | Read_Mode};
    M_I2C_Transmit(send_data, 1);
    M_I2C_Reicive(reg_adress, data, n);
    M_I2C_Clock();
    M_I2C_Stop();
}