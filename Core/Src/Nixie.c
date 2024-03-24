#include "Nixie.h"

enum Rge_Num {
    Reg_1 = 0x1A, Reg_2 = 0x1C, Reg_3 = 0x10, Reg_4 = 0x08
};

// 第一位数码管的指令为0x1A,第二位数码管的指令为0X1C,第三位数码管的指令为0X10,
// 第四位数码管的指令为0x08,前两个数码管为共阳极,后两个数码管为共阴极
void SendNum(uint8_t num, uint8_t type) {
    DataClear();
    switch (type) {
        case 1: {
            SendByte(Anode_List[num]);
            SendByte(Reg_1);
            break;
        }
        case 2: {
            SendByte(Anode_List[num]);
            SendByte(Reg_2);
            break;
        }
        case 3: {
            SendByte(Cathode_List[num]);
            SendByte(Reg_3);
            break;
        }
        case 4: {
            SendByte(Cathode_List[num]);
            SendByte(Reg_4);
            break;
        }
        default:
            break;
    }
    Delay_us(1000);
}

/**
 * @brief: 在四位数码管上显示数值
 * @digit: 要显示的数值
 * @note: 前两位为共阳极部分,后两位为共阴极部分,先发送指令,再发送数据
 */
void DisplayNixie(uint8_t *digit) {
    SendNum(digit[1], 2);
    SendNum(digit[2], 3);
    SendNum(digit[3], 4);
    SendNum(digit[0], 1); //最后一位数码管需要最后显示,否则亮度会降低
}