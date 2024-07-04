/**
  ******************************************************************************
  * @file    ROT/OEMiSB_Boot/Inc/entropy.h
  * @author  MCD Application Team
  * @brief   This file contains header for entropy.c module
  * @note    This solution should be used only if the target device doesn’t provide
  *          a TRNG peripheral, and its usage is discouraged for critical security
  *          or cryptographic purposes.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ENTROPY_H
#define ENTROPY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htimx;

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Entropy_Gather(uint32_t nbBits, __IO uint8_t *pEntropy);

#ifdef __cplusplus
}
#endif

#endif /* ENTROPY_H */
