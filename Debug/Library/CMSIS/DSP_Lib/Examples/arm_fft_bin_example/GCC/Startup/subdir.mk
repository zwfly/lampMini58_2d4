################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/system_ARMCM0.c \
../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/system_ARMCM3.c \
../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/system_ARMCM4.c 

S_UPPER_SRCS += \
../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/startup_ARMCM0.S \
../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/startup_ARMCM3.S \
../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/startup_ARMCM4.S 

OBJS += \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/startup_ARMCM0.o \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/startup_ARMCM3.o \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/startup_ARMCM4.o \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/system_ARMCM0.o \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/system_ARMCM3.o \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/system_ARMCM4.o 

C_DEPS += \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/system_ARMCM0.d \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/system_ARMCM3.d \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/system_ARMCM4.d 


# Each subdirectory must supply rules for building sources it contributes
Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/%.o: ../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/%.o: ../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/Startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


