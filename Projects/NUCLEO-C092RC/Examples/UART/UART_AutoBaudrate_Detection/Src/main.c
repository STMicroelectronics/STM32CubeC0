/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   UART/UART_AutoBaudrate_Detection/Src/main.c
  * @brief  This sample code shows how to use STM32C0xx UART HAL API to use
  *         automatic baud rate detection feature on a UART Rx line.
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
#include "stm32c0xx_ll_usart.h"

#include "stdio.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/**
  * @brief  Structure containing Auto baud rate detection method description
  */
typedef struct
{
  uint32_t      AutoBaudRateMode;         /*!< Specifies Auto baud rate method value */
  uint8_t const *DetectionInfoText;       /*!< Indicates user prompt for execution   */
  uint8_t       DetectionInfoTextSize;    /*!< Indicates size of user prompt         */
} AutoBaudRate_Detection_Method_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* Default baud rate used on serial port at startup */
#define DEFAULT_BAUDRATE        115200U

/* DEL character ascii code */
#define DEL_ASCII_CODE          0x7FU

/* Timeout value for sending information on UART Tx */
#define PRINT_TIMEOUT                  1000U

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/**
  * @brief Text strings printed on PC Com port for user information
  */
static const uint8_t aDelString[] = "DEL";
static const uint8_t aTextInfoStart[] = "\r\nUART AutoBaudRate Detection Example (default baud rate after UART initialisation is 115200).\r\n";
static const uint8_t aTextErrorDetected[] = "\r\n***** Error during Auto baud rate detection process *****\r\n";
static const uint8_t aTextAskForNewBaudRate[] = "Please configure your serial port on PC to a different baud rate, and enter requested character.\r\n";
static const uint8_t aTextDetectionOnStartBit[] = "1 - Baud rate detection on Start bit (received character should start with a 1 in b0) => Enter \"A\"\n\r";
static const uint8_t aTextDetectionOnFallingEdge[] = "2 - Baud rate detection on 0x7F frame (received character should start with a 10xx bit pattern) => Enter \"1\"\n\r";
static const uint8_t aTextDetectionOn7F[] = "3 - Baud rate detection on 0x7F frame (received character should be 0x7F) => Press DEL\n\r";
static const uint8_t aTextDetectionOn55[] = "4 - Baud rate detection on 0x55 frame (received character should be 0x55) =>  Enter \"U\"\n\r";
static const uint8_t aTextDetectionResult[] = " has been properly received.\n\rBaud rate value has been adjusted in BRR to (bps) : ";

/**
  * @brief reception buffer
  */
uint8_t aRXBufferUser[RX_BUFFER_SIZE];

/**
  * @brief Array containing information for each auto baud rate detection method
  */
AutoBaudRate_Detection_Method_t aDetectionMethods[NB_AUTO_BAUD_RATE_MODES] =
{
  { UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT,    aTextDetectionOnStartBit,    COUNTOF(aTextDetectionOnStartBit)    },
  { UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE, aTextDetectionOnFallingEdge, COUNTOF(aTextDetectionOnFallingEdge) },
  { UART_ADVFEATURE_AUTOBAUDRATE_ON0X7FFRAME,   aTextDetectionOn7F,          COUNTOF(aTextDetectionOn7F)          },
  { UART_ADVFEATURE_AUTOBAUDRATE_ON0X55FRAME,   aTextDetectionOn55,          COUNTOF(aTextDetectionOn55)          }
};

/**
  * @brief Status indicating if reception is complete or not
  */
