## <b>PWR_EnterStandbyMode Example Description</b>

How to enter the Standby mode and wake up from this mode by using an external
reset or a wakeup pin.

In the associated software, the system clock is set to 48 MHz.

Request to enter in standby mode:
LED3 is toggling during 5 seconds, then the system automatically
enters Standby mode.

Exit from Standby mode:

A rising edge on PA6 ( pin23 CN5) (connected to LL_PWR_WAKEUP_PIN2) will
wake-up the system from Standby.

Alternatively, an external reset (reset button on board) will wake-up system from Standby
as well as wake-up pin.

After wake-up from Standby mode, program execution restarts in the same way as
after a reset and LED3 restarts toggling.
These steps are repeated in an infinite loop.

LED3 is used to monitor the system state as follows:

 - LED3 toggling : system in Run mode
 - LED3 off: system in Standby mode


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

  - This example runs on STM32C011F6Ux devices.

  - This example has been tested with STMicroelectronics STM32C0116-DISCO
    board and can be easily tailored to any other supported device
    and development board.

  - STM32C0116-DISCO Set-up
    - LED3 connected to PB.6 pin
    - Put a wire between PA6 ( pin23 CN5) and 3.3V pin
	to generate a rising edge on LL_PWR_WAKEUP_PIN2.
    - WakeUp Pin LL_PWR_WAKEUP_PIN2 connected to PA6 ( pin23 CN5)

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example