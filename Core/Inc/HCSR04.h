#ifndef __HCSR04_H
#define __HCSR04_H

//获取测距时间间隔

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "Nixie.h"
#include "gpio.h"
#include "math.h"
#include "my_config.h"


// #include "stm32f10x.h" // Device header

#define TRIG  HCSR04_Trigger(void);

void Value_Processing(uint8_t *dist);

void HCSR04_Trigger(void);

void HCSR04_Init(void);

void HCSR04_GetValue(float *dist);

void Data_Processing(float *Data, float *Sum, uint16_t *step, uint8_t *dist, float *sd, float mean);

void ValueToNixie(float digit, uint8_t *dist);

#endif
