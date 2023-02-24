/**
  ******************************************************************************
  * @file    openbootloader_conf.h
  * @author  MCD Application Team
  * @brief   Contains Open Bootloader configuration
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019-2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OPENBOOTLOADER_CONF_H
#define OPENBOOTLOADER_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* -------------------------------- Device ID ------------------------------- */
#define DEVICE_ID_MSB                     0x04  /* MSB byte of device ID */
#define DEVICE_ID_LSB                     0x53  /* LSB byte of device ID */

/* -------------------------- Definitions for Memories ---------------------- */
#define BL_FLASH_SIZE                     (32U * 1024U)  /* Size of FLASH 32 KByte */
#define FLASH_START_ADDRESS               FLASH_BASE
#define FLASH_END_ADDRESS                 (FLASH_START_ADDRESS + BL_FLASH_SIZE)

#define RAM_SIZE                          (12U * 1024U)  /* Size of RAM 12 kByte */
#define RAM_START_ADDRESS                 SRAM_BASE
#define RAM_END_ADDRESS                   (RAM_START_ADDRESS + RAM_SIZE)

#define OB_SIZE                           128U  /* Size of OB 128 Bytes */
#define OB_START_ADDRESS                  0x1FFF7800U  /* Option bytes registers address */
#define OB_END_ADDRESS                    (OB_START_ADDRESS + OB_SIZE)

#define OTP_SIZE                          1024U  /* Size of OTP 1024 Byte */
#define OTP_START_ADDRESS                 0x1FFF7000U  /* OTP registers address */
#define OTP_END_ADDRESS                   (OTP_START_ADDRESS + OTP_SIZE)

#define ICP_SIZE                          (6U * 1024U)  /* Size of ICP 6 kByte */
#define ICP1_START_ADDRESS                0x1FFF0000U  /* System memory registers address */
#define ICP1_END_ADDRESS                  (ICP1_START_ADDRESS + ICP_SIZE)

#define EB_SIZE                           768U  /* Size of EB 768 Byte */
#define EB_START_ADDRESS                  0x1FFF7500U  /* Engi bytes start address */
#define EB_END_ADDRESS                    (EB_START_ADDRESS + EB_SIZE)  /* Engi bytes end address */

#define OPENBL_RAM_SIZE                   0x00001400U  /* RAM used by the Open Bootloader 5 kBytes */

#define OPENBL_DEFAULT_MEM                FLASH_START_ADDRESS  /* Address used for the Erase, Writep and readp command */

#define RDP_LEVEL_0                       OB_RDP_LEVEL_0
#define RDP_LEVEL_1                       OB_RDP_LEVEL_1
#define RDP_LEVEL_2                       OB_RDP_LEVEL_2

#define AREA_ERROR                        0x0U  /* Error Address Area */
#define FLASH_AREA                        0x1U  /* Flash Address Area */
#define RAM_AREA                          0x2U  /* RAM Address area */
#define OB_AREA                           0x3U  /* Option bytes Address area */
#define OTP_AREA                          0x4U  /* OTP Address area */
#define ICP_AREA                          0x5U  /* System memory area */
#define EB_AREA                           0x6U  /* Engi bytes Address area */

#define FLASH_MASS_ERASE                  0xFFFF
#define FLASH_BANK1_ERASE                 0xFFFE
#define FLASH_BANK2_ERASE                 0xFFFD

#define INTERFACES_SUPPORTED              6U

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* OPENBOOTLOADER_CONF_H */
