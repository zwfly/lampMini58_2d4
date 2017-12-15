################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bsp/src/bsp_2d4.c \
../Bsp/src/bsp_eeprom.c \
../Bsp/src/bsp_key.c \
../Bsp/src/bsp_light.c \
../Bsp/src/bsp_relay.c \
../Bsp/src/bsp_timer0.c \
../Bsp/src/bsp_uart.c \
../Bsp/src/bsp_uart_fifo.c 

OBJS += \
./Bsp/src/bsp_2d4.o \
./Bsp/src/bsp_eeprom.o \
./Bsp/src/bsp_key.o \
./Bsp/src/bsp_light.o \
./Bsp/src/bsp_relay.o \
./Bsp/src/bsp_timer0.o \
./Bsp/src/bsp_uart.o \
./Bsp/src/bsp_uart_fifo.o 

C_DEPS += \
./Bsp/src/bsp_2d4.d \
./Bsp/src/bsp_eeprom.d \
./Bsp/src/bsp_key.d \
./Bsp/src/bsp_light.d \
./Bsp/src/bsp_relay.d \
./Bsp/src/bsp_timer0.d \
./Bsp/src/bsp_uart.d \
./Bsp/src/bsp_uart_fifo.d 


# Each subdirectory must supply rules for building sources it contributes
Bsp/src/%.o: ../Bsp/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


