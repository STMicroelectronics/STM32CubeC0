/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "stm32c0xx_nucleo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private define ------------------------------------------------------------*/
/* to enable for the board entering STOP1 mode,
   to disable for the board sending wake-up stimuli */
//#define BOARD_IN_STOP1_MODE

/* Private variables ---------------------------------------------------------*/
UART_WakeUpTypeDef WakeUpSelection;
__IO uint32_t UserButtonStatus = 0;  /* set to 1 after User Button interrupt  */

/* Buffer used for confirmation messages transmission */
uint8_t aTxBuffer1[] = "RXNE wake-up successful";
uint8_t aTxBuffer2[] = "Start bit detection wake-up successful";
uint8_t aTxBuffer3[] = "7-bit address match wake-up successful";
uint8_t aTxBuffer4[] = "4-bit address match wake-up successful";

uint8_t aTxBuffer[] = "Start bit detection wake-up successful";
uint8_t WakeUpTrigger1[] = "R";
uint8_t WakeUpTrigger2[] = "S";
uint8_t WakeUpTrigger3 = 0xA9; /* Value matches with address 0x29 */
uint8_t WakeUpTrigger4 = 0x82; /* Value matches with address 0x02 */

/* Buffer used for reception */
uint8_t aRxBuffer[RXBUFFERSIZE];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
#if defined(BOARD_IN_STOP1_MODE)
void SystemClock_Config_fromSTOP1(void);
#endif
#if !defined(BOARD_IN_STOP1_MODE)
static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
#endif /* !defined(BOARD_IN_STOP1_MODE) */
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

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

#ifdef BOARD_IN_STOP1_MODE
  /*##-1- Wake Up first step  ###############################################*/
#endif

  /* Configure LED1 */
  BSP_LED_Init(LED1);

