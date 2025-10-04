#include "uart.h"
/*
函数名称：uart_Init
函数功能：初始化串口
函数参数：uint32_t __Baud 波特率
函数返回值：无
作者: wang
*/
void uart_Init(uint32_t __Baud)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIOA和USART1的时钟，以及AFIO（复用功能）时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);

    // 初始化GPIO结构体，并配置TX引脚
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;         // TX引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 重新初始化GPIO结构体，并配置RX引脚
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;            // RX引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure; // 定义配置串口的结构体变量

    // 开启USART1的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // 将USART1寄存器重置为默认值
    USART_DeInit(USART1);

    // 初始化USART结构体
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = __Baud;                                    // 设置波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     // 字节长度为8bit
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          // 1个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             // 没有校验位
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 // 收发模式
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无流控
    USART_Init(USART1, &USART_InitStructure);                                       // 初始化USART1

    USART_Cmd(USART1, ENABLE); // 开启串口1
}
/*
函数名称：usart_send_data
函数功能：发送一个字节的数据
函数参数：uint8_t ucch
函数返回值：无
作者: wang
*/
void usart_send_data(uint8_t ucch)
{
    USART_SendData(USART1, (uint8_t)ucch);
        
        // 等待发送数据缓冲区标志置位
    while( RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE) ){} 
}
/*
函数名称：usart_send_String
函数功能：发送一个字符串
函数参数：uint8_t *ucstr
函数返回值：无
作者: wang
*/
void usart_send_String(uint8_t *ucstr)
{   
      while(ucstr && *ucstr)  // 地址为空或者值为空跳出   
      {     
        usart_send_data(*ucstr++);    
      }
}

//重定义fputc函数  实现printf函数

#if !defined(__MICROLIB)
//不使用微库的话就需要添加下面的函数
#if (__ARMCLIB_VERSION <= 6000000)
//如果编译器是AC5  就定义下面这个结构体
struct __FILE
{
        int handle;
};
#endif

FILE __stdout;

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
        x = x;
}
#endif

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);
        
	while( RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE) ){}
        
    return ch;
}
