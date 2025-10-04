#include "stm32f10x.h"
#include "board.h"
#include "bsp_led.h"
int main(void)
{
	
	board_init();
	LED_Init();

	while(1){
		for(int i=1;i<=5;i++){
	        LED_On(i);
	        delay_ms(100);
	        LED_Off(i);
	    }
	    for(int i=5;i>=1;i--){
	        LED_On(i);
	        delay_ms(100);
	        LED_Off(i);
	    }
	}
}

