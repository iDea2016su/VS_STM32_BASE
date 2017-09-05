#pragma once
#include "sys.h"
#include <IUsart.h>
#include <stm32f10x_tim.h>

class ITimer
{
public:
	ITimer();
	ITimer(u16 period, u8 priporty, void(*fun)());
	~ITimer();
	void countAdd();
	void countSub();
	void start();
	void stop();
	static u8 getNumber();
	static ITimer** itm;
	void(*Ifun)();
	void setCount(u8 c);
	u8 getCount();
	u8 Ipriporty;
	u16 Iperiod;
private:
	static u8 number;
	u8 Icount;
	bool status;
};