/**
  ******************************************************************************
  * @file    interfaces_conf.h
  * @author  MCD Application Team
  * @brief   Contains Interfaces configuration
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
#ifndef INTERFACES_CONF_H
#define INTERFACES_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_ll_usart.h"
#include "stm32c0xx_ll_i2c.h"

#define MEMORIES_SUPPORTED                7U

/* ------------------------- Definitions for USART -------------------------- */
#define USARTx                            USART1
#define USARTx_CLK_ENABLE()               __HAL_RCC_USART1_CLK_ENABLE()
#define USARTx_CLK_DISABLE()              __HAL_RCC_USART1_CLK_DISABLE()
#define USARTx_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_DeInit()                   LL_USART_DeInit(USARTx)

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                     GPIO_PIN_9
#define USARTx_TX_GPIO_PORT               GPIOA
#define USARTx_RX_PIN                     GPIO_PIN_10
#define USARTx_RX_GPIO_PORT               GPIOA
#define USARTx_ALTERNATE                  GPIO_AF1_USART1

/* -------------------------- Definitions for I2C --------------------------- */
#define I2Cx                              I2C1
#define I2Cx_CLK_ENABLE()                 __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_CLK_DISABLE()                __HAL_RCC_I2C1_CLK_DISABLE()
#define I2Cx_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_DeInit()                     LL_I2C_DeInit(I2Cx)

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                      GPIO_PIN_6
#define I2Cx_SCL_PIN_PORT                 GPIOB
#define I2Cx_SDA_PIN                      GPIO_PIN_7
#define I2Cx_SDA_PIN_PORT                 GPIOB
#define I2Cx_ALTERNATE                    GPIO_AF6_I2C1
#define I2C_ADDRESS                       (0x00000063U << 0x01U)
#define I2C_TIMING                        0x00000004U
#define OPENBL_I2C_TIMEOUT                0xFFFFF000U

#endif /* INTERFACES_CONF_H */
