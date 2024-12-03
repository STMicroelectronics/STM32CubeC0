## <b>FDCAN_Loopback Example Description</b>

This example describes how to configure the FDCAN peripheral to  operate in loopback mode.

At the beginning of the main program, the HAL_Init() function is called to reset
all the peripherals and initialize the systick used as 1ms HAL timebase.

Then the *SystemClock_Config()* function is used to configure the system clock (SYSCLK) to run at 48 MHz.

The example is divided into several steps:<br>

  - In the first step, the *HAL_FDCAN_Init()* function is called to configure the module in external loopback mode,  with a **Nominal Bit Rate of 1 MBit/s** and a **sampling point at 75%**.<br>
    Additionally, it has a **Data Bit Rate of 2 MBit/s** and a **sampling point at 75%**.<br>
    Reception filters are then configured with *HAL_FDCAN_ConfigFilter()*, to receive:<br>
      - messages with pre-defined standard ID to Rx FIFO 0<br>
      - messages with pre-defined extended ID to Rx FIFO 1<br>

    Then FDCAN module is started with *HAL_FDCAN_Start()*.<br>
  - In the second step, the following messages are sent:<br>
      - one standard ID message matching Rx FIFO 0 filter<br>
      - two extended ID messages matching Rx FIFO 1 filter<br>
  - In the third step, the application checks that the three messages were received and as expected.


The FDCAN peripheral configuration is ensured by the *HAL_FDCAN_Init()* function.
This later is calling the *HAL_FDCAN_MspInit()* function which core is implementing
the configuration of the needed FDCAN resources according to the used hardware (CLOCK, GPIO, NVIC and DMA).
User may update this function to change FDCAN configuration.


NUCLEO-C092RC's LEDs can be used to monitor the transfer status:

  - LED1 is ON when all three messages were successfully transmitted and received.
  - LED2 toggle slowly when there is an error in transmission/reception process.

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Connectivity, CAN/FDCAN, Loopback, Polling, CAN FIFO, CAN Filter

### <b>Directory contents</b>

File | Description
 --- | ---
FDCAN/FDCAN_Loopback/Inc/stm32c0xx_hal_conf.h   | HAL configuration file
FDCAN/FDCAN_Loopback/Inc/stm32c0xx_it.h         | Header for stm32c0xx_it.c
FDCAN/FDCAN_Loopback/Inc/main.h                 | Header for main.c module
FDCAN/FDCAN_Loopback/Src/stm32c0xx_it.c         | Interrupt handlers
FDCAN/FDCAN_Loopback/Src/main.c                 | Main program
FDCAN/FDCAN_Loopback/Src/stm32c0xx_hal_msp.c    | HAL MSP module
FDCAN/FDCAN_Loopback/Src/system_stm32c0xx.c     | stm32c0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RCTx devices.

  - This example has been tested with NUCLEO-C092RC board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C092RC Set-up:
    - None.
    

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

  - Open your preferred toolchain
  - Rebuild all files and load your image into target memory
  - Run the example
