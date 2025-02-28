/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    Examples/ADC/ADC_Oversampling/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to use a ADC peripheral with
  *          ADC oversampling to perform automatically multiple
  *          ADC conversions and average computation, by ADC hardware,
  *          and therefore off-load the CPU for the equivalent task.
  *          This example is based on the STM32C0xx ADC HAL API.
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

/* Definitions of environment analog values */
  /* Value of analog reference voltage (Vref+), connected to analog voltage   */
  /* supply Vdda (unit: mV).                                                  */
  #define VDDA_APPLI                       (3300UL)

/* Definitions of data related to this example */
  /* Init variable out of expected ADC conversion data range */
  #define VAR_CONVERTED_DATA_INIT_VALUE    (__LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B) + 1)

  /* Init variable out of ADC expected conversion data range for data         */
  /* on 16 bits (oversampling enabled).                                       */
  #define VAR_CONVERTED_DATA_INIT_VALUE_16BITS    (0xFFFF + 1UL)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN PV */

/* Variables for ADC conversion data */
__IO uint16_t uhADCxConvertedData_OVS_ratio16_shift4   = VAR_CONVERTED_DATA_INIT_VALUE;        /* ADC group regular conversion data, oversampling ratio 16 and shift 4 (data scale: 12 bits) */
__IO uint32_t uhADCxConvertedData_OVS_ratio16_shift0   = VAR_CONVERTED_DATA_INIT_VALUE_16BITS; /* ADC group regular conversion data, oversampling ratio 16 and shift 0 (data scale: 16 bits) */
__IO uint16_t uhADCxConvertedData_OVS_disabled         = VAR_CONVERTED_DATA_INIT_VALUE;        /* ADC group regular conversion data, oversampling disabled (data scale corresponds to ADC resolution: 12 bits) */

