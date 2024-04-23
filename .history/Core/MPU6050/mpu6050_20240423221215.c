/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-22 21:06:07
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-23 21:36:46
 * @FilePath: /74HC595/Core/MPU6050/mpu6050.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "mpu6050.h"
#include <stdint.h>
 const uint8_t command1[] = {MPU6050_PWR_MGMT_1_Data,
                                   MPU6050_PWR_MGMT_2_Data};
 const uint8_t command2[] = {MPU6050_SMPLRT_DIV_Data, MPU6050_CONFIG_Data,
                                   MPU6050_GYRO_CONFIG_Data,
                                   MPU6050_ACCEL_CONFIG_Data};
void MPU6050_Init(void) {
    M_I2C_Init();
    M_I2C_Transmit_Data(MPU6050_PWR_MGMT_1, command1, 2);
    M_I2C_Transmit_Data(MPU6050_SMPLRT_DIV, command2, 4);
}

// uint8_t MPU6050_GetID(uint8_t *data) { return MPU6050_ReadReg_Single(MPU6050_WHO_AM_I); }