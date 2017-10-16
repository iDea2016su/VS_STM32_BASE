#pragma once
#include "flash.h"
using namespace flash;

u16 STMFLASH_ReadHalfWord(u32 faddr);
void STMFLASH_Write_NoCheck(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);

class IRam
{
public:
	IRam(int size);
	~IRam();
	void store(u32 WriteAddr,string & buf, u16 NumToWrite);
	void read (u32 ReadAddr, u16 *pBuffer, u16 NumToRead);
	void read(u32 ReadAddr, string & buf, u16 NumToRead);
	void write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);
	void write(u32 WriteAddr, string & buf, u16 NumToWrite);
	u8 getStatus();
private:
	u8 IStatus;
	int ISize;
};



