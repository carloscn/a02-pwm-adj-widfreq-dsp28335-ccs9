
#include "main.h"

#ifdef FLASH
extern Uint16 RamfuncsLoadStart;	// These are defined by the linker (see F28335.cmd)
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
#endif



//---------------定时器相关---------------------//
Uint32 Send_flag=0;
#define T0_CYC 1
//---------------ADC相关---------------------//
Uint16  ADC0_DATA=0,ADC1_DATA=0;

//---------------PWM相关---------------------//
Uint32 pwm_PRD=65534,pwm_PRD_next=65534;
float32 temp_PRD=0;
//---------------显示相关---------------------//
float32 f_pwm=50,sp_pwm=5;
Uint16 f_dis=1,sp_dis=50;

Uint16 key_A=0,key_B=0;
Uint16 key1_currentstate=0,key1_laststate=0,key3_currentstate=0,key3_laststate=0;
Uint16 adj_f_flag=0,adj_sp_flag=0;

// add by mlt.
Uint16 k1 = 0,k2 = 0,k3 = 0,BKL = 0,AN = 800,BN = 800,
        epwm2_g_tbprd = 0,epwm1_tbprd,epwm1_cmpa,
        epwm2_tbprd,epwm2_cmpa,AKL = 0;

float pwm_half_per  = 600,AM = 0.8f,BM = 0.8f,phase_value,current_freq = 0;
//------------

#define                  us(ms)           (float)(ms/1000)


Uint16 Read_ADC0(void)
{
	Uint16 ad_temp=0;
	float32 ad_result=0;
	while(AdcRegs.ADCST.bit.INT_SEQ1==0); //级连时为INT_SEQ1，两路ADC独立使用时为INT_SEQ2
	AdcRegs.ADCST.bit.INT_SEQ1_CLR=1;
	ad_temp=((AdcRegs.ADCRESULT2)>>4); //12位有效的AD，//把通道6的转换结果放到CONV02中
	ad_result=ad_temp*0.00073242;
	ad_temp=(Uint16)(ad_result*100);
	return ad_temp;

}
Uint16 Read_ADC1(void)
{
	Uint16 ad_temp=0;
	float32 ad_result=0;
	while(AdcRegs.ADCST.bit.INT_SEQ1==0); //级连时为INT_SEQ1，两路ADC独立使用时为INT_SEQ2
	AdcRegs.ADCST.bit.INT_SEQ2_CLR=1;
	ad_temp=((AdcRegs.ADCRESULT3)>>4); //12位有效的AD
	ad_result=ad_temp*0.00073242;
	ad_temp=(Uint16)(ad_result*100);
	return ad_temp;
}

void DELAY(int aa)
{
	int i,j,k;
	for(i=0;i<aa;i++)
	{
		for(j=0;j<1000;j++);
		for(k=0;k<1000;k++);
	}
}


void Adj_PWM(Uint16 T,float32 SP)
{
	EPwm4Regs.TBPRD =T*2.0;                        // Set timer period
	EPwm4Regs.CMPA.half.CMPA =T*SP*0.1; //A路占空比
	EPwm4Regs.CMPB = T*SP;//B路占空比
}

Uint16 Calcu_slop(Uint16 inputdata,int k) //计算调频的步进量
{
	float64 temp=0;
	Uint16 outputdata=0;
	temp=pow(inputdata,2);
	temp=inputdata-k*temp/(97656.25+inputdata);
	outputdata=(Uint16)temp;
	return outputdata;
}
interrupt void ISRTimer0(void)
{
	// Acknowledge this interrupt to receive more interrupts from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; //0x0001赋给12组中断ACKnowledge寄存器，对其全部清除，不接受其他中断
	CpuTimer0Regs.TCR.bit.TIF=1; // 定时到了指定时间，标志位置位，清除标志
	CpuTimer0Regs.TCR.bit.TRB=1;  // 重载Timer0的定时数据
	Send_flag++;
}

