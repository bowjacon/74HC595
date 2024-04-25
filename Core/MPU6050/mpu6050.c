/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-22 21:06:07
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-25 15:53:21
 * @FilePath: /74HC595/Core/MPU6050/mpu6050.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "mpu6050.h"
#include "i2c.h"
#include <stdint.h>

// M_I2C_Transmit_Data(MPU6050_PWR_MGMT_1,0x01);//解除睡眠模式,选择陀螺仪时钟
// M_I2C_Transmit_Data(MPU6050_PWR_MGMT_2,0x00);//6轴均不待机
// M_I2C_Transmit_Data(MPU6050_SMPLRT_DIV,0x09);//10分频;
// M_I2C_Transmit_Data(MPU6050_CONFIG,0x06);//有滤波
// M_I2C_Transmit_Data(MPU6050_GYRO_CONFIG,0x18);
// M_I2C_Transmit_Data(MPU6050_ACCCEL_CONFIG,0x18);
void MPU6050_Init(void) {
    M_I2C_Transmit_Data(MPU6050_PWR_MGMT_1, command1, 2);
    M_I2C_Transmit_Data(MPU6050_SMPLRT_DIV, command2, 4);
}
void MPU6050_Read_Temperature(double *temperature) {
    uint8_t data[2];
    M_I2C_Read_Data(MPU6050_TEMP_OUT_H, data, 2);
    int16_t sum = (data[0] << 8 | data[1]);
    *temperature = sum / 340.0 + 36.53;
}
