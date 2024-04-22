/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-22 21:06:07
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-22 21:53:15
 * @FilePath: /74HC595/Core/MPU6050/mpu6050.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
 #include "m"
void MPU6050_Init(void)
{
	MyI2C_Init();
	MPU6050_WriteReg_Continue(MPU6050_PWR_MGMT_1,command1,2); 
	MPU6050_WriteReg_Continue(MPU6050_SMPLRT_DIV,command2,4);
//	MPU6050_WriteReg_Single(MPU6050_PWR_MGMT_1, MPU6050_PWR_MGMT_1_Data); //电源管理寄存器1
//	MPU6050_WriteReg_Single(MPU6050_PWR_MGMT_2, MPU6050_PWR_MGMT_2_Data); //电源管理寄存器2
//	MPU6050_WriteReg_Single(MPU6050_SMPLRT_DIV, MPU6050_SMPLRT_DIV_Data); //配置采样率分频
//	MPU6050_WriteReg_Single(MPU6050_CONFIG, MPU6050_CONFIG_Data); //配置寄存器
//	MPU6050_WriteReg_Single(MPU6050_GYRO_CONFIG, MPU6050_GYRO_CONFIG_Data);//陀螺仪配置寄存器
//	MPU6050_WriteReg_Single(MPU6050_ACCEL_CONFIG, MPU6050_ACCEL_CONFIG_Data);//加速度计配置寄存器
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg_Single(MPU6050_WHO_AM_I);
}