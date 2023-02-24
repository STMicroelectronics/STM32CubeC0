## <b>SPI_FullDuplex_ComPolling_Master Example Description</b>

Data buffer transmission/reception between two boards via SPI using Polling mode.

       Board: NUCLEO-C031C6 (embeds a STM32C031C6 device)
       - CLK Pin: PB3 (CN9, pin 4)
       - MISO Pin: PB4 (CN9, pin 6)
       - MOSI Pin: PB5 (CN9, pin 7)

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 48 MHz.

The SPI peripheral configuration is ensured by the HAL_SPI_Init() function.
This later is calling the HAL_SPI_MspInit()function which core is implementing
the configuration of the needed SPI resources according to the used hardware (CLOCK &
GPIO). You may update this function to change SPI configuration.
The Full-Duplex SPI transfer (16bit) is done using LL Driver functions
LL_SPI_TransmitData16 and LL_SPI_ReceiveData16.

Example execution:

First step, press the User push-button (User push-button), this action initiates a Full-Duplex transfer
between Master and Slave.

After end of transfer, aRxBuffer and aTxBuffer are compared through Buffercmp() in order to
check buffers correctness.

STM32 board LED can be used to monitor the transfer status:

 - LED4 toggles quickly on master board waiting User push-button to be pressed.
 - LED4 turns ON if transmission/reception is complete and OK.
 - LED4 toggles slowly when there is a timeout or an error in transmission/reception process.   

#### <b>Notes</b>

 1. You need to perform a reset on Slave board, then perform it on Master board
    to have the correct behaviour of this example.

 2. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 3. The application need to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Connectivity, SPI, Full-duplex, Transmission, Reception, Master, MISO, MOSI, Polling

### <b>Directory contents</b>

  - SPI/SPI_FullDuplex_ComPolling_Master/Inc/stm32c0xx_hal_conf.h    HAL configuration file
  - SPI/SPI_FullDuplex_ComPolling_Master/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - SPI/SPI_FullDuplex_ComPolling_Master/Inc/main.h                  Header for main.c module
  - SPI/SPI_FullDuplex_ComPolling_Master/Src/stm32c0xx_it.c          Interrupt handlers
  - SPI/SPI_FullDuplex_ComPolling_Master/Src/main.c                  Main program
  - SPI/SPI_FullDuplex_ComPolling_Master/Src/system_stm32c0xx.c      stm32c0xx system source file
  - SPI/SPI_FullDuplex_ComPolling_Master/Src/stm32c0xx_hal_msp.c     HAL MSP file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - Take care to cable connection between Master and Slave Board:
    Cable shall be smaller than 5 cm and rigid if possible.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C031C6 Set-up

    - Connect Master board PB3 (CN9, pin 4) to Slave Board PB3 (CN9, pin 4)
    - Connect Master board PB4 (CN9, pin 6) to Slave Board PB4 (CN9, pin 6)
    - Connect Master board PB5 (CN9, pin 7) to Slave Board PB5 (CN9, pin 7)
    - Connect Master board GND to Slave Board GND

### <b>How to use it ?</b>

In order to make the program work, you must do the following:

 - Open your preferred toolchain
 - Rebuild all files (master project) and load your image into target memory
    o Load the project in Master Board
 - Rebuild all files (slave project) and load your image into target memory
    o Load the project in Slave Board
 - Run the example