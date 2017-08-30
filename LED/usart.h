#pragma  once
#include "stdio.h"	
#include "sys.h" 
#include "stm32f10x_usart.h"
	 
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; 
extern u16 USART_RX_STA;         		 
 
extern void uart_init(u32 bound);
extern void Usart1_print(char *str);

