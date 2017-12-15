################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/USB/USBD_Config_0.c 

OBJS += \
./Library/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/USB/USBD_Config_0.o 

C_DEPS += \
./Library/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/USB/USBD_Config_0.d 


# Each subdirectory must supply rules for building sources it contributes
Library/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/USB/%.o: ../Library/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/USB/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\StdDriver\inc" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\Device\Nuvoton\Mini58Series\Include" -I"E:\work\LCD2.4\project\lampMini58_2d4\Library\CMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


