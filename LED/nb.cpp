#include "nb.h"

NB::NB()
{
}
NB::~NB()
{
}
NB::NB(string ipp, string soc, string pd, string pl, u8 scr, u8 simO)
{
	ip = ipp;
	socket = soc;
	pdp = pd;
	plmn = pl;
	scramble = scr;
	simOperator = simO;
}
void NB::connect()
{
	
}