void main(void)
{
#ifdef FLASH
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	InitFlash();
#endif
	InitSysCtrl();
	DINT;
	InitPieCtrl();

	IER = 0x0000;   // 即使在程序里不需要使用中断功能，也要对 PIE 向量表进行初始化.
	IFR = 0x0000;//  PIE 向量表指针指向中断服务程(ISR)完成其初始化.这样做是为了避免PIE引起的错误.

	InitPieVectTable();
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.TINT0 = &ISRTimer0;
	EDIS;    // This is needed to disable write to EALLOW protected registers

	InitCpuTimers();   // For this example, only initialize the Cpu Timers
	ConfigCpuTimer(&CpuTimer0,150,1000);
	StartCpuTimer0();


	IER |= M_INT1;
	GpioDataRegs.GPBSET.bit.GPIO60=1;
	// Enable TINT0 in the PIE: Group 1 interrupt 7
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;


	EINT;   // 总中断 INTM 使能
	ERTM;   // 使能总实时中断 DBGM
	Init_KEY_GPIO();
	InitAdc();
	Config_ADC();
	//InitEPwm4Gpio();
	//InitEPwm4();
	Init_FSPLED_GPIO();
	Init_VILED_GPIO();
	// add by mlt.
	GPIO_INIT( & GpioCtrlRegs);
	EPWM1_INIT( & EPwm1Regs);
	EPWM2_INIT( & EPwm2Regs);
	// ----------
	LED0=1;
	V_Display(0);
	I_Display(0);
	A_Display(0);
	F_Display(0);

	//
	// 第一个变量是频率  单位Hz
	// 第二个变量是脉宽  单位是us
	// ;;两个参数随意组合，如果输入频率大于500 就会被设定成500 频率小于10 会被设定成10
	// ;;频率步进的时候保持 脉宽数值不要变就好。
	// ;;脉宽步进的时候保持 频率的数值不要变就好。
	EPWM1_SetPwm_Freq_PWidth(500,200);

	while(1)
	{
		if(Send_flag>=200)  //-------------CPU定时器定时发送数据到上位机-----
		{
			ADC0_DATA=Read_ADC0();
			ADC1_DATA=Read_ADC1();
			V_Display(ADC0_DATA);
			I_Display(ADC1_DATA);
			A_Display(f_dis);
			F_Display(sp_dis);
			LED0=~LED0;
			Send_flag=0;
		}
		if(KEY_START==0)
		{
			DELAY_US(10000);   //延时消抖，防止电平抖动导致的误触发
			if(KEY_START==0)
				key_A=1;
		}
		else if((key_A==1)&&(KEY_START==1))
		{
			key_B++;
			key_A=0;
		}
		else;
		if((key_B%2)==1) //开启输出
		{
			ADC0_DATA=Read_ADC0();
			ADC1_DATA=Read_ADC1();
			Adj_PWM(pwm_PRD,sp_pwm);
			key1_laststate=KEY1;
			if(KEY0==0)
			{
				DELAY(1);
				key1_currentstate=KEY1;
				adj_f_flag=1;
			}
			key3_laststate=KEY3;
			if(KEY2==0)
			{
				DELAY(1);
				key3_currentstate=KEY3;
				adj_sp_flag=1;
			}
			if(adj_f_flag==1)
			{

				if((key1_laststate==1)&&(key1_currentstate==0))
				{
					if(f_dis<50)
						pwm_PRD_next=Calcu_slop(pwm_PRD,1);

					else

						pwm_PRD_next=Calcu_slop(pwm_PRD,10);


					if(pwm_PRD_next<=195)
						pwm_PRD_next=195;
				}
				else if((key1_laststate==0)&&(key1_currentstate==1))
				{
					if(f_dis<50)
						pwm_PRD_next=Calcu_slop(pwm_PRD,-1);

					else
					 pwm_PRD_next=Calcu_slop(pwm_PRD,-10);


					if(pwm_PRD_next>=9000)
						pwm_PRD_next=9000;
				}
				else;
				Adj_PWM(pwm_PRD_next,sp_pwm);
				pwm_PRD=pwm_PRD_next;

				f_pwm=97656.25/pwm_PRD_next;
				f_dis=(Uint16)f_pwm;
				adj_f_flag=0;
			}
			if(adj_sp_flag==1)
			{
				if((key3_laststate==1)&&(key3_currentstate==0))
				{
					if( sp_pwm<1)
						sp_pwm+=0.1;
					else
						sp_pwm+=0.5;
					if(sp_pwm>=10)
						sp_pwm=10;
				}
				else if((key3_laststate==0)&&(key3_currentstate==1))
				{
					if( sp_pwm<1)
						sp_pwm-=0.1;
					else
						sp_pwm-=0.5;
					if(sp_pwm<0.1)
						sp_pwm=0;
				}
				else;
				Adj_PWM(pwm_PRD_next,sp_pwm);
				sp_dis=sp_pwm*10;
				adj_sp_flag=0;
			}
		}
		else
		{
			pwm_PRD=65534;
			f_dis=50;
			sp_pwm=0;
			sp_dis=0;
			Adj_PWM(0,0);
		}

	}
}

