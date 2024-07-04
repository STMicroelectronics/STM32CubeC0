/**
  ******************************************************************************
  * @file    low_level_rng.c
  * @author  MCD Application Team
  * @brief   Low Level Interface module that uses RNG
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

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"
#include "entropy.h"
#include "low_level_rng.h"
#include "main.h"
#include <string.h>

/* exported variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define COMPILER_BARRIER() __ASM __IO("" : : : "memory")
#define RNG_NUMBER                10UL
#define RNG_NB_ENTROPY_BITS        8UL

/* Private variables ---------------------------------------------------------*/
uint8_t seed_buf[RNG_NUMBER];
size_t index_seed_buf;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  The Random delay
  * @param  None
  * @retval None
  */
void RNG_Delay(void)
{
  uint8_t delay = 0u;
  int foo = 0;

  delay = RNG_Get_Random();

  for (volatile int i = 0; i < delay; i++) {
      foo++;
  }
}

/**
  * @brief  Initializes random values
  * @param  None
  * @retval None
  */
void RNG_Delay_Init(void)
{
  size_t len = 0U;
  /* generate several random */
  RNG_GetBytes((unsigned char *)seed_buf, sizeof(seed_buf),(size_t *)&len);

}

/**
  * @brief  Get Random Value
  * @param  None
  * @retval Delay
  */
uint8_t RNG_Get_Random(void)
{
  uint8_t delay;

  while (delay == 0u)
  {
    delay = seed_buf[index_seed_buf];
    index_seed_buf++;

    if ( RNG_NUMBER == index_seed_buf )
    {
      RNG_Delay_Init();
      index_seed_buf = 0;
     }
  }
  return delay;
}

/**
  * @brief  Random Number Generator configuration
  * @param  None
  * @retval None
  */
void RNG_Init(void)
{
  /* Reset Seed Buffer */
  memset(seed_buf, 0x00, sizeof(seed_buf) / sizeof(uint8_t));
  /* Reset Seed Buffer counter*/
  index_seed_buf = 0UL;
}

/**
  * @brief  Generates a list of random numbers
  * @param  None
  * @retval None
  */
void RNG_GetBytes(uint8_t *output, size_t length, size_t *output_length)
{
  /* collect random values */
  Entropy_Gather(length * RNG_NB_ENTROPY_BITS, output);
}

/**
  * @brief  DeInitializes the RNG peripheral
  * @param  None
  * @retval None
  */
void RNG_DeInit(void)
{
  /* TIM Peripheral clock disable */
  __HAL_RCC_TIM16_CLK_DISABLE();
  __HAL_RCC_TIM16_FORCE_RESET();
  __HAL_RCC_TIM16_RELEASE_RESET();
  /* Disable interrupt */
  HAL_NVIC_DisableIRQ(TIM16_IRQn);
}
