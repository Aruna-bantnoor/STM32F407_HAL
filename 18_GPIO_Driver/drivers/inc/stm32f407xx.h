/*
 * stm32f407xx.h
 *
 *  Created on: Apr 14, 2026
 *      Author: admin
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define __vo volatile

/* PROCESSOR SPECIFIC DETAILS
 * ARM Cortex Mx Processor NVIC ISERx register addresses
*/

 #define NVIC_ISER0   ((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1   ((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2   ((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3   ((__vo uint32_t*)0xE000E10C)


/* ARM Cortex Mx Processor NVIC ICERx register addresses */
 #define NVIC_ICER0   ((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1   ((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2   ((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3   ((__vo uint32_t*)0xE000E18C)


/* ARM COrtes Mx Processor Priority register address calculation*/
#define NVIC_PR_BASE_ADDR     ((__vo uint32_t *)0xE000E400)


#define NO_OF_PR_BITS_IMPLEMENTED      4

// Base addresses of Flash and SRAM Memories
#define FLASH_BASEADDR                 0x08000000U
#define SRAM1_BASEADDR                 0x20000000U    //112KB
#define SRAM2_BASEADDR                 0x2001C000U
#define ROM                            0x1FFF0000U
#define SRAM                           SRAM1_BASEADDR

// AHBx and APBx Bus peripheral base addresses
#define PERIPH_BASE                    0x40000000U
#define APB1PERIPH_BASE                PERIPH_BASE
#define APB2PERIPH_BASE                0x40010000U
#define AHB1PERIPH_BASE                0X40020000U
#define AHB2PERIPH_BASE                0x50000000U

// Defining base addresses of peripherals which are hanging on AHB1 bus

#define GPIOA_BASEADDR        (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR        (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR        (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR        (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR        (AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR        (AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR        (AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR        (AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASEADDR        (AHB1PERIPH_BASE + 0x2000)

#define RCC_BASEADDR          (AHB1PERIPH_BASE + 0x3800)

// Base addresses of peripherals which are hanging on APB1 Bus

#define I2C1_BASEADDR         (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR         (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR         (APB1PERIPH_BASE + 0x5C00)

#define SPI2_BASEADDR         (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR         (APB1PERIPH_BASE + 0x3C00)

#define USART2_BASEADDR       (APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR       (APB1PERIPH_BASE + 0x4800)
#define UART4_BASEADDR        (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR        (APB1PERIPH_BASE + 0x5000)


// Base addresses of peripherals which are hanging on APB2 bus
#define EXTI_BASEADDR         (APB2PERIPH_BASE + 0x3C00)
#define SPI1_BASEADDR         (APB2PERIPH_BASE + 0x3000)
#define SYSCFG_BASEADDR       (APB2PERIPH_BASE + 0x3800)

#define USART1_BASEADDR       (APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR       (APB2PERIPH_BASE + 0x1400)


// Peripheral register definition structures
typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;


typedef struct
{
    __vo uint32_t CR;
    __vo uint32_t PLLCFGR;
    __vo uint32_t CFGR;
    __vo uint32_t CIR;

    __vo uint32_t AHB1RSTR;
    __vo uint32_t AHB2RSTR;
    __vo uint32_t AHB3RSTR;
    uint32_t RESERVED0;

    __vo uint32_t APB1RSTR;
    __vo uint32_t APB2RSTR;
    uint32_t RESERVED1[2];

    __vo uint32_t AHB1ENR;
    __vo uint32_t AHB2ENR;
    __vo uint32_t AHB3ENR;
    uint32_t RESERVED2;

    __vo uint32_t APB1ENR;
    __vo uint32_t APB2ENR;
    uint32_t RESERVED3[2];

    __vo uint32_t AHB1LPENR;
    __vo uint32_t AHB2LPENR;
    __vo uint32_t AHB3LPENR;
    uint32_t RESERVED4;

    __vo uint32_t APB1LPENR;
    __vo uint32_t APB2LPENR;
    uint32_t RESERVED5[2];

    __vo uint32_t BDCR;
    __vo uint32_t CSR;
    uint32_t RESERVED6[2];

    __vo uint32_t SSCGR;
    __vo uint32_t PLLI2SCFGR;
} RCC_RegDef_t;


