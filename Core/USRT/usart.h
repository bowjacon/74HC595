#include "stm32f10x.h"
#include "string.h"
#include <stdint.h>
#ifndef __USART_H
#define __USART_H

#define Str_Size 256
typedef enum { p_middle, p_end } p_str_place;
typedef struct p_str_struct {
    struct p_str_struct *next;
    struct p_str_struct *last;
    uint8_t ch;
    p_str_place p_place;
} p_str;

void Serial_Init(void);
p_str *p_str_start();
void p_str_insert(uint8_t ch);
void p_str_to_str(char *str);
void p_str_insert_int(int num);
void p_str_insert_double(double num, int n);
p_str *p_str_end();
#define clear_p_str                                                            \
    do {                                                                       \
        p_str_end()->p_place = p_middle;                                       \
        p_str_start()->p_place = p_end;                                        \
    } while (0)

#define Get_Int(a, b)                                                          \
    do {                                                                       \
        clear_p_str;                                                           \
        p_str_insert_int(a);                                                   \
        p_str_to_str(b);                                                       \
    } while (0)

#define Get_Double(a, b, n)                                                    \
    do {                                                                       \
        clear_p_str;                                                           \
        p_str_insert_double(a, n);                                             \
        p_str_to_str(b);                                                       \
    } while (0)
void USART_SendString(char *str);
void u_printf(const char *fmt, ...);
int str_to_int(char *str);
#endif