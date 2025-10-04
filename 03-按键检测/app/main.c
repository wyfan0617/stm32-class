#include "stm32f10x.h"
#include "board.h"
#include "bsp_led.h"
#include "bsp_key.h"
uint8_t ledState = 0;  // LED初始状态为关闭
int main(void)
{

	board_init();
	LED_Init();
	Key_Init();
	while(1){
		if(Key_Scan()){  // 检测到按键按下
			ledState = !ledState;  // 反转LED状态
			if(ledState){
				LED_On(1);  // 打开LED
			} else {
				LED_Off(1); // 关闭LED
			}
			while(Key_Scan()); // 等待按键释放
		}
		delay_ms(10); // 短暂延时，避免过于频繁的检测
}

}


