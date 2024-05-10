
#include "usart.h"
#include "stdlib.h"
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define DEBUG_USARTx USART1
uint8_t buff[Str_Size];
uint8_t rx_buffer[Str_Size];
p_str p[Str_Size];

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
double str_to_double(char *str) {
    double num = 0;
    int i = 0;
    // 判断是否为负数
    if (str[0] == '-') {
        i = 1;
    }
    while (str[i] != '\0') {
        if (str[i] == '.') {
            i++;
            double temp = 0.1;
            while (str[i] != '\0') {
                num += (str[i] - '0') * temp;
                temp /= 10;
                i++;
            }
            break;
        }
        num = num * 10 + str[i] - '0';
        i++;
    }
    if (str[0] == '-') {
        num = -num;
    }
    return num;
}
void *convertBase(uint8_t in, uint8_t out, int num, char *outputNum) {
    // Step 1: Convert the input number to decimal
    int decimalNum = 0;
    int tempNum = num;
    int base1pow = 0;
    while (tempNum > 0) {
        int lastDigit = tempNum % 10;
        tempNum = tempNum / 10;
        decimalNum += lastDigit * quickPow(in, base1pow);
        base1pow++;
    }

    // Step 2: Convert the decimal number to the output base
    int index = 0;
    while (decimalNum > 0) {
        int digit = decimalNum % out;
        outputNum[index++] = (digit > 9) ? (digit - 10) + 'A' : digit + '0';
        decimalNum = decimalNum / out;
    }
    outputNum[index] = '\0';

    // Reverse the outputNum string to get the final result
    for (int i = 0; i < index / 2; i++) {
        char temp = outputNum[i];
        outputNum[i] = outputNum[index - i - 1];
        outputNum[index - i - 1] = temp;
    }
    return outputNum;
}

static void vDMA_Config(DMA_Channel_TypeDef *channel, u32 perBaseAddr,
                        u32 memBaseAddr, u16 memSize, u8 perDir, u16 priority) {
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // Enable DMA1 clock

    DMA_DeInit(channel); // Reset MDA channel
    DMA_InitStructure.DMA_PeripheralBaseAddr =
        perBaseAddr; // Peripheral base address
    DMA_InitStructure.DMA_MemoryBaseAddr = memBaseAddr; // Memory base address
    DMA_InitStructure.DMA_DIR = perDir;         // DMA transmit direction
    DMA_InitStructure.DMA_BufferSize = memSize; // MDA Channel buffer size
    DMA_InitStructure.DMA_PeripheralInc =
        DMA_PeripheralInc_Disable; // Peripheral address incremented
    DMA_InitStructure.DMA_MemoryInc =
        DMA_MemoryInc_Enable; // Memory address incremented
    DMA_InitStructure.DMA_PeripheralDataSize =
        DMA_PeripheralDataSize_Byte; // Peripheral data width
    DMA_InitStructure.DMA_MemoryDataSize =
        DMA_MemoryDataSize_Byte;                  // Memory data width
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; // DMAy Channe mode
    DMA_InitStructure.DMA_Priority = priority;    // MDA Channel priority
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  // Memory-to-memory transfer
    DMA_Init(channel, &DMA_InitStructure);        // DMA init

    DMA_Cmd(channel, ENABLE); // Enable DMA channel
}
void vDMA_Start_Channel_Transfer(DMA_Channel_TypeDef *channel, u16 lenDat) {
    DMA_Cmd(channel, DISABLE);               // Disable DMA channel
    DMA_SetCurrDataCounter(channel, lenDat); // Set data count
    DMA_Cmd(channel, ENABLE);                // Enable DMA channel
}
void vIRQ_NVIC_Config(IRQn_Type perIRQ, u8 prePrio, u8 subPrio) {
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = perIRQ; // IRQ Channel
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =
        prePrio; // Preemption Priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =
        subPrio;                                    // SubPriority Priority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Enable IRQ Channe
    NVIC_Init(&NVIC_InitStructure);                 // Init NVIC
}
static void vUSART1_ITConfig(u8 prePrio, u8 subPrio) {
    USART_Cmd(USART1, DISABLE);                      // Disable USART1
    vIRQ_NVIC_Config(USART1_IRQn, prePrio, subPrio); // Config priority
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);   // Enables Idle interrupt

    // Clear Idle flag
    USART_GetFlagStatus(USART1, USART_FLAG_IDLE); // Get Idle flag
    USART_ReceiveData(USART1);                    // Get receive data

    USART_Cmd(USART1, ENABLE); // Enable USART1
}

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
    vDMA_Config(DMA1_Channel5, (u32)(&USART1->DR), (u32)rx_buffer, Str_Size,
                DMA_DIR_PeripheralSRC, DMA_Priority_High);
    vUSART1_ITConfig(3, 0);
    USART_DMACmd(USART1, USART_DMAReq_Rx | USART_DMAReq_Tx,
                 ENABLE); // Enable DMA receive/transmit request
    p_str_init();
}