// add by mlt.
// unit freqs = x Hz,  pwidth = x us
void    EPWM1_SetPwm_Freq_PWidth( float freq_hz, float pwidth_us )
{
    float occupy  =   0;

    if( pwidth_us < 5 ) {
        pwidth_us = 5;
    }else if( pwidth_us > 200 ) {
        pwidth_us = 200;
    }
    occupy  =   freq_hz * pwidth_us * 0.0001;
    EPWM1_SetPwm_Freq_Occupy( freq_hz, occupy );
}

// add by mlt.
// unit freqs = x Hz,  pwidth = x us
void    EPWM2_SetPwm_Freq_PWidth( float freqs, float pwidth )
{
    float occupy  =   0;

    if( pwidth < 5 ) {
        pwidth = 5;
    }else if( pwidth > 200 ) {
        pwidth = 200;
    }
    occupy  =   freqs * pwidth * 0.0001;
    EPWM2_SetPwm_Freq_Occupy( freqs, occupy ,0 );
}

void    EPWM1_SetPwm_Freq_Occupy( float _f_freqz, float _f_occupy)
{
    Uint16 u16_TBPRD = 0x0000;
    Uint32 u32_TCLK = 150000000;
    Uint32 u32_LTCLK = 37500000;
    Uint32 u32_LMTCLK = 83705;
    Uint16 u16_CMPA = 0x0000;
    float flt_oppy = 0.0f;


    flt_oppy = _f_occupy / 100.0;
    if( _f_freqz < 2000 && _f_freqz > 300) {
        EPwm1Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;       // Clock ratio to SYSCLKOUT
        EPwm1Regs.TBCTL.bit.CLKDIV  = TB_DIV2;
        //TCLK = 150 000 000

        //                     TCLK
        // TBPRD =   -----------------------         (f is pwm wave freqency value)
        //                    2 × f
        epwm1_tbprd = u16_TBPRD = (Uint16) ( (float)u32_LTCLK / ( 2 * _f_freqz ) );
        epwm1_cmpa = u16_CMPA =(Uint16)( ((float)u16_TBPRD) * flt_oppy  );


    }else if( _f_freqz >= 2000 ){
        EPwm1Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1;       // Clock ratio to SYSCLKOUT
        EPwm1Regs.TBCTL.bit.CLKDIV  = TB_DIV1;
        //TCLK = 150 000 000

        //                     TCLK
        // TBPRD =   -----------------------         (f is pwm wave freqency value)
        //                    2 × f
        epwm1_tbprd = u16_TBPRD = (Uint16) ( (float)u32_TCLK / ( 2 * _f_freqz ) );
        epwm1_cmpa = u16_CMPA =(Uint16)( ((float)u16_TBPRD) * flt_oppy  );

    }else if( _f_freqz <= 300 ) {
        EPwm1Regs.TBCTL.bit.HSPCLKDIV   = 0x7;       // Clock ratio to SYSCLKOUT
        EPwm1Regs.TBCTL.bit.CLKDIV  = 0x7;
        //TCLK = 150 000 000

        //                     TCLK
        // TBPRD =   -----------------------         (f is pwm wave freqency value)
        //                    2 × f
        epwm1_tbprd = u16_TBPRD = (Uint16) ( (float)u32_LMTCLK / ( 2 * _f_freqz ) );
        epwm1_cmpa = u16_CMPA =(Uint16)( ((float)u16_TBPRD) * flt_oppy  );
    }



    EPwm1Regs.TBPRD = u16_TBPRD;                        // Set timer period
    EPwm1Regs.CMPA.half.CMPA =  u16_CMPA;
    epwm1_tbprd = epwm1_tbprd + 1;
}


