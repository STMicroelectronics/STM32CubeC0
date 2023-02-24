/**
  ******************************************************************************
  * @file    app_openbootloader.c
  * @author  MCD Application Team
  * @brief   OpenBootloader application entry point
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
#include "main.h"
#include "app_openbootloader.h"
#include "usart_interface.h"
#include "i2c_interface.h"
#include "iwdg_interface.h"
#include "flash_interface.h"
#include "ram_interface.h"
#include "optionbytes_interface.h"
#include "otp_interface.h"
#include "systemmemory_interface.h"
#include "openbl_usart_cmd.h"
#include "openbl_i2c_cmd.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static OPENBL_HandleTypeDef USART_Handle;
static OPENBL_HandleTypeDef I2C_Handle;
static OPENBL_HandleTypeDef IWDG_Handle;

static OPENBL_OpsTypeDef USART_Ops =
{
  OPENBL_USART_Configuration,
  OPENBL_USART_DeInit,
  OPENBL_USART_ProtocolDetection,
  OPENBL_USART_GetCommandOpcode,
  OPENBL_USART_SendByte
};

static OPENBL_OpsTypeDef I2C_Ops =
{
  OPENBL_I2C_Configuration,
  OPENBL_I2C_DeInit,
  OPENBL_I2C_ProtocolDetection,
  OPENBL_I2C_GetCommandOpcode,
  OPENBL_I2C_SendAcknowledgeByte
};

static OPENBL_OpsTypeDef IWDG_Ops =
{
  OPENBL_IWDG_Configuration,
  NULL,
  NULL,
  NULL,
  NULL
};

OPENBL_CommandsTypeDef USART_Cmd =
{
  OPENBL_USART_GetCommand,
  OPENBL_USART_GetVersion,
  OPENBL_USART_GetID,
  OPENBL_USART_ReadMemory,
  OPENBL_USART_WriteMemory,
  OPENBL_USART_Go,
  OPENBL_USART_ReadoutProtect,
  OPENBL_USART_ReadoutUnprotect,
  OPENBL_USART_EraseMemory,
  OPENBL_USART_WriteProtect,
  OPENBL_USART_WriteUnprotect,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  OPENBL_USART_SpecialCommand,
  OPENBL_USART_ExtendedSpecialCommand
};

OPENBL_CommandsTypeDef I2C_Cmd =
{
  OPENBL_I2C_GetCommand,
  OPENBL_I2C_GetVersion,
  OPENBL_I2C_GetID,
  OPENBL_I2C_ReadMemory,
  OPENBL_I2C_WriteMemory,
  OPENBL_I2C_Go,
  OPENBL_I2C_ReadoutProtect,
  OPENBL_I2C_ReadoutUnprotect,
  OPENBL_I2C_EraseMemory,
  OPENBL_I2C_WriteProtect,
  OPENBL_I2C_WriteUnprotect,
  OPENBL_I2C_NonStretchWriteMemory,
  OPENBL_I2C_NonStretchEraseMemory,
  OPENBL_I2C_NonStretchWriteProtect,
  OPENBL_I2C_NonStretchWriteUnprotect,
  OPENBL_I2C_NonStretchReadoutProtect,
  OPENBL_I2C_NonStretchReadoutUnprotect,
  NULL,
  OPENBL_I2C_SpecialCommand,
  OPENBL_I2C_ExtendedSpecialCommand
};

/* Exported variables --------------------------------------------------------*/
uint16_t SpecialCmdList[SPECIAL_CMD_MAX_NUMBER] =
{
  SPECIAL_CMD_DEFAULT
};

uint16_t ExtendedSpecialCmdList[EXTENDED_SPECIAL_CMD_MAX_NUMBER] =
{
  SPECIAL_CMD_DEFAULT
};

/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize open Bootloader.
  * @param  None.
  * @retval None.
  */
void OpenBootloader_Init(void)
{
  /* Register USART interfaces */
  USART_Handle.p_Ops = &USART_Ops;
  USART_Handle.p_Cmd = OPENBL_USART_GetCommandsList();

  OPENBL_RegisterInterface(&USART_Handle);

  /* Register I2C interfaces */
  I2C_Handle.p_Ops = &I2C_Ops;
  I2C_Handle.p_Cmd = OPENBL_I2C_GetCommandsList();

  OPENBL_RegisterInterface(&I2C_Handle);

  /* Register IWDG interfaces */
  IWDG_Handle.p_Ops = &IWDG_Ops;
  IWDG_Handle.p_Cmd = NULL;

  OPENBL_RegisterInterface(&IWDG_Handle);

  /* Initialize interfaces */
  OPENBL_Init();

  /* Initialize memories */
  OPENBL_MEM_RegisterMemory(&FLASH_Descriptor);
  OPENBL_MEM_RegisterMemory(&RAM_Descriptor);
  OPENBL_MEM_RegisterMemory(&OB1_Descriptor);
  OPENBL_MEM_RegisterMemory(&OTP_Descriptor);
  OPENBL_MEM_RegisterMemory(&ICP1_Descriptor);
  OPENBL_MEM_RegisterMemory(&EB_Descriptor);
}

/**
  * @brief  DeInitialize open Bootloader.
  * @param  None.
  * @retval None.
  */
void OpenBootloader_DeInit(void)
{
  System_DeInit();
}

/**
  * @brief  This function is used to select which protocol will be used when communicating with the host.
  * @param  None.
  * @retval None.
  */
void OpenBootloader_ProtocolDetection(void)
{
  static uint32_t interface_detected = 0;

  if (interface_detected == 0)
  {
    interface_detected = OPENBL_InterfaceDetection();

    /* De-initialize the interfaces that are not detected */
    if (interface_detected == 1U)
    {
      OPENBL_InterfacesDeInit();
    }
  }

  if (interface_detected == 1)
  {
    OPENBL_CommandProcess();
  }
}
