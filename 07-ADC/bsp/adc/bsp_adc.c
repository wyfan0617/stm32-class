#include "bsp_adc.h"
#include "board.h"

/*
 * 函 数 名 称：ADC_Config
 * 函 数 功 能：ADC配置
 * 传 入 参 数：无
 * 函 数 返 回：无
 * 作者       ：wang
*/
void ADC_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 					// 配置结构体

	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE); 	// 使能时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;    	   	// 模拟输入
	GPIO_Init(GPIOA, &GPIO_InitStructure); 					// 初始化GPIO


    ADC_InitTypeDef ADC_InitStructure;

    // 打开ADC时钟
    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_ADC1, ENABLE );

    // ADC 模式配置
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;				// 只使用一个ADC，独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE ;					// 禁止扫描模式，单通道不需要扫描
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;				// 连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// 软件触发转换
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;			// 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;							// 转换通道1个

    // 初始化ADC
    ADC_Init(ADC1, &ADC_InitStructure);

    // 配置ADC时钟PCLK2的6分频，即12MHz
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    // 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);

    // 开启ADC ，并开始转换
    ADC_Cmd(ADC1, ENABLE);

    // 初始化ADC 校准寄存器
    ADC_ResetCalibration(ADC1);
    // 等待校准寄存器初始化完成
    while (ADC_GetResetCalibrationStatus(ADC1));

    // ADC开始校准
    ADC_StartCalibration(ADC1);
    // 等待校准完成
    while (ADC_GetCalibrationStatus(ADC1));

    // 使用软件触发ADC转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}

/*
 * 函 数 名 称：Get_ADC_Value
 * 函 数 功 能：获取ADC采样值
 * 传 入 参 数：无
 * 函 数 返 回：采样值
 * 作者       ：wang
*/
uint32_t Get_ADC_Value(void)
{
    uint32_t adc_value = 0;

    // 等待转换结束
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));

    // 读取采样值
    adc_value = ADC_GetConversionValue(ADC1);

    // 返回采样值
    return adc_value;
}

/*
 * 函 数 名 称：Get_Adc_Average
 * 函 数 功 能：获取ADC采样值的平均值
 * 传 入 参 数：times 采样次数
 * 函 数 返 回：平均值
 * 作者       ：wang    
*/
uint16_t Get_Adc_Average(uint8_t times)
{
	uint32_t value = 0;
	uint8_t t;

	for(t=0; t<times; t++)
	{
		value += Get_ADC_Value();
		delay_ms(5);
	}
	return value/times;
}
