#include "ITimer.h"

extern const uint8_t IPriority[12][2];

u8 ITimer::number = 0;
ITimer* ITimer::itm = new ITimer[5];

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
	u8 pri) 
	//void(*fun)(int))
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = period * 2 - 1; //ÉèÖÃÔÚÏÂÒ»¸ö¸üÐÂÊÂ¼þ×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 ×î´óÊ±¼äÎª6s
	TIM_TimeBaseStructure.TIM_Prescaler = (36000 - 1); //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ýÊýµÄÔ¤·ÖÆµÖµ  10KhzµÄ¼ÆÊýÆµÂÊ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //¸ù¾ÝTIM_TimeBaseInitStructÖÐÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊýµ¥Î»
 
 
		/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3ÖÐ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //¸ù¾ÝNVIC_InitStructÖÐÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯ÍâÉèNVIC¼Ä´æÆ÷

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //Çå³ýTIMxµÄÖÐ¶Ï´ý´¦ÀíÎ»:TIM ÖÐ¶ÏÔ´ 
	TIM_ITConfig(  //Ê¹ÄÜ»òÕßÊ§ÄÜÖ¸¶¨µÄTIMÖÐ¶Ï
    TIM3, //TIM2
		TIM_IT_Update |  //TIM ÖÐ¶ÏÔ´
		TIM_IT_Trigger,   //TIM ´¥·¢ÖÐ¶ÏÔ´ 
		ENABLE );
	//TIM_Cmd(TIM3, ENABLE);  //Ê¹ÄÜTIMxÍâÉè
}

u8 ITimer::getNumber()
{
	return number;
}

//extern IUsart port;
