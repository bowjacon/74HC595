#include "Timer.h"
#include "stm32f10x.h" // Device header

volatile uint8_t GetFlag;
extern volatile uint16_t mscount;
volatile uint16_t  Interval= Long_Distance_Interval;
void Timer_Init(void) {
    TIM3_Init(999, 71, 2, 1, DISABLE);
    TIM2_Init(999, 71, 2, 2, ENABLE);
}

void Set_Timer(TIM_TypeDef *TIMx, uint16_t period, uint16_t prescaler,
               uint8_t IRQChannel, uint8_t preemptionPriority,
               uint8_t subPriority) {
    TIM_InternalClockConfig(TIMx); // TIMx使用内部时钟
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode =
            TIM_CounterMode_Up; // 计数模式，此处为向上计数
    TIM_TimeBaseInitStructure.TIM_Period = period;       // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = prescaler; // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter =
            0; // 高级计时器特有，重复计数
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStructure);

    TIM_ClearFlag(TIMx, TIM_FLAG_Update);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE); // 使能中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = IRQChannel; // 中断通道选择
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority; // 优先级，同上
    NVIC_Init(&NVIC_InitStructure);
    // TIM_Cmd(TIMx, DISABLE); // 打开定时器
}

void TIM2_Init(uint16_t period, uint16_t prescaler, uint8_t preemptionPriority,
               uint8_t subPriority, FunctionalState NewState) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,
                           ENABLE); // 选择APB1总线下的定时器Timer2
    Set_Timer(TIM2, period, prescaler, TIM2_IRQn, preemptionPriority,
              subPriority); // 1ms定时间隔
    if (NewState == ENABLE)
        TIM_Cmd(TIM2, ENABLE); // 打开定时器
    else {
        TIM_Cmd(TIM2, DISABLE); // 关闭定时器
    }
}

void TIM3_Init(uint16_t period, uint16_t prescaler, uint8_t preemptionPriority,
               uint8_t subPriority, FunctionalState NewState) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,
                           ENABLE); // 选择APB1总线下的定时器Timer3
    Set_Timer(TIM3, period, prescaler, TIM3_IRQn, preemptionPriority,
              subPriority); // 1ms定时间隔
    if (NewState == ENABLE)
        TIM_Cmd(TIM3, ENABLE); // 打开定时器
    else {
        TIM_Cmd(TIM3, DISABLE); // 关闭定时器
    }
}

void TIM3_IRQHandler() //得到HC-SR04的超声波回波时间
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        mscount++;
    }
}

void TIM2_IRQHandler() // 用于定时获取超声波测距数据
{
    static uint16_t count;
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        count++;
        if (count >=  Interval ) {
            GetFlag = 1;
            count = 0;
        }
    }
}