__IO ITStatus ReceptionReady = RESET;
__IO ITStatus ErrorDetected  = RESET;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void PrintInfo(UART_HandleTypeDef *huart, uint8_t const *pString, uint16_t Size);

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
  uint32_t baudrate;
  uint32_t periphclk;
  uint8_t  baudrate_string[RX_BUFFER_SIZE];
  uint8_t  autobaudrate_mode;

  /* STM32C0xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Low Level Initialization
     */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USART1 is clocked on PCLK. Store PCLK frequency value into local variable */
  periphclk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_USART1);

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* At startup, UART has been first configured with 115200 bps */
  baudrate = DEFAULT_BAUDRATE;

  /* Configure LED1 */
  BSP_LED_Init(LED1);
  /* Configure LED2 */
  BSP_LED_Init(LED2);

  PrintInfo(&huart1, aTextInfoStart, COUNTOF(aTextInfoStart));

  /* For all supported Auto baud rate detection methods */
  for (autobaudrate_mode = 0; autobaudrate_mode < NB_AUTO_BAUD_RATE_MODES; autobaudrate_mode++)
  {
    /* Configure UART with Auto baud rate method and current baud rate */
    huart1.Init.BaudRate = baudrate;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_AUTOBAUDRATE_INIT;
    huart1.AdvancedInit.AutoBaudRateEnable = UART_ADVFEATURE_AUTOBAUDRATE_ENABLE;
    huart1.AdvancedInit.AutoBaudRateMode = aDetectionMethods[autobaudrate_mode].AutoBaudRateMode;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
      Error_Handler();
    }

    /* Send msg using previously set baud rate */
    PrintInfo(&huart1, aTextAskForNewBaudRate, COUNTOF(aTextAskForNewBaudRate));
    PrintInfo(&huart1, aDetectionMethods[autobaudrate_mode].DetectionInfoText,
              aDetectionMethods[autobaudrate_mode].DetectionInfoTextSize);

    /* Reset transmission flag */
    ReceptionReady = RESET;

    /* Wait for receiving 1 char */
    HAL_UART_Receive_IT(&huart1, aRXBufferUser, 1);

    /* While waiting for character from PC side, LED1 is
       blinking according to the following pattern: toggle every 100ms */
    while (ReceptionReady != SET)
    {
      /* Toggle LED1 every 100ms */
      BSP_LED_Toggle(LED1);
      HAL_Delay(100);
    }

    /* Check if Auto baud rate detection has been successfully executed.
       If not, Auto baud Rate Detection error (ABRE) is reported */
    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_ABRE))
    {
      ErrorDetected = SET;
      PrintInfo(&huart1, aTextErrorDetected, COUNTOF(aTextErrorDetected));
    }
    else
    {
      /* Wait for completion of auto baud rate detection : ABRF flag in ISR */
      while (!__HAL_UART_GET_FLAG(&huart1, UART_FLAG_ABRF));

      /* Clear ABRF flag */
      __HAL_UART_SEND_REQ(&huart1, UART_AUTOBAUD_REQUEST);

      /* Retrieve baud rate */
      baudrate = LL_USART_GetBaudRate(huart1.Instance, periphclk,
                                      huart1.Init.ClockPrescaler, huart1.Init.OverSampling);

      /* Print result to Terminal */
      if (aRXBufferUser[0] == DEL_ASCII_CODE)
      {
        /* Specific case of DEL character entered : "DEL" string to print printed on Terminal */
        PrintInfo(&huart1, aDelString, COUNTOF(aDelString));
      }
      else
      {
        PrintInfo(&huart1, aRXBufferUser, 1);
      }
      PrintInfo(&huart1, aTextDetectionResult, COUNTOF(aTextDetectionResult));
      sprintf((char *) baudrate_string, "%u bps \n\n\r", (unsigned int) baudrate);
      PrintInfo(&huart1, baudrate_string, strlen((char *) baudrate_string));
    }
  }

  /* End of example program :
     - If no error has been detected, set LED1 On
     - Otherwise, toggle LED1
  */
  if (ErrorDetected == RESET)
  {
    BSP_LED_On(LED1);
  }
  else
  {
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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_AUTOBAUDRATE_INIT;
  huart1.AdvancedInit.AutoBaudRateEnable = UART_ADVFEATURE_AUTOBAUDRATE_ENABLE;
  huart1.AdvancedInit.AutoBaudRateMode = UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  * @brief  Send text information message on UART Tx line (to PC Com port).
  * @param  huart UART handle.
  * @param  pString String to be sent to user display
  * @param  Size   Size of string
  * @retval None
  */
void PrintInfo(UART_HandleTypeDef *huart, uint8_t const *pString, uint16_t Size)
{
  if (HAL_OK != HAL_UART_Transmit(huart, pString, Size, PRINT_TIMEOUT))
  {
    Error_Handler();
  }
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report end of Rx transfer
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set reception flag: transfer complete */
  ReceptionReady = SET;
}

/**
  * @brief  UART Error callback
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report an UART error
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  /* Error has been detected */
  ErrorDetected = SET;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  /* Turn LED2 on */
  BSP_LED_Off(LED1);
  BSP_LED_On(LED2);
  while (1);
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

  Error_Handler();
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
