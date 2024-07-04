/**
  ******************************************************************************
  * @file    entropy.c
  * @author  MCD Application Team
  * @brief   This file contains functions for Entropy gathering utility
  * @note    This solution should be used only if the target device doesn’t provide
  *          a TRNG peripheral, and its usage is discouraged for critical security
  *          or cryptographic purposes.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "entropy.h"

/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htimx;
static __IO uint32_t EntropyIndex;
static __IO uint32_t EntropyMax;
static __IO uint8_t *pEntropyBuffer;
/* Private function prototypes -----------------------------------------------*/
static void RestartLSI(void);
static void ConfigureMeasureTimer(void);
static void StartMeasureTimer(void);
void TIM_IRQ_HANDLER(void);
/* Functions Definition ------------------------------------------------------*/

/**
  * @brief  Entropy gathering utility
  * @param  nbBits    Number of entropy bits to gather
  * @param  pEntropy  Buffer to receive entropy data (must be enough large to contain nbBits bits)
  * @retval None
  */
void Entropy_Gather(uint32_t nbBits, __IO uint8_t *pEntropy)
{
  /* Avoid Warning[Pa082]: undefined behavior: the order of volatile accesses is undefined in this statement */
  uint32_t EntropyMaxVal;

  EntropyIndex = 0;
  EntropyMax = nbBits;
  pEntropyBuffer = pEntropy;

  /* Reset entropy buffer contents */
  for (uint32_t i = 0U; i < (((nbBits & 0x7UL) == 0UL) ? (nbBits / 8) : (nbBits / 8 + 1)); i++)
  {
    pEntropy[i] = 0U;
  }

  /* Configure timer to measure LSI cycle length */
  ConfigureMeasureTimer();

  /* Restart LSI oscillator */
  RestartLSI();

  /* Launch measurement timer */
  StartMeasureTimer();

  EntropyMaxVal = EntropyMax;
  /* Wait for all entropy bit to be gathered */
  while (EntropyIndex < EntropyMaxVal)
  {}
}

/**
  * @brief  LSI restart utility
  * @param  None
  * @retval None
  */
static void RestartLSI(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  Configure timer to measure LSI cycle length
  * @param  None
  * @retval None
  */
static void ConfigureMeasureTimer(void)
{
  TIM_IC_InitTypeDef sConfigIC = {0};

  htimx.Instance = TIM16;
  htimx.Init.Prescaler = 0;
  htimx.Init.CounterMode = TIM_COUNTERMODE_UP;
  htimx.Init.Period = 0xFFFFU; /* Set Max Period */
  htimx.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htimx.Init.RepetitionCounter = 0;
  htimx.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htimx) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htimx) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htimx, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIMEx_TISelection(&htimx, TIM_TIM16_TI1_LSI, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* TIM interrupt Init */
  HAL_NVIC_SetPriority(TIM16_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM16_IRQn);
}

/**
  * @brief  Start timer to measure LSI cycle length
  * @param  None
  * @retval None
  */
static void StartMeasureTimer(void)
{
  if (HAL_TIM_IC_Start_IT(&htimx, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  Input Capture callback in non-blocking mode
  * @param  htim TIM IC handle
  * @retval None
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  /* Avoid Warning[Pa082]: undefined behavior: the order of volatile accesses is undefined in this statement */
  uint32_t EntropyMaxVal   = EntropyMax;
  uint32_t EntropyIndexVal = EntropyIndex;

  uint32_t meas = HAL_TIM_ReadCapturedValue(&htimx, TIM_CHANNEL_1);
  HAL_TIM_IC_Stop_IT(&htimx, TIM_CHANNEL_1);

  pEntropyBuffer[EntropyIndexVal / 8] |= (uint8_t)((meas & 0x01UL) << (7 - (EntropyIndexVal & 0x07UL)));
  EntropyIndex++;

  if (EntropyIndex < EntropyMaxVal)
  {
    RestartLSI();
    StartMeasureTimer();
  }
}
