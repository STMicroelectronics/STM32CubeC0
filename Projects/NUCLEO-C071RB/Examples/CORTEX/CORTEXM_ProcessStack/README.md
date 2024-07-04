## <b>CORTEXM_ProcessStack Example Description</b>

How to modify the Thread mode stack. Thread mode is entered on reset, and can be
entered as a result of an exception return.  

The associated program is used to:

1. Switch the Thread mode stack from Main stack to Process stack

2. Generate ISR (SVC) to confirm Stack pointer used under exception is Main Stack

3. Returning to main(), check is performed on current Stack to show cortex has switched back to Process
automatically.
In case of error, LED1 remains off. In case of success, LED1 is turned on.

To monitor the stack used a set of variables is available within the program. It is also
possible to use the 'Cortex register' window of the debugger.
 
#### <b>Notes</b>

1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
   based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
   a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
   than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
   To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
2. The application need to ensure that the SysTick time base is always set to 1 millisecond
   to have correct HAL operation.

### <b>Keywords</b>

System, Cortex, Process Stack, HCLK, Thread mode Stack, main stack, process stack, ISR, 

### <b>Directory contents</b>

  - CORTEX/CORTEXM_ProcessStack/Inc/stm32c0xx_hal_conf.h    HAL configuration file
  - CORTEX/CORTEXM_ProcessStack/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - CORTEX/CORTEXM_ProcessStack/Inc/main.h                  Header for main.c module
  - CORTEX/CORTEXM_ProcessStack/Src/stm32c0xx_it.c          Interrupt handlers
  - CORTEX/CORTEXM_ProcessStack/Src//stm32c0xx_hal_msp.c     HAL MSP file
  - CORTEX/CORTEXM_ProcessStack/Src/main.c                  Main program
  - CORTEX/CORTEXM_ProcessStack/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C071RBTx devices.
    
  - This example has been tested with NUCLEO-C071RB board and can be
    easily tailored to any other supported device and development board.

### <b>How to use it ?</b>


In order to make the program work, you must do the following :

- Open your preferred toolchain
- Rebuild all files and load your image into target memory
- Run the example
