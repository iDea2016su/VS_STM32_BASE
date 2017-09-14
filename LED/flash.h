#pragma once
#include "sys.h"
#include <string>
using namespace std;


namespace flash
{
	const u8   B5  = 0XB5;
	const u8   B8  = 0XB8;
	const u8   TRUE = 1;
	const u8   FALSE = 0;
	
	const u32 FLASH_BASE_ADDR = 0X0800C804;
	const u32 FLASH_CONFIG    = FLASH_BASE_ADDR + 0X800;
	const u32 FLASH_IP        = FLASH_CONFIG+0X800;
	const u32 FLASH_SOCKET    = FLASH_IP + 0X800;
	const u32 FLASH_PDP      = FLASH_SOCKET + 0X800;
	const u32 FLASH_PLMN      = FLASH_PDP + 0X800;
}


namespace atcom
{
	const string AT_CFUN_0 = "AT+CFUN=0\r\n";
	const string AT_NCONFIG_0 = "AT+NCONFIG=CR_0354_0338_SCRAMBLING,TRUE\r\n";
	const string AT_NCONFIG_1 = "AT+NCONFIG=CR_0859_SI_AVOID,TRUE\r\n";
	const string AT_REBOOT = "AT+NRB\r\n";
	const string AT_NBAND = "AT+NBAND=8\r\n";
	const string AT_NBAND_CH = "AT+NBAND=5\r\n";
	const string AT_NBAND_CM = "AT+NBAND=8\r\n";
	const string AT_CGATT_Q = "AT+CGATT?\r\n";
	const string AT_CFUN = "AT+CFUN=1\r\n";
	const string AT_IP_CMNET = "AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n";   
	const string AT_IP_CHNET = "AT+CGDCONT=1,\"IP\",\"CTWAP\"\r\n";   
	const string AT_COPS = "AT+COPS=1,2,\"46000\"\r\n"; 
	const string AT_COPS_CM = "AT+COPS=1,2,\"46000\"\r\n";               
	const string AT_COPS_CH = "AT+COPS=1,2,\"46011\"\r\n";
	const string AT_CGATT = "AT+CGATT=1\r\n";
	const string AT_NSMI = "AT+NSMI=1\r\n";
	const string AT_NNMI = "AT+NNMI=2\r\n";
	const string AT_NSOCR = "AT+NSOCR=DGRAM,17,1234,1\r\n";
	const string AT_NSORF = "AT+NSORF=0,500\r\n";
}