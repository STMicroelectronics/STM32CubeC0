## <b>RCC_ClockConfig Example Description</b>

Configuration of the system clock (SYSCLK) and modification of the clock settings in Run mode, using the RCC HAL API.

In this example, after startup SYSCLK is configured to the max frequency using the HSI as clock source,
the User push-button (connected to EXTI_Line13) will be
used to change the clock source:

    - from HSI to HSE
    - from HSE to HSI

Each time the User push-button is pressed EXTI_Line13 interrupt is generated and in the ISR
the clock source is checked using __HAL_RCC_GET_SYSCLK_SOURCE() macro:

- If the HSE oscillator is selected as a source clock, the following steps will be followed to switch
   to HSE oscillator:

     a. Switch the system clock source to HSE
     b. Select HSE as system clock source and configure bus clocks dividers	
     c. Disable the HSI oscillator
     

- If the HSI oscillator is selected as a source clock, the following steps will be followed to switch
   to HSI oscillator:

     a. Switch the system clock source to HSI
     b. Select HSI as system clock source and configure bus clocks dividers	
     c. Disable the HSE oscillator
     
LED1 is toggled with a timing defined by the HAL_Delay() API.

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

RCC, System, Clock Configuration, HSE, HSI, System clock, Oscillator

### <b>Directory contents</b>

    - RCC/RCC_ClockConfig/Inc/stm32c0xx_hal_conf.h    HAL configuration file
    - RCC/RCC_ClockConfig/Inc/stm32c0xx_it.h          Interrupt handlers header file
    - RCC/RCC_ClockConfig/Inc/main.h                  Header for main.c module
    - RCC/RCC_ClockConfig/Src/stm32c0xx_it.c          Interrupt handlers
    - RCC/RCC_ClockConfig/Src/main.c                  Main program
    - RCC/RCC_ClockConfig/Src/system_stm32c0xx.c      STM32C0xx system source file
    - RCC/RCC_ClockConfig/Src/stm32c0xx_hal_msp.c     HAL MSP module

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
