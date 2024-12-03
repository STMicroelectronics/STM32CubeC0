## <b>TIM_ExternalClockMode1 Example Description</b>

- This example shows how to configure the TIM peripheral in external clock mode 1 and use the button as a clock source
to light a LED after 5 presses.

- At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 48 MHz.

- The objective is to configure TIM1 channel 2 in input capture mode and select this signal (tim_ti2_fp2) as a clock
source. To do so, tim_ti2_fp2 is chosen as trigger input source for the slave mode controller in external clock mode 1.

- To prevent button bounce, the button signal is not directly redirected to the timer input. The button pin is
configured in interrupt mode for the rising edges. Thanks to this event, a 250ms pulse is generated on an intermediate
GPIO (TIM_IN_GPIO) and redirected to the timer input. During this amount of time, no other button events are considered.

- The TIM1 channel 1 is configured in output compare mode so that the compare match event is used to light the LED.
Because the output is meaning less, it is frozen.

- The following configuration values are used for TIM1:  
      - Prescaler = 0  
      - Repetition counter = 0  
      - Autoreload = 5  
      - Pulse (CCR1) = 5

NUCLEO-C051C8 board's LEDs can be used to monitor the example status:

- LED4 is ON when the button is pressed 5 times.
- LED4 is slowly blinking when there is an error.

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

TIM, Input, Clock source, External Clock Mode 1, Non-periodic clock, Button.

### <b>Sub-project FSBL directory contents</b>

      - TIM/TIM_ExternalClockMode1/Inc/main.h                       Header for main.c module
      - TIM/TIM_ExternalClockMode1/Inc/stm32c0xx_hal_conf.h         HAL Configuration file
      - TIM/TIM_ExternalClockMode1/Inc/stm32c0xx_nucleo_conf.h      BSP configuration file
      - TIM/TIM_ExternalClockMode1/Inc/stm32c0xx_it.h               Interrupt handlers header file
      - TIM/TIM_ExternalClockMode1/Src/main.c                       Main program
      - TIM/TIM_ExternalClockMode1/Src/stm32c0xx_hal_msp.c          HAL MSP module
      - TIM/TIM_ExternalClockMode1/Src/stm32c0xx_it.c               Interrupt handlers
      - TIM/TIM_ExternalClockMode1/Src/system_stm32c0xx_fsbl.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C051C8Tx devices.

  - This example has been tested with NUCLEO-C051C8 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C051C8 Set-up
    - Connect the following pins together:
      - TIM1_CH2    : PA.09 (Pin 1 CN5)
      - TIM_IN_GPIO : GPIO_PIN_10 (Pin 3 CN9)

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
