/**
  ******************************************************************************
  * @file    boot.h
  * @author  MCD Application Team
  * @brief   Header for boot.c module
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
#ifndef __BOOT_HAL_H__
#define __BOOT_HAL_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief  Boot initialization.
  * @param  None
  * @retval None
  */
void BootInit(void);

/**
  * @brief  This function manage the jump to application.
  * @param  void
  * @retval void
  */
void BootQuit(void);

#endif /* __BOOT_HAL_H__ */






