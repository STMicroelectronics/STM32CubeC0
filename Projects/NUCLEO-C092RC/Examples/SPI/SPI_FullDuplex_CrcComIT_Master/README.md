## <b>SPI_FullDuplex_CrcComIT_Master Example Description</b>

Data buffer transmission/reception with CRC between two boards via SPI using IT.

	Board: NUCLEO-C092RC (embeds a STM32C092RC device)
	CLK Pin: PA.01 (pin 2 on CN8 connector)
	MISO Pin: PA.06 (D12 pin 5 on CN5 connector)
	MOSI Pin: PA.07 (D11 pin 4 on CN5 connector)

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 48 MHz.

The SPI peripheral configuration is ensured by the HAL_SPI_Init() function.
This later is calling the HAL_SPI_MspInit()function which core is implementing
the configuration of the needed SPI resources according to the used hardware (CLOCK,
GPIO, DMA and NVIC). You may update this function to change SPI configuration.

The SPI communication is then initiated.
The HAL_SPI_TransmitReceive_DMA() function allows the reception and the
transmission of a predefined data buffer at the same time (Full Duplex Mode).

If the Master board is used, the project SPI_FullDuplex_CrcComIT_Master must be used.
If the Slave board is used, the project SPI_FullDuplex_CrcComIT_Slave must be used.

For this example the aTxBuffer is predefined and the aRxBuffer size is same as aTxBuffer.

In a first step after the user press the User push-button, SPI Master starts the
communication by sending aTxBuffer and receiving aRxBuffer through
HAL_SPI_TransmitReceive_DMA(), at the same time SPI Slave transmits aTxBuffer
and receives aRxBuffer through HAL_SPI_TransmitReceive_DMA().
The callback functions (HAL_SPI_TxRxCpltCallback and HAL_SPI_ErrorCallbackand) update
the variable wTransferState used in the main function to check the transfer status.
Finally, aRxBuffer and aTxBuffer are compared through Buffercmp() in order to
check buffers correctness.

STM32 board's LEDs can be used to monitor the transfer status:

 - LED1 turns ON when the transmission/reception process is complete.
 - LED2 toggle when there is an error in transmission/reception process.

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

Connectivity, SPI, CRC, Full-duplex, Interrupt, Transmission, Reception, Master, Slave, MISO, MOSI,

### <b>Directory contents</b>

  - SPI/SPI_FullDuplex_CrcComIT_Master/Inc/stm32c0xx_hal_conf.h   HAL configuration file
  - SPI/SPI_FullDuplex_CrcComIT_Master/Inc/stm32c0xx_it.h         Interrupt handlers header file
  - SPI/SPI_FullDuplex_CrcComIT_Master/Inc/main.h                       Header for main.c module
  - SPI/SPI_FullDuplex_CrcComIT_Master/Src/stm32c0xx_it.c         Interrupt handlers
  - SPI/SPI_FullDuplex_CrcComIT_Master/Src/main.c                       Main program
  - SPI/SPI_FullDuplex_CrcComIT_Master/Src/system_stm32c0xx.c     stm32c0xx system source file
  - SPI/SPI_FullDuplex_CrcComIT_Master/Src/stm32c0xx_hal_msp.c    HAL MSP file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RCTx devices.

  - This example has been tested with NUCLEO-C092RC board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C092RC Set-up
    - Connect Master board PA.01 (pin 2 on CN8 connector) to Slave Board PA.01 (pin 2 on CN8 connector)
    - Connect Master board PA.06 (D12 pin 5 on CN5 connector) to Slave Board PA.06 (D12 pin 5 on CN5 connector)
    - Connect Master board PA.07 (D11 pin 4 on CN5 connector) to Slave Board PA.07 (D11 pin 4 on CN5 connector)
    - Connect Master board GND  to Slave Board GND

### <b>How to use it ?</b>

In order to make the program work, you must do the following:

 - Open your preferred toolchain
 - Rebuild all files (master project) and load your image into target memory
    - Load the project in Master Board
 - Rebuild all files (slave project) and load your image into target memory
    - Load the project in Slave Board
 - Run the example



