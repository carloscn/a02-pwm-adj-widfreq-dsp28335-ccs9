#include "../include/DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "../include/DSP2833x_Examples.h"   // DSP2833x Examples Include File

void Init_KEY_GPIO(void)
{
	   EALLOW;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;

	   GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0; //蜂鸣器GPIO设置，GPIO60复用为GPIO功能
	   GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;  //设置为输出

	   GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;
	   GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;

	   GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;
	   GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;

	   GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;
	   GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;

	   GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;
	   GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;


	   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; //LED
	   GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;  //
	   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0; //
	   GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
	   EDIS;
}


