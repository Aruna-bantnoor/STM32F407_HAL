################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/src/05_button_interrupt.c \
../drivers/src/stm32f407xx_gpio_driver.c \
../drivers/src/stm32f407xx_i2c_driver.c 

OBJS += \
./drivers/src/05_button_interrupt.o \
./drivers/src/stm32f407xx_gpio_driver.o \
./drivers/src/stm32f407xx_i2c_driver.o 

C_DEPS += \
./drivers/src/05_button_interrupt.d \
./drivers/src/stm32f407xx_gpio_driver.d \
./drivers/src/stm32f407xx_i2c_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/src/%.o drivers/src/%.su drivers/src/%.cyclo: ../drivers/src/%.c drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32Workspace/19_GPIO_Interrupt/drivers/inc" -I"D:/STM32Workspace/19_GPIO_Interrupt/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-src

clean-drivers-2f-src:
	-$(RM) ./drivers/src/05_button_interrupt.cyclo ./drivers/src/05_button_interrupt.d ./drivers/src/05_button_interrupt.o ./drivers/src/05_button_interrupt.su ./drivers/src/stm32f407xx_gpio_driver.cyclo ./drivers/src/stm32f407xx_gpio_driver.d ./drivers/src/stm32f407xx_gpio_driver.o ./drivers/src/stm32f407xx_gpio_driver.su ./drivers/src/stm32f407xx_i2c_driver.cyclo ./drivers/src/stm32f407xx_i2c_driver.d ./drivers/src/stm32f407xx_i2c_driver.o ./drivers/src/stm32f407xx_i2c_driver.su

.PHONY: clean-drivers-2f-src

