#include "oled.h"
#include "oledfont.h"
/*
函数名称：IIC_WriteByte
函数功能：IIC写入一个字节
函数参数：addr: 设备地址
          data: 要写入的数据
函数返回值：无
作者：wang
*/
 void IIC_WriteByte(uint8_t addr, uint8_t data)
{
    // 发送起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    // 发送设备地址
    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    // 发送数据
    I2C_SendData(I2C1, data);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    // 发送停止信号
    I2C_GenerateSTOP(I2C1, ENABLE);
}

/*
函数名称：OLED_WriteCmd
函数功能：OLED写命令
函数参数：cmd: 要写入的命令
函数返回值：无
作者：wang
*/
 void OLED_WriteCmd(uint8_t cmd)
{
    // 发送起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    // 发送设备地址
    I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    // 发送控制字节(命令)
    I2C_SendData(I2C1, OLED_CMD);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    // 发送命令
    I2C_SendData(I2C1, cmd);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    // 发送停止信号
    I2C_GenerateSTOP(I2C1, ENABLE);
}

/*
函数名称：OLED_WriteData
函数功能：OLED写数据
函数参数：data: 要写入的数据
函数返回值：无
作者：wang
*/
 void OLED_WriteData(uint8_t data)
{
    // 发送起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    // 发送设备地址
    I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    // 发送控制字节(数据)
    I2C_SendData(I2C1, OLED_DATA);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    // 发送数据
    I2C_SendData(I2C1, data);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    // 发送停止信号
    I2C_GenerateSTOP(I2C1, ENABLE);
}

/*
函数名称：OLED_SetPos
函数功能：设置OLED显示位置
函数参数：x: 列地址
          y: 页地址
函数返回值：无
作者：wang
*/

void OLED_SetPos(uint8_t x, uint8_t y)
{
    OLED_WriteCmd(0xB0 + y);
    OLED_WriteCmd(((x & 0xF0) >> 4) | 0x10);
    OLED_WriteCmd(x & 0x0F);
}

/*
函数名称：OLED_Init
函数功能：OLED初始化
函数参数：无
函数返回值：无
作者：wang
*/
void OLED_Init(void)
{
    // IO引脚初始化
    // 对IIC1引脚重映射
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);

    // 对 PB8, PB9 进行初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // IIC1初始化
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 400000;  // 400kHz
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);

    // 延时等待OLED上电稳定
    for(uint32_t i = 0; i < 1000000; i++);

    // SSD1306初始化序列
    OLED_WriteCmd(0xAE); // 关闭显示
    OLED_WriteCmd(0x00); // 设置列地址低位
    OLED_WriteCmd(0x10); // 设置列地址高位
    OLED_WriteCmd(0x40); // 设置起始行地址
    OLED_WriteCmd(0xB0); // 设置页地址
    OLED_WriteCmd(0x81); // 对比度设置
    OLED_WriteCmd(0xFF); // 对比度值
    OLED_WriteCmd(0xA1); // 段重定义设置(A0正常/A1左右反置)
    OLED_WriteCmd(0xA6); // 显示方式(A6正常/A7反显)
    OLED_WriteCmd(0xA8); // 设置驱动路数
    OLED_WriteCmd(0x3F); // 64duty
    OLED_WriteCmd(0xC8); // 重映射模式(C0上下正常/C8上下反置)
    OLED_WriteCmd(0xD3); // 设置显示偏移
    OLED_WriteCmd(0x00); // 无偏移
    OLED_WriteCmd(0xD5); // 设置时钟分频因子
    OLED_WriteCmd(0x80); // 分频因子
    OLED_WriteCmd(0xD8); // 区域颜色模式设置
    OLED_WriteCmd(0x05);
    OLED_WriteCmd(0xD9); // 设置预充电周期
    OLED_WriteCmd(0xF1);
    OLED_WriteCmd(0xDA); // 设置com硬件引脚配置
    OLED_WriteCmd(0x12);
    OLED_WriteCmd(0xDB); // 设置VCOMH电压倍率
    OLED_WriteCmd(0x30);
    OLED_WriteCmd(0x8D); // 电荷泵设置
    OLED_WriteCmd(0x14); // 开启电荷泵
    OLED_WriteCmd(0xAF); // 开启显示

    OLED_Clear();
}

/*
函数名称：OLED_Clear
函数功能：清屏
函数参数：无
函数返回值：无
作者：wang
*/
void OLED_Clear(void)
{
    uint8_t i, j;
    for(i = 0; i < 8; i++)
    {
        OLED_SetPos(0, i);
        for(j = 0; j < 128; j++)
        {
            OLED_WriteData(0x00);
        }
    }
}

/*
函数名称：OLED_Display_On
函数功能：开显示
函数参数：无
函数返回值：无
作者：wang
*/
void OLED_Display_On(void)
{
    OLED_WriteCmd(0x8D);
    OLED_WriteCmd(0x14);
    OLED_WriteCmd(0xAF);
}

/*
函数名称：OLED_Display_Off
函数功能：关显示
函数参数：无
函数返回值：无
作者：wang
*/
void OLED_Display_Off(void)
{
    OLED_WriteCmd(0x8D);
    OLED_WriteCmd(0x10);
    OLED_WriteCmd(0xAE);
}

/*
函数名称：OLED_ShowChar
函数功能：显示字符
函数参数：x: 列地址
          y: 页地址
          chr: 要显示的字符
          size: 字符大小
函数返回值：无
作者：wang
*/
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size)
{
    uint8_t c = chr - ' '; // 得到偏移后的值

    if(x > OLED_WIDTH - 1)
    {
        x = 0;
        y = y + 2;
    }

    if(size == 16)
    {
        OLED_SetPos(x, y);
        for(uint8_t i = 0; i < 8; i++)
        {
            OLED_WriteData(asc2_1608[c][i]);
        }
        OLED_SetPos(x, y + 1);
        for(uint8_t i = 0; i < 8; i++)
        {
            OLED_WriteData(asc2_1608[c][i + 8]);
        }
    }
}

/*
函数名称：OLED_ShowString
函数功能：显示字符串
函数参数：x: 列地址
          y: 页地址
          str: 要显示的字符串
          size: 字符大小
函数返回值：无
作者：wang
*/
void OLED_ShowString(uint8_t x, uint8_t y, char *str, uint8_t size)
{
    uint8_t j = 0;
    while(str[j] != '\0')
    {
        OLED_ShowChar(x, y, str[j], size);
        x += 8;
        if(x > 120)
        {
            x = 0;
            y += 2;
        }
        j++;
    }
}

