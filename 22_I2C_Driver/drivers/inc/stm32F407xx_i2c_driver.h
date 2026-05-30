/*
 * stm32F407xx_i2c_driver.h
 *
 *  Created on: Apr 29, 2026
 *      Author: admin
 */

#ifndef INC_STM32F407XX_I2C_DRIVER_H_
#define INC_STM32F407XX_I2C_DRIVER_H_

#include "stm32f407xx.h"

/*
 * Configuration structure
 */
typedef struct
{
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddress;
    uint8_t  I2C_AckControl;
    uint8_t  I2C_FMDutyCycle;
} I2C_Config_t;

/*
 * Handle structure
 */
typedef struct
{
    I2C_RegDef_t *pI2Cx;
    I2C_Config_t  I2C_Config;
} I2C_Handle_t;

/*
 * SCL Speed
 */
#define I2C_SCL_SPEED_SM    100000
#define I2C_SCL_SPEED_FM    400000

/*
 * ACK control
 */
#define I2C_ACK_ENABLE      1
#define I2C_ACK_DISABLE     0

/*
 * Fast mode duty
 */
#define I2C_FM_DUTY_2       0
#define I2C_FM_DUTY_16_9    1

/*
 * Flags
 */
#define I2C_FLAG_TXE   (1 << I2C_SR1_TXE)
#define I2C_FLAG_RXNE  (1 << I2C_SR1_RXNE)
#define I2C_FLAG_SB    (1 << I2C_SR1_SB)
#define I2C_FLAG_ADDR  (1 << I2C_SR1_ADDR)
#define I2C_FLAG_BTF   (1 << I2C_SR1_BTF)

#define FLAG_SET       1
#define FLAG_RESET     0

/*
 * APIs
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,
                        uint8_t *pTxBuffer,
                        uint32_t len,
                        uint8_t SlaveAddr);

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,
                           uint8_t *pRxBuffer,
                           uint32_t len,
                           uint8_t SlaveAddr);

#endif
