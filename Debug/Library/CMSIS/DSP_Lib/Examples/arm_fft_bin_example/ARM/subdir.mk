################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/arm_fft_bin_data.c \
../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/arm_fft_bin_example_f32.c 

OBJS += \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/arm_fft_bin_data.o \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/arm_fft_bin_example_f32.o 

C_DEPS += \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/arm_fft_bin_data.d \
./Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/arm_fft_bin_example_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/%.o: ../Library/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


