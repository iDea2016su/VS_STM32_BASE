#include "INb.h"
#include "flash.h"
#include "IRam.h"
#include "IUsart.h"
#include "uart.h"

using namespace flash;
using namespace atcom;
using namespace std;
extern IRam ram;

INb::INb()
{
}
INb::~INb()
{
}

INb::INb(USART_TypeDef* usartx, string iip, string isocket, string ipdp, string iplmn, const u8 iscramble, const u8 isimO)
	: IUsport(usartx, 9600, 0, USART_StopBits_1, USART_Parity_No, USART_WordLength_8b)
{
	IIp = iip;
	ram.store(FLASH_IP,IIp,20);
	ISocket = isocket;
	ram.store(FLASH_SOCKET,ISocket,6);
	IPdp = ipdp;
	ram.store(FLASH_PDP,IPdp,6);
	IPlmn = iplmn; 
	ram.store(FLASH_PLMN,IPlmn,6); 
	IScramble = iscramble;
	ISimOperator = isimO;
	IUsport = IUsart(usartx, 9600, 0, USART_StopBits_1, USART_Parity_No, USART_WordLength_8b);
}
void INb::connectUdp()
{
	IUsport.sendStrwithRep(AT_CFUN_0, "OK", 10);
	if (IScramble == 1)
	{
		IUsport.sendStrwithRep(AT_NCONFIG_0, "OK", 10);
		IUsport.sendStrwithRep(AT_NCONFIG_1, "OK", 10);
	}
	else
	{
		IUsport.sendStrwithRep("AT+NCONFIG=CR_0354_0338_SCRAMBLING,FALSE\r\n", "OK", 10);
		IUsport.sendStrwithRep("AT+NCONFIG=CR_0859_SI_AVOID,FALSE\r\n", "OK", 10);
	}
	IUsport.sendStrwithRep(AT_REBOOT, "OK", 10);   
	IUsport.sendStrwithRep(AT_CFUN, "OK", 10);
	if (ISimOperator == 0XB8)
	{
		IUsport.sendStrwithRep(AT_NBAND_CM, "OK", 10);
		IUsport.sendStrwithRep(AT_IP_CMNET, "OK", 10);
		IUsport.sendStrwithRep(AT_COPS_CM, "OK", 10);
	}
	else
	{
		IUsport.sendStrwithRep(AT_NBAND_CH, "OK", 10);
		IUsport.sendStrwithRep(AT_IP_CHNET, "OK", 10);
		IUsport.sendStrwithRep(AT_COPS_CH, "OK", 10);
	}
	IUsport.sendStrwithRep(AT_CGATT, "OK", 10);
	IUsport.sendStrwithRep(AT_CGATT_Q, "CGATT:1", 10);
	IUsport.sendStrwithRep(AT_NSOCR, "OK", 10);
	//IUsport.sendStrwithRep(AT_IMEI_Q, IMEI, 5000);
}

string strToHexStr(string charstr)
{
	string str;
	int len = charstr.length();
	str.resize(len * 2);
	for (int i=0,j=0;i<len;i++,j+=2)
	{
		str[j] = charstr[i] / 16;
		str[j+1] = charstr[i] % 16;
	}
	for (int i = 0;i < 2*len; i++)
	{
		if (str[i] < 10) str[i] += '0';
		else str[i] += '0' + 7;
	}
	return str;
}
void INb::udpStrMsg(string Msg)
{
	string msg="AT+NSOST=0,";
	string len=to_string(Msg.length());
	string hexstr = strToHexStr(Msg);
	msg.append(IIp);
	msg.append(",");
	msg.append(ISocket);
	msg.append(",");
	msg.append(len);
	msg.append(",");
	msg.append(hexstr);
	msg.append("\r\n");
	print(msg.c_str());
}
