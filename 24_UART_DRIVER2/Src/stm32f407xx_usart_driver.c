/*
 * stm32f407xx_usart_driver.c
 *
 *  Created on: Apr 30, 2026
 *      Author: 91762
 */


#include <stm32f407xx.h>



/********************************************************************
 * @fn                  - USART_PeriClockControl
 *
 * @brief               -
 *
 * @param[in]           -
 * @param[in]           -
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pUSARTx ==  USART1)
			USART1_PCLK_EN();
		else if(pUSARTx ==  USART2)
			USART2_PCLK_EN();
		else if(pUSARTx ==  USART3)
			USART3_PCLK_EN();
		else if(pUSARTx ==  UART4)
			UART4_PCLK_EN();
		else if(pUSARTx ==  UART5)
			UART5_PCLK_EN();
		else if(pUSARTx ==  USART6)
			USART6_PCLK_EN();
	}
	else
	{
		if(pUSARTx ==  USART1)
			USART1_PCLK_DI();
		else if(pUSARTx ==  USART2)
			USART2_PCLK_DI();
		else if(pUSARTx ==  USART3)
			USART3_PCLK_DI();
		else if(pUSARTx ==  UART4)
			UART4_PCLK_DI();
		else if(pUSARTx ==  UART5)
			UART5_PCLK_DI();
		else if(pUSARTx ==  USART6)
			USART6_PCLK_DI();
	}
}

/********************************************************************
 * @fn                  - USART_PeripheralControl
 *
 * @brief               -
 *
 * @param[in]           -
 * @param[in]           -
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pUSARTx->CR1 |= (1 << 13);
	}
	else
	{
		pUSARTx->CR1 &= (~1 << 13);
	}
}

/********************************************************************
 * @fn                  - USART_GetFlagStatus
 *
 * @brief               -
 *
 * @param[in]           -
 * @param[in]           -
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx,uint32_t FlagName)
{
	if(pUSARTx->SR & FlagName)
		{
			return FLAG_SET;
		}
		return FLAG_RESET;
}

/********************************************************************
 * @fn                  - USART_SetBaudRate
 *
 * @brief               -
 *
 * @param[in]           -
 * @param[in]           -
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_SetBaudRate(USART_RegDef_t *pUSARTx,uint32_t BaudRate)
{
	//Variable to hold the APB clock
		uint32_t PCLKx;

		uint32_t usartdiv;

		//variables to hold Mantissa and Fraction values
		uint32_t M_part,F_part;

	  uint32_t tempreg=0;

	  //Get the value of APB bus clock in to the variable PCLKx
	  if(pUSARTx == USART1 || pUSARTx == USART6)
	  {
		   //USART1 and USART6 are hanging on APB2 bus
		   PCLKx = RCC_GetPCLK2Value();
	  }else
	  {
		   PCLKx = RCC_GetPCLK1Value();
	  }

	  //Check for OVER8 configuration bit
	  if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
	  {
		   //OVER8 = 1 , over sampling by 8
		   usartdiv = ((25 * PCLKx) / (2 *BaudRate));
	  }else
	  {
		   //over sampling by 16
		   usartdiv = ((25 * PCLKx) / (4 *BaudRate));
	  }

	  //Calculate the Mantissa part
	  M_part = usartdiv/100;

	  //Place the Mantissa part in appropriate bit position . refer USART_BRR
	  tempreg |= M_part << 4;

	  //Extract the fraction part
	  F_part = (usartdiv - (M_part * 100));

	  //Calculate the final fractional
	  if(pUSARTx->CR1 & ( 1 << USART_CR1_OVER8))
	   {
		  //OVER8 = 1 , over sampling by 8
		  F_part = ((( F_part * 8)+ 50) / 100)& ((uint8_t)0x07);

	   }else
	   {
		   //over sampling by 16
		   F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);

	   }

	  //Place the fractional part in appropriate bit position . refer USART_BRR
	  tempreg |= F_part;

	  //copy the value of tempreg in to BRR register
	  pUSARTx->BRR = tempreg;
}

/*
 * Init and De-init
 */
