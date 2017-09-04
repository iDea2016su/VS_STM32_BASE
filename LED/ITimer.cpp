#include "ITimer.h"
#include "delay.h"
#include "led.h"

extern const uint8_t IPriority[12][2];

u8 ITimer::number = 0;
ITimer** ITimer::itm = new ITimer*[5];

ITimer::ITimer()
{
}


ITimer::~ITimer()
{
}


void ITimer::countAdd()
{
	number++;
}


void ITimer::countSub()
{
	number--;
}

ITimer::ITimer(u16 period, 
	u8 pri, 
	void(*fun)())
{	
	//ITimer * iTimer = itm + number;
	itm[number] = this;
	countAdd();
	Ifun = fun;

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	switch (number)
	{
	case 1:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		break;
	default:break;
	}
	TIM_TimeBaseStructure.TIM_Period = period;  
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	switch (number)
	{
 	case 1:
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		break;
	default:break;
	}
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = IPriority[pri][0];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = IPriority[pri][1]; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);   
	switch (number)
	{
	case 1:
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  
		TIM_ITConfig(TIM3, TIM_IT_Update |  TIM_IT_Trigger, ENABLE);
		TIM_Cmd(TIM3, ENABLE);  
		break;
	default:break;
	}
}

u8 ITimer::getNumber()
{
	return number;
}

extern LED led;
u8 n;
extern "C" void TIM3_IRQHandler(void)    
{
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  
		
		n = ITimer::getNumber();
    	ITimer::itm[n - 1]->Ifun();
	}
}