void Usart_ReceiveByte(uint8_t *ch) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        ;
    *ch = USART_ReceiveData(USART1);
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
            case 'l': {
                ++fmt;
                if (*fmt == 'f') {
                    double f = va_arg(ap, double);
                    Get_Double(f, buff, n);
                    USART_SendString(buff);
                }
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
        case 'c': /* 按照字符输出 */
        {
            /** 但是，下一个参数是char吗*/
            /*  可以这样取出吗？ */
            int c = va_arg(ap, int);
            Usart_SendByte(c);
        } break;
        case 'x': {
            int i = va_arg(ap, int);
            TO_HEX(i, buff);
            USART_SendString(buff);
        }
        case 'l': {
            ++fmt;
            if (*fmt == 'f') {
                double f = va_arg(ap, double);
                Get_Double(f, buff, 6);
                USART_SendString(buff);
            }
        } break;
        }
    }
    va_end(ap);
}
#include <stdarg.h>
#include <stdio.h>
volatile uint8_t Serial_RxData;
volatile uint8_t Serial_RxFlag;
volatile uint8_t Serial_BusyFlag = 0;
/**********************************************************************************************************************************************
 * 函数名 : USART1_IRQHandler
 * 描  述 : USART1中断服务
 **********************************************************************************************************************************************/
void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        USART_ClearFlag(USART1, USART_FLAG_RXNE);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }

    if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) // Idle interrupt set
    {
        USART_GetITStatus(USART1, USART_IT_IDLE); // Get idle interrupt state
        USART_ReceiveData(USART1);                // Get USARTx received data
        vDMA_Start_Channel_Transfer(DMA1_Channel5, Str_Size); // Startk
        // transfer
        // u_printf("%s", rx_buffer);
        Serial_RxFlag = 1;
    }
}

// void USART1_IRQHandler(void) {
//     if (Serial_BusyFlag == 1)
//         return;
//     if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
//         Serial_RxData = USART_ReceiveData(USART1);
//         Serial_RxFlag = 1;
//         USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//         // u_printf("%c", Serial_RxData);
//     }
// }
// void DMA1_Channel1_IRQHandler(void) {
//     // 检查是否DMA1_Channel1传输完成
//     if (DMA_GetITStatus(DMA1_IT_TC1)) {
//         DMA_ClearITPendingBit(DMA1_IT_TC1); // 清除中断标志位
//         Serial_RxFlag = 1;
//         // 传输完成，处理数据
//     }
// }

void u_scanf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    // char input[100];
    // USART接受数据，遇到回车结束
    // for (int i = 0;; i++) {
    //     // Usart_ReceiveByte(&input[i]);
    while (Serial_RxFlag == 0)
        ;
    // u_printf("%s", rx_buffer);
    Serial_RxFlag = 0;

    while (*fmt != '\0') {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
            case 'd': {
                int *ip = va_arg(ap, int *);
                *ip = str_to_int(rx_buffer);
            } break;
            case 'l': {
                ++fmt;
                if (*fmt == 'f') {
                    double *fp = va_arg(ap, double *);
                    *fp = str_to_double(rx_buffer);
                }
            } break;
            case 's': {
                char *sp = va_arg(ap, char *);
                strcpy(sp, rx_buffer);
            } break;
            }
        }
        fmt++;
    }
    // Serial_BusyFlag = 0;
    // va_end(ap);
}
// /* !defined( __CROSSWORKS_ARM ) && defined( __GNUC__ ) */
// #ifdef __GNUC__
// #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
// #else
// #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
// #endif

// PUTCHAR_PROTOTYPE {
//     Usart_SendByte((uint8_t)ch);
//     return ch;
// }

// #ifdef __GNUC__
// #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
// #define GETCHAR_PROTOTYPE int __io_getchar(void)
// #else
// #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
// #define GETCHAR_PROTOTYPE int fgetc(FILE *f)
// #endif

// PUTCHAR_PROTOTYPE {
//     Usart_SendByte((uint8_t)ch);
//     return ch;
// }

// GETCHAR_PROTOTYPE {
//     uint8_t ch = 0;

//     /* Clear the Overrun flag just before receiving the first character */
//     //   __HAL_UART_CLEAR_OREFLAG(&huart?);
//     //清除接收溢出标志位
//     // USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//     Usart_ReceiveByte(&ch);
//     return ch;
// }