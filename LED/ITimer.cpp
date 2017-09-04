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
	itm[number] = this;
	countAdd();
	Icount = number;
	Ifun = fun;

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	switch (number)
	{
	case 1:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		break;
	case 2:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		break;
	case 3:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		break;
	case 4:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		break;
	default:break;
	}
	TIM_TimeBaseStructure.TIM_Period = period*2-1;  
	TIM_TimeBaseStructure.TIM_Prescaler = 36000-1;  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	switch (number)
	{
 	case 1:
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		break;
	case 2:
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		break;
	case 3:
		TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
		break;
	case 4:
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
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
	case 2:
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  
		TIM_ITConfig(TIM4, TIM_IT_Update |  TIM_IT_Trigger, ENABLE);
		TIM_Cmd(TIM4, ENABLE);  
		break;
	case 3:
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  
		TIM_ITConfig(TIM5, TIM_IT_Update |  TIM_IT_Trigger, ENABLE);
		TIM_Cmd(TIM5, ENABLE);  
		break;
	case 4:
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
		TIM_ITConfig(TIM2, TIM_IT_Update |  TIM_IT_Trigger, ENABLE);
		TIM_Cmd(TIM2, ENABLE);  
		break;
	default:break;
	}
}

u8 ITimer::getNumber()
{
	return number;
}
void ITimer::setCount(u8 c)
{
	Icount = c;
}
u8 ITimer::getCount()
{
	return Icount;
}

extern LED led;

extern "C" 	void TIM3_IRQHandler(void)    
{
	u8 n, i;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  
		n = ITimer::getNumber();
		for (i = 0; i < n; i++)
		{
			if (ITimer::itm[i]->getCount() == 1)
			{
				ITimer::itm[i]->Ifun();
				break;
			}
		}
	}
}
extern "C" 	void TIM4_IRQHandler(void)    
{
	u8 n, i;
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  
		n = ITimer::getNumber();
		for (i = 0; i < n; i++)
		{
			if (ITimer::itm[i]->getCount() == 2)
			{
				ITimer::itm[i]->Ifun();
				break;
			}
		}
	}
}
extern "C" 	void TIM5_IRQHandler(void)    
{
	u8 n, i;
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  
		n = ITimer::getNumber();
		for (i = 0; i < n; i++)
		{
			if (ITimer::itm[i]->getCount() == 3)
			{
				ITimer::itm[i]->Ifun();
				break;
			}
		}
	}
}

extern "C" 	void TIM2_IRQHandler(void)    
{
	u8 n, i;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
		n = ITimer::getNumber();
		for (i = 0; i < n; i++)
		{
			if (ITimer::itm[i]->getCount() == 4)
			{
				ITimer::itm[i]->Ifun();
				break;
			}
		}
	}
}