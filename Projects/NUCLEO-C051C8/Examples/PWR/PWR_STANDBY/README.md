﻿## <b>PWR_STANDBY Example Description</b>

How to enter the Standby mode and wake up from this mode by using an external reset or the WKUP pin.

The SysTick is programmed to generate an interrupt each 1 ms and in the SysTick
interrupt handler, LED4 is toggled in order to indicate whether the MCU is in Standby or Run mode.

When a falling edge is detected on the EXTI line, an interrupt is generated and the system wakes up
the program then checks and clears the standby flag.
After clearing the standby flag, the software enables wake-up pin PWR_WAKEUP_PIN2 connected to PC.13, then
the corresponding flag indicating that a wakeup event was received from the PWR_WAKEUP_PIN2 is cleared.
Finally, the system enters again Standby mode causing LED4 to stop toggling.

Next, the user can wake-up the system in pressing the User push-button which is connected
to the wake-up pin PWR_WAKEUP_PIN2.The software then comes back in run mode for 5 sec.
A falling edge on WKUP pin will wake-up the system from Standby.
Alternatively, an external RESET of the board will lead to a system wake-up as well.The application needs to ensure that the SysTick

After wake-up from Standby mode, program execution restarts in the same way as after
a RESET and LED4 restarts toggling.

LED4 is used to monitor the system state as follows:

 - LED4 toggling: system in Run mode
 - LED4 off : system in Standby mode
 - LED4 ON: configuration failed (system will go to an infinite loop)

#### <b>Notes</b>
   1. To measure the current consumption in Standby mode, remove JP6 jumper
      and connect an amperemeter to JP6 to measure IDD current.

   2. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

   3. The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

### <b>Keywords</b>

Power, PWR, Standby mode, Interrupt, EXTI, Wakeup, Low Power, External reset

### <b>Directory contents</b>

    - PWR/PWR_STANDBY/Inc/stm32c0xx_conf.h         HAL Configuration file
    - PWR/PWR_STANDBY/Inc/stm32c0xx_it.h           Header for stm32c0xx_it.c
    - PWR/PWR_STANDBY/Inc/main.h                   Header file for main.c
    - PWR/PWR_STANDBY/Src/system_stm32c0xx.c       STM32C0xx system clock configuration file
    - PWR/PWR_STANDBY/Src/stm32c0xx_it.c           Interrupt handlers
    - PWR/PWR_STANDBY/Src/main.c                   Main program
    - PWR/PWR_STANDBY/Src/stm32c0xx_hal_msp.c      HAL MSP module

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
 - Run the example
