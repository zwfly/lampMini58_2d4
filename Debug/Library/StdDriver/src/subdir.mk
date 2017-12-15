################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/StdDriver/src/acmp.c \
../Library/StdDriver/src/adc.c \
../Library/StdDriver/src/clk.c \
../Library/StdDriver/src/fmc.c \
../Library/StdDriver/src/gpio.c \
../Library/StdDriver/src/i2c.c \
../Library/StdDriver/src/pwm.c \
../Library/StdDriver/src/retarget.c \
../Library/StdDriver/src/spi.c \
../Library/StdDriver/src/sys.c \
../Library/StdDriver/src/timer.c \
../Library/StdDriver/src/uart.c \
../Library/StdDriver/src/wdt.c \
../Library/StdDriver/src/wwdt.c 

OBJS += \
./Library/StdDriver/src/acmp.o \
./Library/StdDriver/src/adc.o \
./Library/StdDriver/src/clk.o \
./Library/StdDriver/src/fmc.o \
./Library/StdDriver/src/gpio.o \
./Library/StdDriver/src/i2c.o \
./Library/StdDriver/src/pwm.o \
./Library/StdDriver/src/retarget.o \
./Library/StdDriver/src/spi.o \
./Library/StdDriver/src/sys.o \
./Library/StdDriver/src/timer.o \
./Library/StdDriver/src/uart.o \
./Library/StdDriver/src/wdt.o \
./Library/StdDriver/src/wwdt.o 

C_DEPS += \
./Library/StdDriver/src/acmp.d \
./Library/StdDriver/src/adc.d \
./Library/StdDriver/src/clk.d \
./Library/StdDriver/src/fmc.d \
./Library/StdDriver/src/gpio.d \
./Library/StdDriver/src/i2c.d \
./Library/StdDriver/src/pwm.d \
./Library/StdDriver/src/retarget.d \
./Library/StdDriver/src/spi.d \
./Library/StdDriver/src/sys.d \
./Library/StdDriver/src/timer.d \
./Library/StdDriver/src/uart.d \
./Library/StdDriver/src/wdt.d \
./Library/StdDriver/src/wwdt.d 


# Each subdirectory must supply rules for building sources it contributes
Library/StdDriver/src/%.o: ../Library/StdDriver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


