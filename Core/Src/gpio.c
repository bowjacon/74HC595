#include "gpio.h"
extern volatile uint16_t mscount;
volatile uint8_t ReadyFlag = 0;

void My_GPIO_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    // 推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin =
            (SCK_PIN | RCK_PIN | SDA_PIN | MR_PIN | TRIG_PIN);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // 输入
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
//    GPIO_InitStructure.GPIO_Pin = ECHO_PIN;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, MR_PIN);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line1;//选择中断线
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;//选择EXTI的状态，使能/失能
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;//选择EXTI的模式，中断响应/事件响应
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    //指定EXTI线的触发信号激活边缘，上升沿/下降沿/双边沿（注，库函数中，后面的应该是EXTITrigger_TypeDef）
    EXTI_Init(&EXTI_InitStruct);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;//指定要启用或禁用的IRQ通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//使能或失能
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;//指定NVIC_IRQChannel中指定的IRQ通道的抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//指定NVIC_IRQChannel中指定的IRQ通道的响应优先级
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI1_IRQHandler(void)//中断函数的格式
{
    if (EXTI_GetITStatus(EXTI_Line1))//判断是否为EXTI14进来，返回值为 SET or RESET
    {
        if (GPIO_ReadInputDataBit(GPIOA, ECHO_PIN)) {
            mscount = 0;
            TIM_Cmd(TIM3, ENABLE);
        } else {
            TIM_Cmd(TIM3, DISABLE);
            ReadyFlag = 1;
        }
        EXTI_ClearITPendingBit(EXTI_Line1);//清除中断函数的标志位，否则程序将一直卡在中断函数中
    }
}