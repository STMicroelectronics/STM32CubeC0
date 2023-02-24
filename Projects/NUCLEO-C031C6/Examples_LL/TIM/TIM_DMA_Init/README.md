## <b>TIM_DMA_Init Example Description</b>

Use of the DMA with a timer update request 
to transfer data from memory to Timer Capture Compare Register 3 (TIMx_CCR3). This 
example is based on the STM32C0xx TIM LL API. The peripheral initialization 
uses LL unitary service functions for optimization purposes (performance and size).

The following configuration values are used in this example:

  - TIM1CLK = SystemClock
  - Counter repetition = 3 
  - Prescaler = 0 
  - TIM1 counter clock = SystemClock
  - SystemCoreClock is set to 48 MHz for STM32C0xx Devices.

The objective is to configure TIM1 channel 3 to generate PWM edge aligned 
signal with a frequency equal to 17.57 KHz, and a variable duty cycle that
is changed by the DMA after a specific number of Update DMA request.

The number of this repetitive requests is defined by the TIM1 Repetition counter,
each 4 Update Requests, the TIM1 Channel 3 Duty Cycle changes to the next new 
value defined by the aCCValue buffer.

The PWM waveform can be displayed using an oscilloscope.

Whenever a DMA transfer fails LED4 flashes with a frequency of 1 Hz.
 
#### <b>Notes</b>

 - PWM signal frequency value mentioned above is theoretical (obtained when
   the system clock frequency is exactly 48 MHz). Since the generated system
   clock frequency may vary from one board to another observed PWM signal
   frequency might be slightly different.

### <b>Keywords</b>

Timers, DMA, PWM, Frequency, Duty Cycle, Waveform, Oscilloscope, Output, Signal

### <b>Directory contents</b>

  - TIM/TIM_DMA_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - TIM/TIM_DMA_Init/Inc/main.h                  Header for main.c module
  - TIM/TIM_DMA_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - TIM/TIM_DMA_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - TIM/TIM_DMA_Init/Src/main.c                  Main program
  - TIM/TIM_DMA_Init/Src/system_stm32c0xx.c      STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C031C6 Set-up
    - Connect the TIM1 pins to an oscilloscope to monitor the different waveforms:

      - TIM1_CH3  PA.10: connected to pin 33 of CN10 connector 

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example