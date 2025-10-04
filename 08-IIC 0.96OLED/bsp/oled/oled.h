#ifndef __OLED_H
#define __OLED_H
#include "stm32f10x.h"

// SSD1306 I2C地址
#define OLED_ADDRESS    0x78

// SSD1306命令定义
#define OLED_CMD        0x00
#define OLED_DATA       0x40

// OLED参数
#define OLED_WIDTH      128
#define OLED_HEIGHT     64

// 函数声明
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size);
void OLED_ShowString(uint8_t x, uint8_t y, char *str, uint8_t size);

#endif //__OLED_H

