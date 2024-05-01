#include "step.h"
node step_queue[STEP_SIZE + 2 * STEP_CHECK_SIZE];
max_info maxvalue
    [2]; // 0代表上一次的最大值，1代表这一次的最大值，2代表下一次的最大值
void Step_Init() {
    for (int i = 0; i < STEP_SIZE + 2 * STEP_CHECK_SIZE; i++) {
        step_queue[i].current = &step_queue[i];
        step_queue[i].position = 0;
    }
}
void Step_Find_Max() {
    //遍历step_queue数组，找到最大值
    for (int i = 0; i < STEP_SIZE; i++) {
        if (step_queue[i].value > maxvalue[1].value) {
            maxvalue[1].value = step_queue[i].value;
            maxvalue[1].position = step_queue[i].position;
        }
    }
}
void Step_Value_Update() {}
// void walk_step(void)
// {
// 	data_get_once();

//     maxvalue[1]=find_max(a,20);//找到20个历元的滑动窗口中的潜在峰值
//     if((maxvalue[1].value>MIN_G_SPEED)&&(maxvalue[1].value<MAX_G_SPEED))
//     {
//         value_right=1;
//     }
//     if(time_judge(maxvalue[1].position,maxvalue[0].position))
//     {
//         time_right=1;
//     }
//     if(before_after_judge(maxvalue[1].value,before,after))
//     {
//         before_after_right=1;
//     }

// 		time_right=1;//我的算法中未采用时间间隔滤波，因为实际测量可能会出现丢步的情况
//     if(value_right&&time_right&&before_after_right)
//     {
//         WALK_COUNT++;
//         maxvalue[0].value=maxvalue[1].value;//更新上一波峰值，为下一次波峰比对做准备
//         maxvalue[0].position=maxvalue[1].position;
//     }else//如果不符合要求
//     {
//         maxvalue[1].position+=20;//上一个波峰位置加20
//     }

// 		value_right=0;
// 		time_right=0;
// 		before_after_right=0;

// 		walk_distance=WALK_COUNT*0.60;
// }