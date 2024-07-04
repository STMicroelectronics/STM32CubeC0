/**
  ******************************************************************************
  * @file    low_level_security.c
  * @author  MCD Application Team
  * @brief   security protection implementation for secure boot on STM32U0xx
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
#include <string.h>
#include "stm32c0xx_hal.h"
#include "boot_cfg.h"
#include "mbedtls/sha256.h"
#include "boot_hal_flowcontrol.h"
#include "low_level_security.h"
#include "main.h"

/* exported variables --------------------------------------------------------*/
extern void Error_Handler(void);

/* Private typedef -----------------------------------------------------------*/
struct mpu_region_cfg_t
{
  MPU_Region_InitTypeDef mpu_region_init;
#ifdef FLOW_CONTROL
  uint32_t flow_step_enable;
  uint32_t flow_ctrl_enable;
  uint32_t flow_step_check;
  uint32_t flow_ctrl_check;
#endif /* FLOW_CONTROL */
};

/* Private define ------------------------------------------------------------*/
#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))


/* MPU configuration
  ================== */
const struct mpu_region_cfg_t mpu_region_boot_cfg[] =
{
  /* Region 0 : Flash area with execution right disabled */
  {
    {
      MPU_REGION_ENABLE,
      MPU_REGION_NUMBER0,
      FLASH_BASE,
      MPU_REGION_SIZE_128KB,
      0,
      MPU_TEX_LEVEL0,
      MPU_REGION_PRIV_RO,
      MPU_INSTRUCTION_ACCESS_DISABLE,
      MPU_ACCESS_NOT_SHAREABLE,
      MPU_ACCESS_CACHEABLE,
      MPU_ACCESS_NOT_BUFFERABLE
    },
#ifdef FLOW_CONTROL
    FLOW_STEP_MPU_I_EN_R0,
    FLOW_CTRL_MPU_I_EN_R0,
    FLOW_STEP_MPU_I_CH_R0,
    FLOW_CTRL_MPU_I_CH_R0,
#endif /* FLOW_CONTROL */
  },
  /* Region 1 : Flash area with execution right enabled */
  {
    {
      MPU_REGION_DISABLE,
      MPU_REGION_NUMBER1,
      FLASH_BASE,
      MPU_REGION_SIZE_128KB,
      0,
      MPU_TEX_LEVEL0,
      MPU_REGION_PRIV_RO,
      MPU_INSTRUCTION_ACCESS_ENABLE,
      MPU_ACCESS_NOT_SHAREABLE,
      MPU_ACCESS_CACHEABLE,
      MPU_ACCESS_NOT_BUFFERABLE
    },
#ifdef FLOW_CONTROL
    FLOW_STEP_MPU_I_EN_R1,
    FLOW_CTRL_MPU_I_EN_R1,
    FLOW_STEP_MPU_I_CH_R1,
    FLOW_CTRL_MPU_I_CH_R1,
#endif /* FLOW_CONTROL */
  },
  /* Region 2 : Flash boot area */
  {
    {
      MPU_REGION_ENABLE,
      MPU_REGION_NUMBER2,
      FLASH_BASE,
      MPU_REGION_SIZE_8KB, /* Should be updated if the boot size changes */
      0,
      MPU_TEX_LEVEL0,
      MPU_REGION_PRIV_RO,
      MPU_INSTRUCTION_ACCESS_ENABLE,
      MPU_ACCESS_NOT_SHAREABLE,
      MPU_ACCESS_CACHEABLE,
      MPU_ACCESS_NOT_BUFFERABLE
    },
#ifdef FLOW_CONTROL
    FLOW_STEP_MPU_I_EN_R2,
    FLOW_CTRL_MPU_I_EN_R2,
    FLOW_STEP_MPU_I_CH_R2,
    FLOW_CTRL_MPU_I_CH_R2,
#endif /* FLOW_CONTROL */
  },
  /* Region 3 : Flash hash area */
  {
    {
      MPU_REGION_ENABLE,
      MPU_REGION_NUMBER3,
      FLASH_BASE + FLASH_BOOT_AREA_SIZE - 64,
      MPU_REGION_SIZE_256B,
      0xFC,
      MPU_TEX_LEVEL0,
      MPU_REGION_PRIV_RO,
      MPU_INSTRUCTION_ACCESS_DISABLE,
      MPU_ACCESS_NOT_SHAREABLE,
      MPU_ACCESS_CACHEABLE,
      MPU_ACCESS_NOT_BUFFERABLE
    },
#ifdef FLOW_CONTROL
    FLOW_STEP_MPU_I_EN_R3,
    FLOW_CTRL_MPU_I_EN_R3,
    FLOW_STEP_MPU_I_CH_R3,
    FLOW_CTRL_MPU_I_CH_R3,
#endif /* FLOW_CONTROL */
  },
  /* Region 4 : SRAM1 & BKPSRAM2 area*/
  {
    {
      MPU_REGION_ENABLE,
      MPU_REGION_NUMBER4,
      SRAM_BASE,
      MPU_REGION_SIZE_32KB,
      0xC0,
      MPU_TEX_LEVEL0,
      MPU_REGION_PRIV_RW,
      MPU_INSTRUCTION_ACCESS_DISABLE,
      MPU_ACCESS_SHAREABLE,
      MPU_ACCESS_CACHEABLE,
      MPU_ACCESS_NOT_BUFFERABLE
    },
#ifdef FLOW_CONTROL
    FLOW_STEP_MPU_I_EN_R4,
    FLOW_CTRL_MPU_I_EN_R4,
    FLOW_STEP_MPU_I_CH_R4,
    FLOW_CTRL_MPU_I_CH_R4,
#endif /* FLOW_CONTROL */
  },
  /* Region 5 : Peripheral area */
  {
    {
      MPU_REGION_ENABLE,
      MPU_REGION_NUMBER5,
      PERIPH_BASE,
      MPU_REGION_SIZE_512MB,
      0,
      MPU_TEX_LEVEL0,
      MPU_REGION_PRIV_RW,
      MPU_INSTRUCTION_ACCESS_DISABLE,
      MPU_ACCESS_SHAREABLE,
      MPU_ACCESS_NOT_CACHEABLE,
      MPU_ACCESS_NOT_BUFFERABLE
    },
#ifdef FLOW_CONTROL
    FLOW_STEP_MPU_I_EN_R5,
    FLOW_CTRL_MPU_I_EN_R5,
    FLOW_STEP_MPU_I_CH_R5,
    FLOW_CTRL_MPU_I_CH_R5,
#endif /* FLOW_CONTROL */
  },
  /* Region 6 : System memory area */
  {
    {
      MPU_REGION_ENABLE,
      MPU_REGION_NUMBER6,
      0x1FFF6000UL,
      MPU_REGION_SIZE_32KB,
      0,
      MPU_TEX_LEVEL0,
      MPU_REGION_PRIV_RO,
      MPU_INSTRUCTION_ACCESS_ENABLE,
      MPU_ACCESS_NOT_SHAREABLE,
      MPU_ACCESS_CACHEABLE,
      MPU_ACCESS_NOT_BUFFERABLE
    },
#ifdef FLOW_CONTROL
    FLOW_STEP_MPU_I_EN_R6,
    FLOW_CTRL_MPU_I_EN_R6,
    FLOW_STEP_MPU_I_CH_R6,
    FLOW_CTRL_MPU_I_CH_R6,
#endif /* FLOW_CONTROL */
  },
  /* Region 7 : data area depends on configuration done during provisioning process */
  {
    {
#if (DATA_SIZE > 0)
      MPU_REGION_ENABLE,
#else
      MPU_REGION_DISABLE,
#endif /* (DATA_SIZE > 0) */
      MPU_REGION_NUMBER7,
      FLASH_BASE + FLASH_SIZE_DEFAULT - DATA_MAX_SIZE,
      MPU_REGION_SIZE_32KB,
#if (DATA_SIZE > 0)
      DATA_MPU_SUB_REG, /* enable sub region */
#else
      0,
#endif /* (DATA_SIZE > 0) */
      MPU_TEX_LEVEL0,
      MPU_REGION_PRIV_RW,
      MPU_INSTRUCTION_ACCESS_DISABLE,
      MPU_ACCESS_NOT_SHAREABLE,
      MPU_ACCESS_CACHEABLE,
      MPU_ACCESS_NOT_BUFFERABLE
    },
#ifdef FLOW_CONTROL
    FLOW_STEP_MPU_I_EN_R7,
    FLOW_CTRL_MPU_I_EN_R7,
    FLOW_STEP_MPU_I_CH_R7,
    FLOW_CTRL_MPU_I_CH_R7,
#endif /* FLOW_CONTROL */
  }
};

