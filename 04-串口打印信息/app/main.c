#include "stm32f10x.h"
#include "board.h"
#include "uart.h"
int main(void)
{
	board_init();
	uart_Init(115200);
	for(int i=0;i<10;i++){
		printf("串口打印信息测试\r\n");
	}
	
}



