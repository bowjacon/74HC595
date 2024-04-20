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
 * @Date: 2024-04-18 15:17:21
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-18 19:54:01
 * @FilePath: /74HC595/Core/Inc/74HC595.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-17 22:12:10
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-17 22:29:08
 * @FilePath: /74HC595/Core/Inc/74HC595.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AEd

 */
#ifndef _74HC595_H
#define _74HC595_H
#include "gpio.h"
#define SCK(x) GPIO_WriteBit(HC_PORT, HC_SHCP, x)
#define RCK(x) GPIO_WriteBit(HC_PORT, HC_STCP, x)
#define SDA(x) GPIO_WriteBit(GPIOA, HC_DS, x)
#define MR(x) GPIO_WriteBit(GPIOA, HC_MR, x)
void SendByte(uint8_t byte);
void DataClear(void);
#endif