/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-21 20:22:48
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-24 19:57:08
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

#define I2C_SCL(x) GPIO_WriteBit(I2C_PORT, I2C_SCL_Pin, x)
#define I2C_SDA(x) GPIO_WriteBit(I2C_PORT, I2C_SDA_Pin, x)

void M_I2C_Init(void);
void M_I2C_Transmit(const uint8_t *data, uint8_t n);

/*
 * 读取引脚
 */
#define Read_SDA() GPIO_ReadInputDataBit(I2C_PORT, I2C_SDA_Pin)

void M_I2C_Transmit_Data(uint8_t reg_adress, const uint8_t *data, uint8_t n);
void M_I2C_Reicive_Byte(uint8_t reg_adress, uint8_t *data);
#endif