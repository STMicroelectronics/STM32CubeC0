### <b>TIM_Prescaler_Update Example Description</b>

Use of a timer peripheral to change the prescaler value on the fly.
This example is based on the STM32C0xx TIM LL API. The peripheral initialization uses 
LL unitary service functions for optimization purposes (performance and size).

At the beginning of the main program the SystemClock_Config() function is called
to configure the maximum system clock frequency (48 MHz).

In this example TIM1 input clock (TIM1CLK) frequency is set to the APB clock (PCLK),
since APB pre-scaler is equal to 1.

  - TIM1CLK = PCLK  
  - PCLK = HCLK  
  - TIM1CLK = HCLK = SystemCoreClock/AHB_DIV = 48 MHz/1 = 48 MHz

To set the following TIM1 counter clock frequencies (4kHz, 2kHz, 1kHz), the prescaler (PSC)
values are calculated as follows:

  - PSC = (TIM1CLK / TIM1 counter clock) - 1

The prescaler values are stored in a table:

  - 11999 (4kHz)  
  - 23999 (2kHz)  
  - 47999 (1kHz)

Auto-reload (ARR) value is set to 999 (counting start from 0) to obtain a timebase period
1000 times longer than the counter clock period.

 - 4Hz  
 - 2Hz  
 - 1Hz

User push-button can be used to modify the timebase period from 500ms to 1s, then 2s.
To do so, every time User push-button is pressed, the prescaler register (PSC) is updated.  
In up-counting, update event is generated at each counter overflow (when the counter
reaches the auto-reload value).

The LED1 is toggled every TIM update event, so the LED1 frequency is half the timebase frequency.

Depending the user's button push, the LED blinks in the following order:

  - default:  2Hz    (500ms)  
  - 1st push: 1Hz    (1s)  
  - 2nd push: 500mHz (2s)  
  - 3rd push: 2Hz    (500ms)  
  - ...

STM32 board LED1 can be used to monitor the example.  
There is also a possibility to display the LED1 pin (PA.05) signal on an oscilloscope.

### <b>Keywords</b>

Timer, Timebase, Prescaler, Update, Interrupt, LED

### <b>Directory contents</b>

  - TIM/TIM_Prescaler_Update/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - TIM/TIM_Prescaler_Update/Inc/main.h                  Header for main.c module
  - TIM/TIM_Prescaler_Update/Inc/stm32_assert.h          Template file to include assert_failed function
  - TIM/TIM_Prescaler_Update/Src/stm32c0xx_it.c          Interrupt handlers
  - TIM/TIM_Prescaler_Update/Src/main.c                  Main program
  - TIM/TIM_Prescaler_Update/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RCTx devices.

  - This example has been tested with STMicroelectronics NUCLEO-C092RC
    boards and can be easily tailored to any other supported device
    and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example