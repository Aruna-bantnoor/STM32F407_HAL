/*
 * 001_led_toggle.c
 *
 *  Created on: Apr 16, 2026
 *      Author: admin
 */
#include "stm32f407xx.h"

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// LED Blinking normally Push Pull Configuration
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP; // Push pull configuration
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// NO LED Blinking
	/*GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD; // Open drain configuration
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;*/

	// LED Blinking with Less intensity
	/*GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD; // Open drain configuration
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;  // Blinks with less intensity*/

	// Using external pull up to blink with normal intensity
	/*GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD; // Open drain configuration
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;*/

	GPIO_PeriClockControl(GPIOD, ENABLE);

	GPIO_Init(&GpioLed);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
		delay();
	}
	return 0;
}