/*
 * Peripheral register definition structure fro SPI
 */
typedef struct{
	__vo uint32_t CR1;               /* Address Offset: 0x00*/
	__vo uint32_t CR2;               /* Address Offset: 0x04*/
	__vo uint32_t SR;                /* Address Offset: 0x08*/
	__vo uint32_t DR;                /* Address Offset: 0x0C*/
	__vo uint32_t CRCPR;             /* Address Offset: 0x10*/
	__vo uint32_t RXCRCR;            /* Address Offset: 0x14*/
	__vo uint32_t TXCRCR;            /* Address Offset: 0x18*/
	__vo uint32_t I2SCFGR;           /* Address Offset: 0x1C*/
	__vo uint32_t I2SPR;             /* Address Offset: 0x20*/
}SPI_RegDef_t;


// Peripheral register definition structure for EXTI
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;

// Peripheral register definition structure for SYSCFG
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t RESERVED1[2];
	__vo uint32_t CMPCR;
	uint32_t RESERVED2[2];
	__vo uint32_t CFGR;
}SYSCFG_RegDef_t;

/*
 * Peripheral register definition structure for I2C
 */
typedef struct{
    __vo uint32_t CR1;
    __vo uint32_t CR2;
    __vo uint32_t OAR1;
    __vo uint32_t OAR2;
    __vo uint32_t DR;
    __vo uint32_t SR1;
    __vo uint32_t SR2;
    __vo uint32_t CCR;
    __vo uint32_t TRISE;
    __vo uint32_t FLTR;
} I2C_RegDef_t;

// Peripheral definition (Peripheral base addresses typecasted to xxx_RegDef_t)

#define GPIOA   ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE   ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF   ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG   ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH   ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI   ((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC     ((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI    ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG   ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define I2C1        ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2        ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3        ((I2C_RegDef_t*)I2C3_BASEADDR)

// Clock Enable Macros for GPIOs Peripherals
#define GPIOA_PCLK_EN()   (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()   (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()   (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()   (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()   (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()   (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()   (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()   (RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()   (RCC->AHB1ENR |= (1 << 8))

// Clock Enable Macros for I2Cx Peripherals
#define I2C1_PCLK_EN()                    (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()                    (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()                    (RCC->APB1ENR |= (1 << 23))


// Clock Enable Macros for SPIx peripherals
#define SPI1_PCLK_EN()    (RCC->APB2ENR |= (1U << 12))
#define SPI2_PCLK_EN()    (RCC->APB1ENR |= (1U << 14))
#define SPI3_PCLK_EN()    (RCC->APB1ENR |= (1U << 15))

//Clock Enable Macros for USARTx peripherals
#define USART1_PCLK_EN()  (RCC->APB2ENR |= (1U << 4))
#define USART2_PCLK_EN()  (RCC->APB1ENR |= (1U << 17))
#define USART3_PCLK_EN()  (RCC->APB1ENR |= (1U << 18))
#define UART4_PCLK_EN()   (RCC->APB1ENR |= (1U << 19))
#define UART5_PCLK_EN()   (RCC->APB1ENR |= (1U << 20))
#define USART6_PCLK_EN()  (RCC->APB2ENR |= (1U << 5))

// Clock Enable Macros for SYSCFG peripheral
#define SYSCFG_PCLK_EN()  (RCC->APB2ENR |= (1U << 14))



// Clock Disable Macros for GPIOx peripherals
#define GPIOA_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 0))
#define GPIOB_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 1))
#define GPIOC_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 2))
#define GPIOD_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 3))
#define GPIOE_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 4))
#define GPIOF_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 5))
#define GPIOG_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 6))
#define GPIOH_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 7))
#define GPIOI_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 8))

