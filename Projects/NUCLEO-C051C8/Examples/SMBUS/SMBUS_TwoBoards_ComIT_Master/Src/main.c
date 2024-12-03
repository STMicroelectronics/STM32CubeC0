/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    SMBUS/SMBUS_TwoBoards_ComIT_Master/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use STM32C0xx SMBUS HAL API to
  *          manage a Communication between a Master and a Slave based
  *          on Interrupt procedure.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SMBUS_ADDRESS          0x42
#define SMBUS_PEC_SIZE         0x1

/* Address match */
__IO uint32_t SlaveAddrMatchCode = 0;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = " ****SMBUS_TwoBoards communication using Interrupts****  ****SMBUS_TwoBoards communication using Interrupts****  ****SMBUS_TwoBoards communication using Interrupts**** ";

/* Buffer used for data and PEC reception */
uint8_t aRxBuffer[RXBUFFERSIZE + SMBUS_PEC_SIZE];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SMBUS_HandleTypeDef hsmbus1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_SMBUS_Init(void);
/* USER CODE BEGIN PFP */
static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
static void WaitOnPushButton(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* Configure LED4 */
  BSP_LED_Init(LED4);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_SMBUS_Init();
  /* USER CODE BEGIN 2 */

  /* Configure User push-button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* Wait for USER push-button press before starting the Communication */
  WaitOnPushButton();

  /* The board sends the message and expects to receive it back */

  /*##-2- Start the transmission process #####################################*/
  /* While the SMBUS in reception process, user can transmit data through
  "aTxBuffer" buffer */
  do
  {
    if (HAL_SMBUS_Master_Transmit_IT(&hsmbus1, (uint16_t)SMBUS_ADDRESS, (uint8_t*)aTxBuffer, TXBUFFERSIZE + SMBUS_PEC_SIZE, SMBUS_FIRST_AND_LAST_FRAME_WITH_PEC) != HAL_OK)
    {
      Error_Handler();
    }

    while (HAL_SMBUS_GetState(&hsmbus1) != HAL_SMBUS_STATE_READY)
    {
    }

    /* Error_Handler() function is called when Timeout error occurs.
    When Acknowledge failure occurs (Slave don't acknowledge its address)
    Master restarts communication */
  }
  while (HAL_SMBUS_GetError(&hsmbus1) == HAL_SMBUS_ERROR_ACKF);

  /* Turn LED4 on: Transfer in Transmission process is correct */
  BSP_LED_On(LED4);

  /* Wait for USER push-button press before starting the Communication */
  WaitOnPushButton();

  /*##-3- Put SMBUS peripheral in reception process ############################*/
  do
  {
    if (HAL_SMBUS_Master_Receive_IT(&hsmbus1, (uint16_t)SMBUS_ADDRESS, (uint8_t *)aRxBuffer, RXBUFFERSIZE + SMBUS_PEC_SIZE, SMBUS_FIRST_AND_LAST_FRAME_WITH_PEC) != HAL_OK)
    {
      Error_Handler();
    }

    while (HAL_SMBUS_GetState(&hsmbus1) != HAL_SMBUS_STATE_READY)
    {
    }

    /* Error_Handler() function is called when Timeout error occurs.
    When Acknowledge failure occurs (Slave don't acknowledge it's address)
    Master restarts communication */
  }
  while (HAL_SMBUS_GetError(&hsmbus1) == HAL_SMBUS_ERROR_ACKF);

  /* Compare PEC register and sent PEC #######################################*/
  if (aRxBuffer[RXBUFFERSIZE + SMBUS_PEC_SIZE - 1] != hsmbus1.Instance->PECR)
  {
    /* Processing Error */
    Error_Handler();
  }

  /* Turn LED4 off: Transfer in reception process is correct */
  BSP_LED_Off(LED4);

  /*##-4- Compare the sent and received buffers ##############################*/
  if (Buffercmp((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, RXBUFFERSIZE))
  {
    /* Processing Error */
    Error_Handler();
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_SMBUS_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hsmbus1.Instance = I2C1;
  hsmbus1.Init.Timing = 0x20303E5D;
  hsmbus1.Init.AnalogFilter = SMBUS_ANALOGFILTER_ENABLE;
  hsmbus1.Init.OwnAddress1 = 0x42;
  hsmbus1.Init.AddressingMode = SMBUS_ADDRESSINGMODE_7BIT;
  hsmbus1.Init.DualAddressMode = SMBUS_DUALADDRESS_ENABLE;
  hsmbus1.Init.OwnAddress2 = 0xFF;
  hsmbus1.Init.OwnAddress2Masks = SMBUS_OA2_NOMASK;
  hsmbus1.Init.GeneralCallMode = SMBUS_GENERALCALL_DISABLE;
  hsmbus1.Init.NoStretchMode = SMBUS_NOSTRETCH_DISABLE;
  hsmbus1.Init.PacketErrorCheckMode = SMBUS_PEC_ENABLE;
  hsmbus1.Init.PeripheralMode = SMBUS_PERIPHERAL_MODE_SMBUS_HOST;
  hsmbus1.Init.SMBusTimeout = 0x00008249;
  if (HAL_SMBUS_Init(&hsmbus1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_SMBUS_ConfigDigitalFilter(&hsmbus1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/**
  * @brief  SMBUS error callback.
  * @param  SMBUSHandle: SMBUS handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_SMBUS_ErrorCallback(SMBUS_HandleTypeDef *SMBUSHandle)
{
  /** Error_Handler() function is called when error occurs.
  * 1- When Slave doesn't acknowledge its address, Master restarts communication.
  * 2- When Master doesn't acknowledge the last data transferred, Slave doesn't care in this example.
  */
  if (HAL_SMBUS_GetError(SMBUSHandle) != HAL_SMBUS_ERROR_ACKF)
  {
    /* LED4 toggle */
    BSP_LED_Toggle(LED4);
    HAL_Delay(1000);
  }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 0  : pBuffer1 identical to pBuffer2
  *         >0 : pBuffer1 differs from pBuffer2
  */
static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if ((*pBuffer1) != *pBuffer2)
    {
      return BufferLength;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

/**
  * @brief  Wait for user to press user button.
  * @param  None
  * @retval None
  */
static void WaitOnPushButton(void)
{
  /* Wait for User push-button press before starting the Communication */
  while (BSP_PB_GetState(BUTTON_USER) != GPIO_PIN_RESET)
  {
    BSP_LED_Toggle(LED4);
    HAL_Delay(100);
  }

  BSP_LED_Off(LED4);

  /* Delay to avoid that possible signal rebound is taken as button release */
  HAL_Delay(50);

  /* Wait for User push-button release before starting the Communication */
  while (BSP_PB_GetState(BUTTON_USER) != GPIO_PIN_SET)
  {
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  __disable_irq();

  while (1)
  {
    /* LED4 toggle */
    BSP_LED_Toggle(LED4);
    HAL_Delay(1000);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
