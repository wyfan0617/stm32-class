#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"
#define KEYPORT          GPIOC
#define KEY_PIN_1        GPIO_Pin_13

void Key_Init(void);
uint8_t Key_Scan(void);

#endif

