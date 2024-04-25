/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-21 20:22:48
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-25 15:51:30
 * @FilePath: /74HC595/Core/I2C/i2c.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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
 */
#ifndef I2C_H
#define I2C_H
#include "gpio.h"

#define MPU6050_ADDRESS 0xD0
#define Write_Mode 0
#define Read_Mode 1

/**
 * NOP个数根据实际情况调整
 */
#define I2C_SCL(x)                                                             \
    do {                                                                       \
        if (x) {                                                               \
            I2C_PORT->BSRR = I2C_SCL_Pin;                                      \
        } else {                                                               \
            I2C_PORT->BRR = I2C_SCL_Pin;                                       \
        }                                                                      \
        __NOP(), __NOP(), __NOP(), __NOP();                                    \
    } while (0)

#define I2C_SDA(x)                                                             \
    do {                                                                       \
        if (x) {                                                               \
            I2C_PORT->BSRR = I2C_SDA_Pin;                                      \
        } else {                                                               \
            I2C_PORT->BRR = I2C_SDA_Pin;                                       \
        }                                                                      \
        __NOP(), __NOP(), __NOP(), __NOP();                                    \
    } while (0)

void M_I2C_Init(void);
void M_I2C_Transmit(const uint8_t *data, uint8_t n);

/*
 * 读取引脚
 */
#define Read_SDA (I2C_PORT->IDR & I2C_SDA_Pin)

/**
 * @brief
 * 开始信号
 */
#define M_I2C_Start()                                                          \
    do {                                                                       \
        I2C_SDA(1);                                                            \
        I2C_SCL(1);                                                            \
        I2C_SDA(0);                                                            \
    } while (0)

/**
 * @brief 停止信号
 */

#define M_I2C_Stop()                                                           \
    do {                                                                       \
        I2C_SDA(0);                                                            \
        I2C_SCL(1);                                                            \
        I2C_SDA(1);                                                            \
    } while (0)

/**
 * @brief 应答信号,手动拉低
 *
 */
#define M_I2C_ACK()                                                            \
    do {                                                                       \
        I2C_SCL(0);                                                            \
        I2C_SDA(0);                                                            \
        I2C_SCL(1);                                                            \
        I2C_SCL(0);                                                            \
    } while (0)
/**
 * @brief 非应答信号,靠外部上拉
 */
#define M_I2C_NACK()                                                           \
    do {                                                                       \
        I2C_SCL(0);                                                            \
        I2C_SDA(1);                                                            \
        I2C_SCL(1);                                                            \
        I2C_SCL(0);                                                            \
    } while (0)
void M_I2C_Transmit_Data(uint8_t reg_adress, const uint8_t *data, uint8_t n);
void M_I2C_Reicive_Byte(uint8_t reg_adress, uint8_t *data);
void M_I2C_Receive(uint8_t *data, uint8_t ack_bit);
#define M_I2C_Receive_ACK(data) M_I2C_Receive(data, 1)
#define M_I2C_Receive_NACK(data) M_I2C_Receive(data, 0)
void M_I2C_Read_Data(uint8_t reg_adress, uint8_t *data, uint8_t n);
#endif