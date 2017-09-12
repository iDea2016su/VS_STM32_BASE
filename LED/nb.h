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
	NB(IUsart iusport, char* iip, char* isocket, char* ipdp, char* iplmn, bool iscramble, u8 isimO);
	void connectUdp();
private:
	char* IIp;
	char* ISocket;
	char* IPdp;
	char* IPlmn; 
	char* IImei;
	u8 IScramble;
	u8 ISimOperator;
	IUsart IUsport;
};

