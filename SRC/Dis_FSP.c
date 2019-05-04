#include "../include/DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "../include/DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "../include/Dis_FSP.h"   // DSP2833x Examples Include File
#include "../include/Dis_VI.h"   // DSP2833x Examples Include File


unsigned char  SEGData[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//1-9
unsigned char  SEGDataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef}; //有小数点只用于地址0xc1


void Init_FSPLED_GPIO(void)
{
	   EALLOW;
	   GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;
	   GpioDataRegs.GPBSET.bit.GPIO50 = 1;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO50= 1;

	   GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;
	   GpioDataRegs.GPBSET.bit.GPIO51 = 1;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;

	   GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;
	   GpioDataRegs.GPBSET.bit.GPIO52 = 1;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO52= 1;

	   GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;
	   GpioDataRegs.GPBSET.bit.GPIO53 = 1;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1;
	   EDIS;
}
void TM1637_F_START(void)
{
	CLK_F_1;
	DIO_F_1;
	DELAY_US(150);
	DIO_F_0;
	DELAY_US(150);
	CLK_F_0;
	DELAY_US(150);
}
void TM1637_F_STOP(void)
{
	CLK_F_0;
	DELAY_US(150);
	DIO_F_0;
	DELAY_US(150);
	CLK_F_1;
	DELAY_US(150);
	DIO_F_1;
	DELAY_US(150);
}
void TM1637_F_WriteBIT(unsigned char mBit)
{
	CLK_F_0;
	DELAY_US(150);
	if(mBit)
		DIO_F_1;
	else
		DIO_F_0;
	DELAY_US(150);
	CLK_F_1;
	DELAY_US(150);
}
void TM1637_F_WriteByte(unsigned char mByte)
{
	Uint16 loop=0;
	for(loop=0;loop<8;loop++)
	{
		TM1637_F_WriteBIT((mByte>>loop)&0x01);
	}
	CLK_F_0;
	DELAY_US(150);
	DIO_F_1;
	DELAY_US(150);
	CLK_F_1;
	DELAY_US(150);
}
void TM1637_F_WriteData(unsigned char addr,unsigned char mData)
{
	TM1637_F_START();
	TM1637_F_WriteByte(addr);
	TM1637_F_WriteByte(mData);
	TM1637_F_STOP();
}
void TM1637_F_WriteCammand(unsigned char mData)
{
	TM1637_F_START();
	TM1637_F_WriteByte(mData);
	TM1637_F_STOP();
}
void F_Display(Uint16 data)
{
	TM1637_F_WriteCammand(0x44);
	TM1637_F_WriteData(0xC0,SEGData[data/1000]);
	TM1637_F_WriteData(0xC1,SEGData[data%1000/100]);
	TM1637_F_WriteData(0xC2,SEGData[data%100/10]);
	TM1637_F_WriteData(0xC3,SEGData[data%10]);
	TM1637_F_WriteCammand(0x8a);
}


void TM1637_A_START(void)
{
	CLK_A_1;
	DIO_A_1;
	DELAY_US(150);
	DIO_A_0;
	DELAY_US(150);
	CLK_A_0;
	DELAY_US(150);
}
void TM1637_A_STOP(void)
{
	CLK_A_0;
	DELAY_US(150);
	DIO_A_0;
	DELAY_US(150);
	CLK_A_1;
	DELAY_US(150);
	DIO_A_1;
	DELAY_US(150);
}
void TM1637_A_WriteBIT(unsigned char mBit)
{
	CLK_A_0;
	DELAY_US(150);
	if(mBit)
		DIO_A_1;
	else
		DIO_A_0;
	DELAY_US(150);
	CLK_A_1;
	DELAY_US(150);
}
void TM1637_A_WriteByte(unsigned char mByte)
{
	Uint16 loop=0;
	for(loop=0;loop<8;loop++)
	{
		TM1637_A_WriteBIT((mByte>>loop)&0x01);
	}
	CLK_A_0;
	DELAY_US(150);
	DIO_A_1;
	DELAY_US(150);
	CLK_A_1;
	DELAY_US(150);
}
void TM1637_A_WriteData(unsigned char addr,unsigned char mData)
{
	TM1637_A_START();
	TM1637_A_WriteByte(addr);
	TM1637_A_WriteByte(mData);
	TM1637_A_STOP();
}
void TM1637_A_WriteCammand(unsigned char mData)
{
	TM1637_A_START();
	TM1637_A_WriteByte(mData);
	TM1637_A_STOP();
}
void A_Display(Uint16 data)
{
	TM1637_A_WriteCammand(0x44);
	TM1637_A_WriteData(0xC0,SEGData[data/1000]);
	TM1637_A_WriteData(0xC1,SEGData[data%1000/100]);
	TM1637_A_WriteData(0xC2,SEGData[data%100/10]);
	TM1637_A_WriteData(0xC3,SEGData[data%10]);
	TM1637_A_WriteCammand(0x8a);
}
