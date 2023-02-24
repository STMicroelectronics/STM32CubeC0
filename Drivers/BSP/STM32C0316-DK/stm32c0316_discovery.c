/**
******************************************************************************
* @file    stm32c0316_discovery.c
* @author  MCD Application Team
* @brief   This file provides a set of firmware functions to manage Leds
*          and joystick of STM32C0316-DK board (MB1716)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32c0316_discovery.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32C0316-DK
  * @brief This file provides firmware functions to manage Leds and joystick
  *        available on STM32C0316-DK board from STMicroelectronics.
  * @{
  */

/** @addtogroup STM32C0316_DK_LOW_LEVEL
  * @{
  */

/** @defgroup STM32C0316_DK_LOW_LEVEL_Private_TypesDefinitions LOW LEVEL Private Types Definitions
  * @{
  */
typedef void (* BSP_EXTI_LineCallback)(void);
/**
  * @}
  */

/** @defgroup STM32C0316_DK_LOW_LEVEL_Private_FunctionPrototypes  LOW LEVEL Private Function Prototypes
  * @{
  */
static void BUTTON_USER_EXTI_Callback(void);
#if (USE_BSP_COM_FEATURE > 0)
static void USART1_MspInit(UART_HandleTypeDef *huart);
static void USART1_MspDeInit(UART_HandleTypeDef *huart);
#endif /*USE_BSP_COM_FEATURE */

/**
  * @}
  */
/** @defgroup STM32C0316_DK_LOW_LEVEL_Exported_Variables LOW LEVEL Exported Variables
  * @{
  */
EXTI_HandleTypeDef hpb_exti[BUTTONn];
#if (USE_BSP_COM_FEATURE > 0)
UART_HandleTypeDef hcom_uart[COM_NBR];
USART_TypeDef *COM_UART[COM_NBR]   = {COM1_UART};
#endif /* USE_BSP_COM_FEATURE */
/**
  * @}
  */

/** @defgroup STM32C0316_DK_LOW_LEVEL_Private_Variables LOW LEVEL Private Variables
  * @{
  */
static GPIO_TypeDef *LED_PORT[LEDn] = {LED1_GPIO_PORT};
static const uint32_t LED_PIN[LEDn] = {LED1_PIN};
static GPIO_TypeDef *BUTTON_PORT[BUTTONn] = {BUTTON_USER_GPIO_PORT};
static const uint16_t BUTTON_PIN[BUTTONn] = {BUTTON_USER_PIN};
static const IRQn_Type BUTTON_IRQn[BUTTONn] = {BUTTON_USER_EXTI_IRQn};

#if (USE_COM_LOG > 0)
static COM_TypeDef COM_ActiveLogPort = COM1;
#endif /* USE_COM_LOG */

#if (USE_BSP_COM_FEATURE > 0)
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
static uint32_t IsComMspCbValid[COM_NBR] = {0};
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
#endif /* USE_BSP_COM_FEATURE */

#if (USE_BSP_JOY_FEATURE > 0)
  #if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
     static uint32_t IsJoyMspCbValid[JOY_NBR] = {0};
  #endif
static ADC_HandleTypeDef hjoy_adc;
static void ADC_MspInit(ADC_HandleTypeDef *hadc);
static void ADC_MspDeInit(ADC_HandleTypeDef *hadc);
__weak HAL_StatusTypeDef MX_ADC_Init(ADC_HandleTypeDef *hadc);
#endif
/**
  * @}
  */

/**
  * @}
  */
/** @defgroup STM32C0316_DK_Exported_Functions Exported Functions
  * @{
  */
/**
  * @brief  This method returns the STM32C0316_DK BSP Driver revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
int32_t BSP_GetVersion(void)
{
  return (int32_t)STM32C0316_DK_BSP_VERSION;
}

/**
  * @brief  This method returns the board name
  * @retval pointer to the board name string
  */
