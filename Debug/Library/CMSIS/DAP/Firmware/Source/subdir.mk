################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CMSIS/DAP/Firmware/Source/DAP.c \
../Library/CMSIS/DAP/Firmware/Source/DAP_vendor.c \
../Library/CMSIS/DAP/Firmware/Source/JTAG_DP.c \
../Library/CMSIS/DAP/Firmware/Source/SWO.c \
../Library/CMSIS/DAP/Firmware/Source/SW_DP.c 

OBJS += \
./Library/CMSIS/DAP/Firmware/Source/DAP.o \
./Library/CMSIS/DAP/Firmware/Source/DAP_vendor.o \
./Library/CMSIS/DAP/Firmware/Source/JTAG_DP.o \
./Library/CMSIS/DAP/Firmware/Source/SWO.o \
./Library/CMSIS/DAP/Firmware/Source/SW_DP.o 

C_DEPS += \
./Library/CMSIS/DAP/Firmware/Source/DAP.d \
./Library/CMSIS/DAP/Firmware/Source/DAP_vendor.d \
./Library/CMSIS/DAP/Firmware/Source/JTAG_DP.d \
./Library/CMSIS/DAP/Firmware/Source/SWO.d \
./Library/CMSIS/DAP/Firmware/Source/SW_DP.d 


# Each subdirectory must supply rules for building sources it contributes
Library/CMSIS/DAP/Firmware/Source/%.o: ../Library/CMSIS/DAP/Firmware/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


