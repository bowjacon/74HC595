/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-21 20:22:48
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-23 22:42:15
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
#define SCL_DELAY 4
#define Write_Mode 0
#define Read_Mode 1
typedef enum {
    ACK = 0,
    NACK = 1,
} ACK_FLAG;
#define I2C_SCL(x)                                 \
    do {                                           \
        if (x)                                     \
            GPIO_SetBits(I2C_PORT, I2C_SCL_Pin);   \
        else                                       \
            GPIO_ResetBits(I2C_PORT, I2C_SCL_Pin); \
        Delay_us(SCL_DELAY);                       \
    } while (0)

#define I2C_SDA(x)                                 \
    do {                                           \
        if (x)                                     \
            GPIO_SetBits(I2C_PORT, I2C_SDA_Pin);   \
        else                                       \
            GPIO_ResetBits(I2C_PORT, I2C_SDA_Pin); \
        Delay_us(SCL_DELAY);                       \
    } while (0)

void M_I2C_Init(void);
void M_I2C_Transmit(const uint8_t* data, uint8_t n);

/*
 * 读取引脚
 */
#define Read_SDA() GPIO_ReadInputDataBit(I2C_PORT, I2C_SDA_Pin)

/*
 * 改变SDA为输出模式
 */
#define IN_SDA() \
    GPIO_Init(I2C_PORT, &((GPIO_InitTypeDef) { .GPIO_Pin = I2C_SDA_Pin, .GPIO_Mode = GPIO_Mode_IPU, .GPIO_Speed = GPIO_Speed_50MHz }))

/*
 * 改变SDA为输入模式
 */
#define OUT_SDA() \
    GPIO_Init(I2C_PORT, &((GPIO_InitTypeDef) { .GPIO_Pin = I2C_SDA_Pin, .GPIO_Mode = GPIO_Mode_Out_PP, .GPIO_Speed = GPIO_Speed_50MHz }))
/*
 * 拼接数组
 */
#define Connect_Array(dest, src1, len1, src2, len2) \
    do {                                            \
        for (int i = 0; i < (len1); i++) {          \
            (dest)[i] = (src1)[i];                  \
        }                                           \
        for (int i = 0; i < (len2); i++) {          \
            (dest)[(len1) + i] = (src2)[i];         \
        }                                           \
    } while (0)
void M_I2C_Transmit_Data(uint8_t reg_adress, const uint8_t* data, uint8_t n);
void M_I2C_ReiciveByte_Data(uint8_t reg_adress, uint8_t* data, uint8_t n);
#endif