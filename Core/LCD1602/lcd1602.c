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
 * @Date: 2024-04-13 15:09:00
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-25 14:53:45
 * @FilePath: /74HC595/Core/Src/lcd1602.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "lcd1602.h"
#include "delay.h"
#include <math.h>
#include <stdint.h>
/**
 * @description:
 * @return {*}
 */
// void LCD_CheckBusy(void) {
//   GPIO_InitTypeDef GPIO_InitStructure;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//   GPIO_InitStructure.GPIO_Pin = BUSY_PIN;
//   GPIO_Init(HC_PORT, &GPIO_InitStructure);
//   int counter = 0;
//   while (GPIO_ReadInputDataBit(HC_PORT, BUSY_PIN)) {
//     if (counter++ > LCD_TIMEOUT) { //防止死循环
//       return;
//     }
//     EN(Bit_RESET);
//     RS(Bit_RESET);
//     // RW(Bit_SET);
//     Delay_ms(LCD_Delay);
//     EN(Bit_SET);
//     Delay_ms(LCD_Delay);
//   }
//   // GPIO_WriteBit(LCD_SIGNAL_PORT, LCD_EN_PIN, 0);
//   EN(Bit_RESET);
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//   GPIO_Init(HC_PORT, &GPIO_InitStructure);
// }

/**
 * @description:
 * @param {uint8_t} command
 * @return {*}
 */
void LCD_WriteCommand(uint8_t command) {
    DataClear();
    RS(Bit_RESET);
    SendByte(command);
    EN(Bit_SET);
    Delay_ms(LCD_Delay);
    EN(Bit_RESET);
}

void LCD_WriteData(uint8_t data) {
    DataClear();
    RS(Bit_SET);
    SendByte(data);
    EN(Bit_SET);
    Delay_ms(LCD_Delay);
    EN(Bit_RESET);
}

/**
 * @description:
 * @return {*}
 */
void LCD_Init(void) {

    LCD_WriteCommand(0x38); // 8-bit mode, 2 lines, 5x8 dots/character
    LCD_WriteCommand(0x0C); // Display on, cursor off
    LCD_WriteCommand(0x01); // Clear display
    LCD_WriteCommand(0x06); // Entry mode: increment address, no shift
                            // LCD_WriteCommand(0x80);
}

/**
 * @description:
 * @param {uint8_t} x
 * @param {uint8_t} y
 * @param {char} *str
 * @return {*}
 */
void LCD_DisplayString(uint8_t x, uint8_t y, char *str) {
    LCD_WriteCommand(0x40 + x + y * 64);
    while (*str > 0) {
        LCD_WriteData(*str++);
    }
}
/*
 * @description:显示16进制数
 */
void LCD_ShowNum_16(uint8_t x, uint8_t y, int num) {
    LCD_WriteCommand(0x40 + x + y * 64);
    LCD_WriteData('0');
    LCD_WriteData('x');
    for (int i = 4; i >= 0; i -= 4) {
        int temp = (num >> i) & 0x0F;
        if (temp < 10) {
            LCD_WriteData(temp + '0');
        } else {
            LCD_WriteData(temp - 10 + 'A');
        }
    }
}
/*
 * @description:显示10进制数
 */
void LCD_ShowNum_10(uint8_t x, uint8_t y, uint32_t num) {
    LCD_WriteCommand(0x40 + x + y * 64);
    if (num < 0) {
        LCD_WriteData('-');
        num = -num;
    }
    if (num == 0) {
        LCD_WriteData('0');
        return;
    }
    int temp = num;
    int count = 0;
    while (temp) {
        temp /= 10;
        count++;
    }
    char str[count];
    for (int i = count - 1; i >= 0; i--) {
        str[i] = num % 10 + '0';
        num /= 10;
    }
    for (int i = 0; i < count; i++) {
        LCD_WriteData(str[i]);
    }
}
// 显示浮点数，精度为四位小数
void LCD_ShowNum_10_4(uint8_t x, uint8_t y, double num) {
    LCD_WriteCommand(0x40 + x + y * 64);
    if (num < 0) {
        LCD_WriteData('-');
        num = -num;
    }
    int temp = num;
    LCD_ShowNum_10(x, y, temp);
    LCD_WriteData('.');
    temp = (num - temp) * 10000; // 修改这里，使得小数点后有四位
    if (temp < 0) {
        temp = -temp;
    }
    if (temp == 0) {
        for (int i = 0; i < 4; i++) {
            LCD_WriteData('0');
        }
        return;
    }
    char str[4];                   // 修改这里，使得数组长度为4
    for (int i = 3; i >= 0; i--) { // 修改这里，使得循环从3开始
        str[i] = temp % 10 + '0';
        temp /= 10;
    }
    for (int i = 0; i < 4; i++) { // 修改这里，使得循环到4
        LCD_WriteData(str[i]);
    }
}

/**
 * @breif:快速幂，返回a的b次方
 */
uint32_t quickPow(uint32_t a, uint8_t b) {
    uint32_t res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        b >>= 1;
        a = a * a;
    }
    return res;
}
// 显示浮点数，精度为自定义位数
void LCD_ShowNum_10_n(uint8_t x, uint8_t y, double num, uint8_t n) {
    LCD_WriteCommand(0x40 + x + y * 64);
    if (num < 0) {
        LCD_WriteData('-');
        num = -num;
    }
    int temp = num;
    LCD_ShowNum_10(x, y, temp);
    LCD_WriteData('.');
    temp = (num - temp) * quickPow(10, n); // 修改这里，使得小数点后有四位
    if (temp < 0) {
        temp = -temp;
    }
    if (temp == 0) {
        for (int i = 0; i < n; i++) {
            LCD_WriteData('0');
        }
        return;
    }
    char str[n];                       // 修改这里，使得数组长度为4
    for (int i = n - 1; i >= 0; i--) { // 修改这里，使得循环从3开始
        str[i] = temp % 10 + '0';
        temp /= 10;
    }
    for (int i = 0; i < n; i++) { // 修改这里，使得循环到4
        LCD_WriteData(str[i]);
    }
}