#ifdef BOARD_IN_STOP1_MODE  
  /* LED1 is on till stop mode */
  BSP_LED_On(LED1);

  /* wait for two seconds before test start */
  HAL_Delay(2000);
  
  /* make sure that no UART transfer is on-going */ 
  while(__HAL_UART_GET_FLAG(&huart1, USART_ISR_BUSY) == SET);
  /* make sure that UART is ready to receive
   * (test carried out again later in HAL_UARTEx_StopModeWakeUpSourceConfig) */
  while(__HAL_UART_GET_FLAG(&huart1, USART_ISR_REACK) == RESET);

  /* set the wake-up event:
   * specify wake-up on RXNE flag */
  WakeUpSelection.WakeUpEvent = UART_WAKEUP_ON_READDATA_NONEMPTY;
  if (HAL_UARTEx_StopModeWakeUpSourceConfig(&huart1, WakeUpSelection)!= HAL_OK)
  {
    Error_Handler(); 
  }
 
  /* Enable the UART Wake UP from STOP1 mode Interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_WUF);
  
  /* about to enter STOP1 mode: switch off LED */
  BSP_LED_Off(LED1);
  /* enable MCU wake-up by UART */
  HAL_UARTEx_EnableStopMode(&huart1);
  /* enter STOP1 mode */
  HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);

  /* ... STOP1 mode ... */
  
  
  /* at that point, MCU has been awoken: the LED has been turned back on */
  SystemClock_Config_fromSTOP1();

  /* Wake Up based on RXNE flag successful */ 
  HAL_UARTEx_DisableStopMode(&huart1);

  /* wait for some delay */
  HAL_Delay(100);
  /* Inform other board that wake up is successful */
  if (HAL_UART_Transmit(&huart1, (uint8_t*)aTxBuffer1, COUNTOF(aTxBuffer1)-1, 5000)!= HAL_OK)  
  {
    Error_Handler();
  }  
  
  /*##-2- Wake Up second step  ###############################################*/
  /* make sure that no UART transfer is on-going */ 
  while(__HAL_UART_GET_FLAG(&huart1, USART_ISR_BUSY) == SET);
  /* make sure that UART is ready to receive 
   * (test carried out again later in HAL_UARTEx_StopModeWakeUpSourceConfig) */
  while(__HAL_UART_GET_FLAG(&huart1, USART_ISR_REACK) == RESET);
  
  /* set the wake-up event:
   * specify wake-up on start-bit detection */
  WakeUpSelection.WakeUpEvent = UART_WAKEUP_ON_STARTBIT;
  if (HAL_UARTEx_StopModeWakeUpSourceConfig(&huart1, WakeUpSelection)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Enable the UART Wake UP from STOP1 mode Interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_WUF);
  
  /* about to enter STOP1 mode: switch off LED */
  BSP_LED_Off(LED1);
  /* enable MCU wake-up by UART */
  HAL_UARTEx_EnableStopMode(&huart1);
  /* enter STOP1 mode */
  HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);

  /* ... STOP1 mode ... */
  
  
  /* at that point, MCU has been awoken: the LED has been turned back on */
  SystemClock_Config_fromSTOP1();

  /* Wake Up on start bit detection successful */ 
  HAL_UARTEx_DisableStopMode(&huart1);
  /* wait for some delay */
  HAL_Delay(100);
  /* Inform other board that wake up is successful */
  if (HAL_UART_Transmit(&huart1, (uint8_t*)aTxBuffer2, COUNTOF(aTxBuffer2)-1, 5000)!= HAL_OK)
  {
    Error_Handler();
  }
  
  
  /*##-3- Wake Up third step  ################################################*/
 /* make sure that no UART transfer is on-going */ 
  while(__HAL_UART_GET_FLAG(&huart1, USART_ISR_BUSY) == SET);
  /* make sure that UART is ready to receive
   * (test carried out again later in HAL_UARTEx_StopModeWakeUpSourceConfig) */
  while(__HAL_UART_GET_FLAG(&huart1, USART_ISR_REACK) == RESET);
     
  /* set the wake-up event:  
   * specify address-to-match type. 
   * The address is 0x29, meaning the character triggering the 
   * address match is 0xA9 */
  WakeUpSelection.WakeUpEvent = UART_WAKEUP_ON_ADDRESS;
  WakeUpSelection.AddressLength = UART_ADDRESS_DETECT_7B;
  WakeUpSelection.Address = 0x29;  
  if (HAL_UARTEx_StopModeWakeUpSourceConfig(&huart1, WakeUpSelection)!= HAL_OK)
  {
    Error_Handler(); 
  }

  /* Enable the UART Wake UP from stop mode Interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_WUF);
  
  /* about to enter stop mode: switch off LED */
  BSP_LED_Off(LED1);
  /* enable MCU wake-up by UART */
  HAL_UARTEx_EnableStopMode(&huart1);
  /* enter STOP1 mode */
  HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);

  /* ... STOP1 mode ... */
  
  
  /* at that point, MCU has been awoken: the LED has been turned back on */
  SystemClock_Config_fromSTOP1();

  /* Wake Up on 7-bit address detection successful */ 
  HAL_UARTEx_DisableStopMode(&huart1);
  /* wait for some delay */
  HAL_Delay(100);
  /* Inform other board that wake up is successful */
  if (HAL_UART_Transmit(&huart1, (uint8_t*)aTxBuffer3, COUNTOF(aTxBuffer3)-1, 5000)!= HAL_OK)  
  {
    Error_Handler();
  } 
  

  /*##-4- Wake Up fourth step  ###############################################*/
 /* make sure that no UART transfer is on-going */ 
  while(__HAL_UART_GET_FLAG(&huart1, USART_ISR_BUSY) == SET);
  /* make sure that UART is ready to receive
   * (test carried out again later in HAL_UARTEx_StopModeWakeUpSourceConfig) */
  while(__HAL_UART_GET_FLAG(&huart1, USART_ISR_REACK) == RESET);
    
  /* set the wake-up event:  
   * specify address-to-match type. 
   * The address is 0x2, meaning the character triggering the 
   * address match is 0x82 */
  WakeUpSelection.WakeUpEvent = UART_WAKEUP_ON_ADDRESS;
  WakeUpSelection.AddressLength = UART_ADDRESS_DETECT_4B; 
  WakeUpSelection.Address = 0x2;  
  if (HAL_UARTEx_StopModeWakeUpSourceConfig(&huart1, WakeUpSelection)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Enable the UART Wake UP from STOP1 mode Interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_WUF);
  
  /* about to enter STOP1 mode: switch off LED */
  BSP_LED_Off(LED1);
  /* enable MCU wake-up by UART */
  HAL_UARTEx_EnableStopMode(&huart1); 
  /* enter STOP1 mode */
  HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);

  /* ... STOP1 mode ... */
  
  
  /* at that point, MCU has been awoken: the LED has been turned back on */
  SystemClock_Config_fromSTOP1();

  /* Wake Up on 4-bit address detection successful */ 
  /* wait for some delay */
  HAL_Delay(100);
  /* Inform other board that wake up is successful */
  if (HAL_UART_Transmit(&huart1, (uint8_t*)aTxBuffer4, COUNTOF(aTxBuffer4)-1, 5000)!= HAL_OK)  
  {
    Error_Handler();
  }

  
#else

  /*##-1- Prepare the wake-up from stop mode ######################*/
