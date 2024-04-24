/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-22 21:06:07
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-23 22:23:25
 * @FilePath: /74HC595/Core/MPU6050/mpu6050.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MPU6050_H
#define __MPU6050_H
#include "i2c.h"
#include "mpu6050_reg.h"
#include <math.h>

#define MPU6050_PWR_MGMT_1_Data 0x01
#define MPU6050_PWR_MGMT_2_Data 0x00
#define MPU6050_SMPLRT_DIV_Data 0x09
#define MPU6050_CONFIG_Data 0x06
#define MPU6050_GYRO_CONFIG_Data 0x00
#define MPU6050_ACCEL_CONFIG_Data 0x08
#define ACC_Ran                                                                \
    pow(2, (MPU6050_ACCEL_CONFIG_Data >> 3 && 0x01) +                          \
               (MPU6050_ACCEL_CONFIG_Data >> 4 && 0x01) + 1)
#define GYRO_Ran                                                               \
    pow(2, (MPU6050_GYRO_CONFIG_Data >> 3 && 0x01) +                           \
               (MPU6050_GYRO_CONFIG_Data >> 4 && 0x01)) *                      \
        250


void MPU6050_Init(void);
#endif