void    EPWM2_SetPwm_Freq_Occupy( float _f_freqz, float _f_occupy, float _f_phase )
{
    // freqz单位为hZ, 占空比为：_f_occupy，相位：_f_phase度 （范围0~90度）
    Uint16 u16_TBPRD = 0x0000;
    Uint32 u32_TCLK = 150000000;
    Uint32 u32_LTCLK = 37500000;
    Uint32 u32_LMTCLK = 83705;
    Uint16 u16_CMPA = 0x0000;
    float flt_oppy = 0.0f;
    float T;
    current_freq = _f_freqz;
    T = (1/_f_freqz)*100000;
    phase_value = T*(_f_phase/360);         // 单位为us

    flt_oppy = _f_occupy / 100.0;
    if( _f_freqz < 2000 && _f_freqz > 300) {
        EPwm2Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;       // Clock ratio to SYSCLKOUT
        EPwm2Regs.TBCTL.bit.CLKDIV  = TB_DIV2;
        //TCLK = 150 000 000

        //                     TCLK
        // TBPRD =   -----------------------         (f is pwm wave freqency value)
        //                    2 × f
        epwm2_tbprd = u16_TBPRD = (Uint16) ( (float)u32_LTCLK / ( 2 * _f_freqz ) );
        epwm2_cmpa = u16_CMPA =(Uint16)( ((float)u16_TBPRD) * flt_oppy  );


    }else if( _f_freqz >= 2000 ){
        EPwm2Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1;       // Clock ratio to SYSCLKOUT
        EPwm2Regs.TBCTL.bit.CLKDIV  = TB_DIV1;
        //TCLK = 150 000 000

        //                     TCLK
        // TBPRD =   -----------------------         (f is pwm wave freqency value)
        //                    2 × f
        epwm2_tbprd = u16_TBPRD = (Uint16) ( (float)u32_TCLK / ( 2 * _f_freqz ) );
        epwm2_cmpa = u16_CMPA =(Uint16)( ((float)u16_TBPRD) * flt_oppy  );

    }else if( _f_freqz <= 300 ) {
        EPwm2Regs.TBCTL.bit.HSPCLKDIV   = 0x7;       // Clock ratio to SYSCLKOUT
        EPwm2Regs.TBCTL.bit.CLKDIV  = 0x7;
        //TCLK = 150 000 000

        //                     TCLK
        // TBPRD =   -----------------------         (f is pwm wave freqency value)
        //                    2 × f
        epwm2_tbprd = u16_TBPRD = (Uint16) ( (float)u32_LMTCLK / ( 2 * _f_freqz ) );
        epwm2_cmpa = u16_CMPA =(Uint16)( ((float)u16_TBPRD) * flt_oppy  );
    }



    epwm2_g_tbprd = EPwm2Regs.TBPRD = u16_TBPRD;                        // Set timer period
    epwm2_g_tbprd = (Uint16)((float)u16_TBPRD*(_f_phase/360.0));

    EPwm2Regs.TBCTR = 0;

    // Setup TBCLK
    /*
    EPwm2Regs.TBCTL.bit.CTRMODE         = TB_COUNT_UPDOWN; // Count up
    EPwm2Regs.TBCTL.bit.PHSEN       = TB_ENABLE;        // // // Phase = 300/900 * 360 = 120 deg
    EPwm2Regs.TBCTL.bit.PHSDIR  =   TB_DOWN;
    EPwm2Regs.TBCTL.bit.PRDLD   =   TB_SHADOW;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm2Regs.TBCTL.bit.SYNCOSEL        = TB_SYNC_IN;       // Sync down-stream module
    */
    EPwm2Regs.CMPA.half.CMPA =  u16_CMPA;
    epwm2_tbprd = epwm2_tbprd + 1;
    SetPhaseValue(_f_phase);

}

