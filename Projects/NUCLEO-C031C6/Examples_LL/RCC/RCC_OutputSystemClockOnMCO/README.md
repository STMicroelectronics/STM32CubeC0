## <b>RCC_OutputSystemClockOnMCO Example Description</b>

Configuration of MCO pin (PA8) to output the system clock.

At start-up, User push-button and MCO pin are configured. The program configures SYSCLK
to the max frequency using HSI48 as clock source.

The signal on PA8 (pin 24 of CN10 connector) can be monitored with an oscilloscope
to check the different MCO configuration set at each User push-button press.

Different configuration will be observed :

 - SYSCLK frequency with frequency value around @48MHz.
 - SYSCLK frequency value divided by 2, hence around @24MHz.
 - HSI frequency value divided by 4, hence around @12MHz.

When user press User push-button, a **LED4** toggle is done to indicate a change in MCO config.

### <b>Keywords</b>

System, RCC, PLL, HSI, PLLCLK, SYSCLK, HSE, Clock, Oscillator

### <b>Directory contents</b>

  - RCC/RCC_OutputSystemClockOnMCO/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - RCC/RCC_OutputSystemClockOnMCO/Inc/main.h                  Header for main.c module
  - RCC/RCC_OutputSystemClockOnMCO/Inc/stm32_assert.h          Template file to include assert_failed function
  - RCC/RCC_OutputSystemClockOnMCO/Src/stm32c0xx_it.c          Interrupt handlers
  - RCC/RCC_OutputSystemClockOnMCO/Src/main.c                  Main program
  - RCC/RCC_OutputSystemClockOnMCO/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C031C6 Set-up

    - Connect the MCO pin to an oscilloscope to monitor the different waveforms:
      - PA.08: connected to pin 24 of CN10 connector

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example