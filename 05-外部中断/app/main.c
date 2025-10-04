#include "stm32f10x.h"
#include "board.h"
#include "bsp_led.h"
#include "bsp_key.h"

// 全局变量，用于控制中断任务
volatile uint32_t blink_counter = 0;  // 闪烁计数器
volatile uint8_t interrupt_active = 0; // 中断任务激活标志

// 外部中断配置函数
void EXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 将EXTI13线连接到PC13
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);

    // 配置EXTI13线
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  // 下降沿触发（按键按下）
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

// 外部中断服务函数
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        // 只有在中断任务未激活时才响应新的中断
        if(interrupt_active == 0)
        {
            // 启动中断任务
            interrupt_active = 1;
            blink_counter = 0;
        }

        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
}

int main(void)
{
    uint8_t led_idx = 1;  // LED流水灯索引

    // 初始化
    board_init();  // 初始化系统时钟和延时函数
    LED_Init();
    Key_Init();
    EXTI_Config();

    LED_All_Off();

    while(1)
    {
        // 检查是否有中断任务激活
        if(interrupt_active)
        {
            // 中断任务：LED1闪烁5秒（每次闪烁周期500ms，共闪烁10次 = 5秒）
            if(blink_counter < 10)
            {
								LED_All_Off();
                LED_On(1);
                delay_ms(250);
                LED_Off(1);
                delay_ms(250);
                blink_counter++;
            }
            else
            {
                // 5秒结束，恢复流水灯
                interrupt_active = 0;
                blink_counter = 0;
                LED_All_Off();
            }
        }
        else
        {
            // 正常流水灯任务
            LED_All_Off();
            LED_On(led_idx);
            delay_ms(200);

            led_idx++;
            if(led_idx > 5)
                led_idx = 1;
        }
    }
}





