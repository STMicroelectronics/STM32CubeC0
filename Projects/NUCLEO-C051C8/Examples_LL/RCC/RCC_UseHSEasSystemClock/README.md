## <b>RCC_UseHSEasSystemClock Example Description</b>

Use of the RCC LL API to start the HSE and use it as system clock.

At start-up, HSI clock is used as system clock (default clock after reset) and then Systick is 
configured at 1 ms using HSI_VALUE define.

Then, HSE is started and we wait for ready state. System clock is set to HSE thanks to IT 
triggered by HSE ready.

- LED4 is turned ON to indicate that HSE is ready.
- LED4 is toggled with a timing of 1 second in case of error to switch SYSCLK to HSE or if HSE CSS
failure is detected (through NMI IT).


### <b>Keywords</b>

System, RCC, PLL, PLLCLK, SYSCLK, HSE, Clock, Oscillator, HSI


### <b>Directory contents</b>

  - RCC/RCC_UseHSEasSystemClock/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - RCC/RCC_UseHSEasSystemClock/Inc/main.h                  Header for main.c module
  - RCC/RCC_UseHSEasSystemClock/Inc/stm32_assert.h          Template file to include assert_failed function
  - RCC/RCC_UseHSEasSystemClock/Src/stm32c0xx_it.c          Interrupt handlers
  - RCC/RCC_UseHSEasSystemClock/Src/main.c                  Main program
  - RCC/RCC_UseHSEasSystemClock/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C051C8Tx devices.
    
  - This example has been tested with NUCLEO-C051C8 
    board and can be easily tailored to any other supported device
    and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
