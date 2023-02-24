/**
  ******************************************************************************
  * @file    optionbytes_interface.c
  * @author  MCD Application Team
  * @brief   Contains Option Bytes access functions
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

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

#include "openbl_mem.h"

#include "app_openbootloader.h"
#include "common_interface.h"
#include "optionbytes_interface.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
OPENBL_MemoryTypeDef OB1_Descriptor =
{
  OB_START_ADDRESS,
  OB_END_ADDRESS,
  OB_SIZE,
  OB_AREA,
  OPENBL_OB_Read,
  OPENBL_OB_Write,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Launch the option byte loading.
  * @retval None.
  */
void OPENBL_OB_Launch(void)
{
  /* Set the option start bit */
  HAL_FLASH_OB_Launch();

  /* Set the option lock bit and Lock the flash */
  HAL_FLASH_OB_Lock();
  HAL_FLASH_Lock();
}

/**
  * @brief  This function is used to read data from a given address.
  * @param  Address The address to be read.
  * @retval Returns the read value.
  */
uint8_t OPENBL_OB_Read(uint32_t Address)
{
  return (*(uint8_t *)(Address));
}

/**
  * @brief  This function is used to write data in Option bytes.
  * @param  Address The address where that data will be written.
  * @param  pData The data to be written.
  * @param  DataLength The length of the data to be written.
  * @retval None.
  */
void OPENBL_OB_Write(uint32_t Address, uint8_t *pData, uint32_t DataLength)
{
  /* Unlock the FLASH & Option Bytes Registers access */
  HAL_FLASH_Unlock();
  HAL_FLASH_OB_Unlock();

  /* Clear error programming flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

  if ((DataLength != 0) && (*pData != RDP_LEVEL_2))
  {
    /* Write the user and read protection option bytes */
    if (DataLength > 1U)
    {
      /* FLASH->OPTR (0x1FFF7800) */
      FLASH->OPTR = (uint32_t)((*(__IO uint32_t *)(pData + 0)));
    }

    /* Write the PCROP 1A Start address option byte */
    if (DataLength > 0x8)
    {
      /* FLASH->PCROP1ASR (0x1FFF7808) */
      FLASH->PCROP1ASR = (uint32_t)((*(__IO uint32_t *)(pData + 0x8)));
    }

    /* Write the PCROP 1A End address option byte */
    if (DataLength > 0x10)
    {
      /* FLASH->PCROP1AER (0x1FFF7810) */
      FLASH->PCROP1AER = (uint32_t)((*(__IO uint32_t *)(pData + 0x10)));
    }

    /* Write the WRP 1A start & and option byte */
    if (DataLength > 0x18)
    {
      /* FLASH->WRP1AR (0x1FFF7818) */
      FLASH->WRP1AR = (uint32_t)((*(__IO uint32_t *)(pData + 0x18)));
    }

    /* Write the WRP 1B start & end option byte */
    if (DataLength > 0x20)
    {
      /* FLASH->WRP1BR (0x1FFF7820) */
      FLASH->WRP1BR = (uint32_t)((*(__IO uint32_t *)(pData + 0x20)));
    }

    /* Write the PCROP 1B start option byte */
    if (DataLength > 0x28)
    {
      /* FLASH->PCROP1BSR (0x1FFF7828) */
      FLASH->PCROP1BSR = (uint32_t)((*(__IO uint32_t *)(pData + 0x28)));
    }

    /* Write the PCROP 1B end option byte */
    if (DataLength > 0x30)
    {
      /* FLASH->PCROP1BER (0x1FFF7830) */
      FLASH->PCROP1BER = (uint32_t)((*(__IO uint32_t *)(pData + 0x30)));
    }

    /* Write the IPCC data buffer address option byte */
    if (DataLength > 0x70)
    {
      /* FLASH->SECR (0x1FFF7870) */
      FLASH->SECR = (uint32_t)((*(__IO uint32_t *)(pData + 0x70)));
    }
  }

  SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);

  /* Register system reset callback */
  Common_SetPostProcessingCallback(OPENBL_OB_Launch);
}
