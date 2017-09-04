#include "sys.h"
#include "delay.h"
#include "led.h"
#include <IUsart.h>
#include <ITimer.h>

void TIM3_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  

	TIM_TimeBaseStructure.TIM_Period = arr;  
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
	TIM_ITConfig(  
		TIM3, 
		TIM_IT_Update,
		ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);   

	TIM_Cmd(TIM3, ENABLE);   
							 
}
LED led(PortB, 10);


void tf()
{
	 delay_ms(100); 
	 led.off();
		
	 delay_ms(100);
	 led.on();
	
}
int main()
{	

	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	IUsart uart = IUsart(USART1, 9600, 2, USART_StopBits_1, USART_Parity_No, USART_WordLength_8b);
    ITimer t(5000,2,tf);
	while (1)
	{
	 
		delay_ms(1000); 
		//led.on();
		uart.sendStr("hello\r\n");
//		Usart1_print(__FILE__);
	    //printf("%shhhh\r\n", __FILE__);
	}
}	