/**
  ******************************************************************************
  * @file    boot_hal_flowcontrol.h
  * @author  MCD Application Team
  * @brief   Header for flow control in boot_hal.c module
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
#ifndef BOOT_HAL_FLOWCONTROL_H
#define BOOT_HAL_FLOWCONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "boot_cfg.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
  * @brief  Flow Control : Initial value
  */
#define FLOW_STAGE_CFG              0xfffffe00U
#define FLOW_STAGE_CHK              0xffffe01eU

/**
  * @brief  Flow Control : Initial value
  */
#define FLOW_CTRL_INIT_VALUE        0x00005776U        /*!< Init value definition */

/**
  * @brief  Flow Control : Steps definition
  */
#ifdef OEMISB_MPU_PROTECTION
#define FLOW_STEP_MPU_I_EN_R0       0x00006787U        /*!< Step MPU Region 0 Init enable value */
#define FLOW_STEP_MPU_I_EN_R1       0x00007999U        /*!< Step MPU Region 1 Init enable value */
#define FLOW_STEP_MPU_I_EN_R2       0x0000aab5U        /*!< Step MPU Region 2 Init enable value */
#define FLOW_STEP_MPU_I_EN_R3       0x0000cccdU        /*!< Step MPU Region 3 Init enable value */
#define FLOW_STEP_MPU_I_EN_R4       0x0000d2d3U        /*!< Step MPU Region 4 Init enable value */
#define FLOW_STEP_MPU_I_EN_R5       0x0000e3dcU        /*!< Step MPU Region 5 Init enable value */
#define FLOW_STEP_MPU_I_EN_R6       0x00043d7aU        /*!< Step MPU Region 6 Init enable value */
#define FLOW_STEP_MPU_I_EN_R7       0x0001cf0eU        /*!< Step MPU Region 7 Init enable value */
#define FLOW_STEP_MPU_I_EN          0x000673eaU        /*!< Step MPU Secure Init enable value */
#else /* OEMISB_MPU_PROTECTION */
#define FLOW_STEP_MPU_I_EN_R0       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_EN_R1       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_EN_R2       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_EN_R3       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_EN_R4       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_EN_R5       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_EN_R6       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_EN_R7       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_EN          0x00000000U        /*!< No effect on control flow */
#endif /* OEMISB_MPU_PROTECTION */

#ifdef OEMISB_MPU_PROTECTION
#define FLOW_STEP_MPU_I_CH_R0       0x00067f4dU        /*!< Step MPU Region 0 Init check value */
#define FLOW_STEP_MPU_I_CH_R1       0x0006b381U        /*!< Step MPU Region 1 Init check value */
#define FLOW_STEP_MPU_I_CH_R2       0x0006bf26U        /*!< Step MPU Region 2 Init check value */
#define FLOW_STEP_MPU_I_CH_R3       0x0001cef0U        /*!< Step MPU Region 3 Init check value */
#define FLOW_STEP_MPU_I_CH_R4       0x000a6e24U        /*!< Step MPU Region 4 Init check value */
#define FLOW_STEP_MPU_I_CH_R5       0x0001d0eeU        /*!< Step MPU Region 5 Init check value */
#define FLOW_STEP_MPU_I_CH_R6       0x000569ceU        /*!< Step MPU Region 6 Init check value */
#define FLOW_STEP_MPU_I_CH_R7       0x000577d0U        /*!< Step MPU Region 7 Init check value */
#define FLOW_STEP_MPU_I_CH          0x0001e1e1U        /*!< Step MPU Init check value */
#else /* OEMISB_MPU_PROTECTION */
#define FLOW_STEP_MPU_I_CH_R0       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_CH_R1       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_CH_R2       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_CH_R3       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_CH_R4       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_CH_R5       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_CH_R6       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_CH_R7       0x00000000U        /*!< No effect on control flow */
#define FLOW_STEP_MPU_I_CH          0x00000000U        /*!< No effect on control flow */
#endif /* OEMISB_MPU_PROTECTION */

#define FLOW_STEP_HASH_CH_R0        0x00023bd7U         /*!< Step HASH Region 0 check value */
#define FLOW_STEP_HASH_CH_R1        0x00025dafU         /*!< Step HASH Region 1 check value*/
#define FLOW_STEP_HASH_CH_R2        0x00029cf6U         /*!< Step HASH Region 2 check value */
#define FLOW_STEP_HASH_CH_R3        0x00012cd3U         /*!< Step HASH Region 3 check value */
#define FLOW_STEP_HASH_CH_R4        0x0000b4abU         /*!< Step HASH Region 4 check value */
#define FLOW_STEP_HASH_CH_R5        0x0000fdc2U         /*!< Step HASH Region 5 check value */

/**
  * @brief  Flow Control : Control values runtime protections
  */
/* Flow control Stage 1 */
#define FLOW_CTRL_MPU_I_EN_R0       (FLOW_CTRL_INIT_VALUE  ^  FLOW_STEP_MPU_I_EN_R0)
#define FLOW_CTRL_MPU_I_EN_R1       (FLOW_CTRL_MPU_I_EN_R0 ^  FLOW_STEP_MPU_I_EN_R1)
#define FLOW_CTRL_MPU_I_EN_R2       (FLOW_CTRL_MPU_I_EN_R1 ^  FLOW_STEP_MPU_I_EN_R2)
#define FLOW_CTRL_MPU_I_EN_R3       (FLOW_CTRL_MPU_I_EN_R2 ^  FLOW_STEP_MPU_I_EN_R3)
#define FLOW_CTRL_MPU_I_EN_R4       (FLOW_CTRL_MPU_I_EN_R3 ^  FLOW_STEP_MPU_I_EN_R4)
#define FLOW_CTRL_MPU_I_EN_R5       (FLOW_CTRL_MPU_I_EN_R4 ^  FLOW_STEP_MPU_I_EN_R5)
#define FLOW_CTRL_MPU_I_EN_R6       (FLOW_CTRL_MPU_I_EN_R5 ^  FLOW_STEP_MPU_I_EN_R6)
#define FLOW_CTRL_MPU_I_EN_R7       (FLOW_CTRL_MPU_I_EN_R6 ^  FLOW_STEP_MPU_I_EN_R7)
#define FLOW_CTRL_MPU_I_EN          (FLOW_CTRL_MPU_I_EN_R7 ^  FLOW_STEP_MPU_I_EN)

