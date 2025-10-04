#include "stm32f10x.h"
#include "board.h"
#include "bsp_led.h"
int main(void)
{
	
	board_init();
	LED_Init();

	LED_On(1);

}