const uint8_t *BSP_GetBoardName(void)
{
  return (uint8_t *)STM32C0316_DK_BSP_BOARD_NAME;
}

/**
  * @brief  This method returns the board ID
  * @retval pointer to the board name string
  */
const uint8_t *BSP_GetBoardID(void)
{
  return (uint8_t *)STM32C0316_DK_BSP_BOARD_ID;
}

/**
  * @brief  Configures LED on GPIO.
  * @param  Led LED to be configured.
  *          This parameter can be one of the following values:
  *            @arg  LED1
  * @retval BSP status
  */
int32_t BSP_LED_Init(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;
  GPIO_InitTypeDef  gpio_init_structure;

  if(Led != LED1)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
      /* Enable the LED1 GPIO clock */
      LED1_GPIO_CLK_ENABLE();

    /* Configure the GPIO_LED pin */
    gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_structure.Pull = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_structure.Pin = LED_PIN [Led];
    HAL_GPIO_Init(LED_PORT[Led], &gpio_init_structure);
    HAL_GPIO_WritePin(LED_PORT [Led], (uint16_t)LED_PIN[Led], GPIO_PIN_SET);
  }

  return ret;
}

/**
  * @brief  DeInit LEDs.
  * @param  Led LED to be configured.
  *          This parameter can be one of the following values:
  *            @arg  LED1
  * @retval BSP status
  */
int32_t BSP_LED_DeInit(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;
  GPIO_InitTypeDef  gpio_init_structure;

  if(Led != LED1)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Configure the GPIO_LED pin */
    gpio_init_structure.Pin = LED_PIN [Led];
    HAL_GPIO_WritePin(LED_PORT[Led], (uint16_t)LED_PIN[Led], GPIO_PIN_RESET);
    HAL_GPIO_DeInit(LED_PORT[Led], gpio_init_structure.Pin);
  }

  return ret;
}

/**
  * @brief  Turns selected LED On.
  * @param  Led LED to be set on
  *          This parameter can be one of the following values:
  *            @arg  LED1
  * @retval BSP status
  */
int32_t BSP_LED_On(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;

  if(Led != LED1)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    HAL_GPIO_WritePin(LED_PORT [Led], (uint16_t)LED_PIN [Led], GPIO_PIN_RESET);
  }

  return ret;
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led LED to be set off
  *          This parameter can be one of the following values:
  *            @arg  LED1
  * @retval BSP status
  */
int32_t BSP_LED_Off(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;

  if(Led != LED1)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    HAL_GPIO_WritePin(LED_PORT [Led], (uint16_t)LED_PIN [Led], GPIO_PIN_SET);
  }

  return ret;
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led LED to be toggled
  *          This parameter can be one of the following values:
  *            @arg  LED1
  * @retval BSP status
  */
int32_t BSP_LED_Toggle(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;

  if(Led != LED1)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    HAL_GPIO_TogglePin(LED_PORT[Led], (uint16_t)LED_PIN[Led]);
  }

  return ret;
}

/**
  * @brief  Get the selected LED state.
  * @param  Led LED to be get its state
  *          This parameter can be one of the following values:
  *            @arg  LED1
  * @retval LED status
  */
int32_t BSP_LED_GetState(Led_TypeDef Led)
{
  int32_t ret;

  if(Led != LED1)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    ret = (int32_t)HAL_GPIO_ReadPin (LED_PORT [Led], (uint16_t)LED_PIN [Led]);
  }

  return ret;
}

/**
  * @brief  Configures button GPIO and EXTI Line.
  * @param  Button: Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_USER: User Push Button
  * @param  ButtonMode Button mode
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_MODE_GPIO: Button will be used as simple IO
  *            @arg  BUTTON_MODE_EXTI: Button will be connected to EXTI line
  *                                    with interrupt generation capability
  * @retval BSP status
  */