#define FLOW_CTRL_STAGE_1            FLOW_CTRL_MPU_I_EN

/* Flow control Stage 2 */
#define FLOW_CTRL_MPU_I_CH_R0       (FLOW_CTRL_STAGE_1     ^  FLOW_STEP_MPU_I_CH_R0)
#define FLOW_CTRL_MPU_I_CH_R1       (FLOW_CTRL_MPU_I_CH_R0 ^  FLOW_STEP_MPU_I_CH_R1)
#define FLOW_CTRL_MPU_I_CH_R2       (FLOW_CTRL_MPU_I_CH_R1 ^  FLOW_STEP_MPU_I_CH_R2)
#define FLOW_CTRL_MPU_I_CH_R3       (FLOW_CTRL_MPU_I_CH_R2 ^  FLOW_STEP_MPU_I_CH_R3)
#define FLOW_CTRL_MPU_I_CH_R4       (FLOW_CTRL_MPU_I_CH_R3 ^  FLOW_STEP_MPU_I_CH_R4)
#define FLOW_CTRL_MPU_I_CH_R5       (FLOW_CTRL_MPU_I_CH_R4 ^  FLOW_STEP_MPU_I_CH_R5)
#define FLOW_CTRL_MPU_I_CH_R6       (FLOW_CTRL_MPU_I_CH_R5 ^  FLOW_STEP_MPU_I_CH_R6)
#define FLOW_CTRL_MPU_I_CH_R7       (FLOW_CTRL_MPU_I_CH_R6 ^  FLOW_STEP_MPU_I_CH_R7)
#define FLOW_CTRL_MPU_I_CH          (FLOW_CTRL_MPU_I_CH_R7 ^  FLOW_STEP_MPU_I_CH)

#define FLOW_CTRL_STAGE_2            FLOW_CTRL_MPU_I_CH

#define FLOW_CTRL_HASH_CH_R0        (FLOW_CTRL_STAGE_2 ^      FLOW_STEP_HASH_CH_R0)
#define FLOW_CTRL_HASH_CH_R1        (FLOW_CTRL_HASH_CH_R0 ^   FLOW_STEP_HASH_CH_R1)
#define FLOW_CTRL_HASH_CH_R2        (FLOW_CTRL_HASH_CH_R1 ^   FLOW_STEP_HASH_CH_R2)
#define FLOW_CTRL_HASH_CH_R3        (FLOW_CTRL_HASH_CH_R2 ^   FLOW_STEP_HASH_CH_R3)
#define FLOW_CTRL_HASH_CH_R4        (FLOW_CTRL_HASH_CH_R3 ^   FLOW_STEP_HASH_CH_R4)
#define FLOW_CTRL_HASH_CH_R5        (FLOW_CTRL_HASH_CH_R4 ^   FLOW_STEP_HASH_CH_R5)

#define FLOW_CTRL_STAGE_3            FLOW_CTRL_HASH_CH_R5

#define FLOW_CTRL_STAGE_4            FLOW_CTRL_STAGE_3

/* External variables --------------------------------------------------------*/
/**
  *  Flow control protection values
  *  Flow control stage
  */
extern volatile uint32_t uFlowProtectValue;
extern volatile uint32_t uFlowStage;

/* Exported macros -----------------------------------------------------------*/
/** Control with STEP operation :
  * (uFlowValue XOR STEP_VALUE) should be equal to CTRL_VALUE ==> execution stopped if failed !
  */
#if defined(FLOW_CONTROL)
#define FLOW_CONTROL_STEP(C,B,A) \
  do{ \
    (C) ^= (B);\
    if ((C) != (A))\
    { \
      Error_Handler();\
    } \
  }while(0)
#else
#define FLOW_CONTROL_STEP(C,B,A) ((void)0)
#endif

/** Control without STEP operation :
  * uFlowValue should be equal to CTRL_VALUE ==> execution stopped if failed !
  */
#if defined(FLOW_CONTROL)
#define FLOW_CONTROL_CHECK(B,A) \
  do{ \
    if ((B) != (A))\
    { \
      Error_Handler();\
    } \
  }while(0)
#else
#define FLOW_CONTROL_CHECK(B,A) ((void)0)
#endif

/** Control flow initialization
  */
#if defined(FLOW_CONTROL)
#define FLOW_CONTROL_INIT(B,A) \
  do{ \
    (B) = (A);\
  }while(0)
#else
#define FLOW_CONTROL_INIT(B,A) ((void)0)
#endif

/** STEP update only :
  * (uFlowValue XOR STEP_VALUE)
  */
#if defined(FLOW_CONTROL)
#define FLOW_STEP(B,A) \
  do{ \
    (B) ^= (A);\
  }while(0)
#else
#define FLOW_STEP(B,A) ((void)0)
#endif

/* Exported functions ------------------------------------------------------- */

/** @defgroup BOOT_FLOWCONTROL_Exported_Functions Exported Functions
  * @{
  */


/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* BOOT_HAL_FLOWCONTROL_H */