/* Private function prototypes -----------------------------------------------*/
static void mpu_init_cfg(void);
#ifdef OEMISB_MPU_PROTECTION
static int8_t mpu_cfg_check(MPU_Region_InitTypeDef *MPU_Init);
#endif /* OEMISB_MPU_PROTECTION */
static uint32_t sb_memcmp(const void *s1, const void *s2, size_t n);

/**
  * @brief  Apply the runtime security protections
  *
  * @param  None
  * @note   By default, the optimal security protections are applied
  * @retval None
  */
void LL_SECU_ApplyRunTimeProtections(void)
{
  /* Set MPU to forbid execution outside of immutable code  */
  mpu_init_cfg();
}

/**
  * @brief  Check if the Static security protections are configured.
  *         Those protections are not impacted by a Reset. They are set using the Option Bytes.
  *         When the device is locked, these protections cannot be changed anymore.
  * @param  None
  * @note   By default, the best security protections are applied to the different
  *         flash sections in order to maximize the security level for the specific MCU.
  * @retval None
  */
void LL_SECU_CheckStaticProtections(void)
{
  static FLASH_OBProgramInitTypeDef flash_option_bytes_bank = {0};
  uint32_t end;

  /* Get bank areaA OB  */
  flash_option_bytes_bank.WRPArea = OB_WRPAREA_ZONE_A;
  HAL_FLASHEx_OBGetConfig(&flash_option_bytes_bank);

  /* Check flash write protection */
  end = FLASH_PAGE_NB - (DATA_SIZE/FLASH_PAGE_SIZE) - 1;
  if ((flash_option_bytes_bank.WRPStartOffset > flash_option_bytes_bank.WRPEndOffset)
      || (flash_option_bytes_bank.WRPStartOffset != 0)
      || (flash_option_bytes_bank.WRPEndOffset != end))
  {
    Error_Handler();
  }
  /* Check secure user flash protection */
  end = FLASH_BOOT_AREA_SIZE / FLASH_PAGE_SIZE;
  if (end > flash_option_bytes_bank.SecSize)
  {
    Error_Handler();
  }

  /* Check Boot lock protection */
  if (flash_option_bytes_bank.BootEntryPoint != OB_BOOT_ENTRY_FORCED_FLASH)
  {
    Error_Handler();
  }

  /* Check RDL level : boot if current RDP level is greater or equal to selected RDP level */
  switch (OEMISB_OB_RDP_LEVEL_VALUE)
  {
    case OB_RDP_LEVEL_2:
      if (flash_option_bytes_bank.RDPLevel != OB_RDP_LEVEL_2)
      {
        Error_Handler();
      }
      break;

    case OB_RDP_LEVEL_1:
      if ((flash_option_bytes_bank.RDPLevel != OB_RDP_LEVEL_2) &&
          (flash_option_bytes_bank.RDPLevel != OB_RDP_LEVEL_1))
      {
        Error_Handler();
      }
      break;

    case OB_RDP_LEVEL_0:
      break;

    default:
      Error_Handler();
      break;
  }
}

