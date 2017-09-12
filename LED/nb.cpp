#include "nb.h"
#include "flash.h"
#include "stmflash.h"
using namespace flash;

NB::NB()
{
}
NB::~NB()
{
}

NB::NB(IUsart iusport, char* iip, char* isocket, char* ipdp, char* iplmn, bool iscramble, u8 isimO)
{
	 IIp=iip;
	 STMFLASH_Write(FLASH_IP, (u16*)(IIp), 12);
	 ISocket=isocket;
	 IPdp=ipdp;
     IPlmn=iplmn; 
	 IScramble = iscramble;
	 ISimOperator = isimO;
	 IUsport = iusport;
}
void NB::connectUdp()
{
	
}