################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.c \
../Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.c \
../Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.c \
../Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.c \
../Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.c \
../Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.c \
../Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.c \
../Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.c 

OBJS += \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.o \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.o \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.o \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.o \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.o \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.o \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.o \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.o 

C_DEPS += \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.d \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.d \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.d \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.d \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.d \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.d \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.d \
./Library/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Library/CMSIS/DSP_Lib/Source/FastMathFunctions/%.o: ../Library/CMSIS/DSP_Lib/Source/FastMathFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


