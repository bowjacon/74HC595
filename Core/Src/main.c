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
  // LCD_DisplayString(3,2,"E");
  LCD_WriteCommand(0x80);
  while (1) {
    for (int i = 'A'; i <= 'Z'; i++) {
      LCD_WriteData(i);
      Delay_ms(500);
    }
  }
}