int32_t BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  int32_t ret = BSP_ERROR_NONE;
  GPIO_InitTypeDef gpio_init_structure;
  static BSP_EXTI_LineCallback ButtonCallback[BUTTONn] = {BUTTON_USER_EXTI_Callback,};
  static uint32_t  BSP_BUTTON_PRIO [BUTTONn] = {BSP_BUTTON_USER_IT_PRIORITY,};
  static const uint32_t BUTTON_EXTI_LINE[BUTTONn] = {BUTTON_USER_EXTI_LINE,};

  if (Button != BUTTON_USER)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Enable the BUTTON clock*/
    BUTTON_USER_GPIO_CLK_ENABLE();

    gpio_init_structure.Pin = BUTTON_PIN [Button];
    gpio_init_structure.Pull = GPIO_PULLDOWN;
    gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;

    if (ButtonMode == BUTTON_MODE_GPIO)
    {
      /* Configure Button pin as input */
      gpio_init_structure.Mode = GPIO_MODE_INPUT;
      HAL_GPIO_Init(BUTTON_PORT [Button], &gpio_init_structure);
    }
    else /* (ButtonMode == BUTTON_MODE_EXTI) */
    {
      /* Configure Button pin as input with External interrupt */
      gpio_init_structure.Mode = GPIO_MODE_IT_FALLING;

      HAL_GPIO_Init(BUTTON_PORT[Button], &gpio_init_structure);

      (void)HAL_EXTI_GetHandle(&hpb_exti[Button], BUTTON_EXTI_LINE[Button]);
      (void)HAL_EXTI_RegisterCallback(&hpb_exti[Button],  HAL_EXTI_COMMON_CB_ID, ButtonCallback[Button]);

      /* Enable and set Button EXTI Interrupt to the lowest priority */
      HAL_NVIC_SetPriority((BUTTON_IRQn[Button]), BSP_BUTTON_PRIO[Button], 0x00);
      HAL_NVIC_EnableIRQ((BUTTON_IRQn[Button]));
    }
  }

  return ret;
}

/**
  * @brief  Push Button DeInit.
  * @param  Button Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_USER: User Push Button
  * @note PB DeInit does not disable the GPIO clock
  * @retval BSP status
  */
int32_t BSP_PB_DeInit(Button_TypeDef Button)
{
  int32_t ret = BSP_ERROR_NONE;
  GPIO_InitTypeDef gpio_init_structure;

  if (Button != BUTTON_USER)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    gpio_init_structure.Pin = BUTTON_PIN[Button];
    HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
    HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);
  }

  return ret;
}

/**
  * @brief  Returns the selected button state.
  * @param  Button Button to be checked
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_USER: User Push Button
  * @retval The Button GPIO pin value
  */
int32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return (int32_t)HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  This function handles Push-Button interrupt requests.
  * @param  Button Specifies the pin connected EXTI line
  * @retval None
  */
void BSP_PB_IRQHandler(Button_TypeDef Button)
{
  HAL_EXTI_IRQHandler(&hpb_exti[Button]);
}

/**
  * @brief  BSP Push Button callback
  * @param  Button Specifies the pin connected EXTI line
  * @retval None.
  */
__weak void BSP_PB_Callback(Button_TypeDef Button)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Button);
  /* This function should be implemented by the user application.
     It is called into this driver when an event on Button is triggered. */
}

#if (USE_BSP_COM_FEATURE > 0)
/**
  * @brief  Configures COM port.
  * @param  COM port to be configured.
  *          This parameter should be COM1
  * @param  COM_Init Pointer to a UART_HandleTypeDef structure that contains the
  *                configuration information for the specified LPUART peripheral.
  * @retval BSP status
  */
