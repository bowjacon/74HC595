/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-22 21:06:07
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-25 18:17:22
 * @FilePath: /74HC595/Core/MPU6050/mpu6050.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MPU6050_H
#define __MPU6050_H
#include "i2c.h"
#include "mpu6050_reg.h"
#include <math.h>
#include <stdint.h>

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

static const uint8_t command1[] = {MPU6050_PWR_MGMT_1_Data,
                                   MPU6050_PWR_MGMT_2_Data};
static const uint8_t command2[] = {MPU6050_SMPLRT_DIV_Data, MPU6050_CONFIG_Data,
                                   MPU6050_GYRO_CONFIG_Data,
                                   MPU6050_ACCEL_CONFIG_Data};
// #pragma pack(push, 1)
// typedef struct {
//     uint8_t value; // 0~3
//     uint16_t div;  // 0~16384
// } MPU6050_ACCEL;
// #pragma pack(pop)

typedef struct {
    uint8_t accel_value;
} My_Mpu6050;
void MPU6050_Init();
void MPU6050_Read_Temperature(double *temperature);
void MPU6050_Get_Accelerometer(double *ax, double *ay, double *az);

#define ACCEL_Origin 16384 // 2^14=16384
static enum {
    ACCEL_2G = 1,
    ACCEL_4G = 2,
    ACCEL_8G = 3,
    ACCEL_16G = 4,
} ACCEL_X;
// #define ACCEL_2G 0
// #define ACCEL_4G 1
// #define ACCEL_8G 2
// #define ACCEL_16G 3
// #pragma pack(pop)
// struct MPU6050_ACCEL{

// };

void MPU6050_Set_Accel_Fsr(uint8_t value);
void MPU6050_Accel_Transform(double *ax, double *ay, double *az, uint8_t value);
#endif