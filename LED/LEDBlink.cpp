#include "sys.h"
#include "string.h"
#include "delay.h"
#include "led.h"
#include <IUsart.h>
#include <ITimer.h>
#include "flash.h"
#include "usart.h"
#include "IRam.h"


using namespace flash;

LED led(PortB, 10);
IUsart uart = IUsart(USART1, 9600, 0, USART_StopBits_1, USART_Parity_No, USART_WordLength_8b);
string str = "ooooo\r\n";
void f()
{
	delay_ms(100); 
	led.off();
		
	delay_ms(100);
	led.on();
}
void tf()
{
	//uart.sendStr((char *)uart.getBuf());
	//uart.clear();
}
int main()
{	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	IRam ram= IRam(256);
   //s ITimer t(500,2,tf);
	ITimer t1(1000, 3, f);
//	t.start();
	t1.start();
	while (1)
	{
		delay_ms(1000);
		ram.store(FLASH_IP,(u16*)(str.data()),10);
		uart.sendStr(str.data());
		uart.sendChar(ram.getStatus()+'0');
		str = (char*)uart.getBuf();
	}
}	