/* initialize the User push-button in Interrupt mode */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);
  
  /* Wait for User push-button press before starting the test.
     In the meantime, LED1 is blinking */
  while(UserButtonStatus == 0)
  {
      /* Toggle LED1 */
      BSP_LED_Toggle(LED1);
      HAL_Delay(100);
  }
  
  
  /*##-2- Send the wake-up from stop mode first trigger ######################*/
  /*      (RXNE flag setting)                                                 */
  BSP_LED_On(LED1);
  if(HAL_UART_Transmit(&huart1, (uint8_t*)WakeUpTrigger1,1, 5000)!= HAL_OK)
  {
    Error_Handler();
  }
  
  /* Put UART peripheral in reception process to wait for other board
     wake up confirmation */  
  if(HAL_UART_Receive(&huart1, (uint8_t *)aRxBuffer, COUNTOF(aTxBuffer1)-1, 10000) != HAL_OK)
  {
    Error_Handler();
  }
  BSP_LED_Off(LED1);
   
  /* Compare the expected and received buffers */
  if(Buffercmp((uint8_t*)aTxBuffer1,(uint8_t*)aRxBuffer,COUNTOF(aTxBuffer1)-1))
  {
    Error_Handler();
  }

  /* wait for two seconds before test second step */
  HAL_Delay(2000);
  
  /*##-3- Send the wake-up from stop mode second trigger #####################*/
  /*      (start Bit detection)                                               */
  BSP_LED_On(LED1);  
  if(HAL_UART_Transmit(&huart1, (uint8_t*)WakeUpTrigger2, 1, 5000)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Put UART peripheral in reception process to wait for other board
     wake up confirmation */  
  if(HAL_UART_Receive(&huart1, (uint8_t *)aRxBuffer, COUNTOF(aTxBuffer2)-1, 10000) != HAL_OK)
  {
    Error_Handler();
  }
  BSP_LED_Off(LED1);
   
  /* Compare the expected and received buffers */
  if(Buffercmp((uint8_t*)aTxBuffer2,(uint8_t*)aRxBuffer,COUNTOF(aTxBuffer2)-1))
  {
    Error_Handler();
  }

  /* wait for two seconds before test third step */
  HAL_Delay(2000);


  /*##-4- Send the wake-up from stop mode third trigger ######################*/
  /*      (7-bit address match)                                               */ 
  BSP_LED_On(LED1);
   if(HAL_UART_Transmit(&huart1, &WakeUpTrigger3, 1, 5000)!= HAL_OK)
  {
    Error_Handler();
  }
 
  /* Put UART peripheral in reception process to wait for other board
     wake up confirmation */  
  if(HAL_UART_Receive(&huart1, (uint8_t *)aRxBuffer, COUNTOF(aTxBuffer3)-1, 10000) != HAL_OK)
  {
    Error_Handler();
  }
  BSP_LED_Off(LED1);
   
  /* Compare the expected and received buffers */
  if(Buffercmp((uint8_t*)aTxBuffer3,(uint8_t*)aRxBuffer,COUNTOF(aTxBuffer3)-1))
  {
    Error_Handler();
  }

  /* wait for two seconds before test fourth and last step */
  HAL_Delay(2000);


  /*##-5- Send the wake-up from stop mode fourth trigger #####################*/
  /*      (4-bit address match)                                               */  
  BSP_LED_On(LED1);
  if(HAL_UART_Transmit(&huart1, &WakeUpTrigger4, 1, 5000)!= HAL_OK)
  {
    Error_Handler();
  }
  
  
  /* Put UART peripheral in reception process to wait for other board
     wake up confirmation */  
  if(HAL_UART_Receive(&huart1, (uint8_t *)aRxBuffer, COUNTOF(aTxBuffer4)-1, 10000) != HAL_OK)
  {
    Error_Handler();
  }
  BSP_LED_Off(LED1);
   
  /* Compare the expected and received buffers */
  if(Buffercmp((uint8_t*)aTxBuffer4,(uint8_t*)aRxBuffer,COUNTOF(aTxBuffer4)-1))
  {
    Error_Handler();
  }

  HAL_Delay(2000);

#endif /* BOARD_IN_STOP1_MODE */



  /* Turn on LED1 if test passes then enter infinite loop */
  BSP_LED_On(LED1);
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
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the common peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_HSIKER;
  PeriphClkInit.HSIKerClockDivider = RCC_HSIKER_DIV3;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
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
  #ifdef BOARD_IN_STOP_MODE
  LPUART1_EXTI_ENABLE_IT();
  #endif /* BOARD_IN_STOP_MODE */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : USER_BUTTON_Pin */
  GPIO_InitStruct.Pin = USER_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(USER_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
#if defined(BOARD_IN_STOP1_MODE)
/**
  * @brief  System Clock Configuration restored after STOP1 mode
  * @param  None
  * @retval None
  */
void SystemClock_Config_fromSTOP1(void)
{
  SystemClock_Config();
}
#endif

/**
  * @brief  UART error callbacks
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  Error_Handler();
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == BUTTON_USER_PIN)
  {  
    UserButtonStatus = 1;
  }
}

/**
  * @brief UART wakeup from Stop mode callback
  * @param huart: uart handle
  * @retval None
  */
void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
  /* Turn back on LED1 */
  BSP_LED_On(LED1);
}


#if !defined(BOARD_IN_STOP1_MODE)
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
#endif /* !defined(BOARD_IN_STOP1_MODE) */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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
