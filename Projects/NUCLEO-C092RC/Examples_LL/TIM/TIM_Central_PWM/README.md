### <b>TIM_Central_PWM Example Description</b>

Use of a timer peripheral to generate 3 center aligned PWMs output signals.
The fourth channel can be used to trigger ADC conversions during the low period of the PWM signals.  
This example is based on the STM32C0xx TIM LL API. The peripheral initialization uses 
LL unitary service functions for optimization purposes (performance and size).

At the beginning of the main program the SystemClock_Config() function is called
to configure the maximum system clock frequency (48 MHz).

In this example TIM1 input clock (TIM1CLK) frequency is set to the APB clock (PCLK),
since APB pre-scaler is equal to 1.

  - TIM1CLK = PCLK  
  - PCLK = HCLK  
  - TIM1CLK = HCLK = SystemCoreClock/AHB_DIV = 48 MHz/1 = 48 MHz

To set the TIM1 counter clock frequency to 48 MHz, the pre-scaler (PSC) is kept at 0.

Auto-reload (ARR) is calculated to get a time base period of 100 us, meaning a time base
frequency of 10 kHz.  
As the counter counts up and down for 1 period, we have to take into account that
the period is twice the time of the ARR value, so the ARR must be divided by 2.

  - ARR = ((TIM1 counter clock / time base frequency)/2) - 1  
  - ARR = ((TIM1 counter clock / 10000)/2) - 1
  - ARR = 2400 - 1

Channels 1, 2 and 3 are set to PWM mode 1, but channel 4 is set to PWM mode 2
and is therefore out of phase with the others.

The capture/compare register (CCR1) of the output channel 1 is set to a quarter of
the auto-reload value meaning a duty cycle (DT) of 25%, the output channel 2 is set
to 50% DT and output channel 3 is set to 75% DT.

 - CCR1 = (0.25 * ARR) - 1 = 600 - 1
 - CCR2 = (0.50 * ARR) - 1 = 1200 - 1
 - CCR3 = (0.75 * ARR) - 1 = 1800 - 1

Channel 4 operates in PWM mode 2 with a 2% duty cycle. It is used as TRGO2 source to
shows how ADC conversions can be synchronized on given 3-phase PWM signals
(ADC related configuration isn't in the scope of the present example).

- CCR4 = (0.98 * ARR) - 1 = 2352 - 1

The following figure shows the expected result:

                   <---------------100us--------------->
                                  _________                             _________
      tim_oc1   :  ______________|         |___________________________|         |_____________
                                 <--25us-->
                             __________________                    __________________
      tim_oc2   :  _________|                  |__________________|                  |_________
                             <------50us------>
                        ____________________________          ____________________________
      tim_oc3   :  ____|                            |________|                            |____
                        <-----------75us----------->
                                                         _
      tim_oc4   :  _____________________________________| |____________________________________
                                                       <2us>

The generated PWM signals can be displayed using an oscilloscope.

#### <b>Notes</b>

 1. PWM signal frequency value mentioned above is theoretical (obtained when
    the system clock frequency is exactly 48 MHz). Since the generated system
    clock frequency may vary from one board to another observed PWM signal
    frequency might be slightly different.

 2. In PWM mode, preload mode is enabled for the auto-reload register and the
    capture/compare registers. Registers update is forced by software prior starting
    the PWM signals generation.

### <b>Keywords</b>

Timer, PWM, Center Aligned, Measure, Noise, Oscilloscope, Output, Signal

### <b>Directory contents</b>

  - TIM/TIM_Central_PWM/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - TIM/TIM_Central_PWM/Inc/main.h                  Header for main.c module
  - TIM/TIM_Central_PWM/Inc/stm32_assert.h          Template file to include assert_failed function
  - TIM/TIM_Central_PWM/Src/stm32c0xx_it.c          Interrupt handlers
  - TIM/TIM_Central_PWM/Src/main.c                  Main program
  - TIM/TIM_Central_PWM/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RCTx devices.

  - This example has been tested with STMicroelectronics NUCLEO-C092RC
    boards and can be easily tailored to any other supported device
    and development board.

  - NUCLEO-C092RC Set-up:
      - TIM1_CH1 (PA.0  PIN28 CN7)
      - TIM1_CH2 (PA.1  PIN30 CN7)
      - TIM1_CH3 (PA.10 PIN33 CN10)
      - TIM1_CH4 (PA.11 PIN14 CN10)

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example