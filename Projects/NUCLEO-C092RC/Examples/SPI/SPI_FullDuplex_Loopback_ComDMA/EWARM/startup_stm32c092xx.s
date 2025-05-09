;******************************************************************************
;* File Name          : startup_stm32c031xx.s
;* Author             : MCD Application Team
;* Description        : STM32C031xx devices vector table for EWARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == __iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR
;*                        address
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M0+ processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;******************************************************************************
;* @attention
;*
;* Copyright (c) 2022 STMicroelectronics.
;* All rights reserved.
;*
;* This software is licensed under terms that can be found in the LICENSE file
;* in the root directory of this software component.
;* If no LICENSE file comes with this software, it is provided AS-IS.
;*
;*******************************************************************************
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                      ; Reset Handler

        DCD     NMI_Handler                        ; NMI Handler
        DCD     HardFault_Handler                  ; Hard Fault Handler
        DCD     0                                  ; Reserved
        DCD     0                                  ; Reserved
        DCD     0                                  ; Reserved
        DCD     0                                  ; Reserved
        DCD     0                                  ; Reserved
        DCD     0                                  ; Reserved
        DCD     0                                  ; Reserved
        DCD     SVC_Handler                        ; SVCall Handler
        DCD     0                                  ; Reserved
        DCD     0                                  ; Reserved
        DCD     PendSV_Handler                     ; PendSV Handler
        DCD     SysTick_Handler                    ; SysTick Handler

        ; External Interrupts
        DCD     WWDG_IRQHandler                    ; Window Watchdog
        DCD     0                                  ; Reserved
        DCD     RTC_IRQHandler                     ; RTC through EXTI Line
        DCD     FLASH_IRQHandler                   ; FLASH
        DCD     RCC_IRQHandler                     ; RCC
        DCD     EXTI0_1_IRQHandler                 ; EXTI Line 0 and 1
        DCD     EXTI2_3_IRQHandler                 ; EXTI Line 2 and 3
        DCD     EXTI4_15_IRQHandler                ; EXTI Line 4 to 15
        DCD     0                                  ; Reserved
        DCD     DMA1_Channel1_IRQHandler           ; DMA1 Channel 1
        DCD     DMA1_Channel2_3_IRQHandler         ; DMA1 Channel 2 and Channel 3
        DCD     DMAMUX1_DMA1_CH4_5_6_7_IRQHandler  ; DMAMUX, DMA1 Channel 4 to 7
        DCD     ADC1_IRQHandler                    ; ADC1
        DCD     TIM1_BRK_UP_TRG_COM_IRQHandler     ; TIM1 Break, Update, Trigger and Commutation
        DCD     TIM1_CC_IRQHandler                 ; TIM1 Capture Compare
        DCD     TIM2_IRQHandler                    ; TIM2
        DCD     TIM3_IRQHandler                    ; TIM3
        DCD     0                                  ; Reserved
        DCD     0                                  ; Reserved
        DCD     TIM14_IRQHandler                   ; TIM14
        DCD     TIM15_IRQHandler                   ; TIM15
        DCD     TIM16_IRQHandler                   ; TIM16
        DCD     TIM17_IRQHandler                   ; TIM17
        DCD     I2C1_IRQHandler                    ; I2C1
        DCD     I2C2_IRQHandler                    ; I2C2
        DCD     SPI1_IRQHandler                    ; SPI1
        DCD     SPI2_IRQHandler                    ; SPI2
        DCD     USART1_IRQHandler                  ; USART1
        DCD     USART2_IRQHandler                  ; USART2
        DCD     USART3_4_IRQHandler                ; USART3 and USART4
        DCD     FDCAN1_IT0_IRQHandler              ; FDCAN1 interrupt request 0 pending
        DCD     FDCAN1_IT1_IRQHandler              ; FDCAN1 interrupt request 1 pending

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG_IRQHandler
        B WWDG_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCC_IRQHandler
        B RCC_IRQHandler

        PUBWEAK EXTI0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_1_IRQHandler
        B EXTI0_1_IRQHandler

        PUBWEAK EXTI2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_3_IRQHandler
        B EXTI2_3_IRQHandler

        PUBWEAK EXTI4_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_15_IRQHandler
        B EXTI4_15_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler

        PUBWEAK DMA1_Channel2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel2_3_IRQHandler
        B DMA1_Channel2_3_IRQHandler

        PUBWEAK DMAMUX1_DMA1_CH4_5_6_7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMAMUX1_DMA1_CH4_5_6_7_IRQHandler
        B DMAMUX1_DMA1_CH4_5_6_7_IRQHandler

        PUBWEAK ADC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC1_IRQHandler
        B ADC1_IRQHandler

        PUBWEAK TIM1_BRK_UP_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_BRK_UP_TRG_COM_IRQHandler
        B TIM1_BRK_UP_TRG_COM_IRQHandler

        PUBWEAK TIM1_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_CC_IRQHandler
        B TIM1_CC_IRQHandler

        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
        B TIM2_IRQHandler

        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_IRQHandler
        B TIM3_IRQHandler

        PUBWEAK TIM14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM14_IRQHandler
        B TIM14_IRQHandler

        PUBWEAK TIM15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM15_IRQHandler
        B TIM15_IRQHandler

        PUBWEAK TIM16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM16_IRQHandler
        B TIM16_IRQHandler

        PUBWEAK TIM17_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM17_IRQHandler
        B TIM17_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK I2C2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_IRQHandler
        B I2C2_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK USART3_4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART3_4_IRQHandler
        B USART3_4_IRQHandler

        PUBWEAK FDCAN1_IT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDCAN1_IT0_IRQHandler
        B FDCAN1_IT0_IRQHandler

        PUBWEAK FDCAN1_IT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDCAN1_IT1_IRQHandler
        B FDCAN1_IT1_IRQHandler

        END


