#include "bsp_led.h"

/*
函数名称：led_init
函数功能：LED初始化
函数参数：无
函数返回值：无
作者：wang
*/
void LED_Init(void){
    //开启GPIOA时钟 其挂载在APB2总线上
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //定义GPIO初始化结构 
    GPIO_InitTypeDef GPIO_InitStructure;

    //结构体初始化 如果不初始化 结构体成员会是随机值
    GPIO_StructInit(&GPIO_InitStructure); 

    //配置GPIO
    GPIO_InitStructure.GPIO_Pin = LED_PIN_1 | LED_PIN_2 | LED_PIN_3 | LED_PIN_4 | LED_PIN_5;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度50MHz

    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化GPIOA    

    LED_All_Off(); 
}

/*
函数名称：LED_Control
函数功能：LED控制
函数参数：idx:LED索引 onoff:开关状态
函数返回值：无
作者：wang
*/
void LED_Control(uint8_t idx, bool onoff)
{
	switch (idx)
	{
	case 1:
		GPIO_WriteBit(LEDPORT, LED_PIN_1 , onoff ? Bit_SET : Bit_RESET);
		break;
	case 2:
		GPIO_WriteBit(LEDPORT, LED_PIN_2 , onoff ? Bit_SET : Bit_RESET);
		break;
	case 3:
		GPIO_WriteBit(LEDPORT, LED_PIN_3 , onoff ? Bit_SET : Bit_RESET);
		break;
	case 4:
		GPIO_WriteBit(LEDPORT, LED_PIN_4 , onoff ? Bit_SET : Bit_RESET);
		break;
	case 5:
		GPIO_WriteBit(LEDPORT, LED_PIN_5 , onoff ? Bit_SET : Bit_RESET);
		break;
	default:
		break;
	}
}
/*
函数名称：LED_On
函数功能：LED打开
函数参数：idx:LED索引
函数返回值：无
作者：wang
*/
void LED_On(uint8_t idx)
{
    LED_Control(idx, true);
}

/*
函数名称：LED_Off
函数功能：LED关闭
函数参数：idx:LED索引
函数返回值：无
作者：wang
*/
void LED_Off(uint8_t idx)
{
    LED_Control(idx, false);
}
/*
函数名称：LED_All_Off
函数功能：LED全关
函数参数：无
函数返回值：无
作者：wang
*/
void LED_All_Off(void)
{
    LED_Control(1, false);
    LED_Control(2, false);  
    LED_Control(3, false);
    LED_Control(4, false);
    LED_Control(5, false);
}

