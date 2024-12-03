/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
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
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"
#include "stm32c0xx_ll_utils.h"
#include <stdio.h>
#include <string.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*#define DEVICE_64K_FLASH_ENABLE*/    /*Defined: The project is for 64KB device*/

/*#define DEVICE_256K_FLASH_ENABLE*/   /*Defined: The project is for 256KB device*/

#define DATA_SIZE                        0x4000

/* Add definition of OEMISB_FLASH_SIZE */
#if defined(DEVICE_64K_FLASH_ENABLE)
#define OEMISB_FLASH_SIZE              0x10000
#elif defined(DEVICE_256K_FLASH_ENABLE)
#define OEMISB_FLASH_SIZE              0x40000
#else
#define OEMISB_FLASH_SIZE              0x20000
#endif

/* Constants used by Serial Command Line Mode */
#define TX_TIMEOUT          ((uint32_t)100U)
#define RX_TIMEOUT          ((uint32_t)2000U)

void Error_Handler(void);

/* Definition for USARTx clock resources */
#define COM_INSTANCE                           USART2
#define COM_CLK_ENABLE()                       __HAL_RCC_USART2_CLK_ENABLE()
#define COM_TX_GPIO_PORT                       GPIOA
#define COM_TX_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM_TX_PIN                             GPIO_PIN_2
#define COM_TX_AF                              GPIO_AF1_USART2

#define COM_RX_GPIO_PORT                       GPIOA
#define COM_RX_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM_RX_PIN                             GPIO_PIN_3
#define COM_RX_AF                              GPIO_AF1_USART2
#endif /* __MAIN_H */