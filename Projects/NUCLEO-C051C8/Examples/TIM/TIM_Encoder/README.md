## <b>TIM_Encoder Example Description</b>       

This example shows how to configure the TIM1 peripheral in encoder mode to
determinate the rotation direction.
               
     -------------                               -------------
    |             |CH1:PA6          CH1:PA8     |             |
    |             |---------------------------->|             |
    |    TIM3     |                             |    TIM1     |
    |             |CH2:PB5          CH2:PA9     |             |
    | Quadrature  |---------------------------->| Quadrature  |
    | encoder     |                             | encoder     |
    | emulator    |                             | interface   |
    |             |                             |             |
    |             |                             |             |
    |             |                             |-------------|     -----------
    |             |                             |  Direction  |--> |uwDirection|     
     -------------                               -------------      -----------
               Encoder interface example description
               
               


  To emulate a quadrature encoder, TIM3 is configured in toggle mode to generate
2 quadrature signals on (PA6 and PB5) at 10KHz. Each 1s, signals change phase
(+90�/-90�) to emulate a Forward/Backward rotation.  

  TIM1 is configured in encoder mode interface, counting on TI1 and TI2.
  The counting direction corresponds to the rotation direction of the connected 
sensor (emulated by TIM3 signals).
Rotation direction can be monitored by putting "uwDirection" variable in the 
Live Watch window.
  When uwDirection = 0, and according to the "Counting direction versus encoder
signals" table, rotation direction is Forward.
  When uwDirection = 1, and according to the "Counting direction versus encoder
signals" table, rotation direction is Backward.

#### <b>Notes</b> 

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
 2. The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

### <b>Keywords</b>

Timer, Encoder mode, Master, Slave, Duty Cycle, rotation direction, Waveform, Oscilloscope, Output, Signal

### <b>Directory contents</b>

  - TIM/TIM_Encoder/Inc/stm32c0xx_hal_conf.h    HAL configuration file
  - TIM/TIM_Encoder/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - TIM/TIM_Encoder/Inc/main.h                  Header for main.c module  
  - TIM/TIM_Encoder/Src/stm32c0xx_it.c          Interrupt handlers
  - TIM/TIM_Encoder/Src/main.c                  Main program
  - TIM/TIM_Encoder/Src/stm32c0xx_hal_msp.c     HAL MSP file
  - TIM/TIM_Encoder/Src/system_stm32c0xx.c      STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C051C8Tx devices.
    
  - This example has been tested with NUCLEO-C051C8 board and can be
    easily tailored to any other supported device and development board.      

  - NUCLEO-C051C8 Set-up
    - Connect PA6 (pin 5 in CN5 connector) (TIM3_Channel 1) to PA8 (pin 24 in CN10 connector) (TIM1_Channel 1).
    - Connect PB5 (pin 7 in CN9 connector) (TIM3_Channel 2) to PA9 (pin 1 in CN5 connector) (TIM1_Channel 2).
    - Put uwDirection in the debugger live watch to detect the rotation direction
      change.

 
### <b>How to use it ?</b>

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files: Project->Rebuild all
 - Load project image: Project->Download and Debug
 - Run program: Debug->Go(F5) 
