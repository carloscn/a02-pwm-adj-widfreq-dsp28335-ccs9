################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./SRC/DSP2833x_ADC_cal.obj" \
"./SRC/DSP2833x_Adc.obj" \
"./SRC/DSP2833x_CSMPasswords.obj" \
"./SRC/DSP2833x_CodeStartBranch.obj" \
"./SRC/DSP2833x_CpuTimers.obj" \
"./SRC/DSP2833x_DBGIER.obj" \
"./SRC/DSP2833x_DMA.obj" \
"./SRC/DSP2833x_DefaultIsr.obj" \
"./SRC/DSP2833x_DisInt.obj" \
"./SRC/DSP2833x_ECan.obj" \
"./SRC/DSP2833x_ECap.obj" \
"./SRC/DSP2833x_EPwm.obj" \
"./SRC/DSP2833x_EQep.obj" \
"./SRC/DSP2833x_GlobalVariableDefs.obj" \
"./SRC/DSP2833x_Gpio.obj" \
"./SRC/DSP2833x_I2C.obj" \
"./SRC/DSP2833x_Mcbsp.obj" \
"./SRC/DSP2833x_MemCopy.obj" \
"./SRC/DSP2833x_PieCtrl.obj" \
"./SRC/DSP2833x_PieVect.obj" \
"./SRC/DSP2833x_Sci.obj" \
"./SRC/DSP2833x_Spi.obj" \
"./SRC/DSP2833x_SysCtrl.obj" \
"./SRC/DSP2833x_Xintf.obj" \
"./SRC/DSP2833x_usDelay.obj" \
"./SRC/Dis_FSP.obj" \
"./SRC/Dis_VI.obj" \
"./SRC/KEY.obj" \
"./SRC/main.obj" \
"../CMD/28335_RAM_lnk.cmd" \
"../CMD/DSP2833x_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include SRC/subdir_vars.mk
-include CMD/subdir_vars.mk
-include SRC/subdir_rules.mk
-include CMD/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
A02_PWM_ADJ_WIDFRE_CCSV6.out \

EXE_OUTPUTS__QUOTED += \
"A02_PWM_ADJ_WIDFRE_CCSV6.out" \

BIN_OUTPUTS += \
A02_PWM_ADJ_WIDFRE_CCSV6.hex \

BIN_OUTPUTS__QUOTED += \
"A02_PWM_ADJ_WIDFRE_CCSV6.hex" \


# All Target
all: A02_PWM_ADJ_WIDFRE_CCSV6.out

# Tool invocations
A02_PWM_ADJ_WIDFRE_CCSV6.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"A02_PWM_ADJ_WIDFRE_CCSV6.map" --stack_size=0x300 --warn_sections -i"D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/lib" -i"D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="A02_PWM_ADJ_WIDFRE_CCSV6_linkInfo.xml" --rom_model -o "A02_PWM_ADJ_WIDFRE_CCSV6.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

A02_PWM_ADJ_WIDFRE_CCSV6.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/hex2000"  -o "A02_PWM_ADJ_WIDFRE_CCSV6.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "SRC\DSP2833x_Adc.pp" "SRC\DSP2833x_CpuTimers.pp" "SRC\DSP2833x_DMA.pp" "SRC\DSP2833x_DefaultIsr.pp" "SRC\DSP2833x_ECan.pp" "SRC\DSP2833x_ECap.pp" "SRC\DSP2833x_EPwm.pp" "SRC\DSP2833x_EQep.pp" "SRC\DSP2833x_GlobalVariableDefs.pp" "SRC\DSP2833x_Gpio.pp" "SRC\DSP2833x_I2C.pp" "SRC\DSP2833x_Mcbsp.pp" "SRC\DSP2833x_MemCopy.pp" "SRC\DSP2833x_PieCtrl.pp" "SRC\DSP2833x_PieVect.pp" "SRC\DSP2833x_Sci.pp" "SRC\DSP2833x_Spi.pp" "SRC\DSP2833x_SysCtrl.pp" "SRC\DSP2833x_Xintf.pp" "SRC\Dis_FSP.pp" "SRC\Dis_VI.pp" "SRC\KEY.pp" "SRC\main.pp" 
	-$(RM) "SRC\DSP2833x_ADC_cal.obj" "SRC\DSP2833x_Adc.obj" "SRC\DSP2833x_CSMPasswords.obj" "SRC\DSP2833x_CodeStartBranch.obj" "SRC\DSP2833x_CpuTimers.obj" "SRC\DSP2833x_DBGIER.obj" "SRC\DSP2833x_DMA.obj" "SRC\DSP2833x_DefaultIsr.obj" "SRC\DSP2833x_DisInt.obj" "SRC\DSP2833x_ECan.obj" "SRC\DSP2833x_ECap.obj" "SRC\DSP2833x_EPwm.obj" "SRC\DSP2833x_EQep.obj" "SRC\DSP2833x_GlobalVariableDefs.obj" "SRC\DSP2833x_Gpio.obj" "SRC\DSP2833x_I2C.obj" "SRC\DSP2833x_Mcbsp.obj" "SRC\DSP2833x_MemCopy.obj" "SRC\DSP2833x_PieCtrl.obj" "SRC\DSP2833x_PieVect.obj" "SRC\DSP2833x_Sci.obj" "SRC\DSP2833x_Spi.obj" "SRC\DSP2833x_SysCtrl.obj" "SRC\DSP2833x_Xintf.obj" "SRC\DSP2833x_usDelay.obj" "SRC\Dis_FSP.obj" "SRC\Dis_VI.obj" "SRC\KEY.obj" "SRC\main.obj" 
	-$(RM) "SRC\DSP2833x_ADC_cal.pp" "SRC\DSP2833x_CSMPasswords.pp" "SRC\DSP2833x_CodeStartBranch.pp" "SRC\DSP2833x_DBGIER.pp" "SRC\DSP2833x_DisInt.pp" "SRC\DSP2833x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

