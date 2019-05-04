#include "../include/DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "../include/DSP2833x_Examples.h"   // DSP2833x Examples Include File


#define CLK_V_1 GpioDataRegs.GPASET.bit.GPIO8=1
#define CLK_V_0 GpioDataRegs.GPACLEAR.bit.GPIO8=1
#define DIO_V_1 GpioDataRegs.GPASET.bit.GPIO9=1
#define DIO_V_0 GpioDataRegs.GPACLEAR.bit.GPIO9=1
#define CLK_I_1 GpioDataRegs.GPASET.bit.GPIO10=1
#define CLK_I_0 GpioDataRegs.GPACLEAR.bit.GPIO10=1
#define DIO_I_1 GpioDataRegs.GPASET.bit.GPIO11=1
#define DIO_I_0 GpioDataRegs.GPACLEAR.bit.GPIO11=1
