#pragma  once
#include "stdio.h"	
#include "sys.h" 
#include "stm32f10x_usart.h"
	 
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; 
extern u16 USART_RX_STA;         		 
 
extern void uart_init(u32 bound);
extern void Usart1_print(char *str);

