## <b>PWR_EnterStandbyMode Example Description</b>

How to enter the Standby mode and wake up from this mode by using an external
reset or a wakeup pin.

In the associated software, the system clock is set to 48 MHz.
An EXTI line is connected to the User push-button through PC.13 and configured to generate an
interrupt on falling edge upon key press.

Request to enter in standby mode:

When a falling edge is detected on the EXTI line, an interrupt is generated.
In the EXTI handler routine, the wake-up pin LL_PWR_WAKEUP_PIN2 is enabled and the
corresponding wake-up flag cleared. Then, the system enters Standby mode causing
LED4 to stop toggling.

Exit from Standby mode:

The user can wake-up the system in pressing the User push-button which is
connected to the wake-up pin LL_PWR_WAKEUP_PIN2.
A falling edge on WKUP pin will wake-up the system from Standby.

Alternatively, an external reset (reset button on board) will wake-up system from Standby
as well as wake-up pin.

After wake-up from Standby mode, program execution restarts in the same way as
after a reset and LED4 restarts toggling.
These steps are repeated in an infinite loop.

LED4 is used to monitor the system state as follows:

 - LED4 fast toggling (each 200ms): system in Run mode from reset (power on reset or reset pin while system was in Run mode)
 - LED4 slow toggling (each 500ms): system in Run mode after exiting from Standby mode
 - LED4 off: system in Standby mode

#### <b>Notes</b>

 1. To measure the current consumption in Standby mode, remove JP6 jumper 
    and connect an ampere meter to JP6 to measure IDD current.

 2. This example can not be used in DEBUG mode due to the fact
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

  - This example has been tested with STMicroelectronics NUCLEO-C031C6
    board and can be easily tailored to any other supported device
    and development board.

  - NUCLEO-C031C6 Set-up
    - LED4 connected to PA.05 pin
    - User push-button connected to pin PC.13 (EXTI_Line13)
    - WakeUp Pin LL_PWR_WAKEUP_PIN2 connected to PC.13

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example