#pragma once
#include <string>
#include "IUsart.h"
using namespace std;
#define  B5   0XB5
#define  B8   0XB8
class NB
{
public:
	NB();
	~NB();
	NB(string ipp,string soc,string pd,string pl,u8 scr,u8 simO);
	void connect(void);
private:
	
	string ip;
	string socket;
	string pdp;
	string plmn; 
	string imei;
	u8 scramble;
	u8 simOperator;
	
	IUsart usport;
};

