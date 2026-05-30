/*
 * stm32f407xx_i2c_driver.c
 *
 *  Created on: Apr 29, 2026
 *      Author: admin
 */

#include "stm32f407xx_i2c_driver.h"

/*
 * Private helpers
 */
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    SlaveAddr = SlaveAddr << 1;
    SlaveAddr &= ~(1);
    pI2Cx->DR = SlaveAddr;
}

static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    SlaveAddr = SlaveAddr << 1;
    SlaveAddr |= 1;
    pI2Cx->DR = SlaveAddr;
}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx)
{
    volatile uint32_t dummy;
    dummy = pI2Cx->SR1;
    dummy = pI2Cx->SR2;
    (void)dummy;
}

/*
 * Clock helper (simplified)
 */
uint32_t RCC_GetPCLK1Value(void)
{
    return 16000000;
}

/*
 * Init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    uint32_t tempreg = 0;

    // ACK
    tempreg |= (pI2CHandle->I2C_Config.I2C_AckControl << I2C_CR1_ACK);
    pI2CHandle->pI2Cx->CR1 = tempreg;

    // CR2
    tempreg = RCC_GetPCLK1Value() / 1000000U;
    pI2CHandle->pI2Cx->CR2 = tempreg & 0x3F;

    // OAR1
    tempreg = 0;
    tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
    tempreg |= (1 << 14);
    pI2CHandle->pI2Cx->OAR1 = tempreg;

    // CCR
    uint16_t ccr_value;
    tempreg = 0;

    if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        ccr_value = RCC_GetPCLK1Value() /
                    (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
        tempreg |= (ccr_value & 0xFFF);
    }
    else
    {
        tempreg |= (1 << I2C_CCR_FS);

        if (pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
        {
            ccr_value = RCC_GetPCLK1Value() /
                        (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
        }
        else
        {
            tempreg |= (1 << I2C_CCR_DUTY);
            ccr_value = RCC_GetPCLK1Value() /
                        (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
        }

        tempreg |= (ccr_value & 0xFFF);
    }

    pI2CHandle->pI2Cx->CCR = tempreg;

    // TRISE
    if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        tempreg = (RCC_GetPCLK1Value() / 1000000U) + 1;
    }
    else
    {
        tempreg = ((RCC_GetPCLK1Value() * 300) / 1000000000U) + 1;
    }

    pI2CHandle->pI2Cx->TRISE = tempreg & 0x3F;
}

/*
 * Peripheral Control
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
        pI2Cx->CR1 |= (1 << I2C_CR1_PE);
    else
        pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
}

/*
 * ACK Control
 */
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if (EnOrDi == I2C_ACK_ENABLE)
        pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
    else
        pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
}

/*
 * Flag check
 */
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
    if (pI2Cx->SR1 & FlagName)
        return FLAG_SET;

    return FLAG_RESET;
}

/*
 * Master Send
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,
                        uint8_t *pTxBuffer,
                        uint32_t len,
                        uint8_t SlaveAddr)
{
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

    I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, SlaveAddr);

    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));

    I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

    while (len > 0)
    {
        while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));

        pI2CHandle->pI2Cx->DR = *pTxBuffer;
        pTxBuffer++;
        len--;
    }

    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF));

    I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
}

/*
 * Master Receive
 */
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,
                           uint8_t *pRxBuffer,
                           uint32_t len,
                           uint8_t SlaveAddr)
{
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

    I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx, SlaveAddr);

    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));

    if (len == 1)
    {
        I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);
        I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
        I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

        while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE));

        *pRxBuffer = pI2CHandle->pI2Cx->DR;
        return;
    }

    I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

    for (uint32_t i = len; i > 0; i--)
    {
        while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE));

        if (i == 2)
        {
            I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);
            I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
        }

        *pRxBuffer = pI2CHandle->pI2Cx->DR;
        pRxBuffer++;
    }
}
