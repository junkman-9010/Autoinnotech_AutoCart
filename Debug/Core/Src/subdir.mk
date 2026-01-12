################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/MCT8316Z_Control.c \
../Core/Src/TOF400C_VL53L1X.c \
../Core/Src/hw_can.c \
../Core/Src/hw_dac.c \
../Core/Src/hw_gpio.c \
../Core/Src/hw_i2c.c \
../Core/Src/hw_rs485.c \
../Core/Src/hw_rtc.c \
../Core/Src/hw_spi.c \
../Core/Src/hw_system.c \
../Core/Src/hw_tim.c \
../Core/Src/hw_uart.c \
../Core/Src/hw_usb.c \
../Core/Src/main.c \
../Core/Src/modbus-rtu.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/MCT8316Z_Control.o \
./Core/Src/TOF400C_VL53L1X.o \
./Core/Src/hw_can.o \
./Core/Src/hw_dac.o \
./Core/Src/hw_gpio.o \
./Core/Src/hw_i2c.o \
./Core/Src/hw_rs485.o \
./Core/Src/hw_rtc.o \
./Core/Src/hw_spi.o \
./Core/Src/hw_system.o \
./Core/Src/hw_tim.o \
./Core/Src/hw_uart.o \
./Core/Src/hw_usb.o \
./Core/Src/main.o \
./Core/Src/modbus-rtu.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/MCT8316Z_Control.d \
./Core/Src/TOF400C_VL53L1X.d \
./Core/Src/hw_can.d \
./Core/Src/hw_dac.d \
./Core/Src/hw_gpio.d \
./Core/Src/hw_i2c.d \
./Core/Src/hw_rs485.d \
./Core/Src/hw_rtc.d \
./Core/Src/hw_spi.d \
./Core/Src/hw_system.d \
./Core/Src/hw_tim.d \
./Core/Src/hw_uart.d \
./Core/Src/hw_usb.d \
./Core/Src/main.d \
./Core/Src/modbus-rtu.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/MCT8316Z_Control.cyclo ./Core/Src/MCT8316Z_Control.d ./Core/Src/MCT8316Z_Control.o ./Core/Src/MCT8316Z_Control.su ./Core/Src/TOF400C_VL53L1X.cyclo ./Core/Src/TOF400C_VL53L1X.d ./Core/Src/TOF400C_VL53L1X.o ./Core/Src/TOF400C_VL53L1X.su ./Core/Src/hw_can.cyclo ./Core/Src/hw_can.d ./Core/Src/hw_can.o ./Core/Src/hw_can.su ./Core/Src/hw_dac.cyclo ./Core/Src/hw_dac.d ./Core/Src/hw_dac.o ./Core/Src/hw_dac.su ./Core/Src/hw_gpio.cyclo ./Core/Src/hw_gpio.d ./Core/Src/hw_gpio.o ./Core/Src/hw_gpio.su ./Core/Src/hw_i2c.cyclo ./Core/Src/hw_i2c.d ./Core/Src/hw_i2c.o ./Core/Src/hw_i2c.su ./Core/Src/hw_rs485.cyclo ./Core/Src/hw_rs485.d ./Core/Src/hw_rs485.o ./Core/Src/hw_rs485.su ./Core/Src/hw_rtc.cyclo ./Core/Src/hw_rtc.d ./Core/Src/hw_rtc.o ./Core/Src/hw_rtc.su ./Core/Src/hw_spi.cyclo ./Core/Src/hw_spi.d ./Core/Src/hw_spi.o ./Core/Src/hw_spi.su ./Core/Src/hw_system.cyclo ./Core/Src/hw_system.d ./Core/Src/hw_system.o ./Core/Src/hw_system.su ./Core/Src/hw_tim.cyclo ./Core/Src/hw_tim.d ./Core/Src/hw_tim.o ./Core/Src/hw_tim.su ./Core/Src/hw_uart.cyclo ./Core/Src/hw_uart.d ./Core/Src/hw_uart.o ./Core/Src/hw_uart.su ./Core/Src/hw_usb.cyclo ./Core/Src/hw_usb.d ./Core/Src/hw_usb.o ./Core/Src/hw_usb.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/modbus-rtu.cyclo ./Core/Src/modbus-rtu.d ./Core/Src/modbus-rtu.o ./Core/Src/modbus-rtu.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

