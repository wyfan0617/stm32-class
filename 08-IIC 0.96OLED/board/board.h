#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f10x.h"

void board_init(void);

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

void delay_1us(uint32_t us);
void delay_1ms(uint32_t ms);





#endif
