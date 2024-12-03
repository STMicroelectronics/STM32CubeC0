## <b>DMA_FLASHToRAM Example Description</b>

This example describes how to use DMA to transfer a word data buffer from Flash memory to embedded
SRAM through the HAL API.

At the beginning of the main program, the HAL_Init() function is called to reset
all the peripherals and initialize the systick used as 1ms HAL timebase.

Then the *SystemClock_Config()* function is used to configure the system clock (SYSCLK) to run at 48 MHz.

DMA1_Channel1 is configured to transfer the contents of a 32-word data
buffer stored in Flash memory to the reception buffer declared in RAM.

The start of transfer is triggered by software. DMA1_Channel1 memory-to-memory
transfer is enabled. Source and destination addresses incrementing is also enabled.

The transfer is started by setting the channel enable bit for DMA1_Channel1.

At the end of the transfer a Transfer Complete interrupt is generated since it
is enabled and the callback function (customized by user) is called.

NUCLEO-C051C8 board's LEDs can be used to monitor the transfer status:

 - LED4 is ON when the transfer is complete (into the Transfer Complete interrupt
   routine).
 - LED4 is toggled with a period of 1000 ms when an Error_Handler() is called

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

System, DMA, Data Transfer, Memory to memory, Stream, Flash, RAM

### <b>Directory contents</b>

File | Description
 --- | ---
DMA/DMA_FLASHToRAM/Inc/stm32c0xx_hal_conf.h      | HAL configuration file
DMA/DMA_FLASHToRAM/Inc/stm32c0xx_it.h            | Header for stm32c0xx_it.c
DMA/DMA_FLASHToRAM/Inc/main.h                      | Header for main.c module
DMA/DMA_FLASHToRAM/Src/stm32c0xx_it.c            | Interrupt handlers
DMA/DMA_FLASHToRAM/Src/main.c                      | Main program
DMA/DMA_FLASHToRAM/Src/stm32c0xx_hal_msp.c       | HAL MSP module
DMA/DMA_FLASHToRAM/Src/system_stm32c0xx.c        | stm32c0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C051C8Tx devices.

  - This example has been tested with STMicroelectronics NUCLEO-C051C8
    board and can be easily tailored to any other supported device
    and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
