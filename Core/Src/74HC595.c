/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-17 22:11:59
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-18 12:10:28
 * @FilePath: /74HC595/Core/Src/74HC595.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%A
 */
#include "74HC595.h"
#include "stm32f10x_gpio.h"

/**
 * @brief 74HC595初始化
 */
void H595Init(void) {
  SCK(0);
  RCK(0);
  SDA(0);
}
void DataClear(void) {
    // GPIO_ResetBits(GPIOA, HC_MR );
    MR(Bit_RESET);
    __NOP();
    __NOP();
    // GPIO_SetBits(GPIOA, HC_MR );
    MR(Bit_SET);
}
/**
 * @brief 发送一个字节
 */
void SendByte(uint8_t byte) {
  for (int i = 0; i < 8; i++) {
    SCK(0);
    SDA(byte & 0x80);
    SCK(1);
    byte <<= 1;
    SCK(0);
  }
  RCK(1);
  __NOP();
  __NOP();
  RCK(0);
}
