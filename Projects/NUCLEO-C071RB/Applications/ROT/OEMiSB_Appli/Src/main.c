/**
  ******************************************************************************
  * @file    Templates/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body
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
#include "main.h"
#include "stm32c0xx_hal.h"
#include "stm32c0xx_ll_bus.h"
#if defined(__ICCARM__)
#include <LowLevelIOInterface.h>
#endif /* __ICCARM__ */
/** @addtogroup Templates
  * @{
  */

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define NB_BYTES                (8U)

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void USART2_Config(void);

#if (DATA_SIZE > 0)
void FW_APP_PrintMainMenu(void);
void FW_APP_Run(void);
void Read_DATA(void);
void Write_DATA(void);
void Erase_DATA(void);
#endif


static UART_HandleTypeDef  uart_device;

/* Private functions ---------------------------------------------------------*/

#if defined(__ICCARM__)
/* New definition from EWARM V9, compatible with EWARM8 */
int iar_fputc(int ch);
#define PUTCHAR_PROTOTYPE int iar_fputc(int ch)
#elif defined ( __CC_ARM ) || defined(__ARMCC_VERSION)
/* ARM Compiler 5/6*/
int io_putchar(int ch);
#define PUTCHAR_PROTOTYPE int io_putchar(int ch)
#elif defined(__GNUC__)
#define PUTCHAR_PROTOTYPE int32_t uart_putc(int32_t ch)
#endif /* __ICCARM__ */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of putchar here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&uart_device, (uint8_t *)&ch, 1, 0xFFFF);
  
  return ch;
}

/* Redirects printf to TFM_DRIVER_STDIO in case of ARMCLANG*/
#if defined(__ARMCC_VERSION)
FILE __stdout;

/* __ARMCC_VERSION is only defined starting from Arm compiler version 6 */
int fputc(int ch, FILE *f)
{
  /* Send byte to USART */
  io_putchar(ch);

  /* Return character written */
  return ch;
}
#elif defined(__GNUC__)
/* Redirects printf to TFM_DRIVER_STDIO in case of GNUARM */
int _write(int fd, char *str, int len)
{
  int i;

  for (i = 0; i < len; i++)
  {
    /* Send byte to USART */
    uart_putc(str[i]);
  }

  /* Return the number of characters written */
  return len;
}
#elif defined(__ICCARM__)
size_t __write(int file, unsigned char const *ptr, size_t len)
{
  size_t idx;
  unsigned char const *pdata = ptr;

  for (idx = 0; idx < len; idx++)
  {
    iar_fputc((int)*pdata);
    pdata++;
  }
  return len;
}
#endif /*  __GNUC__ */
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize COM */
  USART2_Config();
  HAL_UART_Init(&uart_device);

  printf("\r\n======================================================================");
  printf("\r\n=              (C) COPYRIGHT 2024 STMicroelectronics                 =");
  printf("\r\n=                                                                    =");
  printf("\r\n=                          OEMiSB User App                           =");
  printf("\r\n======================================================================");
  printf("\r\n\r\n");
  printf("\r\n============================= Main Menu ==============================\r\n\n");

#if (DATA_SIZE > 0)
  FW_APP_Run();
#endif

   /* Infinite loop */
  while (1)
  {

  }

}

/**
  * @brief  Display the TEST Main Menu choices on HyperTerminal
  * @param  None.
  * @retval None.
  */
#if (DATA_SIZE > 0)
void FW_APP_PrintMainMenu(void)
{
  printf("  Read flash data ------------------------------------------ 1\r\n\n");
  printf("  Write flash data ----------------------------------------- 2\r\n\n");
  printf("  Erase flash data ----------------------------------------- 3\r\n\n");
  printf("  Selection :\r\n\n");
}

/**
  * @brief  Display the TEST Main Menu choices on HyperTerminal
  * @param  None.
  * @retval None.
  */
