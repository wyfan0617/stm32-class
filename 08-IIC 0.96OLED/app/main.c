#include "stm32f10x.h"
#include "board.h"
#include "oled.h"

int main(void)
{
	// 初始化OLED
	OLED_Init();

	// 显示Hello World
	OLED_ShowString(0, 0, "Hello World", 16);
	OLED_ShowString(0, 2, "XJ-Robot", 16);
	while(1)
	{

	}

}

