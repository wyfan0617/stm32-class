#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"

void ADC_Config(void);
uint32_t Get_ADC_Value(void);
uint16_t Get_Adc_Average(uint8_t times);

#endif
