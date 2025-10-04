#include "stm32f10x.h"
#include "board.h"
#include "bsp_led.h"

uint8_t flag = 0;

void TIM3_Init(void);

int main(void)
{

	board_init();
	LED_Init();

	TIM3_Init();

	while(1)
	{
	
	}

}

void TIM3_Init(void)
{
	// 使能TIM3时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* 配置定时器参数 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1; // TIMER3时钟频率72MHz

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // 使能TIM3配置

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; // 选择TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;

	NVIC_Init(&NVIC_InitStructure); // 使能NVIC配置

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 使能TIM3中断

	TIM_Cmd(TIM3, ENABLE);  //使能TIM3

}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{ // {}中为中断处理

		// 反转LED灯
		if( flag == 0 )
		{
			LED_On(1);
			flag = 1;
		}
		else
		{
			LED_Off(1);
			flag = 0;
		}
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}


