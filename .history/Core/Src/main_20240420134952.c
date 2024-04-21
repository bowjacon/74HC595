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
 * @LastEditTime: 2024-04-20 13:31:22
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
#include "lcd1602.h"
int main(void) {
  My_GPIO_Init();
  LCD_Init();
  LCD_DisplayString(3,2,"ni hao");
  // LCD_WriteCommand(0x80);
  // LCD_DisplayString(0,1,"NI HAO");
  while (1) {
    // for (char  i = 0; i <= 26; i++) {
    //   LCD_DisplayString(0, 2,"a"+i);
    //   Delay_ms(500);
    // }
    // LCD_DisplayString(0, 1, "NI HAO");
    // Delay_ms(500);
    // LCD_DisplayString(0, 1, "HELLO");
    // Delay_ms(500);
  }
}
