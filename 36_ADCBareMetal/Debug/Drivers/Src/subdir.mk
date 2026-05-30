################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm32f407xx_RCC_driver.c \
../Drivers/Src/stm32f407xx_adc_driver.c \
../Drivers/Src/stm32f407xx_gpio_driver.c \
../Drivers/Src/stm32f407xx_i2c_driver.c \
../Drivers/Src/stm32f407xx_spi_driver.c \
../Drivers/Src/stm32f407xx_systick_driver.c \
../Drivers/Src/stm32f407xx_timer_driver.c \
../Drivers/Src/stm32f407xx_usart_driver.c 

OBJS += \
./Drivers/Src/stm32f407xx_RCC_driver.o \
./Drivers/Src/stm32f407xx_adc_driver.o \
./Drivers/Src/stm32f407xx_gpio_driver.o \
./Drivers/Src/stm32f407xx_i2c_driver.o \
./Drivers/Src/stm32f407xx_spi_driver.o \
./Drivers/Src/stm32f407xx_systick_driver.o \
./Drivers/Src/stm32f407xx_timer_driver.o \
./Drivers/Src/stm32f407xx_usart_driver.o 

C_DEPS += \
./Drivers/Src/stm32f407xx_RCC_driver.d \
./Drivers/Src/stm32f407xx_adc_driver.d \
./Drivers/Src/stm32f407xx_gpio_driver.d \
./Drivers/Src/stm32f407xx_i2c_driver.d \
./Drivers/Src/stm32f407xx_spi_driver.d \
./Drivers/Src/stm32f407xx_systick_driver.d \
./Drivers/Src/stm32f407xx_timer_driver.d \
./Drivers/Src/stm32f407xx_usart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I"D:/STM32Workspace/36_ADCBareMetal/Drivers/Inc" -I"D:/STM32Workspace/36_ADCBareMetal/Drivers/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/stm32f407xx_RCC_driver.cyclo ./Drivers/Src/stm32f407xx_RCC_driver.d ./Drivers/Src/stm32f407xx_RCC_driver.o ./Drivers/Src/stm32f407xx_RCC_driver.su ./Drivers/Src/stm32f407xx_adc_driver.cyclo ./Drivers/Src/stm32f407xx_adc_driver.d ./Drivers/Src/stm32f407xx_adc_driver.o ./Drivers/Src/stm32f407xx_adc_driver.su ./Drivers/Src/stm32f407xx_gpio_driver.cyclo ./Drivers/Src/stm32f407xx_gpio_driver.d ./Drivers/Src/stm32f407xx_gpio_driver.o ./Drivers/Src/stm32f407xx_gpio_driver.su ./Drivers/Src/stm32f407xx_i2c_driver.cyclo ./Drivers/Src/stm32f407xx_i2c_driver.d ./Drivers/Src/stm32f407xx_i2c_driver.o ./Drivers/Src/stm32f407xx_i2c_driver.su ./Drivers/Src/stm32f407xx_spi_driver.cyclo ./Drivers/Src/stm32f407xx_spi_driver.d ./Drivers/Src/stm32f407xx_spi_driver.o ./Drivers/Src/stm32f407xx_spi_driver.su ./Drivers/Src/stm32f407xx_systick_driver.cyclo ./Drivers/Src/stm32f407xx_systick_driver.d ./Drivers/Src/stm32f407xx_systick_driver.o ./Drivers/Src/stm32f407xx_systick_driver.su ./Drivers/Src/stm32f407xx_timer_driver.cyclo ./Drivers/Src/stm32f407xx_timer_driver.d ./Drivers/Src/stm32f407xx_timer_driver.o ./Drivers/Src/stm32f407xx_timer_driver.su ./Drivers/Src/stm32f407xx_usart_driver.cyclo ./Drivers/Src/stm32f407xx_usart_driver.d ./Drivers/Src/stm32f407xx_usart_driver.o ./Drivers/Src/stm32f407xx_usart_driver.su

.PHONY: clean-Drivers-2f-Src

