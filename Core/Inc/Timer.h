#ifndef __TIMER_H
#define __TIMER_H

#include "my_config.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void Timer_Init(void);

void Set_Timer(TIM_TypeDef *TIMx, uint16_t period, uint16_t prescaler,
               uint8_t IRQChannel, uint8_t preemptionPriority,
               uint8_t subPriority);

void TIM2_Init(uint16_t period, uint16_t prescaler, uint8_t preemptionPriority,
               uint8_t subPriority, FunctionalState NewState);

void TIM3_Init(uint16_t period, uint16_t prescaler, uint8_t preemptionPriority,
               uint8_t subPriority, FunctionalState NewState);

#endif
