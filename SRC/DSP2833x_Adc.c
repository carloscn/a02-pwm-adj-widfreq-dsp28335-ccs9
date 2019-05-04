#include "../include/DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "../include/DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ADC_usDELAY  5000L

//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);


    // *IMPORTANT*
	// The ADC_cal function, which  copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	    EALLOW;
		SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
		ADC_cal();
		EDIS;




    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
	// CPU_CLOCK_SPEED define statement in the DSP2833x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.

    AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels
}
void Config_ADC(void)
{
	 InitAdc();
	   EALLOW;
	   SysCtrlRegs.HISPCP.all=0X3;
	   EDIS;
	   AdcRegs.ADCTRL1.bit.ACQ_PS=0x1;
	   AdcRegs.ADCTRL3.bit.ADCCLKPS=0X0;
	   AdcRegs.ADCTRL1.bit.SEQ_CASC=0X1;
	   AdcRegs.ADCTRL1.bit.CONT_RUN=0X1;

	   AdcRegs.ADCTRL1.bit.SEQ_OVRD=0X1;

	   AdcRegs.ADCCHSELSEQ1.bit.CONV02=0X0;  //把通道6的转换结果放到CONV02中
	   AdcRegs.ADCCHSELSEQ1.bit.CONV03=0X1;  //把通道7的转换结果放到CONV03中
	   //ADCCHSELSEQ1:CONV00~CONV03 ADCCHSELSEQ2:CONV04~CONV07
	   AdcRegs.ADCMAXCONV.bit.MAX_CONV1=2;  //开启两个通道转换
	   AdcRegs.ADCTRL2.all=0X2000;
}
//===========================================================================
// End of file.
//===========================================================================
