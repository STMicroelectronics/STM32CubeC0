## <b>PWR_STOP Example Description</b>

How to enter the Stop mode and wake-up from this mode by using an interrupt.


In the associated software, an EXTI line is connected to the user button through PC13 and configured to generate an
interrupt on falling edge upon key press.
The SysTick is programmed to generate an interrupt each 1 ms and in the SysTick 
interrupt handler, LED4 is toggled in order to indicate whether the MCU is in stop mode 
or run mode.

LED4 is used to monitor the system state as follows:

 - LED4 toggling: system in Run mode
 - LED4 off : system in Standby mode

5 seconds after start-up, the system automatically enters stop mode and LED4 stops toggling.

The User push-button can be pressed at any time to wake-up the system.

The software then comes back in run mode for 5 sec. before automatically entering stop mode again.

Note: To measure the current consumption in stop mode, remove JP6 jumper
      and connect an amperemeter to JP6 to measure IDD current.

Note: This example can not be used in DEBUG mode due to the fact
      that the Cortex-M0+ core is no longer clocked during low power mode
      so debugging features are disabled.

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Power, PWR, Stop mode, Interrupt, EXTI, Wakeup, Low Power,

### <b>Directory contents</b>

  -  PWR/PWR_STOP/Inc/stm32c0xx_conf.h     HAL Configuration file
  -  PWR/PWR_STOP/stm32c0xx_it.h           Header for stm32c0xx_it.c
  -  PWR/PWR_STOP/Inc/main.h               Header file for main.c
  -  PWR/PWR_STOP/Src/system_stm32c0xx.c   STM32C0xx system clock configuration file
  -  PWR/PWR_STOP/Src/stm32c0xx_it.c       Interrupt handlers
  -  PWR/PWR_STOP/Src/main.c               Main program
  -  PWR/PWR_STOP/Src/stm32c0xx_hal_msp.c  HAL MSP module

### <b>Hardware and Software environment</b>

  - This example runs on STM32C051C8Tx devices

  - This example has been tested with STMicroelectronics NUCLEO-C051C8
    board and can be easily tailored to any other supported device
    and development board.

  - NUCLEO-C051C8 Set-up
    - LED4 connected to PA.05 pin

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Once the image is loaded, power off the NUCLEO board in unplugging
   the power cable then power on the board again 
 - Run the example