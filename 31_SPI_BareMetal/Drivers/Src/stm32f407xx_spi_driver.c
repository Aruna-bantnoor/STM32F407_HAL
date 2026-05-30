/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: Apr 30, 2026
 *      Author: 91762
 */


/*
 * Peripheral Clock setup
 */
/********************************************************************
 * @fn                  - GPIO_Init
 *
 * @brief               - This function enables or disables peripheral clock for given GPIO port
 *
 * @param[in]           - base address of the GPIO peripheral
 * @param[in]           - enable or disbale macros
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */


#include <stm32f407xx_spi_driver.h>



/*
* Peripheral Clock setup
*/
/********************************************************************
* @fn                  - GPIO_Init
*
* @brief               - This function enables or disables peripheral clock for given GPIO port
*
* @param[in]           - base address of the GPIO peripheral
* @param[in]           - enable or disbale macros
* @param[in]           -
*
* @return              - none
*
* @Note                - none
*
*/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx ==  SPI1)
			SPI1_PCLK_EN();
		else if(pSPIx == SPI2)
			SPI2_PCLK_EN();
		else if(pSPIx == SPI3)
			SPI3_PCLK_EN();
	}
	else
	{
		if(pSPIx ==  SPI1)
			SPI1_PCLK_DI();
		else if(pSPIx == SPI2)
			SPI2_PCLK_DI();
		else if(pSPIx == SPI3)
			SPI3_PCLK_DI();
	}
}

/*
* Init and De-init
*/
/********************************************************************
* @fn                  - GPIO_Init
*
* @brief               - This function enables or disables peripheral clock for given GPIO port
*
* @param[in]           - base address of the GPIO peripheral
* @param[in]           - enable or disbale macros
* @param[in]           -
*
* @return              - none
*
* @Note                - none
*
*/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	// enable peripheral clock
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	// configure SPI_CR1 register

	uint32_t temp = 0;

	// configure device mode
	temp |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;

	// configure bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// BIDIMODE should be cleared
		temp &= ~(1 << 15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		// BIDIMODE should be set
		temp |= (1 << 15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		// BIDIMODE should be cleared
		temp &= ~(1 << 15);
		// RXONLY bit must be set
		temp |= (1 << 10);
	}

	// configure spi serial clock speed(baud rate)
	temp |= pSPIHandle->SPIConfig.SPI_SclkSpeed << 3;

	// configure DFF
	temp |= pSPIHandle->SPIConfig.SPI_DFF << 11;
	// configure CPOL
	temp |= pSPIHandle->SPIConfig.SPI_CPOL << 1;

	// configure CPHA
	temp |= pSPIHandle->SPIConfig.SPI_CPHA << 0;

	temp |= pSPIHandle->SPIConfig.SPI_SSM << 9;

	pSPIHandle->pSPIx->CR1 = temp;
}

/********************************************************************
* @fn                  - GPIO_Init
*
* @brief               - This function enables or disables peripheral clock for given GPIO port
*
* @param[in]           - base address of the GPIO peripheral
* @param[in]           - enable or disbale macros
* @param[in]           -
*
* @return              - none
*
* @Note                - none
*
*/
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t FlagName)
{
	if(pSPIx->SR && FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}
/*
* Data send and receive
*/
/********************************************************************
* @fn                  - GPIO_Init
*
* @brief               - This function enables or disables peripheral clock for given GPIO port
*
* @param[in]           - base address of the GPIO peripheral
* @param[in]           - enable or disbale macros
* @param[in]           -
*
* @return              - none
*
* @Note                - This is a blocking call
*
*/
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t len)
{
	while(len > 0)
	{
		// wait until TXE is set
	    while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET);

	    // check the DFF bit in CR1
	    if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
	    {
	    	// 16 bit DFF
	    	// load the data to DR
	    	pSPIx->DR = *((uint16_t*)pTxBuffer);
	    	len--;
	    	len--;
	    	(uint16_t*)(pTxBuffer)++;
	    }
	    else
	    {
	    	// 8 bit DFF
	    	pSPIx->DR = *(pTxBuffer);
	    	len--;
	    	pTxBuffer++;
	    }
	}
}

/********************************************************************
* @fn                  - GPIO_Init
*
* @brief               - This function enables or disables peripheral clock for given GPIO port
*
* @param[in]           - base address of the GPIO peripheral
* @param[in]           - enable or disbale macros
* @param[in]           -
*
* @return              - none
*
* @Note                - none
*
*/
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t len)
{
	while(len > 0)
	{
		// wait until RXNE is set
		while(SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG) == FLAG_RESET);

		// check the DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit DFF
			// load the data from DR to Rxbuffer
			*((uint16_t*)pRxBuffer) = pSPIx->DR;
			len--;
			len--;
			(uint16_t*)(pRxBuffer)++;
		}
		else
		{
			// 8 bit DFF
			 *(pRxBuffer) = pSPIx->DR;
			len--;
			pRxBuffer++;
		}
	}
}

void SPI_TransmitReceive(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint8_t *pRxBuffer, uint32_t len)
{
    while(len > 0)
    {
        // 1. Wait until TX buffer empty
        while(!(pSPIx->SR & (1 << SPI_SR_TXE)));

        // 2. Send data
        pSPIx->DR = *pTxBuffer;

        // 3. Wait until RX buffer not empty
        while(!(pSPIx->SR & (1 << SPI_SR_RXNE)));

        // 4. Read received data
        *pRxBuffer = pSPIx->DR;

        // 5. Move pointers
        pTxBuffer++;
        pRxBuffer++;
        len--;
    }

    // Wait until SPI not busy
    while(pSPIx->SR & (1 << SPI_SR_BSY));

    // Clear OVR
    uint8_t temp;
    temp = pSPIx->DR;
    temp = pSPIx->SR;
}
/********************************************************************
* @fn                  - GPIO_Init
*
* @brief               - This function enables or disables peripheral clock for given GPIO port
*
* @param[in]           - base address of the GPIO peripheral
* @param[in]           - enable or disbale macros
* @param[in]           -
*
* @return              - none
*
* @Note                - none
*
*/
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

/********************************************************************
* @fn                  - GPIO_Init
*
* @brief               - This function enables or disables peripheral clock for given GPIO port
*
* @param[in]           - base address of the GPIO peripheral
* @param[in]           - enable or disbale macros
* @param[in]           -
*
* @return              - none
*
* @Note                - none
*
*/
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

/********************************************************************
* @fn                  - GPIO_Init
*
* @brief               - This function enables or disables peripheral clock for given GPIO port
*
* @param[in]           - base address of the GPIO peripheral
* @param[in]           - enable or disbale macros
* @param[in]           -
*
* @return              - none
*
* @Note                - none
*
*/
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}
	else
	{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}

}


















































