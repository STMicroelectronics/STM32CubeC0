## <b>EXTI_ToggleLedOnIT_Init Example Description</b>

This example describes how to configure the EXTI and use GPIOs to toggle the user LEDs available on the board when
a user button is pressed. This example is based on the STM32C0xx LL API. Peripheral initialization is done using LL
initialization function to demonstrate LL init usage.

In this example, one EXTI line (EXTI_Line13) is configured to generate an interrupt on each falling edge.

In the interrupt routine a led connected to a specific GPIO pin is toggled.

In this example:

- EXTI_Line13 is connected to PC.13 pin
- when falling edge is detected on EXTI_Line13 by pressing User push-button, LED4 toggles

On NUCLEO-C031C6:

- EXTI_Line13 is connected to User push-button

### <b>Keywords</b>

System, GPIO, Output, Alternate function, EXTI, Toggle

### <b>Directory contents</b>

  - EXTI/EXTI_ToggleLedOnIT_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - EXTI/EXTI_ToggleLedOnIT_Init/Inc/main.h                  Header for main.c module
  - EXTI/EXTI_ToggleLedOnIT_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - EXTI/EXTI_ToggleLedOnIT_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - EXTI/EXTI_ToggleLedOnIT_Init/Src/main.c                  Main program
  - EXTI/EXTI_ToggleLedOnIT_Init/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example