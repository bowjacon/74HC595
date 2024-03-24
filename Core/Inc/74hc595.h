#ifndef _745H95_H
#define _745H95_H
//OE:低电平有效
//MR:默认接高电平

#include "stm32f10x_conf.h"
#include "delay.h"
#include "gpio.h"

void DataClear(void);

#define SCK(X)        GPIO_WriteBit(GPIOA,SCK_PIN,X);
#define RCK(X)        GPIO_WriteBit(GPIOA,RCK_PIN,X);
#define SDA(X)        GPIO_WriteBit(GPIOA,SDA_PIN,X);

void H595Init(void);

void SendByte(uint8_t byte);

#endif 