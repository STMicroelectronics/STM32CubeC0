/**
******************************************************************************
* @file    boot_cfg.h
* @author  MCD Application Team
* @brief   Header for boot configuration
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
#ifndef BOOT_CFG_H
#define BOOT_CFG_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Boot size can be changed but it require updating MPU configuration */
#define FLASH_BOOT_AREA_SIZE (0x2000UL)
/* Exported macro ------------------------------------------------------------*/
#define OEMISB_MODE_DEV
#define OEMISB_OB_RDP_LEVEL_VALUE OB_RDP_LEVEL_0 /*< RDP level */
#define OEMISB_MPU_PROTECTION
/* Exported functions ------------------------------------------------------- */
#endif /* BOOT_CFG_H */
