#include "main.h"

//extern volatile uint8_t GetFlag;
extern volatile uint8_t RunFlag;
int main(void) {
//    float distance = 0;
    My_GPIO_Init();
    H595Init();
    Timer_Init();
    HCSR04_Init();
    uint8_t dist[4];
    while (1) {
        Value_Processing(dist);
        if(!RunFlag)DisplayNixie(dist);
    }
}