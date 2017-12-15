################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/src/app_2d4.c \
../App/src/app_crc.c \
../App/src/app_dome.c \
../App/src/app_eeprom.c \
../App/src/app_repeat_exe.c \
../App/src/app_uart.c \
../App/src/app_work.c \
../App/src/main.c 

OBJS += \
./App/src/app_2d4.o \
./App/src/app_crc.o \
./App/src/app_dome.o \
./App/src/app_eeprom.o \
./App/src/app_repeat_exe.o \
./App/src/app_uart.o \
./App/src/app_work.o \
./App/src/main.o 

C_DEPS += \
./App/src/app_2d4.d \
./App/src/app_crc.d \
./App/src/app_dome.d \
./App/src/app_eeprom.d \
./App/src/app_repeat_exe.d \
./App/src/app_uart.d \
./App/src/app_work.d \
./App/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/%.o: ../App/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


