/*
 * _______________#########_______________________
 * ______________############_____________________
 * ______________#############____________________
 * _____________##__###########___________________
 * ____________###__######_#####__________________
 * ____________###_#######___####_________________
 * ___________###__##########_####________________
 * __________####__###########_####_______________
 * ________#####___###########__#####_____________
 * _______######___###_########___#####___________
 * _______#####___###___########___######_________
 * ______######___###__###########___######_______
 * _____######___####_##############__######______
 * ____#######__#####################_#######_____
 * ____#######__##############################____
 * ___#######__######_#################_#######___
 * ___#######__######_######_#########___######___
 * ___#######____##__######___######_____######___
 * ___#######________######____#####_____#####____
 * ____######________#####_____#####_____####_____
 * _____#####________####______#####_____###______
 * ______#####______;###________###______#________
 * ________##_______####________####______________
 *
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-18 15:17:21
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-28 14:50:53
 * @FilePath: /74HC595/Core/Src/main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

/*
 * @Author: bowjacon 2772408947@qq.com
 * @Date: 2024-04-12 13:51:11
 * @LastEditors: bowjacon 2772408947@qq.com
 * @LastEditTime: 2024-04-18 14:55:57
 * @FilePath: /74HC595/Core/Src/main.c
//  * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// #include "stm32c8t6.h"
#include "main.h"
#include "delay.h"
#include <stdint.h>
#include <stdio.h>

// #define PI 3.1415926
int main(void) {
    My_GPIO_Init();
    LCD_Init();
    double temperture = 0;

    // mpu_dmp_init();
    double pitch, roll, yaw;
    uint8_t id;
    unsigned long step = 1;
    // Mpu6050_Handle.accel.div = ACCEL_REG_0 << ACCEL_2G;
    MPU6050_Init();
    // MPU_Set_Accel_Fsr(Mpu6050_Handle.accel);
    // MPU6050_DMP_Init();
    // double sin_a = arm_sin_f32(PI / 6);
    // M_I2C_Reicive_Byte(MPU6050_WHO_AM_I, &id);
    // LCD_ShowNum_16(0, 1, id);
    // LCD_ShowNum_10_n(0, 1, sin_a, 4);
    // dmp_set_pedometer_step_count(1);
    // LCD_ShowNum_10(0, 1, Mpu6050_Handle.accel.div);
    double ax, ay, az;
    uint8_t buffer[1024] = "hello";
    uint8_t buffer1[1024] = "world";
    Serial_Init();
    // RetargetInit(USART1);
    float32_t num[3] = {1, 2, 3};
    float32_t *p = num;
    float nums[3];
    // arm_rms_f32(p, 3, nums);
    // USART_SendString(USART1, "Hello World\n");
    // Get_Double(12.3555, buffer);
    u_printf("%.4f\n", 12.3555);
    // printf("%d\n",a);
    // printf("%s\n", buffer);
    //将nums转换为字符串
    // for(int i = 0; i < 3; i++) {
    //     printf("%d\n", nums[i]);
    // }
    // short ax_s, ay_s, az_s;
    while (1) {
        // MPU6050_Get_Accelerometer(&ax, &ay, &az);
        // ax = ax_s >> (ACCEL_REG_0 - Mpu6050_Handle.accel_value);
        // ay = ay_s >> (ACCEL_REG_0 - Mpu6050_Handle.accel_value);
        // az = az_s >> (ACCEL_REG_0 - Mpu6050_Handle.accel_value);
        // MPU6050_Read_Temperature(&temperture);
        // LCD_ShowNum_10_n(0, 2, temperture, 2);
        // LCD_ShowNum_10_4(0, 1, sin_a);
        // arm_rms_f32(&num, 3, nums);
        // scanf("%s", buffer);
        // printf("%s\n", buffer);
        // Delay_ms(500);
        // LCD_ShowNum_10(0, 1, ax);
        // LCD_ShowNum_10(0, 1, Mpu6050_Handle.accel.div);
        // MPU6050_DMP_Get_Data(&pitch, &roll, &yaw);
        // LCD_ShowNum_10_n(0, 1, pitch, 2);
        // LCD_ShowNum_10_n(6, 1, roll, 2);
        // LCD_ShowNum_10_n(11, 1, yaw, 2);
        // if (step > 100) {
        //     step = 1;
        //     dmp_set_pedometer_step_count(1);
        // }
        // if (dmp_get_pedometer_step_count(&step)==-1) {
        //     LCD_DisplayString(0, 1, "Error");
        // } else {
        //     LCD_ShowNum_10(0, 1, step);
        // }
        Delay_ms(500);
    }
}
