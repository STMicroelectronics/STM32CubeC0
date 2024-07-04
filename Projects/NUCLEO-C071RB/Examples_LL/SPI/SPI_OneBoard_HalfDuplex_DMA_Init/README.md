## <b>SPI_OneBoard_HalfDuplex_DMA_Init SPI Example Description</b>

Configuration of GPIO and SPI peripherals to transmit 
bytes from an SPI Master device to an SPI Slave device in DMA mode. This example
is based on the STM32C0xx SPI LL API. The peripheral initialization uses the 
LL initialization function to demonstrate LL init usage.

This example works with only one NUCLEO-C071RB.

SPI1 Peripheral is configured in Master mode Half-Duplex Tx.
SPI2 Peripheral is configured in Slave mode Half-Duplex Rx.
GPIO associated to User push-button is linked with EXTI. 

Example execution:

LED1 is blinking Fast (200ms) and wait User push-button action.
Press User push-button on BOARD start a Half-Duplex communication through DMA.
On MASTER side (SPI1), Clock will be generated on SCK line, Transmission done on MOSI Line.
On SLAVE side (SPI2) reception is done through the MISO Line.

LED1 is On if data is well received.

In case of errors, LED1 is blinking Slowly (1s).

### <b>Keywords</b>

Connectivity, SPI, Half-duplex, Transmission, Reception, Master, Slave, MISO, MOSI, DMA

### <b>Directory contents</b>

	- SPI/SPI_OneBoard_HalfDuplex_DMA_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
	- SPI/SPI_OneBoard_HalfDuplex_DMA_Init/Inc/main.h                  Header for main.c module
	- SPI/SPI_OneBoard_HalfDuplex_DMA_Init/Inc/stm32_assert.h          Template file to include assert_failed function
	- SPI/SPI_OneBoard_HalfDuplex_DMA_Init/Src/stm32c0xx_it.c          Interrupt handlers
	- SPI/SPI_OneBoard_HalfDuplex_DMA_Init/Src/main.c                  Main program
	- SPI/SPI_OneBoard_HalfDuplex_DMA_Init/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on NUCLEO-C071RB devices.

  - This example has been tested with NUCLEO-C071RB board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C071RB Set-up:
  
    - Connect Master SCK  PA1 to Slave SCK  PA0
    - Connect Master MOSI PA7 to Slave MISO PB6

Relation with Board connector:

	PA1 is connected to pin 2 of CN8 connector
	PA7 is connected to pin 4 of CN5 connector
	PA0 is connected to pin 1 of CN8 connector
	PB6 is connected to pin 2 of CN9 connector

### <b>How to use it ?</b> 

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

