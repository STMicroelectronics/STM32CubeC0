## <b>Templates_LL Example Description</b>

This projects provides a reference template through the LL API that can be used to build any firmware application.

This project LL template provides:

 - Inclusion of all LL drivers (include files in "main.h" and LL sources files in IDE environment, with option "USE_FULL_LL_DRIVER" in IDE environment)
   - **Note**: If optimization is needed afterwards, user can perform a cleanup by removing unused drivers.
 - Definition of LEDs and user button (file: main.h)
   - **Note**: User button name printed on board may differ from naming "user button" in code: "key button", ...
 - Clock configuration (file: main.c)

This project LL template does not provide:

 - Functions to initialize and control LED and user button
 - Functions to manage IRQ handler of user button

To port a LL example to the targeted board:

1. Select the LL example to port.
   To find the board on which LL examples are deployed, refer to LL examples list in "STM32CubeProjectsList.html", table section "Examples_LL"
   or AN    : STM32Cube firmware examples for stm32c0xx Series

2. Replace source files of the LL template by the ones of the LL example, except code specific to board.

   **Note**: Code specific to board is specified between tags:

         /* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */
         /* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */
         
   - Replace file main.h, with updates:
     - Keep LED and user button definition of the LL template under tags
    
   - Replace file main.c, with updates:
     - Keep clock configuration of the LL template: function "SystemClock_Config()"
     - Depending of LED availability, replace LEDx_PIN by another LEDx (number) available in file main.h
     
   - Replace file stm32c0xx_it.h
   - Replace file stm32c0xx_it.c


### <b>Keywords</b>

Template LL

### <b>Directory contents</b>

  - Templates_LL/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - Templates_LL/Inc/main.h                  Header for main.c module
  - Templates_LL/Inc/stm32_assert.h          Template file to include assert_failed function
  - Templates_LL/Src/stm32c0xx_it.c          Interrupt handlers
  - Templates_LL/Src/main.c                  Main program
  - Templates_LL/Src/system_stm32c0xx.c      STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C0116xx devices.

  - This example has been compiled on EWARM v8.50.9, MDK ARM v5.36.0.0 and STM32CubeIDE v1.9.0

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
