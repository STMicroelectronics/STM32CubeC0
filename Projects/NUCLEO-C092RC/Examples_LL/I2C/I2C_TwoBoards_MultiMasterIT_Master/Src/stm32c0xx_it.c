/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    I2C/I2C_TwoBoards_MultiMasterIT_Master/Src/stm32c0xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32c0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32C0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32c0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */

  /* USER CODE END EXTI4_15_IRQn 0 */
  if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_13) != RESET)
  {
    LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_13);
    /* USER CODE BEGIN LL_EXTI_LINE_13_FALLING */
    /* Call the associated callback */
    UserButton_Callback();
    /* USER CODE END LL_EXTI_LINE_13_FALLING */
  }
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break, update, trigger and commutation interrupts.
  */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 0 */
  /* Check whether update interrupt is pending */
  if (LL_TIM_IsActiveFlag_UPDATE(TIM1) == 1)
  {
    /* Clear the update interrupt flag */
    LL_TIM_ClearFlag_UPDATE(TIM1);
  }

  /* TIM1 update interrupt processing */
  TimerUpdate_Callback();
  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 0 */
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 1 */
}

/**
  * @brief This function handles I2C1 interrupt (combined with EXTI 23).
  */
void I2C1_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_IRQn 0 */
  /* Check NACK flag value in ISR register */
  if (LL_I2C_IsActiveFlag_NACK(I2C1))
  {
    /* End of Transfer */
    LL_I2C_ClearFlag_NACK(I2C1);
  }
  /* Check TXIS flag value in ISR register */
  else if (LL_I2C_IsActiveFlag_TXIS(I2C1))
  {
    /* Call function Master Ready to Transmit Callback */
    Master1_Ready_To_Transmit_Callback();
  }
  /* Check STOP flag value in ISR register */
  else if (LL_I2C_IsActiveFlag_STOP(I2C1))
  {
    /* Clear STOP flag value in ISR register */
    LL_I2C_ClearFlag_STOP(I2C1);

    /* Check TXE flag value in ISR register */
    if (!LL_I2C_IsActiveFlag_TXE(I2C1))
    {
      /* Flush the TXDR register */
      LL_I2C_ClearFlag_TXE(I2C1);
    }

    /* Call function Master Complete Callback */
    Master1_Complete_Callback();
  }
  /* Check TXE flag value in ISR register */
  else if (LL_I2C_IsActiveFlag_TXE(I2C1))
  {
    /* Do nothing */
    /* This Flag will be set by hardware when the TXDR register is empty */
    /* If needed, use LL_I2C_ClearFlag_TXE() interface to flush the TXDR register  */
  }
  else
  {
    /* Call Error function */
    Master1_Error_Callback();
  }
  /* USER CODE END I2C1_IRQn 0 */
  /* USER CODE BEGIN I2C1_IRQn 1 */

  /* USER CODE END I2C1_IRQn 1 */
}

/**
  * @brief This function handles I2C2 interrupt.
  */
void I2C2_IRQHandler(void)
{
  /* USER CODE BEGIN I2C2_IRQn 0 */
  /* Check NACK flag value in ISR register */
  if (LL_I2C_IsActiveFlag_NACK(I2C2))
  {
    /* End of Transfer */
    LL_I2C_ClearFlag_NACK(I2C2);
  }
  /* Check TXIS flag value in ISR register */
  else if (LL_I2C_IsActiveFlag_TXIS(I2C2))
  {
    /* Call function Master Ready to Transmit Callback */
    Master2_Ready_To_Transmit_Callback();
  }
  /* Check STOP flag value in ISR register */
  else if (LL_I2C_IsActiveFlag_STOP(I2C2))
  {
    /* Clear STOP flag value in ISR register */
    LL_I2C_ClearFlag_STOP(I2C2);

    /* Check TXE flag value in ISR register */
    if (!LL_I2C_IsActiveFlag_TXE(I2C2))
    {
      /* Flush the TXDR register */
      LL_I2C_ClearFlag_TXE(I2C2);
    }

    /* Call function Master Complete Callback */
    Master2_Complete_Callback();
  }
  /* Check TXE flag value in ISR register */
  else if (LL_I2C_IsActiveFlag_TXE(I2C2))
  {
    /* Do nothing */
    /* This Flag will be set by hardware when the TXDR register is empty */
    /* If needed, use LL_I2C_ClearFlag_TXE() interface to flush the TXDR register */
  }
  else
  {
    /* Call Error function */
    Master2_Error_Callback();
  }

  /* USER CODE END I2C2_IRQn 0 */
  /* USER CODE BEGIN I2C2_IRQn 1 */

  /* USER CODE END I2C2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
