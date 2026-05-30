/*
 * timer_interrupt_led_toggle.c
 */

#include "stm32f407xx.h"

/************* LED INIT (PD12) *************/
void LED_Init(void)
{
    GPIO_Handle_t led;

    led.pGPIOx = GPIOD;
    led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    GPIO_Init(&led);
}

/************* TIMER2 INIT *************/
void TIM2_Init(void)
{
    // Enable TIM2 clock
    TIM2_PCLK_EN();

    /*
     * Timer clock = 16 MHz
     *
     * Prescaler = 16000 - 1
     * Timer counter clock = 16MHz / 16000 = 1 kHz
     */

    TIM2->PSC = 16000 - 1;

    /*
     * ARR = 1000 - 1
     * Overflow every 1000 counts
     * 1000 / 1000Hz = 1 second
     */

    TIM2->ARR = 1000 - 1;

    // Enable update interrupt
    TIM2->DIER |= (1 << 0);

    // Enable TIM2 interrupt in NVIC
    *NVIC_ISER0 |= (1 << 28);

    // Start timer
    TIM2->CR1 |= (1 << 0);
}

/************* TIMER2 ISR *************/
void TIM2_IRQHandler(void)
{
    // Check update interrupt flag
    if(TIM2->SR & (1 << 0))
    {
        // Clear update interrupt flag
        TIM2->SR &= ~(1 << 0);

        // Toggle LED
        GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
    }
}

/************* MAIN *************/
int main(void)
{
    // Initialize LED
    LED_Init();

    // Initialize Timer2
    TIM2_Init();

    while(1)
    {
        // CPU free
    }
}
