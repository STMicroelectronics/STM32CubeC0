## <b>Templates Example Description</b>

This projects provides a reference template that can be used to build any firmware application.

This directory provides a reference template project that can be used to build any firmware application for
STM32C031xx devices using STM32CubeC0 HAL and running on STM32C0316-DISCO board from STMicroelectronics. 

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Directory contents</b>

  - Templates/Src/main.c                 Main program
  - Templates/Src/system_stm32c0xx.c     STM32C0xx system clock configuration file
  - Templates/Src/stm32c0xx_it.c         Interrupt handlers 
  - Templates/Src/stm32c0xx_hal_msp.c    HAL MSP module
  - Templates/Inc/main.h                 Main program header file  
  - Templates/Inc/stm32c0xx_hal_conf.h   HAL Configuration file
  - Templates/Inc/stm32c0xx_it.h         Interrupt handlers header file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031xx devices.

  - This example has been compiled on EWARM v8.50.9 , MDK ARM v5.36.0.0 and STM32CubeIDE v1.9.0

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
