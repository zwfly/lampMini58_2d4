################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/RTE/Device/ARMCM3/system_ARMCM3.c 

OBJS += \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/RTE/Device/ARMCM3/system_ARMCM3.o 

C_DEPS += \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/RTE/Device/ARMCM3/system_ARMCM3.d 


# Each subdirectory must supply rules for building sources it contributes
Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/RTE/Device/ARMCM3/%.o: ../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/RTE/Device/ARMCM3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


