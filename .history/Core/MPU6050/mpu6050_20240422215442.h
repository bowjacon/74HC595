#ifndef __MPU6050_H
#define __MPU6050_H
#include "mpu6050_reg.h"
#include<math.h>
#define MPU6050_PWR_MGMT_1_Data 0x01
#define MPU6050_PWR_MGMT_2_Data 0x00
#define MPU6050_SMPLRT_DIV_Data 0x09
#define MPU6050_CONFIG_Data 0x06
#define MPU6050_GYRO_CONFIG_Data 0x00
#define MPU6050_ACCEL_CONFIG_Data 0x08
#define ACC_Ran pow(2,(MPU6050_ACCEL_CONFIG_Data>>3&&0x01)+(MPU6050_ACCEL_CONFIG_Data>>4&&0x01)+1)
#define GYRO_Ran pow(2,(MPU6050_GYRO_CONFIG_Data>>3&&0x01)+(MPU6050_GYRO_CONFIG_Data>>4&&0x01))*250

void Time_Basic(uint8_t RegAddress);
void MPU6050_WriteReg_Single(uint8_t RegAddress,uint8_t data);
void MPU6050_WriteReg_Continue(uint8_t RegAddress,uint8_t *command,uint8_t Flag);
uint8_t MPU6050_ReadReg_Single(uint8_t RegAddress);
void MPU6050_ReadReg_Continue(uint8_t RegAddress,int16_t *Data,uint8_t Flag);

void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData_Single(void);
void MPU6050_GetData_Continue(void);

typedef struct 
{
	int16_t AccX;
	int16_t Accy;
	int16_t Accz;
	int16_t GyrX;
	int16_t Gyry;
	int16_t Gyrz;
	int16_t Temp;
}MPU6050_Data_InitTypeDef;

//void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
//						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);

#endif
