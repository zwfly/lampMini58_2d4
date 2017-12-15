################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.c \
../Library/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.c 

OBJS += \
./Library/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.o \
./Library/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.o 

C_DEPS += \
./Library/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.d \
./Library/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.d 


# Each subdirectory must supply rules for building sources it contributes
Library/CMSIS/DSP_Lib/Source/CommonTables/%.o: ../Library/CMSIS/DSP_Lib/Source/CommonTables/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


