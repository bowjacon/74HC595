#include "step.h"
#include "node.h"
node step_node[Node_N];
void Step_Value_Update() {
    double ax, ay, az, value;
    MPU6050_Get_Accelerometer(&ax, &ay, &az);
    insert_end(sqrt(ax * ax + ay * ay + az * az), step_node);
    //  value==sqrt(ax*ax+ay*ay+az*az);
    // MPU6050_Get_Accelerometer(&ax, &ay, &az);
}
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