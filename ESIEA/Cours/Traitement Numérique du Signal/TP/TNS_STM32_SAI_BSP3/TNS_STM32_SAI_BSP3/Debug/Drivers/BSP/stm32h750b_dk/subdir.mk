################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/stm32h750b_dk/stm32h750b_discovery.c \
../Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_audio.c \
../Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_bus.c 

OBJS += \
./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery.o \
./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_audio.o \
./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_bus.o 

C_DEPS += \
./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery.d \
./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_audio.d \
./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_bus.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/stm32h750b_dk/%.o Drivers/BSP/stm32h750b_dk/%.su Drivers/BSP/stm32h750b_dk/%.cyclo: ../Drivers/BSP/stm32h750b_dk/%.c Drivers/BSP/stm32h750b_dk/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/BSP/stm32h750b_dk -I../Drivers/BSP/Components/common -I../Drivers/BSP/Components/wm8994 -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-stm32h750b_dk

clean-Drivers-2f-BSP-2f-stm32h750b_dk:
	-$(RM) ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery.cyclo ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery.d ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery.o ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery.su ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_audio.cyclo ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_audio.d ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_audio.o ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_audio.su ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_bus.cyclo ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_bus.d ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_bus.o ./Drivers/BSP/stm32h750b_dk/stm32h750b_discovery_bus.su

.PHONY: clean-Drivers-2f-BSP-2f-stm32h750b_dk

