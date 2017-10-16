#pragma once
#include <string>
#include "IUsart.h"
using namespace std;

class INb
{
public:
	INb();
	~INb();
	INb(USART_TypeDef* usartx, string iip, string isocket, string ipdp, string iplmn, const u8 iscramble, const u8 isimO);
	void connectUdp();
	void connectCoap();
	void udpStrMsg(string Msg);
	void udpStrMsg(string MsgStart, string Msg, string MsgEnd);
	void coapStrMsg(string Msg);
	void coapStrMsg(string MsgStart, string Msg, string MsgEnd);
	string receiveUdp();
	string receiveCoap();
	void setIp(string ip);
	void setSocket(string socket);
private:
	string IIp;
	string ISocket;
	string IPdp;
	string IPlmn; 
	string IImei;
	u8 IScramble;
	u8 ISimOperator;
	IUsart  IUsport;
};

