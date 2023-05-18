################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../CLCD_program.c \
../DIO_program.c \
../EXTI_program.c \
../GIE_program.c \
../KEYPAD_program.c \
../LIBRARY_program.c \
../MOTOR_program.c \
../PORT_program.c \
../SSD_program.c \
../STEPPER_program.c \
../TIMERS_program.c \
../main.c 

OBJS += \
./ADC_program.o \
./CLCD_program.o \
./DIO_program.o \
./EXTI_program.o \
./GIE_program.o \
./KEYPAD_program.o \
./LIBRARY_program.o \
./MOTOR_program.o \
./PORT_program.o \
./SSD_program.o \
./STEPPER_program.o \
./TIMERS_program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./CLCD_program.d \
./DIO_program.d \
./EXTI_program.d \
./GIE_program.d \
./KEYPAD_program.d \
./LIBRARY_program.d \
./MOTOR_program.d \
./PORT_program.d \
./SSD_program.d \
./STEPPER_program.d \
./TIMERS_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


