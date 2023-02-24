## <b>PWR_EnterStandbyMode Example Description</b>

How to enter the Standby mode and wake up from this mode by using an external
reset or a wakeup pin.

In the associated software, the system clock is set to 48 MHz.

Request to enter in standby mode:
LED1 is toggling during 5 seconds, then the system automatically
enters Standby mode.

Exit from Standby mode:

A rising edge on PA.00 (D4 pin6 CN6) (connected to LL_PWR_WAKEUP_PIN1) will
wake-up the system from Standby.

Alternatively, an external reset (reset button on board) will wake-up system from Standby
as well as wake-up pin.

After wake-up from Standby mode, program execution restarts in the same way as
after a reset and LED1 restarts toggling.
These steps are repeated in an infinite loop.

LED1 is used to monitor the system state as follows:

 - LED1 toggling : system in Run mode
 - LED1 off: system in Standby mode


#### <b>Notes</b>

 1. This example can not be used in DEBUG mode due to the fact
    that the Cortex-M0+ core is no longer clocked during low power mode
    so debugging features are disabled.


### <b>Keywords</b>

Power, PWR, Standby mode, Interrupt, EXTI, Wakeup, Low Power, External reset,

### <b>Directory contents</b>

  - PWR/PWR_EnterStandbyMode/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - PWR/PWR_EnterStandbyMode/Inc/main.h                  Header for main.c module
  - PWR/PWR_EnterStandbyMode/Inc/stm32_assert.h          Template file to include assert_failed function
  - PWR/PWR_EnterStandbyMode/Src/stm32c0xx_it.c          Interrupt handlers
  - PWR/PWR_EnterStandbyMode/Src/main.c                  Main program
  - PWR/PWR_EnterStandbyMode/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with STMicroelectronics STM32C0316-DISCO
    board and can be easily tailored to any other supported device
    and development board.

  - STM32C0316-DISCO Set-up :
    - LED1 connected to PA.5 pin
    - Put a wire between PA.00 (D4 pin6 CN6) and 3.3V pin
	to generate a rising edge on LL_PWR_WAKEUP_PIN1.
    - WakeUp Pin LL_PWR_WAKEUP_PIN1 connected to PA.00 (D4 pin6 CN6)

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example