void SetPhaseValue( Uint16 phase )
{
    Uint32 n;
    n = phase*(2778/current_freq);  // T = 1/current_freq;    2778 = (1/360)*1000000;  t = 120*ts;
    EPwm1Regs.TBCTR = 0;
    DELAY_US(n);
    EPwm2Regs.TBCTR = 0;
}

void GPIO_INIT( volatile struct GPIO_CTRL_REGS *REG )
{
    EALLOW;
    /* Enable internal pull-up for the selected pins */
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.

    // PWM6A PWM6B
    REG->GPAPUD.bit.GPIO0   =   0;              // Enable pull-up on GPIO2 (EPWM6A)     EPWM1A
    REG->GPAPUD.bit.GPIO1   =   0;              // Enable pull-up on GPIO2 (EPWM6B)     EPWM1B
    REG->GPAPUD.bit.GPIO2   =   0;              // Enable pull-up on GPIO2 (EPWM6A)     EPWM2A
    REG->GPAPUD.bit.GPIO3   =   0;              // Enable pull-up on GPIO2 (EPWM6B)     EPWM2B
    REG->GPAMUX1.bit.GPIO0  =   1;
    REG->GPAMUX1.bit.GPIO1  =   1;
    REG->GPAMUX1.bit.GPIO2  =   1;
    REG->GPAMUX1.bit.GPIO3  =   1;

    REG->GPBMUX2.bit.GPIO54 = 0;
    REG->GPBDIR.bit.GPIO54 = 1;
    REG->GPBMUX2.bit.GPIO56 = 0;
    REG->GPBDIR.bit.GPIO56 = 1;
    REG->GPBMUX2.bit.GPIO57= 0;
    REG->GPBDIR.bit.GPIO57 = 1;

    EDIS;
}

void EPWM1_INIT( volatile struct EPWM_REGS *REG )
{
    REG->TBPRD = pwm_half_per;                        // Set timer period
    //REG->TBPRD = 1874;                        // Set timer period
    //REG->TBPRD = 10000;                        // Set timer period
    REG->TBPHS.half.TBPHS       = 0x0000;           // Phase is 0
    REG->TBCTR = 0x0000;                      // Clear counter
    // Setup TBCLK
    REG->TBCTL.bit.CTRMODE      = TB_COUNT_UPDOWN; // Count up
    REG->TBCTL.bit.PHSEN        = TB_DISABLE;        // // Allow each timer to be sync'ed
    REG->TBCTL.bit.PRDLD        = TB_SHADOW;
    REG->TBCTL.bit.HSPCLKDIV    = TB_DIV1;       // Clock ratio to SYSCLKOUT
    REG->TBCTL.bit.CLKDIV       = TB_DIV1;
    REG->TBCTL.bit.SYNCOSEL     = 0x00;     // Sync down-stream module


    REG->CMPCTL.bit.SHDWAMODE   = CC_SHADOW;    // Load registers every ZERO
    REG->CMPCTL.bit.SHDWBMODE   = CC_SHADOW;
    REG->CMPCTL.bit.LOADAMODE   = CC_CTR_ZERO;
    REG->CMPCTL.bit.LOADBMODE   = CC_CTR_ZERO;


    // Set actions
    REG->AQCTLA.bit.CAU         = AQ_SET;             // Set PWM1A on Zero
    REG->AQCTLA.bit.CAD         = AQ_CLEAR;

    REG->AQCTLB.bit.CAU         = AQ_CLEAR;          // Set PWM1A on Zero
    REG->AQCTLB.bit.CAD         = AQ_SET;

    // Active Low PWMs - Setup Deadband
    REG->DBCTL.bit.OUT_MODE     = DB_DISABLE;
    REG->DBCTL.bit.POLSEL       = DB_ACTV_LO;
    REG->DBCTL.bit.IN_MODE      = DBA_ALL;
    REG->DBRED                  = 0;                // 1us
    REG->DBFED                  = 0;

    // Interrupt where we will change the Deadband
    REG->ETSEL.bit.INTSEL       = ET_CTR_ZERO;     // Select INT on Zero event
    REG->ETSEL.bit.INTEN        = 1;                // Enable INT
    REG->ETPS.bit.INTPRD        = ET_1ST;           // Generate INT on 3rd event

    REG->ETCLR.bit.SOCA         = 0;
    REG->ETCLR.bit.INT          =   1;



    // Setup compare
    REG->CMPA.half.CMPA         = (Uint16)REG->TBPRD /2;
    REG->CMPB   = (Uint16)REG->TBPRD /2;
}

