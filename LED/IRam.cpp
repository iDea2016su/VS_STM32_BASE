#include "IRam.h"
#include "flash.h"
#include "IUsart.h"

using namespace flash;

#if (defined STM32F10X_HD) || (defined STM32F10X_MD)  
#define STM_SECTOR_SIZE 2048
#else 
#define STM_SECTOR_SIZE	1024			  
#endif 
#define STM32_FLASH_BASE 0x08000000
static u16 STMFLASH_BUF[STM_SECTOR_SIZE / 2]; 
const u8 flag[4] = { 0, 250, 50, 0 };
extern IUsart uart;
IRam::IRam(int size)
{
	ISize = size;
	u8 cnofig[4] = { 0, 0, 0, 0 };
	int temp;
	read(FLASH_CONFIG, (u16*)cnofig, 4);
	temp = cnofig[0] + cnofig[1] + cnofig[2] + cnofig[3];
	if (temp != 300) 
	{
		write(FLASH_CONFIG, (u16*)flag, 4);
		IStatus = 0;
	}
	else
	{
		IStatus = 1;
	}
}


IRam::~IRam()
{
}


void IRam::store(u32 WriteAddr, 
	string &buf, 
	u16 NumToWrite)
{
	u16 *pBuffer = (u16 *)buf.c_str();
	u16 *Buffer = new u16[20];
	if (!IStatus)
	{
		write(WriteAddr, pBuffer, NumToWrite);
	}
	read(WriteAddr, Buffer, NumToWrite);
	buf = (char*)Buffer;
}


void IRam::write(u32 WriteAddr, 
	u16 *pBuffer, 
	u16 NumToWrite)
{
	
		
	u32 secpos; 	   //扇区地址
	u16 secoff; 	   //扇区内偏移地址(16位字计算)
	u16 secremain;  //扇区内剩余地址(16位字计算)	   
 	u16 i;    
	u32 offaddr;    //去掉0X08000000后的地址
	if(WriteAddr < STM32_FLASH_BASE || (WriteAddr >= (STM32_FLASH_BASE + 1024*ISize)))return; //非法地址
	FLASH_Unlock(); 						//解锁
	offaddr = WriteAddr - STM32_FLASH_BASE; 		//实际偏移地址.
	secpos = offaddr / STM_SECTOR_SIZE; 			//扇区地址  0~127 for STM32F103RBT6
	secoff = (offaddr % STM_SECTOR_SIZE) / 2; 		//在扇区内的偏移(2个字节为基本单位.)
	secremain = STM_SECTOR_SIZE / 2 - secoff; 		//扇区剩余空间大小   
	if(NumToWrite <= secremain)secremain = NumToWrite; //不大于该扇区范围
	while (1) 
	{	
		read(secpos*STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2); //读出整个扇区的内容
		for (i = 0; i < secremain; i++)//校验数据
		{
			if (STMFLASH_BUF[secoff + i] != 0XFFFF)break;//需要擦除  	  
		}
		if (i < secremain)//需要擦除
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE + STM32_FLASH_BASE); //擦除这个扇区
			for (i = 0; i < secremain; i++)//复制
			{
				STMFLASH_BUF[i + secoff] = pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2); //写入整个扇区  
		}else STMFLASH_Write_NoCheck(WriteAddr, pBuffer, secremain); //写已经擦除了的,直接写入扇区剩余区间. 				   
		if (NumToWrite == secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++; 				//扇区地址增1
			secoff = 0; 				//偏移位置为0 	 
		   	pBuffer += secremain;   	//指针偏移
			WriteAddr += secremain; 	//写地址偏移	   
		   	NumToWrite -= secremain; 	//字节(16位)数递减
			if(NumToWrite > (STM_SECTOR_SIZE / 2))secremain = STM_SECTOR_SIZE / 2; //下一个扇区还是写不完
			else secremain = NumToWrite; //下一个扇区可以写完了
		}	 
	}
	;	
	FLASH_Lock(); //上锁
}
void IRam::read(u32 ReadAddr, u16 *pBuffer, u16 NumToRead)
{
	u16 i;
	for (i = 0; i < NumToRead; i++)
	{
		pBuffer[i] = STMFLASH_ReadHalfWord(ReadAddr); //读取2个字节.
		ReadAddr += 2; //偏移2个字节.	
	}
}

u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}
void STMFLASH_Write_NoCheck(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)   
{ 			 		   
	u16 i;
	for (i = 0; i < NumToWrite; i++)
	{
		FLASH_ProgramHalfWord(WriteAddr, pBuffer[i]);
		WriteAddr += 2; 
	}  
} 

u8 IRam::getStatus()
{
	return IStatus;
}


void IRam::write(u32 WriteAddr, string & buf, u16 NumToWrite)
{
	u16 *pBuffer = (u16 *)buf.c_str();
	u16 *clear = new u16[NumToWrite];
	for (int i = 0; i < NumToWrite; i++)
	{
		clear[i] = 0;
	}
	write(WriteAddr, clear, NumToWrite);	
	write(WriteAddr, pBuffer, NumToWrite);
	delete [] clear;
}


void IRam::read(u32 ReadAddr, string & buf, u16 NumToRead)
{
	u16 *Buffer = new u16[NumToRead];
	read(ReadAddr, Buffer, NumToRead);
	buf = (char*)Buffer;
}
