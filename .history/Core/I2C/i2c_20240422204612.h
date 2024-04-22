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