void FW_APP_Run(void)
{
  uint8_t key = 0U;

  /*##1- Print Main Menu message*/
  FW_APP_PrintMainMenu();

  while (1U)
  {
    /* Clean the input path */
    __HAL_UART_FLUSH_DRREGISTER(&uart_device);

    /* Receive key */
    if (HAL_UART_Receive(&uart_device, &key, 1U, RX_TIMEOUT) == HAL_OK)
    {
      switch (key)
      {
        case '1' :
          Read_DATA();
          break;
        case '2' :
          Write_DATA();
          break;
        case '3' :
          Erase_DATA();
          break;
        default:
          printf("Invalid Number !\r");
          break;
      }

      /* Print Main Menu message */
      FW_APP_PrintMainMenu();
    }
  }
}

void Read_DATA(void)
{
  uint8_t buffer[NB_BYTES];

  memcpy((void *)buffer, (void *)(FLASH_BASE + FLASH_SIZE_DEFAULT - DATA_SIZE), NB_BYTES);
  /* display the first 32 data bytes */
  printf("Data from flash: ");
  for (int i = 0U; i < NB_BYTES; i++)
  {
    printf("%x",buffer[i]);
  }
  printf("\r\n\n");
}

void Write_DATA(void)
{
  uint8_t buffer[NB_BYTES] = {0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};

  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)(FLASH_BASE + FLASH_SIZE_DEFAULT - DATA_SIZE), *((uint64_t*)buffer));
  printf("Write in flash: 0x");
  for (int i = 0U; i < NB_BYTES; i++)
  {
    printf("%x",buffer[i]);
  }
  printf("\r\n\n");
}

void Erase_DATA(void)
{
  uint32_t page_error = 0U;
  FLASH_EraseInitTypeDef p_erase_init;
  p_erase_init.TypeErase   = FLASH_TYPEERASE_PAGES;
  p_erase_init.Page        = FLASH_PAGE_NB - (DATA_SIZE/FLASH_PAGE_SIZE);
  p_erase_init.NbPages     = 1;
  HAL_FLASHEx_Erase(&p_erase_init, &page_error);
  printf("Erase written sector\r\n\n");
}

#endif

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  LL_RCC_HSI_SetCalibTrimming(64);
  LL_RCC_SetHSIDiv(LL_RCC_HSI_DIV_1);
  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_HCLK_DIV_1);

  /* Sysclk activation on the HSI */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  
  //LL_Init1msTick(48000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(48000000);
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void USART2_Config(void)
{

  GPIO_InitTypeDef GPIO_Init;

  /* Configure COM Tx as alternate function */
  COM_TX_GPIO_CLK_ENABLE();
  COM_RX_GPIO_CLK_ENABLE();
  COM_CLK_ENABLE();
  GPIO_Init.Pin       = COM_TX_PIN;
  GPIO_Init.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_Init.Pull      = GPIO_PULLUP;
  GPIO_Init.Alternate = COM_TX_AF;
  HAL_GPIO_Init(COM_TX_GPIO_PORT, &GPIO_Init);

  /* Configure COM Rx as alternate function */
  GPIO_Init.Pin       = COM_RX_PIN;
  GPIO_Init.Alternate = COM_RX_AF;
  HAL_GPIO_Init(COM_RX_GPIO_PORT, &GPIO_Init);

  uart_device.Instance = COM_INSTANCE;
  uart_device.Init.BaudRate       = 115200;
  uart_device.Init.WordLength     = UART_WORDLENGTH_8B;
  uart_device.Init.StopBits       = UART_STOPBITS_1;
  uart_device.Init.Parity         = UART_PARITY_NONE;
  uart_device.Init.Mode           = UART_MODE_TX_RX;
  uart_device.Init.HwFlowCtl      = UART_HWCONTROL_NONE;
  uart_device.Init.OverSampling   = UART_OVERSAMPLING_8;
  uart_device.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  uart_device.Init.ClockPrescaler = UART_PRESCALER_DIV1;

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* Infinite loop */
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
/**
  * @}
  */
