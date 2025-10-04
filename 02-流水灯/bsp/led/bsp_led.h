#ifndef __BSP_LED_H
#define __BSP_LED_H 

#include "stm32f10x.h"
#include "stdio.h"
#include <stdbool.h>
#define LEDPORT          GPIOA
#define LED_PIN_1        GPIO_Pin_3
#define LED_PIN_2        GPIO_Pin_4
#define LED_PIN_3        GPIO_Pin_5
#define LED_PIN_4        GPIO_Pin_6
#define LED_PIN_5        GPIO_Pin_7 

void LED_Init(void);
void LED_Control(uint8_t idx, bool onoff);
void LED_On(uint8_t idx);
void LED_Off(uint8_t idx);
void LED_All_Off(void);


#endif 

