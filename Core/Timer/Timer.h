/*
 * _______________#########_______________________ 
 * ______________############_____________________ 
 * ______________#############____________________ 
 * _____________##__###########___________________ 
 * ____________###__######_#####__________________ 
 * ____________###_#######___####_________________ 
 * ___________###__##########_####________________ 
 * __________####__###########_####_______________ 
 * ________#####___###########__#####_____________ 
 * _______######___###_########___#####___________ 
 * _______#####___###___########___######_________ 
 * ______######___###__###########___######_______ 
 * _____######___####_##############__######______ 
 * ____#######__#####################_#######_____ 
 * ____#######__##############################____ 
 * ___#######__######_#################_#######___ 
 * ___#######__######_######_#########___######___ 
 * ___#######____##__######___######_____######___ 
 * ___#######________######____#####_____#####____ 
 * ____######________#####_____#####_____####_____ 
 * _____#####________####______#####_____###______ 
 * ______#####______;###________###______#________ 
 * ________##_______####________####______________ 
 * 
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-12 13:51:11
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-16 22:19:57
 * @FilePath: /74HC595/Core/Inc/Timer.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef __TIMER_H
#define __TIMER_H

// #include "my_config.h"
#include "step.h"
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
extern node step_queue[STEP_SIZE + 2 * STEP_CHECK_SIZE];
#endif