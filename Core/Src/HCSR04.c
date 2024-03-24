#include "HCSR04.h"

volatile uint16_t mscount;
extern volatile uint8_t GetFlag;
extern volatile uint16_t Interval;

void HCSR04_Trigger(void) {
    GPIO_SetBits(GPIOA, TRIG_PIN);   // Set the TRIG_PIN high
    Delay_us(15);                    // Wait for 10us
    GPIO_ResetBits(GPIOA, TRIG_PIN); // Set the TRIG_PIN low
}

void HCSR04_GetValue(float *dist) {
    mscount = 0;
    HCSR04_Trigger();
    while (!GPIO_ReadInputDataBit(GPIOA, ECHO_PIN));
    TIM_Cmd(TIM3, ENABLE);
    while (GPIO_ReadInputDataBit(GPIOA, ECHO_PIN));
    TIM_Cmd(TIM3, DISABLE);
    uint16_t Time = TIM_GetCounter(TIM3);
    TIM3->CNT = 0;
    *dist = (float) ((Time + mscount * 1000) / 58.0);
}


void Value_Processing(uint8_t *dist) {
    static float Data[Process_Count];
    static float mean;
    static float Sum;
    static float sd;
    static float Test_sum;
    static uint16_t Step;
    float value;
    if (!GetFlag) return;
    else {
        HCSR04_GetValue(&value);
        Data[Step] = value;
        Sum += value;
        Test_sum += value;
        Step++;
        if (Step == Short_Count) {
            if (Test_sum / Short_Count > (mean + 3 * sd) || Test_sum / Short_Count < (mean - 3 * sd)) {
                Interval = Short_Distance_Interval;
            } else {
                Interval = Long_Distance_Interval;
            }
            Test_sum = 0;
        } else if (Step == Process_Count) {
            mean = Sum / Process_Count;
            Data_Processing(Data, &Sum, &Step, dist, &sd, mean);
            //当采样次数达到指定次数是开始处理数据
        }
        GetFlag = 0;
    }
}

void Data_Processing(float *Data, float *Sum, uint16_t *step, uint8_t *dist, float *sd, float mean) {
    uint16_t count = 0;
    uint8_t i;
    float distance;
    uint16_t n = *step;
    for (i = 0; i < n; i++) {
        *sd += (Data[i] - mean) * (Data[i] - mean);
    }
    *sd = sqrt(*sd / (n - 1));
    float sd_value = *sd;
    for (i = 0; i < n; i++) {
        if (Data[i] > (mean + 3 * sd_value) || Data[i] < (mean - 3 * sd_value)) {
            continue;
        }
        Data[count++] = Data[i];
    }
    if (count != n) {
        mean = 0;
        for (i = 0; i < count; i++) {
            mean += Data[i];
        }
        distance = mean / count;
    } else {
        distance = mean;
    }
    ValueToNixie(distance, dist);
    *step = 0;
    *Sum = 0;
}

void ValueToNixie(float digit, uint8_t * dist) {
    uint8_t integer_temp = (uint8_t) digit;
    uint8_t decimalP_temp = (uint8_t) ((digit - integer_temp) * 100);
    dist[3] = (integer_temp % 100) / 10;
    dist[2] = (integer_temp % 100) % 10;
    dist[1] = decimalP_temp / 10;
    dist[0] = decimalP_temp % 10;
}