/**
  * @brief  Check application integrity.
  * @param  None
  * @note   Compute hash on application area and compare with the stored one.
  * @retval None
  */
uint32_t LL_SECU_CheckApplicationIntegrity(void)
{
  uint32_t result = SB_FAIL;
  uint32_t result2 = SB_FAIL;
  uint32_t appli_size = 0;
  uint32_t offset = FLASH_BASE + FLASH_BOOT_AREA_SIZE;
  uint32_t end = FLASH_BASE + FLASH_SIZE - DATA_SIZE;
  uint8_t application_computed_sha256[32] = {0};

  memcpy((void *)&appli_size, (void *)(FLASH_BASE + FLASH_BOOT_AREA_SIZE - 32), 4);

  offset += appli_size;

  FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_HASH_CH_R0, FLOW_CTRL_HASH_CH_R0);

  /* Compute sha256 on the application area */

  mbedtls_sha256_ret((unsigned char const *)(FLASH_BASE + FLASH_BOOT_AREA_SIZE), appli_size, application_computed_sha256, 0);

  FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_HASH_CH_R1, FLOW_CTRL_HASH_CH_R1);

  /* Compare sha256 */
  if (sb_memcmp((uint8_t*)(FLASH_BASE + FLASH_BOOT_AREA_SIZE - 64), application_computed_sha256, 32) != SB_SUCCESS)
  {
    Error_Handler();
  }
  else
  {
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_HASH_CH_R2, FLOW_CTRL_HASH_CH_R2);

    result = SB_SUCCESS;
  }

  /* Compare sha256 a second time */
  if (sb_memcmp((uint8_t*)(FLASH_BASE + FLASH_BOOT_AREA_SIZE - 64), application_computed_sha256, 32) != SB_SUCCESS)
  {
    Error_Handler();
  }
  else
  {
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_HASH_CH_R3, FLOW_CTRL_HASH_CH_R3);

    result2 = SB_SUCCESS;
  }

  /* Check results */
  if (result != SB_SUCCESS || result2 != SB_SUCCESS)
  {
    Error_Handler();
  }
  else
  {
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_HASH_CH_R4, FLOW_CTRL_HASH_CH_R4);

    result2 = SB_SUCCESS;
  }

  /* Check the empty area */
  if (offset % 8)
  {
    uint32_t end = (((offset / 8) + 1) * 8);
    while (offset < end)
    {
      uint8_t data8 = *(uint8_t*)offset;
      if (data8 != 0xFF)
      {
        Error_Handler();
      }
      offset += sizeof(data8);
    }
  }

  while (offset < end)
  {
    uint64_t data64 = *(uint64_t*)offset;
    if (data64 != 0xFFFFFFFFFFFFFFFF)
    {
      Error_Handler();
    }
    offset += sizeof(data64);
  }

  FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_HASH_CH_R5, FLOW_CTRL_HASH_CH_R5);

  return SB_SUCCESS;
}


