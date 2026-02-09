################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/device_drivers/gpio.c \
../Src/device_drivers/timers.c 

OBJS += \
./Src/device_drivers/gpio.o \
./Src/device_drivers/timers.o 

C_DEPS += \
./Src/device_drivers/gpio.d \
./Src/device_drivers/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/device_drivers/%.o Src/device_drivers/%.su Src/device_drivers/%.cyclo: ../Src/device_drivers/%.c Src/device_drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_L432KC -DSTM32L4 -DSTM32 -DSTM32L432KCUx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -Wall -Wextra -Wconversion -Wenum-conversion -Wno-sign-conversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-device_drivers

clean-Src-2f-device_drivers:
	-$(RM) ./Src/device_drivers/gpio.cyclo ./Src/device_drivers/gpio.d ./Src/device_drivers/gpio.o ./Src/device_drivers/gpio.su ./Src/device_drivers/timers.cyclo ./Src/device_drivers/timers.d ./Src/device_drivers/timers.o ./Src/device_drivers/timers.su

.PHONY: clean-Src-2f-device_drivers

