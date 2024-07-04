/**
  ******************************************************************************
  * @file    low_level_rng.h
  * @author  MCD Application Team
  * @brief   Header for low_level_rng.c module
  *
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LOW_LEVEL_RNG_H
#define LOW_LEVEL_RNG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief  Random Number Generator configuration
  * @param  None
  * @retval None
  */
void RNG_Init(void);

/**
  * @brief  Generates a list of random numbers
  * @param  None
  * @retval None
  */
void RNG_GetBytes(uint8_t *output, size_t length, size_t *output_length);

/**
  * @brief  DeInitializes the RNG peripheral
  * @param  None
  * @retval None
  */
void RNG_DeInit(void);

/**
  * @brief  The Random delay
  * @param  None
  * @retval None
  */
void RNG_Delay(void);

/**
  * @brief  Initializes random values
  * @param  None
  * @retval None
  */
void RNG_Delay_Init(void);

/**
  * @brief  Get Random Value
  * @param  None
  * @retval Delay
  */
uint8_t RNG_Get_Random(void);

#endif /* LOW_LEVEL_RNG_H */
