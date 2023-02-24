/**
  ******************************************************************************
  * @file    stm32c0116_discovery_conf_template.h
  * @author  MCD Application Team
  * @brief   configuration file.
  *          This file should be copied to the application folder and renamed
  *          to stm32c0116_discovery_conf.h
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32C0116_DK_CONF_H
#define STM32C0116_DK_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32C0116_DK
  * @{
  */

/** @defgroup STM32C0116_DK_CONFIG Config
  * @{
  */

/** @defgroup STM32C0116_DK_CONFIG_Exported_Constants Exported Constants
  * @{
  */

/* COM define */
#define USE_BSP_COM_FEATURE               0U
#define USE_COM_LOG                       0U

/* Button user interrupt priority */
#define BSP_BUTTON_USER_IT_PRIORITY          0x0FUL  /* Default is lowest priority level */

/* JOY define */
#define USE_BSP_JOY_FEATURE               1U

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32C0116_DK_CONF_H */
