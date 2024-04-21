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
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2; //设置I2C的时钟频率
    I2C_InitStructure.I2C_OwnAddress1 = SlaveAddress; //设置本机地址
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; //使能应答
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //规定地址长度为7位
    I2C_InitStructure.I2C_ClockSpeed = 400000; //设置I2C的时钟频率
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);//使能I2C1
    I2C_AcknowledgeConfig(I2C1, ENABLE);//使能应答
}
void I2C_WriteByte(uint8_t REG_Address,uint8_t REG_data)
{
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1,SlaveAddress,I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1,REG_Address);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_SendData(I2C1,REG_data);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C1,ENABLE);
}
