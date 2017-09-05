#include "sys.h"
#include "delay.h"
#include "led.h"
#include <IUsart.h>
#include <ITimer.h>

LED led(PortB, 10);
IUsart uart = IUsart(USART1, 9600, 0, USART_StopBits_1, USART_Parity_No, USART_WordLength_8b);
void f()
{
	delay_ms(100); 
	led.off();
		
	delay_ms(100);
	led.on();
}
void tf()
{
	uart.sendStr((char *)uart.getBuf());
	uart.clear();
}
int main()
{	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    ITimer t(500,2,tf);
	ITimer t1(1000, 3, f);
	t.start();
	t1.start();
	while (1)
	{
	 
		delay_ms(1000); 
		
//		Usart1_print(__FILE__);
	    //printf("%shhhh\r\n", __FILE__);
	}
}	