__IO float    fConvertedData_OVS_EquivalentValue12bits = 4.4f; /* Calculation of oversampling raw data to the equivalent data (from variable "uhADCxConvertedData_OVS_ratio16_shift0") to the equivalent data on 12 bits with floating point */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

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

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  /* Initialize LED on board */
  BSP_LED_Init(LED1);

  /* Perform ADC calibration */
  if (HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK)
  {
    /* Calibration Error */
    Error_Handler();
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /*## Step 1: ADC oversampling initial settings  ##########################*/

    /* Start ADC group regular conversion */
    if (HAL_ADC_Start(&hadc1) != HAL_OK)
    {
      /* ADC conversion start error */
      Error_Handler();
    }

    /* Wait for ADC conversion completed */
    if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
    {
      /* End Of Conversion flag not set on time */
      Error_Handler();
    }

    /* Retrieve ADC conversion data */
    /* (data scale with oversampling ratio 16 and shift 4 corresponds         */
    /* to ADC resolution: 12 bits)                                            */
    uhADCxConvertedData_OVS_ratio16_shift4 = HAL_ADC_GetValue(&hadc1);


    /*## Step 2: ADC oversampling modified settings  #########################*/
    /* Modify ADC oversampling settings:                                      */
    /* - ratio: 16                                                            */
    /* - shift: 0 (no shift)                                                  */
    /* Set ADC oversampling parameters */
    HAL_ADC_Stop(&hadc1);
    hadc1.Init.OversamplingMode = ENABLE;
    hadc1.Init.Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_16;
    hadc1.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
      Error_Handler();
    }

    /* Start ADC group regular conversion */
    if (HAL_ADC_Start(&hadc1) != HAL_OK)
    {
      /* ADC conversion start error */
      Error_Handler();
    }

    /* Wait for ADC conversion completed */
    if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
    {
      /* End Of Conversion flag not set on time */
      Error_Handler();
    }

    /* Retrieve ADC conversion data */
    /* (data scale with oversampling ratio 16 and shift 0 exceeds             */
    /* ADC resolution 12 bits, data scale expected: 16 bits)                  */
    uhADCxConvertedData_OVS_ratio16_shift0 = HAL_ADC_GetValue(&hadc1);


    /*## Step 3: ADC oversampling disabled  ##################################*/
    /* Modify ADC oversampling settings:                                      */
    /* - scope: none (oversampling disabled)                                  */
    /* Set ADC oversampling scope */
    HAL_ADC_Stop(&hadc1);
    hadc1.Init.OversamplingMode = DISABLE;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
      Error_Handler();
    }

    /* Start ADC group regular conversion */
    if (HAL_ADC_Start(&hadc1) != HAL_OK)
    {
      /* ADC conversion start error */
      Error_Handler();
    }

    /* Wait for ADC conversion completed */
    if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
    {
      /* End Of Conversion flag not set on time */
      Error_Handler();
    }

    /* Retrieve ADC conversion data */
    /* (data scale with oversampling disabled corresponds                     */
    /* to ADC resolution: 12 bits)                                            */
    uhADCxConvertedData_OVS_disabled = HAL_ADC_GetValue(&hadc1);


    /* Restore ADC oversampling initial settings for next loop:               */
    /* - scope: ADC group regular                                             */
    /* - ratio: 16                                                            */
    /* - shift: 4                                                             */
    /* Set ADC oversampling scope */
    HAL_ADC_Stop(&hadc1);
    hadc1.Init.OversamplingMode = ENABLE;
    hadc1.Init.Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_16;
    hadc1.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_4;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
      Error_Handler();
    }

    /*## Step 4: ADC conversion data evaluation  #############################*/
    /* Expected raw data: */
    /*  - Data of initial oversampling configuration (ratio 16, shift 4)      */
    /*    should be on the same scale as ADC resolution: 12 bits.             */
    /*  - Data of modified oversampling configuration (ratio 16, shift 0)     */
    /*    should exceed ADC resolution 12 bits and be on scale: 16 bits       */
    /*  - Data of oversampling disabled should be on the same scale as        */
    /*    ADC resolution: 12 bits.                                            */
    /* Expected data comparison: */
    /*  - Data of initial oversampling configuration (ratio 16, shift 4)      */
    /*    and modified oversampling configuration (ratio 16, shift 0) with    */
    /*    SW calculation of equivalent data on 12 bits with floating point    */
    /*    should be similar.                                                  */
    /*    This SW calculation is equivalent to the ADC oversampling           */
    /*    operation "shift 4".                                                */
    /*  - ADC conversion data with oversampling enabled should have less      */
    /*    variation than with oversampling disabled: oversampling is          */
    /*    equivalent to an averaging (average on 16 ADC conversions with      */
    /*    settings of this example).                                          */

    /* Note: Optionally, for this example purpose, check ADC conversion       */
    /*       data validity.                                                   */
    /* Data value should not exceed range resolution 12 bits */
    if ((uhADCxConvertedData_OVS_ratio16_shift4 > __LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B)) ||
        (uhADCxConvertedData_OVS_disabled > __LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B)))
    {
      /* Error: Data not valid */
      Error_Handler();
    }

    /* Data value should not exceed range of resolution 16 bits */
    if (uhADCxConvertedData_OVS_ratio16_shift0 > 0xFFFF)
    {
      /* Error: Data not valid */
      Error_Handler();
    }

    /* For this example purpose, calculation of oversampling raw data         */
    /* (from variable "uhADCxConvertedData_OVS_ratio16_shift0")               */
    /* to the equivalent data on 12 bits with floating point                  */
    fConvertedData_OVS_EquivalentValue12bits = (((float)uhADCxConvertedData_OVS_ratio16_shift0) / 16);

    /* Data value should not exceed range resolution 12 bits */
    if (fConvertedData_OVS_EquivalentValue12bits > __LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B))
    {
      /* Error: Data not valid */
      Error_Handler();
    }


    /* Toggle LED on at the end of all ADC conversions */
    BSP_LED_Toggle(LED1);

    HAL_Delay(LED_BLINK_SLOW);

    /* Note: ADC conversion data is stored into variables:                    */
    /*       - "uhADCxConvertedData_OVS_ratio16_shift4"                       */
    /*       - "uhADCxConvertedData_OVS_ratio16_shift0"                       */
    /*       - "uhADCxConvertedData_OVS_disabled"                             */
    /*       Computed data with floating point:                               */
    /*       - "fConvertedData_OVS_EquivalentValue12bits"                     */
    /*       (for debug: see variable content into watch window).             */

    /* Note: ADC conversion data can be computed to physical values           */
    /*       using ADC LL driver helper macro:                                */
    /*         uhADCxConvertedData_Voltage_mVolt                              */
    /*         = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI,                    */
    /*                                         uhADCxConvertedData),          */
    /*                                         LL_ADC_RESOLUTION_12B)         */

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
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_SEQ_FIXED;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_79CYCLES_5;
  hadc1.Init.OversamplingMode = ENABLE;
  hadc1.Init.Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_16;
  hadc1.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_4;
  hadc1.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_LOW;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED1_Pin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* Turn on LED and remain in infinite loop */
  while (1)
  {
    BSP_LED_On(LED1);
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
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