/********************************************************************
 * @fn                  - USART_Init
 *
 * @brief               -
 *
 * @param[in]           -
 * @param[in]           -
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_Init(USART_Handle_t *pUSARTHandle)
{
	uint32_t tempreg = 0;

	/**********************Configuration of CR1***********************/

	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{
		//Enable the receiver bit
		tempreg |= (1 << USART_CR1_RE);
	}
	else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		//Enable the transmitter bit
		tempreg |= (1 << USART_CR1_TE);
	}
	else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		//Enable both transmitter and receiver bits
		tempreg |= ((1 << USART_CR1_RE) | (1 << USART_CR1_TE));
	}

	//configure the word length
	tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M;

	//configure parity control bit fields
	if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
	{
		// Enable the parity control
		tempreg |= (1 << USART_CR1_PCE);

		// Default even parity is enabled
	}
	else if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
	{
		// Enable the parity control
		tempreg |= (1 << USART_CR1_PCE);

		//Enable odd parity
		tempreg |= (1 << USART_CR1_PS);
	}

	// program the CR1 register
	pUSARTHandle->pUSARTx->CR1 = tempreg;

	/**********************Configuration of CR2***********************/

	tempreg = 0;

	//configure number of stop bits
	tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

	//program the CR2 register
	pUSARTHandle->pUSARTx->CR2 = tempreg;

	/**********************Configuration of CR3***********************/

	tempreg = 0;

	// configure USART hardware flow control
	if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		// enable CTS flow control
		tempreg |= (1 << USART_CR3_CTSE);
	}
	else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		// enable CTS flow control
		tempreg |= (1 << USART_CR3_RTSE);
	}
	else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		// enable CTS and RTS flow control
		tempreg |= (1 << USART_CR3_CTSE);
		tempreg |= (1 << USART_CR3_RTSE);
	}

	pUSARTHandle->pUSARTx->CR3 = tempreg;

	/**********************Configuration of baud rate***********************/
	USART_SetBaudRate(pUSARTHandle->pUSARTx,pUSARTHandle->USART_Config.USART_Baud);
}

/********************************************************************
 * @fn                  - USART_DeInit
 *
 * @brief               -
 *
 * @param[in]           -
 * @param[in]           -
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_DeInit(USART_RegDef_t *pUSARTx)
{

}


/*
 * Data Send and Receive
 */
/********************************************************************
 * @fn                  - USART_SendData
 *
 * @brief               -
 *
 * @param[in]           -
 * @param[in]           -
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_SendData(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer,uint32_t len)
{
	uint16_t *pdata;

	//Loop over until len number of bytes are transferred
	for(uint32_t i = 0;i < len;i++)
	{
		// wait until TXE flag is set in SR
		while(!(USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TXE)));

		// check USART_wordlength for 9-bit or 8-bit
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			//if 9BIT load the DR with 2bytes masking the bits other than first 9 bits
			pdata = (uint16_t*)pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			//check for USART_Parity
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				// no parity is used in transfer, so 9 bits of user data will be sent
				// implement the code to increment pTxBuffer twice
				pTxBuffer += 2;
			}
			else
			{
				//parity bit is used in this transfer. so 8 bits of user data will be sent
				//the 9th bit will be replaced by parity bit by the Hardware
				pTxBuffer++;
			}
		}
		else
		{
			//8BIT transfer
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer & 0xFF);

			pTxBuffer++;
		}
	}

	//wait till TC flag is set in SR
	while(!(USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TC)));
}

/********************************************************************
 * @fn                  - USART_ReceiveData
 *
 * @brief               -
 *
 * @param[in]           -
 * @param[in]           -
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_ReceiveData(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer,uint32_t len)
{
	//Loop over until len number of bytes are received
	for(uint32_t i = 0;i < len;i++)
	{
		//wait till RXNE flag is set in SR
		while(!(USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_RXNE)));

		//check word length
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			// we are going to receive 9 bit data in a frame

			// check parity control
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				// no parity is used, so all 9 bits are data bits
				// read only first 9 bits

				*((uint16_t*)pRxBuffer) = (pUSARTHandle->pUSARTx->DR & (uint16_t)0x01FF);

				// increment buffer twice
				pRxBuffer += 2;
			}
			else
			{
				// parity is used, so 8 bits will be user data
				*pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
				pRxBuffer++;
			}
		}
		else
		{
			// we are going to receive 8 bits of data
			// check for parity control
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				// no parity is used, so all 8 bits are data bits
				// read 8 bits from DR
				*pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
			}
			else
			{
				// parity is used, only 7 bits are user data
				*pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0x7F);
			}

			//increment buffer
			pRxBuffer++;

		}

	}
}
