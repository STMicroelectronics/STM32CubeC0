## <b>SPI_FullDuplex_Loopback_ComDMA Example Description</b>

Data buffer transmission/reception with a single board via SPI using DMA.

       Board: NUCLEO-C092RC (embeds a STM32C092RC device)
       - CLK Pin: PA1 (CN7, pin 30)
       - MISO Pin: PA6 (CN10, pin 13)
       - MOSI Pin: PA7 (CN10, pin 15)

HAL architecture allows user to easily change code to move to Polling or IT mode.

The particularity of this SPI example is that it uses a single board and a single
SPI instance to perform a transfer. Since MOSI pin is connected to MISO pin and SPI is
configured in Master mode, SPI is able to send a buffer to itself. This example is useful
to validate your own GPIO configuration on MISO and MOSI lines.
As the SPI IP is clocked by its input frequency, the output CLK pin is left floating.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 48 MHz.

The SPI peripheral configuration is ensured by the HAL_SPI_Init() function.
This later is calling the HAL_SPI_MspInit() function which implements
the configuration of the needed SPI resources according to the used hardware (CLOCK, 
GPIO, DMA and NVIC). You may update this function to change SPI configuration.

The SPI communication is then initiated.
The HAL_SPI_TransmitReceive_DMA() function allows the reception and the 
transmission of a predefined data buffer at the same time (Full Duplex Mode). 

For this example the aTxBuffer is predefined and the aRxBuffer size is same as aTxBuffer.

In a first step after the user press the User push-button, SPI starts the 
communication by sending aTxBuffer and receiving aRxBuffer through 
HAL_SPI_TransmitReceive_DMA(), at the same time SPI Slave transmits aTxBuffer 
and receives aRxBuffer through HAL_SPI_TransmitReceive_DMA(). 
The callback functions (HAL_SPI_TxRxCpltCallback and HAL_SPI_ErrorCallback) update 
the variable wTransferState used in the main function to check the transfer status.
Finally, aRxBuffer and aTxBuffer are compared through Buffercmp() in order to 
check buffers correctness.

STM32 board's LEDs can be used to monitor the transfer status:

 - LED1 toggles quickly on board waiting User push-button to be pressed.
 - LED1 turns ON if transmission/reception is complete and OK.
 - LED1 toggles slowly when there is a timeout or an error in transmission/reception process.   

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application need to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Connectivity, SPI, Full-duplex, Interrupt, Transmission, Reception, MISO, MOSI, DMA

### <b>Directory contents</b>

  - SPI/SPI_FullDuplex_Loopback_ComDMA/Inc/stm32c0xx_hal_conf.h   HAL configuration file
  - SPI/SPI_FullDuplex_Loopback_ComDMA/Inc/stm32c0xx_it.h         Interrupt handlers header file
  - SPI/SPI_FullDuplex_Loopback_ComDMA/Inc/main.h                 Header for main.c module  
  - SPI/SPI_FullDuplex_Loopback_ComDMA/Src/stm32c0xx_it.c         Interrupt handlers
  - SPI/SPI_FullDuplex_Loopback_ComDMA/Src/main.c                 Main program
  - SPI/SPI_FullDuplex_Loopback_ComDMA/Src/system_stm32c0xx.c     stm32c0xx system source file
  - SPI/SPI_FullDuplex_Loopback_ComDMA/Src/stm32c0xx_hal_msp.c    HAL MSP file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RCx devices.

  - This example has been tested with NUCLEO-C092RC board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C092RC Set-up

    - Connect MISO Pin (PA6 :(CN10, pin 13)) to MOSI Pin (PA7 :(CN10, pin 15))

### <b>How to use it ?</b>

In order to make the program work, you must do the following:

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
    o Load the project in Board
 - Run the example