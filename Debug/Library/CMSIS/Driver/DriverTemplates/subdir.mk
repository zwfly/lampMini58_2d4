################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CMSIS/Driver/DriverTemplates/Driver_CAN.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_Flash.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_I2C.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_MCI.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_SAI.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_SPI.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_USART.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_USBD.c \
../Library/CMSIS/Driver/DriverTemplates/Driver_USBH.c 

OBJS += \
./Library/CMSIS/Driver/DriverTemplates/Driver_CAN.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_Flash.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_I2C.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_MCI.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_SAI.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_SPI.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_USART.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_USBD.o \
./Library/CMSIS/Driver/DriverTemplates/Driver_USBH.o 

C_DEPS += \
./Library/CMSIS/Driver/DriverTemplates/Driver_CAN.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_Flash.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_I2C.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_MCI.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_SAI.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_SPI.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_USART.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_USBD.d \
./Library/CMSIS/Driver/DriverTemplates/Driver_USBH.d 


# Each subdirectory must supply rules for building sources it contributes
Library/CMSIS/Driver/DriverTemplates/%.o: ../Library/CMSIS/Driver/DriverTemplates/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


