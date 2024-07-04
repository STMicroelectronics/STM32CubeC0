/**
  ******************************************************************************
  * @file    boot_hal.c
  * @author  MCD Application Team
  * @brief   This file contains hardware protections configuration and jump to application
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
#include "boot_cfg.h"
#include "boot.h"
#include "low_level_security.h"
#include "low_level_rng.h"
#include "boot_hal_flowcontrol.h"
#include "main.h"
/* exported variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(FLOW_CONTROL)
/* Global variable for Flow Control state */
volatile uint32_t uFlowProtectValue = FLOW_CTRL_INIT_VALUE;
#endif /* FLOW_CONTROL */

volatile uint32_t uFlowStage = FLOW_STAGE_CFG;

/* Private function prototypes -----------------------------------------------*/
static void jump_to_application(uint32_t exit_sticky_address, uint32_t dummy1, uint32_t dummy2, uint8_t mpu_region_number);

/**
  * @brief  Boot initialization.
  * @param  void
  * @retval void
  */
void BootInit(void)
{
  /* Start HW randomization */
  RNG_Init();

  RNG_Delay_Init();

  /* Apply Run time Protection */
  LL_SECU_ApplyRunTimeProtections();

  /* Check static protections */
  LL_SECU_CheckStaticProtections();

  /* Check Flow control state */
  FLOW_CONTROL_CHECK(uFlowProtectValue, FLOW_CTRL_STAGE_1);
  uFlowStage = FLOW_STAGE_CHK;

  /* Double protections apply / check to resist to basic fault injections */
  (void)RNG_Delay();

  /* Apply Run time Protection */
  LL_SECU_ApplyRunTimeProtections();

  /* Check static protections */
  LL_SECU_CheckStaticProtections();
}

/**
  * @brief  This function manage the jump to application.
  * @param  void
  * @retval void
  */
void BootQuit(void)
{
  /* Check Flow control state */
  FLOW_CONTROL_CHECK(uFlowProtectValue, FLOW_CTRL_STAGE_4);

  RNG_DeInit();

  /* Jump to application by enabling HDP and MPU region 1
     The address of the jump is selected by the HDP area */
  jump_to_application(0x1FFF6000UL, 0, 0, MPU_REGION_NUMBER1);   // 0x1FFF6000UL to replace by HAL MACRO if available

  /* Avoid compiler to pop registers after having changed MSP */
#if !defined(__ICCARM__)
  __builtin_unreachable();
#else
  while (1);
#endif /* defined(__ICCARM__) */
}

__attribute__((naked)) void jump_to_application(uint32_t exit_sticky_address, uint32_t dummy1, uint32_t dummy2, uint8_t mpu_region_number)
{
    __ASM volatile(
#if !defined(__ICCARM__)
        ".syntax unified                   \n"
#endif /* !defined(__ICCARM__) */
        "ldr     r1, [r0]                  \n"  /* assume R1 R2 are useless */
        "ldr     r2, [r0,#4]               \n"  /* R3 used for MPU region number */
        "mov     sp, r1                    \n"
        "bx      r2                        \n"
    );
}

/**
  * @brief  This function is executed in case of error occurrence.
  *         This function does not return.
  * @param  None
  * @retval None
  */
#ifdef OEMISB_MODE_DEV
void Error_Handler(void)
{
    while(1);
}
#else /* OEMISB_MODE_DEV */
#if defined(__ICCARM__)
__NO_RETURN void Error_Handler(void)
#else
void Error_Handler(void)
#endif
{
  /* It is customizeable */
  NVIC_SystemReset();
#if !defined(__ICCARM__)
  /* Avoid bx lr instruction (for fault injection) */
  __builtin_unreachable();
#endif /* defined(__ICCARM__) */
}
#endif /* OEMISB_MODE_DEV */

#if defined(__ARMCC_VERSION)
/* reimplement the function to reach Error Handler */
void __aeabi_assert(const char *expr, const char *file, int line)
{
  Error_Handler();
}
#endif  /* __ARMCC_VERSION */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    Error_Handler();
}
#endif /* USE_FULL_ASSERT */
