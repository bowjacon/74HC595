#include "i2c.h"
void I2C_config(void)
{
    //定义结构体
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;
    //开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
    //初始化GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //初始化I2C，开启I2C1
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C ; 
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2; 
    I2C_InitStructure.I2C_OwnAddress1 = SlaveAddress; 
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; 
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //规定
    I2C_InitStructure.I2C_ClockSpeed = 400000; 
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
    I2C_AcknowledgeConfig(I2C1, ENABLE);
}