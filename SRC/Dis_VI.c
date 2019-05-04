#include "../include/DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "../include/DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "../include/Dis_VI.h"   // DSP2833x Examples Include File

void Init_VILED_GPIO(void)
{
	   EALLOW;
	   GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;
	   GpioDataRegs.GPASET.bit.GPIO8 = 1;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO8= 1;

	   GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;
	   GpioDataRegs.GPASET.bit.GPIO9 = 1;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO9= 1;

	   GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;
	   GpioDataRegs.GPASET.bit.GPIO10 = 1;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO10= 1;

	   GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;
	   GpioDataRegs.GPASET.bit.GPIO11 = 1;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO11= 1;
	   EDIS;
}
void TM1637_V_START(void)
{
	CLK_V_1;
	DIO_V_1;
	DELAY_US(150);
	DIO_V_0;
	DELAY_US(150);
	CLK_V_0;
	DELAY_US(150);
}
void TM1637_V_STOP(void)
{
	CLK_V_0;
	DELAY_US(150);
	DIO_V_0;
	DELAY_US(150);
	CLK_V_1;
	DELAY_US(150);
	DIO_V_1;
	DELAY_US(150);
}
void TM1637_V_WriteBIT(unsigned char mBit)
{
	CLK_V_0;
	DELAY_US(150);
	if(mBit)
		DIO_V_1;
	else
		DIO_V_0;
	DELAY_US(150);
	CLK_V_1;
	DELAY_US(150);
}
void TM1637_V_WriteByte(unsigned char mByte)
{
	Uint16 loop=0;
	for(loop=0;loop<8;loop++)
	{
		TM1637_V_WriteBIT((mByte>>loop)&0x01);
	}
	CLK_V_0;
	DELAY_US(150);
	DIO_V_1;
	DELAY_US(150);
	CLK_V_1;
	DELAY_US(150);
}
void TM1637_V_WriteData(unsigned char addr,unsigned char mData)
{
	TM1637_V_START();
	TM1637_V_WriteByte(addr);
	TM1637_V_WriteByte(mData);
	TM1637_V_STOP();
}
void TM1637_V_WriteCammand(unsigned char mData)
{
	TM1637_V_START();
	TM1637_V_WriteByte(mData);
	TM1637_V_STOP();
}
void V_Display(Uint16 data)
{
	TM1637_V_WriteCammand(0x44);
	TM1637_V_WriteData(0xC0,SEGData[data/1000]);
	TM1637_V_WriteData(0xC1,SEGDataDp[data%1000/100]);
	TM1637_V_WriteData(0xC2,SEGData[data%100/10]);
	TM1637_V_WriteData(0xC3,SEGData[data%10]);
	TM1637_V_WriteCammand(0x8a);
}


void TM1637_I_START(void)
{
	CLK_I_1;
	DIO_I_1;
	DELAY_US(150);
	DIO_I_0;
	DELAY_US(150);
	CLK_I_0;
	DELAY_US(150);
}
void TM1637_I_STOP(void)
{
	CLK_I_0;
	DELAY_US(150);
	DIO_I_0;
	DELAY_US(150);
	CLK_I_1;
	DELAY_US(150);
	DIO_I_1;
	DELAY_US(150);
}
void TM1637_I_WriteBIT(unsigned char mBit)
{
	CLK_I_0;
	DELAY_US(150);
	if(mBit)
		DIO_I_1;
	else
		DIO_I_0;
	DELAY_US(150);
	CLK_I_1;
	DELAY_US(150);
}
void TM1637_I_WriteByte(unsigned char mByte)
{
	Uint16 loop=0;
	for(loop=0;loop<8;loop++)
	{
		TM1637_I_WriteBIT((mByte>>loop)&0x01);
	}
	CLK_I_0;
	DELAY_US(150);
	DIO_I_1;
	DELAY_US(150);
	CLK_I_1;
	DELAY_US(150);
}
void TM1637_I_WriteData(unsigned char addr,unsigned char mData)
{
	TM1637_I_START();
	TM1637_I_WriteByte(addr);
	TM1637_I_WriteByte(mData);
	TM1637_I_STOP();
}
void TM1637_I_WriteCammand(unsigned char mData)
{
	TM1637_I_START();
	TM1637_I_WriteByte(mData);
	TM1637_I_STOP();
}
void I_Display(Uint16 data)
{
	TM1637_I_WriteCammand(0x44);
	TM1637_I_WriteData(0xC0,SEGData[data/1000]);
	TM1637_I_WriteData(0xC1,SEGDataDp[data%1000/100]);
	TM1637_I_WriteData(0xC2,SEGData[data%100/10]);
	TM1637_I_WriteData(0xC3,SEGData[data%10]);
	TM1637_I_WriteCammand(0x8a);
}
