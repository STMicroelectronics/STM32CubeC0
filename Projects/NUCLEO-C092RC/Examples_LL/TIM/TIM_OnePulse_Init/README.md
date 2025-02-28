## <b>TIM_OnePulse_Init Example Description</b>

Configuration of a timer to generate a positive pulse in
Output Compare mode with a length of tPULSE and after a delay of tDELAY. This example
is based on the STM32C0xx TIM LL API. The peripheral initialization uses
LL initialization function to demonstrate LL Init.

The pulse is generated on OC1.

This example uses 2 timer instances:

  - TIM1 generates a positive pulse of 50 us after a delay of 50 us. User push-button
    is used to start TIM1 counter.
	
                                              ___
                                             |   |
    User push-button ________________________|   |________________________________
                                                            ___________
                                                           |           |
    OC1              ______________________________________|           |________
    (TIM1_CH1)                                <---50 us---><---50 us--->
                                                |            |_ uwMeasuredPulseLength
                                                |_ uwMeasuredDelay

  TIM1_CH1 delay and pulse length are measured every time a pulse is generated.
  Both can be observed through the debugger by monitoring the variables uwMeasuredDelay and
  uwMeasuredPulseLength respectively.

  - TIM2 generates a positive pulse of 3 s after a delay of 2 s. TIM2 counter start
    is controlled through the slave mode controller. TI2FP2 signals is selected as
    trigger input meaning that TIM2 counter starts when a rising edge is detected on
    TI2FP2.
	
                                  ___
                                 |   |
    TI2 _________________________|   |_________________________________________
    (TIM2_CH2)
                                               ___________________________
                                              |                           |
    OC1 ______________________________________|                           |____
    (TIM2_CH1)                   <-----2s-----><----------3 s------------->



Both TIM1 and TIM2 are configured to generate a single pulse (timer counter
stops automatically at the next update event (UEV).

Connecting TIM1 OC1 to TIM2 TI2 allows to trigger TIM2 counter by pressing
the User push-button.

### <b>Keywords</b>

Timers, Output, signals, One Pulse, PWM, Oscilloscope, External signal, Autoreload, Waveform

### <b>Directory contents</b>

    - TIM/TIM_OnePulse_Init/Inc/stm32c0xx_it.h         Interrupt handlers header file
    - TIM/TIM_OnePulse_Init/Inc/main.h                  Header for main.c module
    - TIM/TIM_OnePulse_Init/Inc/stm32_assert.h          Template file to include assert_failed function
    - TIM/TIM_OnePulse_Init/Src/stm32c0xx_it.c         Interrupt handlers
    - TIM/TIM_OnePulse_Init/Src/main.c                  Main program
    - TIM/TIM_OnePulse_Init/Src/system_stm32c0xx.c     STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RCTx devices.

  - This example has been tested with NUCLEO-C092RC board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C092RC Set-up:
      - TIM1_CH1  PA.08: pin 8 in CN9 connector
      - TIM2_CH1  PA.05: pin 6 of CN5 connector
      - TIM2_CH2  PA.01: connected to pin 2 of CN8 connector
	  - User push-button PC.13: pin 23 in CN7 connector

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


