## <b>RCC_LSIConfig Example Description</b>
How to enable/disable the low-speed internal (LSI) RC oscillator (about 32 KHz) at run time, using the RCC HAL API.

Board: NUCLEO-C092RC (embeds a STM32C092RC device)
Microcontroller Clock Output MCO Pin: PA.09

In this example, after startup SYSCLK is configured to the max frequency using the PLL with
MSIS as clock source, the User push-button (connected to EXTI_Line13)
is used to enable/disable LSI:
each time the User push-button is pressed, EXTI_Line13 interrupt is generated and the ISR
enables the LSI when it is off, disables it when it is on.

LED1 behaviour is as follows according to LSI activation:
when LSI is on, LED1 is toggling (every 100 ms).
when LSI is off, LED1 is on.
LSI clock waveform is available on the MCO pin PA.09 and can be captured
on an oscilloscope.

In case of configuration error, LED2 is on.


#### <b>Notes</b>
1.  Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

2.  The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

### <b>Keywords</b>

System, RCC, LSI, PLL, PLLCLK, SYSCLK, Clock, Oscillator

### <b>Directory contents</b>

  - RCC/RCC_LSIConfig/Inc/stm32c0xx_hal_conf.h    HAL configuration file
  - RCC/RCC_LSIConfig/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - RCC/RCC_LSIConfig/Inc/main.h                        Header for main.c module
  - RCC/RCC_LSIConfig/Src/stm32c0xx_it.c          Interrupt handlers
  - RCC/RCC_LSIConfig/Src/main.c                        Main program
  - RCC/RCC_LSIConfig/Src/system_stm32c0xx.c      STM32C0xx system source file
  - RCC/RCC_LSIConfig/Src/stm32c0xx_hal_msp.c     HAL MSP module

### <b>Hardware and Software environment</b> 

  - This example runs on STM32C092RCTx devices.

  - This example has been tested with NUCLEO-C092RC
    board and can be easily tailored to any other supported device
    and development board.

### <b>How to use it ?</b> 

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
