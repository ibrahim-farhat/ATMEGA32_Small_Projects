################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
TIMERS_Lec3ChangeBuzzerToneByPot.lss \

FLASH_IMAGE += \
TIMERS_Lec3ChangeBuzzerToneByPot.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: TIMERS_Lec3ChangeBuzzerToneByPot.elf secondary-outputs

# Tool invocations
TIMERS_Lec3ChangeBuzzerToneByPot.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,TIMERS_Lec3ChangeBuzzerToneByPot.map -mmcu=atmega32 -o "TIMERS_Lec3ChangeBuzzerToneByPot.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TIMERS_Lec3ChangeBuzzerToneByPot.lss: TIMERS_Lec3ChangeBuzzerToneByPot.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S TIMERS_Lec3ChangeBuzzerToneByPot.elf  >"TIMERS_Lec3ChangeBuzzerToneByPot.lss"
	@echo 'Finished building: $@'
	@echo ' '

TIMERS_Lec3ChangeBuzzerToneByPot.hex: TIMERS_Lec3ChangeBuzzerToneByPot.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex TIMERS_Lec3ChangeBuzzerToneByPot.elf  "TIMERS_Lec3ChangeBuzzerToneByPot.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: TIMERS_Lec3ChangeBuzzerToneByPot.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 TIMERS_Lec3ChangeBuzzerToneByPot.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) TIMERS_Lec3ChangeBuzzerToneByPot.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
