#include "../include/DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "../include/DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define CLK_F_1 GpioDataRegs.GPBSET.bit.GPIO50=1
#define CLK_F_0 GpioDataRegs.GPBCLEAR.bit.GPIO50=1
#define DIO_F_1 GpioDataRegs.GPBSET.bit.GPIO51=1
#define DIO_F_0 GpioDataRegs.GPBCLEAR.bit.GPIO51=1
#define CLK_A_1 GpioDataRegs.GPBSET.bit.GPIO52=1
#define CLK_A_0 GpioDataRegs.GPBCLEAR.bit.GPIO52=1
#define DIO_A_1 GpioDataRegs.GPBSET.bit.GPIO53=1
#define DIO_A_0 GpioDataRegs.GPBCLEAR.bit.GPIO53=1
