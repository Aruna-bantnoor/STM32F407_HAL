#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

/* Task Handles */
TaskHandle_t LEDTaskHandle = NULL;
TaskHandle_t ButtonTaskHandle = NULL;

// Macros
#define TRUE          1
#define FALSE         0
#define NOT_PRESSED   FALSE
#define PRESSED       TRUE

/* Global Variables */
uint8_t button_status_flag = NOT_PRESSED;

/* Function Prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void LEDTask(void *parameters);
void UserButtonTask(void *parameters);

int main(void)
{
    /* Reset peripherals */
    HAL_Init();

    /* Configure System Clock */
    SystemClock_Config();

    /* Initialize GPIO */
    MX_GPIO_Init();

    /* Create LED Task */
    xTaskCreate(
                LEDTask,
                "LED_Task",
                128,
                NULL,
                2,
                &LEDTaskHandle
               );

    /* Create Button Task */
    xTaskCreate(
                UserButtonTask,
                "Button_Task",
                128,
                NULL,
                2,
                &ButtonTaskHandle
               );

    /* Start Scheduler */
    vTaskStartScheduler();

    /* Infinite Loop */
    while (1)
    {

    }
}

/* LED Task */
void LEDTask(void *parameters)
{
	while(1)
	{
		if(button_status_flag == PRESSED)
		{
				// turn LED on
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,SET);
		}
		else
		{
				// turn LED off
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,RESET);
		}

	}
}

/* Button Task */
void UserButtonTask(void *parameters)
{
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
		{
				// button pressed
			button_status_flag = PRESSED;
		}
		else
		{
				// button not pressed
			button_status_flag = NOT_PRESSED;
		}

	}
}

/* System Clock Configuration */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* Power Control clock enable */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* Configure Voltage Scaling */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* HSI Configuration */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

    /* PLL OFF */
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /* CPU Clock Configuration */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;

    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

/* GPIO Initialization */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure LED Pins */
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* Configure Button Pin */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* Error Handler */
void Error_Handler(void)
{
    __disable_irq();

    while (1)
    {

    }
}
