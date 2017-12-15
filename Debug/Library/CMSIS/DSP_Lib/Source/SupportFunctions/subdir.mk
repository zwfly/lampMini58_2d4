################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_f32.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q15.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q31.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q7.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_f32.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q15.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q31.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q7.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q15.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q31.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q7.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_float.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q31.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q7.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_float.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_q15.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_q7.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_float.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_q15.c \
../Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_q31.c 

OBJS += \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_f32.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q15.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q31.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q7.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_f32.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q15.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q31.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q7.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q15.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q31.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q7.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_float.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q31.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q7.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_float.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_q15.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_q7.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_float.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_q15.o \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_q31.o 

C_DEPS += \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_f32.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q15.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q31.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q7.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_f32.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q15.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q31.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q7.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q15.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q31.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q7.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_float.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q31.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q7.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_float.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_q15.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_q7.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_float.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_q15.d \
./Library/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Library/CMSIS/DSP_Lib/Source/SupportFunctions/%.o: ../Library/CMSIS/DSP_Lib/Source/SupportFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


