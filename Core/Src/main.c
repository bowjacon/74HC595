#include "main.h"

//extern volatile uint8_t GetFlag;
extern volatile uint8_t RunFlag;

int main(void) {
//    float distance = 0;
    My_GPIO_Init();
    H595Init();
    Timer_Init();
    HCSR04_Init();
    uint8_t dist[5];
    while (1) {
//        TRIG();
        Value_Processing(dist);
        DisplayNixie(dist);
    }
}