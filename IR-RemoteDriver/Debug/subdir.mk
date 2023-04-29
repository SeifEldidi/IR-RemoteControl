################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gpiodriver.c \
../Internal_Interrupts.c \
../Interrupts.c \
../LCD.c \
../Remote.c \
../Timer0.c \
../Timer1.c \
../Timer2.c \
../main.c 

OBJS += \
./Gpiodriver.o \
./Internal_Interrupts.o \
./Interrupts.o \
./LCD.o \
./Remote.o \
./Timer0.o \
./Timer1.o \
./Timer2.o \
./main.o 

C_DEPS += \
./Gpiodriver.d \
./Internal_Interrupts.d \
./Interrupts.d \
./LCD.d \
./Remote.d \
./Timer0.d \
./Timer1.d \
./Timer2.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g3 -gdwarf-2 -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


