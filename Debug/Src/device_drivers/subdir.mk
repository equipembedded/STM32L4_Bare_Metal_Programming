################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/device_drivers/clocks.c \
../Src/device_drivers/ens160.c \
../Src/device_drivers/exti.c \
../Src/device_drivers/gpio.c \
../Src/device_drivers/i2c.c \
../Src/device_drivers/spi.c \
../Src/device_drivers/ssd1306.c \
../Src/device_drivers/timers.c \
../Src/device_drivers/usart.c 

OBJS += \
./Src/device_drivers/clocks.o \
./Src/device_drivers/ens160.o \
./Src/device_drivers/exti.o \
./Src/device_drivers/gpio.o \
./Src/device_drivers/i2c.o \
./Src/device_drivers/spi.o \
./Src/device_drivers/ssd1306.o \
./Src/device_drivers/timers.o \
./Src/device_drivers/usart.o 

C_DEPS += \
./Src/device_drivers/clocks.d \
./Src/device_drivers/ens160.d \
./Src/device_drivers/exti.d \
./Src/device_drivers/gpio.d \
./Src/device_drivers/i2c.d \
./Src/device_drivers/spi.d \
./Src/device_drivers/ssd1306.d \
./Src/device_drivers/timers.d \
./Src/device_drivers/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/device_drivers/%.o Src/device_drivers/%.su Src/device_drivers/%.cyclo: ../Src/device_drivers/%.c Src/device_drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_L432KC -DSTM32L4 -DSTM32 -DSTM32L432KCUx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -Wall -Wextra -Wconversion -Wenum-conversion -Wno-sign-conversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-device_drivers

clean-Src-2f-device_drivers:
	-$(RM) ./Src/device_drivers/clocks.cyclo ./Src/device_drivers/clocks.d ./Src/device_drivers/clocks.o ./Src/device_drivers/clocks.su ./Src/device_drivers/ens160.cyclo ./Src/device_drivers/ens160.d ./Src/device_drivers/ens160.o ./Src/device_drivers/ens160.su ./Src/device_drivers/exti.cyclo ./Src/device_drivers/exti.d ./Src/device_drivers/exti.o ./Src/device_drivers/exti.su ./Src/device_drivers/gpio.cyclo ./Src/device_drivers/gpio.d ./Src/device_drivers/gpio.o ./Src/device_drivers/gpio.su ./Src/device_drivers/i2c.cyclo ./Src/device_drivers/i2c.d ./Src/device_drivers/i2c.o ./Src/device_drivers/i2c.su ./Src/device_drivers/spi.cyclo ./Src/device_drivers/spi.d ./Src/device_drivers/spi.o ./Src/device_drivers/spi.su ./Src/device_drivers/ssd1306.cyclo ./Src/device_drivers/ssd1306.d ./Src/device_drivers/ssd1306.o ./Src/device_drivers/ssd1306.su ./Src/device_drivers/timers.cyclo ./Src/device_drivers/timers.d ./Src/device_drivers/timers.o ./Src/device_drivers/timers.su ./Src/device_drivers/usart.cyclo ./Src/device_drivers/usart.d ./Src/device_drivers/usart.o ./Src/device_drivers/usart.su

.PHONY: clean-Src-2f-device_drivers

