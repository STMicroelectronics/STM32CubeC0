## <b>PWR_EnterStopMode Example Description</b>

How to enter the Stop 0 mode.

After start-up LED4 is toggling during 5 seconds, then the system automatically
enter in Stop 0 mode (Final state).

LED4 is used to monitor the system state as follows:

 - **LED4 toggling :** system in Run mode
 - **LED4 off :** system in Stop 0 mode

This example does not implement a wake-up source from any peripheral: to wake-up the device,
press on Reset button.

#### <b>Notes</b>

 1. This example can not be used in DEBUG mode due to the fact
      that the Cortex-M0+ core is no longer clocked during low power mode
      so debugging features are disabled.

### <b>Keywords</b>

Power, PWR, Stop mode, Interrupt, Low Power

### <b>Directory contents</b>

  - PWR/PWR_EnterStopMode/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - PWR/PWR_EnterStopMode/Inc/main.h                  Header for main.c module
  - PWR/PWR_EnterStopMode/Inc/stm32_assert.h          Template file to include assert_failed function
  - PWR/PWR_EnterStopMode/Src/stm32c0xx_it.c          Interrupt handlers
  - PWR/PWR_EnterStopMode/Src/main.c                  Main program
  - PWR/PWR_EnterStopMode/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with STMicroelectronics NUCLEO-C031C6
    board and can be easily tailored to any other supported device
    and development board.

  - NUCLEO-C031C6 Set-up
    - LED4 connected to PA.05 pin

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
