################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/DIO_V1/subdir.mk
-include HAL/LCD_handler_v1/subdir.mk
-include HAL/KeyPad_Handler_V1/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Safe_Lock_Using_Keypad_And_LCD.lss \

FLASH_IMAGE += \
Safe_Lock_Using_Keypad_And_LCD.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Safe_Lock_Using_Keypad_And_LCD.elf secondary-outputs

# Tool invocations
Safe_Lock_Using_Keypad_And_LCD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Safe_Lock_Using_Keypad_And_LCD.map -mmcu=atmega32 -o "Safe_Lock_Using_Keypad_And_LCD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Safe_Lock_Using_Keypad_And_LCD.lss: Safe_Lock_Using_Keypad_And_LCD.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Safe_Lock_Using_Keypad_And_LCD.elf  >"Safe_Lock_Using_Keypad_And_LCD.lss"
	@echo 'Finished building: $@'
	@echo ' '

Safe_Lock_Using_Keypad_And_LCD.hex: Safe_Lock_Using_Keypad_And_LCD.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Safe_Lock_Using_Keypad_And_LCD.elf  "Safe_Lock_Using_Keypad_And_LCD.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Safe_Lock_Using_Keypad_And_LCD.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Safe_Lock_Using_Keypad_And_LCD.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Safe_Lock_Using_Keypad_And_LCD.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
