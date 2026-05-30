/*
 * stmToesp32.c
 *
 *  Created on: Apr 30, 2026
 *      Author: admin
 */


/*
 * ESP32 -> STM
 * 22 - 	PB6
 * 21 -     PB7
 * */
#include "stm32f407xx.h"

/* ================= GLOBAL HANDLE ================= */
I2C_Handle_t I2C1Handle;

/* ================= GPIO INIT ================= */
void I2C_GPIOInits(void)
{
    GPIO_Handle_t I2CPins;

    I2CPins.pGPIOx = GPIOB;
    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4; // AF4
    I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
    I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    // SCL -> PB6
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&I2CPins);

    // SDA -> PB7
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&I2CPins);
}

/* ================= I2C INIT ================= */
void I2C1_Inits(void)
{
    I2C1Handle.pI2Cx = I2C1;
    I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
    I2C1Handle.I2C_Config.I2C_DeviceAddress = 0x61;
    I2C1Handle.I2C_Config.I2C_SCLSpeed = 10000;

    I2C_Init(&I2C1Handle);
}

/* ================= MAIN ================= */
int main(void)
{
    char msg[] = "HELLO";
    uint8_t rxBuf[10];

    // Enable clocks
    GPIO_PeriClockControl(GPIOB, ENABLE);
    I2C1_PCLK_EN();

    // Init
    I2C_GPIOInits();
    I2C1_Inits();

    // Enable I2C
    I2C_PeripheralControl(I2C1, ENABLE);

    while(1)
    {
        // Send data to ESP32
        I2C_MasterSendData(&I2C1Handle, (uint8_t*)msg, 5, 0x68);

        for(volatile int i=0;i<500000;i++);

        // Receive response
        I2C_MasterReceiveData(&I2C1Handle, rxBuf, 2, 0x68);

        // put breakpoint here to check rxBuf

        for(volatile int i=0;i<500000;i++);
    }
}
