/*
开始信号：在SCL为高电平时，SDA由高电平转为低电平
结束信号：在SCL为高电平时，SDA由低电平转为高电平
写"1":在SCL高电平期间，SDA的电平不能发生变化，保持为高电平，并且在SCL的下降沿到来时，数据生效
写"0":在SCL高电平期间，SDA的电平不能发生变化，保持为低电平，并且在SCL的下降沿到来时，数据生效
写命令：[开始信号]-->[写入器件地址+应答]-->[写入寄存器地址+应答]-->[写入数据+应答]-->[停止信号]
读命令:  
    [开始信号]-->[写入器件地址+应答]-->[写入寄存器地址+应答]-->
        [写入器件地址+应答]-->[读取数据+应答]-->...-->[最后数据+无应答]-->[停止信号]
 */
#include "i2c.h"

void M_I2C_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = I2C_SCL_Pin | I2C_SDA_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_PORT, &GPIO_InitStructure);
}