// Clock Disable Macros for I2Cx peripherals
#define I2C1_PCLK_DI()    (RCC->APB1ENR &= ~(1U << 21))
#define I2C2_PCLK_DI()    (RCC->APB1ENR &= ~(1U << 22))
#define I2C3_PCLK_DI()    (RCC->APB1ENR &= ~(1U << 23))

// Clock Disable Macros for SPIx peripherals
#define SPI1_PCLK_DI()    (RCC->APB2ENR &= ~(1U << 12))
#define SPI2_PCLK_DI()    (RCC->APB1ENR &= ~(1U << 14))
#define SPI3_PCLK_DI()    (RCC->APB1ENR &= ~(1U << 15))

// Clock Disable Macros for USARTx peripherals
#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1U << 4))
#define USART2_PCLK_DI()    (RCC->APB1ENR &= ~(1U << 17))
#define USART3_PCLK_DI()    (RCC->APB1ENR &= ~(1U << 18))
#define UART4_PCLK_DI()   (RCC->APB1ENR &= ~(1U << 19))
#define UART5_PCLK_DI()   (RCC->APB1ENR &= ~(1U << 20))
#define USART6_PCLK_DI()  (RCC->APB2ENR &= ~(1U << 5))

// Clock Disable Macros for SYSCFG peripheral
#define SYSCFG_PCLK_DI()  (RCC->APB2ENR &= ~(1U << 14))

// Macros to reset GPIOx peripherals
#define GPIOA_REG_RESET()              do{ (RCC->AHB1RSTR |= (1U << 0)); (RCC->AHB1RSTR &= ~(1U << 0)); }while(0)
#define GPIOB_REG_RESET()              do{ (RCC->AHB1RSTR |= (1U << 1)); (RCC->AHB1RSTR &= ~(1U << 1)); }while(0)
#define GPIOC_REG_RESET()              do{ (RCC->AHB1RSTR |= (1U << 2)); (RCC->AHB1RSTR &= ~(1U << 2)); }while(0)
#define GPIOD_REG_RESET()              do{ (RCC->AHB1RSTR |= (1U << 3)); (RCC->AHB1RSTR &= ~(1U << 3)); }while(0)
#define GPIOE_REG_RESET()              do{ (RCC->AHB1RSTR |= (1U << 4)); (RCC->AHB1RSTR &= ~(1U << 4)); }while(0)
#define GPIOF_REG_RESET()              do{ (RCC->AHB1RSTR |= (1U << 5)); (RCC->AHB1RSTR &= ~(1U << 5)); }while(0)
#define GPIOG_REG_RESET()              do{ (RCC->AHB1RSTR |= (1U << 6)); (RCC->AHB1RSTR &= ~(1U << 6)); }while(0)
#define GPIOH_REG_RESET()              do{ (RCC->AHB1RSTR |= (1U << 7)); (RCC->AHB1RSTR &= ~(1U << 7)); }while(0)
#define GPIOI_REG_RESET()              do{ (RCC->AHB1RSTR |= (1U << 8)); (RCC->AHB1RSTR &= ~(1U << 8)); }while(0)


#define GPIO_BASEADDR_TO_CODE(x)     ( (x == GPIOA) ? 0 :\
		                               (x == GPIOB) ? 1 :\
		                               (x == GPIOC) ? 2 :\
		                               (x == GPIOB) ? 3 :\
		                               (x == GPIOA) ? 4 :\
		                               (x == GPIOB) ? 5 :\
		                               (x == GPIOA) ? 6 :\
		                               (x == GPIOB) ? 7 : 0 )

// IRQ Number of STM32F407x MCU

#define IRQ_NO_EXTI0       6
#define IRQ_NO_EXTI1       7
#define IRQ_NO_EXTI2       8
#define IRQ_NO_EXTI3       9
#define IRQ_NO_EXTI4       10
#define IRQ_NO_EXTI9_5     23
#define IRQ_NO_EXTI15_10   40

