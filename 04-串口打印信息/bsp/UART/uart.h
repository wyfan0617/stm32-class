#ifndef __UART_H__
#define __UART_H__
#include "stm32f10x.h"
#include "stdio.h"

 /* 串口缓冲区的数据长度 */
#define USART1_RECEIVE_LENGTH  1024


 //外部可调用函数的声明
void uart_Init(uint32_t __Baud);
void usart_send_data(uint8_t ucch);
void usart_send_String(uint8_t *ucstr);
#endif // 