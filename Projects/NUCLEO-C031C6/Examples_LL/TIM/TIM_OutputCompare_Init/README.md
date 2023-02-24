## <b>TIM_OutputCompare_Init Example Description</b>

Configuration of the TIM peripheral to generate an output 
waveform in different output compare modes. This example is based on the 
STM32C0xx TIM LL API. The peripheral initialization uses 
LL unitary service functions for optimization purposes (performance and size).

In this example TIM3 input clock (TIM3CLK) frequency is set to APB clock (PCLK),
since APB pre-scaler is equal to 1.

    TIM3CLK = PCLK
    PCLK = HCLK
    => TIM3CLK = HCLK = SystemCoreClock (48 Mhz)

To set the TIM3 counter clock frequency to 10 KHz, the pre-scaler (PSC) is
calculated as follows:

    PSC = (TIM3CLK / TIM3 counter clock) - 1
    PSC = (SystemCoreClock /10 KHz) - 1

SystemCoreClock is set to 48 MHz for STM32C0xx Devices.

Auto-reload (ARR) is calculated to get a time base period of 100 ms,
meaning a time base frequency of 10 Hz.

    ARR = (TIM3 counter clock / time base frequency) - 1
    ARR = (TIM3 counter clock / 10) - 1

The capture/compare register (CCR1) of the output channel is set to half the
auto-reload value. Therefore the timer output compare delay is 50 ms.
Generally speaking this delay is calculated as follows:

    CC1_delay = TIM3 counter clock / CCR1

The timer output channel must be connected to PA6 on board NUCLEO-C031C6.
Thus TIM3_CH1 status (on/off) mirrors the timer output level (active v.s. inactive).

User push-button can be used to change the output compare mode:

  - When the output channel is configured in output compare toggle:  TIM3_CH1 
    TOGGLES when the counter (CNT) matches the capture/compare register (CCR1).
  - When the output channel is configured in output compare active:  TIM3_CH1 
    switched ON when the counter (CNT) matches the capture/compare register
    (CCR1).
  - When the output channel is configured in output compare inactive:  TIM3_CH1 
    switched OFF when the counter (CNT) matches the capture/compare register
    (CCR1).
    
Initially the output channel is configured in output compare toggle mode.

### <b>Keywords</b>

Timers, TIM, Output, signals, Output compare toggle, PWM, Oscilloscope

### <b>Directory contents</b>

  - TIM/TIM_OutputCompare_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - TIM/TIM_OutputCompare_Init/Inc/main.h                  Header for main.c module
  - TIM/TIM_OutputCompare_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - TIM/TIM_OutputCompare_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - TIM/TIM_OutputCompare_Init/Src/main.c                  Main program
  - TIM/TIM_OutputCompare_Init/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.
  - NUCLEO-C031C6 Set-up:
      - TIM3_CH1  PA6: connected to pin 13 of CN10 connector 

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example