/**
  * @brief  MPU configuration
  * @param  None
  * @retval None
  */
static void mpu_init_cfg(void)
{
#ifdef OEMISB_MPU_PROTECTION
  int32_t i;

  /* configuration stage */
  if (uFlowStage == FLOW_STAGE_CFG)
  {
    /* configure MPU regions */
    for (i = 0; i < ARRAY_SIZE(mpu_region_boot_cfg); i++)
    {
      HAL_MPU_ConfigRegion((MPU_Region_InitTypeDef *)&mpu_region_boot_cfg[i].mpu_region_init);

      /* Execution stopped if flow control failed */
      FLOW_CONTROL_STEP(uFlowProtectValue, mpu_region_boot_cfg[i].flow_step_enable,
                                           mpu_region_boot_cfg[i].flow_ctrl_enable);
    }
    /* Enable MPU */
    HAL_MPU_Enable(MPU_HFNMI_PRIVDEF_NONE);
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_MPU_I_EN, FLOW_CTRL_MPU_I_EN);
  }
  /* verification stage */
  else
  {
    /* Check MPU regions */
    for (i = 0; i < ARRAY_SIZE(mpu_region_boot_cfg); i++)
    {
      if (mpu_cfg_check((MPU_Region_InitTypeDef *)&mpu_region_boot_cfg[i].mpu_region_init) != 0)
      {
        Error_Handler();
      }
      else
      {
        /* Execution stopped if flow control failed */
        FLOW_CONTROL_STEP(uFlowProtectValue, mpu_region_boot_cfg[i].flow_step_check,
                                             mpu_region_boot_cfg[i].flow_ctrl_check);
      }
    }

    /* Verify that MPU is enabled */
    if (MPU->CTRL != (MPU_HFNMI_PRIVDEF_NONE | MPU_CTRL_ENABLE_Msk))
    {
      Error_Handler();
    }
    else
    {
      FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_MPU_I_CH, FLOW_CTRL_MPU_I_CH);
    }
  }

