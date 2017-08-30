#include <stdio.h>
#include "usart.h"
#pragma import(__use_no_semihosting)   
#pragma import(__use_no_semihosting_swi)
struct __FILE
{
	int handle;
};
/* FILE is typedef¡¯d in stdio.h. */
FILE __stdout;
void  _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{      
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
	USART_SendData(USART1, (uint8_t)ch);   
	return ch;
}