#include "74hc595.h"

/*
 * @brief 74HC595初始化
 */
void H595Init(void) {
    SCK(0);
    RCK(0);
    SDA(0);
}

void DataClear(void) {
    GPIO_ResetBits(GPIOA, MR_PIN);
    __NOP();
    __NOP();
    GPIO_SetBits(GPIOA, MR_PIN);
}

/*
 * @brief 发送一个字节
 */
void SendByte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        SCK(0);
        SDA(byte & 0x80);
        SCK(1);
        byte <<= 1;
        // __NOP();
        // __NOP();
        SCK(0);
    }
    RCK(1);
    __NOP();
    __NOP();
    // Delay_us(1);
    RCK(0);
}
