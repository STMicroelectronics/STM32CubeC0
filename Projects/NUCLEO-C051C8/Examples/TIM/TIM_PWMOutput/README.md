## <b>TIM_PWMOutput Example Description</b>

This example shows how to configure the TIM peripheral in PWM (Pulse Width Modulation)
mode.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.

The SystemClock_Config() function is used to configure the system clock for STM32C051C8Tx devices :
The CPU at 48 MHz.

    In this example TIM1 input clock (TIM1CLK) is set to APB1 clock (PCLK1),
    since APB1 prescaler is equal to 1.
      TIM1CLK = PCLK1
      PCLK1 = HCLK
      => TIM1CLK = HCLK = SystemCoreClock

    To get TIM1 counter clock at SystemCoreClock, the prescaler is set to 0

    To get TIM1 output clock at 25 KHz, the period (ARR)) is computed as follows:
       ARR = (TIM1 counter clock / TIM1 output clock) - 1
           = 2295

    TIM1 Channel1 duty cycle = (TIM1_CCR1/ TIM1_ARR + 1)* 100 = 50%
    TIM1 Channel2 duty cycle = (TIM1_CCR2/ TIM1_ARR + 1)* 100 = 37.5%
    TIM1 Channel3 duty cycle = (TIM1_CCR3/ TIM1_ARR + 1)* 100 = 25%
    TIM1 Channel4 duty cycle = (TIM1_CCR4/ TIM1_ARR + 1)* 100 = 12.5%

LED4 is ON when there are an error.

The PWM waveforms can be displayed using an oscilloscope.

#### <b>Notes</b>

 1. The duty cycles values mentioned above are theoretical (obtained when the system clock frequency is exactly 48 MHz).
    They might be slightly different depending on system clock frequency precision.

 2. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 3. This example needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Timer, TIM, Output, signal, PWM, Oscilloscope, Frequency, Duty cycle, Waveform

### <b>Directory contents</b>

    - TIM/TIM_PWMOutput/Inc/stm32c0xx_hal_conf.h    HAL configuration file
    - TIM/TIM_PWMOutput/Inc/stm32c0xx_it.h          Interrupt handlers header file
    - TIM/TIM_PWMOutput/Inc/main.h                  Header for main.c module  
    - TIM/TIM_PWMOutput/Src/stm32c0xx_it.c          Interrupt handlers
    - TIM/TIM_PWMOutput/Src/main.c                  Main program
    - TIM/TIM_PWMOutput/Src/stm32c0xx_hal_msp.c     HAL MSP file
    - TIM/TIM_PWMOutput/Src/system_stm32c0xx.c      STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C051C8Tx devices.
  - In this example, the clock is set to 48 MHz.

  - This example has been tested with STMicroelectronics NUCLEO-C051C8 
    board and can be easily tailored to any other supported device 
    and development board.

  - NUCLEO-C051C8 Set-up
   Connect the following pins to an oscilloscope to monitor the different waveforms:

       - TIM1_CH1 : PA.00 (pin 28 in CN7 connector)
       - TIM1_CH2 : PA.01 (pin 30 in CN7 connector)
       - TIM1_CH3 : PB.06 (pin 35 in CN10 connector)
       - TIM1_CH4 : PB.07 (pin 37  in CN10 connector)


### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

