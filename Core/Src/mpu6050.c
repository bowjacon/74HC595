/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-22 21:06:07
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-28 14:48:50
 * @FilePath: /74HC595/Core/MPU6050/mpu6050.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "mpu6050.h"
#include <stdint.h>
My_Mpu6050 Mpu6050_Handle;
// M_I2C_Transmit_Data(MPU6050_PWR_MGMT_1,0x01);//解除睡眠模式,选择陀螺仪时钟
// M_I2C_Transmit_Data(MPU6050_PWR_MGMT_2,0x00);//6轴均不待机
// M_I2C_Transmit_Data(MPU6050_SMPLRT_DIV,0x09);//10分频;
// M_I2C_Transmit_Data(MPU6050_CONFIG,0x06);//有滤波
// M_I2C_Transmit_Data(MPU6050_GYRO_CONFIG,0x18);
// M_I2C_Transmit_Data(MPU6050_ACCCEL_CONFIG,0x18);
void MPU6050_Init() {

    M_I2C_Transmit_Data(MPU6050_PWR_MGMT_1, command1, 2);
    M_I2C_Transmit_Data(MPU6050_SMPLRT_DIV, command2, 4);
    // Mpu6050_Handle->accel.value = ACCEL_2G;
    Mpu6050_Handle.accel_value = ACCEL_2G;
    MPU6050_Set_Accel_Fsr(Mpu6050_Handle.accel_value);
}
void MPU6050_Read_Temperature(double *temperature) {
    uint8_t data[2];
    M_I2C_Read_Data(MPU6050_TEMP_OUT_H, data, 2);
    int16_t sum = (data[0] << 8 | data[1]);
    *temperature = sum / 340.0 + 36.53;
}

void MPU6050_Get_Accelerometer(double *ax, double *ay, double *az) {
    u8 result;
    u8 acecel[6];
    M_I2C_Read_Data(MPU6050_ACCEL_XOUT_H, acecel, 6);
    if (result == 0) {
        uint16_t raw_ax = (uint16_t)((acecel[0] << 8) | acecel[1]);
        *ax = (double)raw_ax * Mpu6050_Handle.accel_value / ACCEL_Origin;
        uint16_t raw_ay = (uint16_t)((acecel[0] << 8) | acecel[1]);
        *ay = (double)raw_ay * Mpu6050_Handle.accel_value / ACCEL_Origin;
        uint16_t raw_az = (uint16_t)((acecel[0] << 8) | acecel[1]);
        *az = (double)raw_az * Mpu6050_Handle.accel_value / ACCEL_Origin;
    }
}
//设置MPU6050加速度传感器满量程范围
// fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败
void MPU6050_Set_Accel_Fsr(uint8_t value) {
    M_I2C_Transmit_Byte(MPU6050_ACCEL_CONFIG,
                        value << 3); //设置加速度传感器满量程范围
    // accel->div = ACCEL_REG_0 << accel->value; //根据范围计算分度值
}

// void MPU6050_Accel_Transform(double *ax, double *ay, double *az,
//                              uint8_t value) {
//     *ax = (uint32_t)*ax << (ACCEL_REG_0 - value);
//     *ay = (uint32_t)*ay << (ACCEL_REG_0 - value);
//     *az = (uint32_t)*az << (ACCEL_REG_0 - value);
//     // *ax1 = (double)*ax / ACC_Ran;
//     // *ay1 = (double)*ay / ACC_Ran;
//     // *az1 = (double)*az / ACC_Ran;
// }