void EPWM2_INIT( volatile struct EPWM_REGS *REG )
{

    REG->TBPRD = pwm_half_per;                        // Set timer period
    //REG->TBPRD = 1874;                        // Set timer period
    //REG->TBPRD = 10000;                        // Set timer period
    REG->TBPHS.half.TBPHS   = 0;           // Phase is 0
    REG->TBCTR = 0x0000;                      // Clear counter

    // Setup TBCLK
    REG->TBCTL.bit.CTRMODE      = TB_COUNT_UPDOWN; // Count up
    REG->TBCTL.bit.PHSEN        = TB_ENABLE;        // // // Phase = 300/900 * 360 = 120 deg
    REG->TBCTL.bit.PHSDIR   =   TB_DOWN;
    REG->TBCTL.bit.PRDLD    =   TB_SHADOW;
    REG->TBCTL.bit.HSPCLKDIV    = TB_DIV1;       // Clock ratio to SYSCLKOUT
    REG->TBCTL.bit.CLKDIV       = TB_DIV1;
    REG->TBCTL.bit.SYNCOSEL     = TB_SYNC_IN;       // Sync down-stream module


    REG->CMPCTL.bit.SHDWAMODE   = CC_SHADOW;    // Load registers every ZERO
    REG->CMPCTL.bit.SHDWBMODE   = CC_SHADOW;
    REG->CMPCTL.bit.LOADAMODE   = CC_CTR_ZERO;
    REG->CMPCTL.bit.LOADBMODE   = CC_CTR_ZERO;

;
    // Set actions
    REG->AQCTLA.bit.CAU         = AQ_SET;             // Set PWM1A on Zero
    REG->AQCTLA.bit.CAD         = AQ_CLEAR;

    REG->AQCTLB.bit.CAU         = AQ_CLEAR;          // Set PWM1A on Zero
    REG->AQCTLB.bit.CAD         = AQ_SET;

    // Active Low PWMs - Setup Deadband
    REG->DBCTL.bit.OUT_MODE     = DB_DISABLE;
    REG->DBCTL.bit.POLSEL       = DB_ACTV_LO;
    REG->DBCTL.bit.IN_MODE      = DBA_ALL;
    REG->DBRED                  = 0;                // 1us
    REG->DBFED                  = 0;

    // Interrupt where we will change the Deadband
    REG->ETSEL.bit.INTSEL       = ET_CTR_ZERO;     // Select INT on Zero event
    REG->ETSEL.bit.INTEN        = 1;                // Enable INT
    REG->ETPS.bit.INTPRD        = ET_1ST;           // Generate INT on 3rd event

    REG->ETCLR.bit.SOCA         = 0;
    REG->ETCLR.bit.INT          =   1;
    // Setup compare
    REG->CMPA.half.CMPA         = (Uint16)REG->TBPRD /2;
    REG->CMPB   = (Uint16)REG->TBPRD /2;

}
