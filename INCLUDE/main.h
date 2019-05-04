/*
 * main.h
 *
 *  Created on: 2018年3月8日
 *      Author: weihaochen
 */

#ifndef R02_PWM_ADJ_WIDFRE_CCSV6_INCLUDE_MAIN_H_
#define R02_PWM_ADJ_WIDFRE_CCSV6_INCLUDE_MAIN_H_

#include "../include/DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "../include/DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"   // DSP2833x Examples Include File


//---------------拨码开关相关---------------------//
#define KEY0 GpioDataRegs.GPADAT.bit.GPIO24
#define KEY1 GpioDataRegs.GPADAT.bit.GPIO25
#define KEY2 GpioDataRegs.GPADAT.bit.GPIO26
#define KEY3 GpioDataRegs.GPADAT.bit.GPIO27

#define   LED0  GpioDataRegs.GPADAT.bit.GPIO0  //自定义4个控制LED的GPIO数据寄存器
#define   LED1  GpioDataRegs.GPADAT.bit.GPIO1
#define   BUZZ_C    GpioDataRegs.GPBSET.bit.GPIO60=1; //蜂鸣器不鸣叫
#define   BUZZ_O    GpioDataRegs.GPBCLEAR.bit.GPIO60=1;//蜂鸣器鸣叫
#define KEY_START GpioDataRegs.GPADAT.bit.GPIO13 //用于开启或停止输出

interrupt void ISRTimer0(void);
void EPWM2_INIT( volatile struct EPWM_REGS *REG );
void EPWM1_INIT( volatile struct EPWM_REGS *REG);
void GPIO_INIT( volatile struct GPIO_CTRL_REGS *REG );
void SetPhaseValue( Uint16 phase );
void    EPWM2_SetPwm_Freq_Occupy( float _f_freqz, float _f_occupy, float _f_phase );
void    EPWM1_SetPwm_Freq_Occupy( float _f_freqz, float _f_occupy);
void    EPWM1_SetPwm_Freq_PWidth( float freqs, float pwidth );
void    EPWM2_SetPwm_Freq_PWidth( float freqs, float pwidth );
#endif /* R02_PWM_ADJ_WIDFRE_CCSV6_INCLUDE_MAIN_H_ */
