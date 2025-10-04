#include "bsp_key.h"

/*
函数名称：Key_Init
函数功能：按键初始化
函数参数：无
函数返回值：无
作者：wang
*/
void Key_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = KEY_PIN_1 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEYPORT, &GPIO_InitStructure);
}


/*
函数名称：Key_Scan
函数功能：按键扫描
函数参数：无
函数返回值：1-按下，0-未按下
作者：wang
*/
uint8_t Key_Scan(void){
    if(GPIO_ReadInputDataBit(KEYPORT, KEY_PIN_1 ) == 0){
        while(GPIO_ReadInputDataBit(KEYPORT, KEY_PIN_1 ) == 0);
        return 1;
    }
    return 0;
}
