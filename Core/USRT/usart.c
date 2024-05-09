
#include "usart.h"
#include <stdarg.h>
#include <stdint.h>
uint8_t buff[256];
p_str p[Str_Size];

/**
 * @breif:快速幂，返回a的b次方
 */
static uint32_t quickPow(uint32_t a, uint8_t b) {
    uint32_t res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        b >>= 1;
        a = a * a;
    }
    return res;
}
void p_str_init() {
    for (int i = 0; i < Str_Size; i++) {
        p[i].last = (i == 0) ? NULL : &p[i - 1];
        p[i].next = (i == Str_Size - 1) ? NULL : &p[i + 1];
    }
    p[0].p_place = p_end;
}

p_str *p_str_start() {

    for (int i = 0; i < Str_Size; i++) {
        if (p[i].last == NULL) {
            return &p[i];
        }
    }
    return NULL;
}
p_str *p_str_end() {
    p_str *str_begin = p_str_start();
    while (str_begin->p_place != p_end) {
        str_begin = str_begin->next;
    }
    return str_begin;
}

void p_str_insert(uint8_t ch) {
    p_str *p = p_str_end();
    p->ch = ch;
    p->p_place = p_middle;
    p->next->p_place = p_end;
}
void p_str_insert_int(int num) {
    if (num < 0) {
        p_str_insert('-');
        num = -num;
    }
    if (num == 0) {
        p_str_insert('0');
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
        p_str_insert(str[i]);
    }
}
void p_str_insert_double(double num, int n) {
    int temp = num;
    p_str_insert_int(temp);
    p_str_insert('.');
    temp = (num - temp) * quickPow(10, n); // 修改这里，使得小数点后有四位
    if (temp < 0) {
        temp = -temp;
    }
    if (temp == 0) {
        for (int i = 0; i < n; i++) {
            p_str_insert('0');
        }
        return;
    }
    char str[n];                       // 修改这里，使得数组长度为4
    for (int i = n - 1; i >= 0; i--) { // 修改这里，使得循环从3开始
        str[i] = temp % 10 + '0';
        temp /= 10;
    }
    for (int i = 0; i < n; i++) { // 修改这里，使得循环到4
        p_str_insert(str[i]);
    }
}
void p_str_to_str(char *str) {
    p_str *p = p_str_start();
    int i = 0;
    while (p->p_place != p_end) {
        str[i++] = p->ch;
        p = p->next;
    }
    str[i] = '\0';
}
int str_to_int(char *str) {
    int num = 0;
    int i = 0;
    // 判断是否为负数
    if (str[0] == '-') {
        i = 1;
    }
    while (str[i] != '\0') {
        num = num * 10 + str[i] - '0';
        i++;
    }
    if (str[0] == '-') {
        num = -num;
    }
    return num;
}

/**
 * @brief  USART GPIO 配置,工作参数配置
 * @param  无
 * @retval 无
 */
void Serial_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
    p_str_init();
}
void Usart_SendByte(uint8_t ch) {
    USART_SendData(USART1, ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ;
}
void USART_SendString(char *str) {
    unsigned int i = 0;

    while (*(str + i) != '\0') {
        Usart_SendByte(*(str + i));
        i++;
    }
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        ;
}
void u_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt); /* 用最后一个具有参数的类型的参数去初始化ap */
    for (; *fmt; ++fmt) {
        if (*fmt != '%') {
            Usart_SendByte(*fmt);
            continue;
        }
        ++fmt;
        if (*fmt == '.') {
            ++fmt;
            int n = *fmt - '0';
            ++fmt;
            switch (*fmt) {
            case 'f': {
                float f = va_arg(ap, double);
                Get_Double(f, buff, n);
                USART_SendString(buff);
            } break;
            }
            continue;
        }
        switch (*fmt) {
        case '%':
            Usart_SendByte('%');
            break;
        case 'd': {
            int i = va_arg(ap, int);
            Get_Int(i, buff);
            USART_SendString(buff);
        } break;
        case 's': {
            char *s = va_arg(ap, char *);
            USART_SendString(s);
        } break;
        case 'f': {
            float f = va_arg(ap, double);
            Get_Double(f, buff, 6);
            USART_SendString(buff);
        } break;
        }
    }
    va_end(ap);
}
