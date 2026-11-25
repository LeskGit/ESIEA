################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/stm32h750b_dk/subdir.mk
-include Drivers/BSP/Components/wm8994/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := TNS_STM32_SAI_BSP3
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
TNS_STM32_SAI_BSP3.elf \

MAP_FILES += \
TNS_STM32_SAI_BSP3.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
TNS_STM32_SAI_BSP3.list \


# All Target
all: main-build

# Main-build Target
main-build: TNS_STM32_SAI_BSP3.elf secondary-outputs

# Tool invocations
TNS_STM32_SAI_BSP3.elf TNS_STM32_SAI_BSP3.map: $(OBJS) $(USER_OBJS) C:\Users\Hacks\Documents\GitHub\ESIEA\ESIEA\Cours\Traitement\ Numérique\ du\ Signal\TP\TNS_STM32_SAI_BSP3\TNS_STM32_SAI_BSP3\STM32H750XBHX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "TNS_STM32_SAI_BSP3.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\Hacks\Documents\GitHub\ESIEA\ESIEA\Cours\Traitement Numérique du Signal\TP\TNS_STM32_SAI_BSP3\TNS_STM32_SAI_BSP3\STM32H750XBHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="TNS_STM32_SAI_BSP3.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

TNS_STM32_SAI_BSP3.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "TNS_STM32_SAI_BSP3.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) TNS_STM32_SAI_BSP3.elf TNS_STM32_SAI_BSP3.list TNS_STM32_SAI_BSP3.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