int32_t BSP_COM_Init(COM_TypeDef COM, COM_InitTypeDef *COM_Init)
{
  int32_t ret = BSP_ERROR_NONE;

  if (COM >= COM_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Set the COM Instance */
    hcom_uart[COM].Instance = COM_UART[COM];

    /* Init the UART Msp */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)
    USART1_MspInit(&hcom_uart[COM]);
#else
    if (IsComMspCbValid[COM] == 0U)
    {
      if (BSP_COM_RegisterDefaultMspCallbacks(COM) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

    if (MX_USART1_Init(&hcom_uart[COM], COM_Init) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  DeInit COM port.
  * @param  COM COM port to be configured.
  *          This parameter can be (COM1)
  * @retval BSP status
  */
int32_t BSP_COM_DeInit(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if (COM >= COM_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* UART configuration */
    hcom_uart[COM].Instance = COM_UART[COM];

#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)
    USART1_MspDeInit(&hcom_uart[COM]);
#endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 0) */

    if (HAL_UART_DeInit(&hcom_uart[COM]) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  Configures COM port.
  * @param  huart UART handle
  * @param  COM_Init Pointer to a UART_HandleTypeDef structure that contains the
  *                  configuration information for the specified LPUART peripheral.
  * @retval HAL error code
  */
__weak HAL_StatusTypeDef MX_USART1_Init(UART_HandleTypeDef *huart, MX_UART_InitTypeDef *COM_Init)
{
  /* UART configuration */
  huart->Init.BaudRate     = COM_Init->BaudRate;
  huart->Init.Mode         = UART_MODE_TX_RX;
  huart->Init.Parity       = (uint32_t)COM_Init->Parity;
  huart->Init.WordLength   = (uint32_t)COM_Init->WordLength;
  huart->Init.StopBits     = (uint32_t)COM_Init->StopBits;
  huart->Init.HwFlowCtl    = (uint32_t)COM_Init->HwFlowCtl;
  huart->Init.OverSampling = UART_OVERSAMPLING_8;

  return HAL_UART_Init(huart);
}

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
/**
  * @brief Register Default COM Msp Callbacks
  * @param  COM COM port to be configured.
  * @retval BSP status
  */
int32_t BSP_COM_RegisterDefaultMspCallbacks(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if (COM >= COM_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_UART_RESET_HANDLE_STATE(&hcom_uart[COM]);

    /* Register default MspInit/MspDeInit Callback */
    if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, USART1_MspInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, USART1_MspDeInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsComMspCbValid[COM] = 1U;
    }
  }

  /* BSP status */
  return ret;
}

/**
  * @brief  Register COM Msp Callback registering
  * @param  COM port to be configured.
  * @param  Callbacks pointer to COM MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_COM_RegisterMspCallbacks(COM_TypeDef COM, BSP_COM_Cb_t *Callback)
{
  int32_t ret = BSP_ERROR_NONE;

  if (COM >= COM_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_UART_RESET_HANDLE_STATE(&hcom_uart[COM]);

    /* Register MspInit/MspDeInit Callbacks */
    if (HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, Callback->pMspInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if (HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, Callback->pMspDeInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsComMspCbValid[COM] = 1U;
    }
  }

  /* BSP status */
  return ret;
}
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

#if (USE_COM_LOG > 0)
/**
  * @brief  Select the active COM port.
  * @param  COM port to be activated.
  * @retval BSP status
  */
int32_t BSP_COM_SelectLogPort(COM_TypeDef COM)
{
  if (COM_ActiveLogPort != COM)
  {
    COM_ActiveLogPort = COM;
  }
  return BSP_ERROR_NONE;
}

/**
  * @brief  Redirect console output to COM
  */
#ifdef __GNUC__
int __io_putchar(int ch)
{
  HAL_UART_Transmit(&hcom_uart [COM_ActiveLogPort], (uint8_t *) &ch, 1, COM_POLL_TIMEOUT);
  return ch;
}
#else
size_t __write(int handle, const unsigned char * buffer, size_t size)
{
  HAL_UART_Transmit(&hcom_uart [COM_ActiveLogPort], (uint8_t *) buffer, size, COM_POLL_TIMEOUT);
  return size;
}
#endif /* __GNUC__ */
#endif /* USE_COM_LOG */
#endif /* USE_BSP_COM_FEATURE */

#if (USE_BSP_JOY_FEATURE > 0)
/**
  * @brief  Configures joystick GPIO and EXTI modes.
  * @param  JOY Joystick to be initialized
  * @param  JoyMode Button mode.
  *          This parameter can be one of the following values:
  *            @arg  JOY_MODE_GPIO: Joystick pins will be used as simple IOs
  *            @arg  JOY_MODE_EXTI: Joystick pins will be connected to EXTI line
  *                                 with interrupt generation capability
  * @param  JoyPins joystick pins to be initialized
  * @retval BSP status
  */
int32_t BSP_JOY_Init(JOY_TypeDef JOY, JOYMode_TypeDef JoyMode, JOYPin_TypeDef JoyPins)
{
  int32_t ret = BSP_ERROR_NONE;
  
   UNUSED(JoyMode); 
   UNUSED(JoyPins);
   
  if(JOY >= JOYn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 0)
    /* Init the ADC Msp */
    ADC_MspInit(&hjoy_adc);
#else
    if(IsJoyMspCbValid[JOY] == 0U)
    {
      if(BSP_JOY_RegisterDefaultMspCallbacks(JOY) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif
    if(MX_ADC_Init(&hjoy_adc) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  De-Initialize the Potentiometer.
  * @param  JOY  Potentiometer to be activated.
  * @param  JoyPins joystick pins to be de-initialized  
  * @retval BSP status
  */
int32_t BSP_JOY_DeInit(JOY_TypeDef JOY, JOYPin_TypeDef JoyPins)
{
  int32_t ret = BSP_ERROR_NONE;

   UNUSED(JoyPins);
   
  if(JOY >= JOYn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* ADC configuration */
    hjoy_adc.Instance = JOY1_ADC;

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 0)
    ADC_MspDeInit(&hjoy_adc);

#endif /* (USE_HAL_ADC_REGISTER_CALLBACKS == 0) */

    if(HAL_ADC_DeInit(&hjoy_adc) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  Returns the current joystick status.
  * @param  JOY Joystick instance
  * @retval BSP error code if value is negative or one of the following values:
  *            @arg  JOY_NONE  if voltage level is not one of below values 
  *            @arg  JOY_SEL   if voltage level is around  0 V / 0
  *            @arg  JOY_DOWN  if voltage level is between 1.32 V / 1638
  *            @arg  JOY_LEFT  if voltage level is between 0.67 V / 831
  *            @arg  JOY_RIGHT if voltage level is between 2.65 V / 3288 
  *            @arg  JOY_UP    if voltage level is between 2.01 V / 2494
  */
int32_t BSP_JOY_GetState(JOY_TypeDef JOY)
{
  int32_t ret = BSP_ERROR_NONE;
  uint16_t key_converted_value = 0;
  uint32_t key_pressed;
  
  if(JOY >= JOYn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
 /* Start the conversion process */
  HAL_ADC_Start(&hjoy_adc);
  
  /* Wait for the end of conversion */
  if (HAL_ADC_PollForConversion(&hjoy_adc, JOY_ADC_POLL_TIMEOUT) != HAL_TIMEOUT)
  {
    /* Get the converted value of regular channel */
    key_converted_value = HAL_ADC_GetValue(&hjoy_adc);
  }
  if((key_converted_value > 2370) && (key_converted_value < 2618))
  {
    key_pressed = JOY_UP;
  }
  else if((key_converted_value > 3000) && (key_converted_value < 3312))
  {
    key_pressed = JOY_RIGHT;
  }
  else if(key_converted_value < 10)
  {
    key_pressed = JOY_SEL;
  }
  else if((key_converted_value > 1514) && (key_converted_value < 1762))
  {
    key_pressed = JOY_DOWN;
  }
  else if((key_converted_value > 709) && (key_converted_value < 955))
  {
    key_pressed = JOY_LEFT;
  }
  else
  {
    key_pressed = JOY_NONE;
  }
  /* Return Code Joystick key pressed */
   ret = (int32_t)key_pressed;
  }	  

  return (int32_t)ret;
}

/**
  * @brief  Configures ADC peripheral
  * @param  hadc ADC handle
  * @retval HAL error code
  */
__weak HAL_StatusTypeDef MX_ADC_Init(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef ret = HAL_OK;
  ADC_ChannelConfTypeDef sConfig;

  /* ADC configuration */
  hadc->Instance                   = JOY1_ADC;
  hadc->Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;   /* ADC clock of STM32C0 must not exceed 14MHz        */
  hadc->Init.Resolution            = ADC_RESOLUTION_12B;
  hadc->Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  hadc->Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD; /* Sequencer will convert the number of channels 
	                                     configured below, successively from the lowest to the highest channel number */
  hadc->Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
  hadc->Init.LowPowerAutoWait      = DISABLE;
  hadc->Init.LowPowerAutoPowerOff  = DISABLE;
  hadc->Init.ContinuousConvMode    = DISABLE;                    /* Continuous mode disabled to have only 1 
	                                                                conversion at each conversion trig                */
  hadc->Init.NbrOfConversion       = 1;
  hadc->Init.DiscontinuousConvMode = DISABLE;                    /* Parameter discarded because sequencer is disabled */
  hadc->Init.ExternalTrigConv      = ADC_SOFTWARE_START;         /* Software start to trig the 1st conversion 
	                                                                          manually, without external event        */
  hadc->Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE; /* Parameter discarded because trig by 
	                                                                          software start                          */
  hadc->Init.DMAContinuousRequests = DISABLE;
  hadc->Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;
  hadc->Init.SamplingTimeCommon1   = ADC_SAMPLETIME_39CYCLES_5;
  hadc->Init.OversamplingMode      = DISABLE;

  if (HAL_ADC_Init(hadc) != HAL_OK)
  {
    ret =  HAL_ERROR;
  }/* Run ADC calibration */
  else if (HAL_ADCEx_Calibration_Start(hadc) != HAL_OK)
  {
    return HAL_ERROR;
  }
  else
  {
    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time */
    sConfig.Channel      = JOY1_ADC_CHANNEL;
    sConfig.Rank         = 1;
    sConfig.SamplingTime = JOY1_SAMPLING_TIME;
#if defined(ADC_SINGLE_ENDED)
    sConfig.SingleDiff   = ADC_SINGLE_ENDED;
#endif
#if defined(ADC_OFFSET_NONE)
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
#endif
    if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
    {
      ret =  HAL_ERROR;
    }
  }

  return ret;
}
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/**
  * @brief Register Default Potentiometer Msp Callbacks
  * @param JOY Potentiometer instance
  * @retval BSP status
  */
int32_t BSP_JOY_RegisterDefaultMspCallbacks (JOY_TypeDef JOY)
{
  int32_t ret = BSP_ERROR_NONE;

  if(JOY >= JOYn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_ADC_RESET_HANDLE_STATE(&hjoy_adc);

    /* Register default MspInit/MspDeInit Callback */
    if(HAL_ADC_RegisterCallback(&hjoy_adc, HAL_ADC_MSPINIT_CB_ID, ADC_MspInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_ADC_RegisterCallback(&hjoy_adc, HAL_ADC_MSPDEINIT_CB_ID, ADC_MspDeInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsJoyMspCbValid[JOY] = 1U;
    }
  }

  /* BSP status */
  return ret;
}

/**
  * @brief Register Potentiometer Msp Callback registering
  * @param JOY Potentiometer instance
  * @param Callbacks     pointer to Potentiometer MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_JOY_RegisterMspCallbacks (JOY_TypeDef JOY, BSP_JOY_Cb_t *Callback)
{
  int32_t ret = BSP_ERROR_NONE;

  if(JOY >= JOYn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_ADC_RESET_HANDLE_STATE(&hjoy_adc);

    /* Register MspInit/MspDeInit Callbacks */
    if(HAL_ADC_RegisterCallback(&hjoy_adc, HAL_ADC_MSPINIT_CB_ID, Callback->pMspInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_ADC_RegisterCallback(&hjoy_adc, HAL_ADC_MSPDEINIT_CB_ID, Callback->pMspDeInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsJoyMspCbValid[JOY] = 1U;
    }
  }

  /* BSP status */
  return ret;
}
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
#endif /* USE_BSP_JOY_FEATURE */
/**
  * @}
  */

/** @defgroup STM32C0316_DK_LOW_LEVEL_Private_Functions LOW LEVEL Private Functions
  * @{
  */
/**
  * @brief  KEY EXTI line detection callbacks.
  * @retval None
  */
static void BUTTON_USER_EXTI_Callback(void)
{
  BSP_PB_Callback(BUTTON_USER);
}

#if (USE_BSP_COM_FEATURE > 0)
/**
  * @brief  Initializes USART MSP.
  * @param  huart UART handle
  * @retval None
  */
static void USART1_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef gpio_init_structure;

  UNUSED(huart);

  /* Enable GPIO clock */
  COM1_TX_GPIO_CLK_ENABLE();
  COM1_RX_GPIO_CLK_ENABLE();

  /* Enable UART clock */
  COM1_CLK_ENABLE();

  /* Configure UART Tx as alternate function */
  gpio_init_structure.Pin       = COM1_TX_PIN;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Alternate = COM1_TX_AF;
  HAL_GPIO_Init(COM1_TX_GPIO_PORT, &gpio_init_structure);

  /* Configure UART Rx as alternate function */
  gpio_init_structure.Pin       = COM1_RX_PIN;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Alternate = COM1_RX_AF;
  HAL_GPIO_Init(COM1_RX_GPIO_PORT, &gpio_init_structure);
}

/**
  * @brief  Initialize USART Msp part
  * @param  huart UART handle
  * @retval None
  */
static void USART1_MspDeInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef          gpio_init_structure;

  UNUSED(huart);

  /* COM GPIO pin configuration */
  gpio_init_structure.Pin  = COM1_TX_PIN;
  HAL_GPIO_DeInit(COM1_TX_GPIO_PORT, gpio_init_structure.Pin);

  gpio_init_structure.Pin  = COM1_RX_PIN;
  HAL_GPIO_DeInit(COM1_RX_GPIO_PORT, gpio_init_structure.Pin);

  /* Disable UART clock */
  COM1_CLK_DISABLE();
}
#endif /* USE_BSP_COM_FEATURE */

#if (USE_BSP_JOY_FEATURE > 0)
/**
  * @brief  Initialize JOY1 Msp part
  * @param  hadc ADC handle
  * @retval None
  */
static void ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef          gpio_init_structure;

  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  JOY1_CLK_ENABLE();
  JOY1_CHANNEL_GPIO_CLK_ENABLE();

  /* ADC Channel GPIO pin configuration */
  gpio_init_structure.Pin  = JOY1_CHANNEL_GPIO_PIN;
  gpio_init_structure.Mode = GPIO_MODE_ANALOG;
  gpio_init_structure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(JOY1_CHANNEL_GPIO_PORT, &gpio_init_structure);
}

/**
  * @brief  De-Initialize JOY1 Msp part
  * @param  hadc ADC handle
  * @retval None
  */
static void ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef          gpio_init_structure;

  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* JOY GPIO pin configuration */
  gpio_init_structure.Pin  = JOY1_CHANNEL_GPIO_PIN;
  HAL_GPIO_DeInit(JOY1_CHANNEL_GPIO_PORT, gpio_init_structure.Pin);

  /* Disable ADC clock */
  JOY1_CLK_DISABLE();
}
#endif /* USE_BSP_JOY_FEATURE */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