// Macros for all the possible priority levels

#define NVIC_IRQ_PRI0      0
#define NVIC_IRQ_PRI1     1
#define NVIC_IRQ_PRI2      2
#define NVIC_IRQ_PRI3      3
#define NVIC_IRQ_PRI4      4
#define NVIC_IRQ_PRI5      5
#define NVIC_IRQ_PRI6      6
#define NVIC_IRQ_PRI7      7
#define NVIC_IRQ_PRI8      8
#define NVIC_IRQ_PRI9      9
#define NVIC_IRQ_PRI10     10
#define NVIC_IRQ_PRI11     11
#define NVIC_IRQ_PRI12     12
#define NVIC_IRQ_PRI13     13
#define NVIC_IRQ_PRI14     14
#define NVIC_IRQ_PRI15     15

// Some generic macros
#define ENABLE                 1
#define DISABLE                0
#define SET                    ENABLE
#define RESET                  DISABLE
#define GPIO_PIN_SET           SET
#define GPIO_PIN_RESET         RESET

/*
 * Bit position definitions of SPI_CR1 peripheral
 */
#define SPI_CR1_CPHA        0
#define SPI_CR1_CPOL        1
#define SPI_CR1_MSTR        2
#define SPI_CR1_BR          3
#define SPI_CR1_SPE         6
#define SPI_CR1_LSBFIRST    7
#define SPI_CR1_SSI         8
#define SPI_CR1_SSM         9
#define SPI_CR1_RXONLY      10
#define SPI_CR1_DFF         11
#define SPI_CR1_CRCNEXT     12
#define SPI_CR1_CRCEN       13
#define SPI_CR1_BIDIODE     14
#define SPI_CR1_BIDIMODE    15

/*
 * Bit position definitions of SPI_CR2 peripheral
 */
#define SPI_CR2_RXDMAEN        0
#define SPI_CR2_TXDMAEN        1
#define SPI_CR2_SSOE           2
#define SPI_CR2_FRF            3
#define SPI_CR2_ERRIE          4
#define SPI_CR2_RXNEIE         5
#define SPI_CR2_TXEIE          6

/*
 * Bit position definitions of SPI_SR peripheral
 */
#define SPI_SR_RXNE            0
#define SPI_SR_TXE             1
#define SPI_SR_CHSIDE          2
#define SPI_SR_UDR             3
#define SPI_SR_CRCERR          4
#define SPI_SR_MODF            5
#define SPI_SR_OVR             6
#define SPI_SR_BSY             7
#define SPI_SR_FRE             8

/*
 * Bit position definitions of I2C_CR1 peripheral
 */
#define I2C_CR1_PE             0
#define I2C_CR1_NOSTRETCH      7
#define I2C_CR1_START          8
#define I2C_CR1_STOP           9
#define I2C_CR1_ACK            10
#define I2C_CR1_SWRST          15

/*
 * Bit position definitions of I2C_CR2 peripheral
 */
#define I2C_CR2_FREQ          0
#define I2C_CR2_ITERREN       8
#define I2C_CR2_ITEVTEN       9
#define I2C_CR2_ITBUFEN       10

/*
 * Bit position definitions of I2C_SR1 peripheral
 */
#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 					3
#define I2C_SR1_STOPF 					4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 				14

/*
 * Bit position definitions of I2C_SR2 peripheral
 */
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 				4
#define I2C_SR2_DUALF 					7

/*
 * Bit position definitions of I2C_CCR peripheral
 */
#define I2C_CCR_CCR 					 0
#define I2C_CCR_DUTY 					14
#define I2C_CCR_FS  				 	15

#include "stm32f407xx_gpio_driver.h"
#include <stm32f407xx_i2c_driver.h>


#endif /* INC_STM32F407XX_H_ */
