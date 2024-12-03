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

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void Error_Handler(void);

/*#define DEVICE_64K_FLASH_ENABLE*/    /*Defined: The project is for 64KB flash device*/

/*#define DEVICE_256K_FLASH_ENABLE*/  /*Defined: The project is for 256KB flash device*/

/* Add definition of OEMISB_FLASH_SIZE */
#if defined(DEVICE_64K_FLASH_ENABLE)
#define OEMISB_FLASH_SIZE               0x10000
#elif defined(DEVICE_256K_FLASH_ENABLE)
#define OEMISB_FLASH_SIZE               0x40000
#else
#define OEMISB_FLASH_SIZE               0X20000
#endif
/* Definition for USARTx clock resources */

#define DATA_SIZE                        0x4000
#define DATA_MAX_SIZE                    0x4000
#define DATA_MPU_SUB_REG                 0x0

#endif /* __MAIN_H */

