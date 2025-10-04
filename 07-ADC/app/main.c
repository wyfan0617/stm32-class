#include "stm32f10x.h"
#include "board.h"
#include "bsp_adc.h"

uint16_t adc_value = 0;

int main(void)
{

	board_init();

	ADC_Config(); // ADC1通道5初始化


	while(1)
	{
		adc_value =4095-Get_Adc_Average(30);

		delay_ms(1000);
	}

}