#endif /* OEMISB_MPU_PROTECTION */
}

#ifdef OEMISB_MPU_PROTECTION
/**
  * @brief Compare with the current mpu configuration
  * @param MPU_Init Pointer to a MPU_Region_InitTypeDef structure that contains
  *                the configuration information to compare with.
  * @retval None
  */
static int8_t mpu_cfg_check(MPU_Region_InitTypeDef *MPU_Init)
{
  uint32_t base_cfg = 0;
  uint32_t limit_cfg = 0;

  /* Set the Region number */
  MPU->RNR = MPU_Init->Number;

  base_cfg = (MPU_Init->BaseAddress & MPU_RBAR_ADDR_Msk) | MPU_Init->Number;
  limit_cfg = ((uint32_t)MPU_Init->DisableExec             << MPU_RASR_XN_Pos)   |
              ((uint32_t)MPU_Init->AccessPermission        << MPU_RASR_AP_Pos)   |
              ((uint32_t)MPU_Init->TypeExtField            << MPU_RASR_TEX_Pos)  |
              ((uint32_t)MPU_Init->IsShareable             << MPU_RASR_S_Pos)    |
              ((uint32_t)MPU_Init->IsCacheable             << MPU_RASR_C_Pos)    |
              ((uint32_t)MPU_Init->IsBufferable            << MPU_RASR_B_Pos)    |
              ((uint32_t)MPU_Init->SubRegionDisable        << MPU_RASR_SRD_Pos)  |
              ((uint32_t)MPU_Init->Size                    << MPU_RASR_SIZE_Pos) |
              ((uint32_t)MPU_Init->Enable                  << MPU_RASR_ENABLE_Pos);

  if ((MPU->RBAR == base_cfg) && (MPU->RASR == limit_cfg))
  {
    return 0;
  }
  else
  {
    return -1;
  }
}
#endif /* OEMISB_MPU_PROTECTION */
/**
  * @brief  Compares the first n bytes of memory area s1 and memory area s2
  * @param  s1  Specify pointer to a block of memory
  * @param  s2  Specify pointer to a block of memory
  * @param  n  Specify the number of bytes to be compared
  * @retval fih_int
  */
static uint32_t sb_memcmp(const void *s1, const void *s2, size_t n)
{
  size_t i;
  uint32_t *s1_p = (uint32_t*) s1;
  uint32_t *s2_p = (uint32_t*) s2;
  uint32_t res = 0U;
  uint32_t ret = SB_FAIL;

  if (!(n % (sizeof(uint32_t))))
  {
    for (i = 0; i < (n / (sizeof(uint32_t))); i++)
    {
      res |= (s1_p[i] ^ s2_p[i]);
    }
    if (i == (n / (sizeof(uint32_t))) && (res == 0U))
    {
      ret = SB_SUCCESS;
    }
  }

  return ret;
}
