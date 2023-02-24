## <b>SPI_TwoBoards_FullDuplex_IT_Slave_Init Example Description</b>

Data buffer transmission and receptionvia SPI using Interrupt mode. This
example is based on the STM32C0xx SPI LL API. The peripheral
initialization uses LL unitary service functions for optimization purposes (performance and size).

The communication is done with 2 boards through SPI.

This example shows how to configure GPIO and SPI peripherals
to use a Full-Duplex communication using IT mode through the STM32C0xx COM_INSTANCE1_TYPE LL API.

This example is split in two projects, Master board and Slave board:

- Master Board :

  - SPI1 Peripheral is configured in Master mode.
  - SPI1_IRQn activated.
  - RXNE and TXE Interrupts SPI peripheral activated.
  - GPIO associated to User push-button is linked with EXTI.

- Slave Board :
  - SPI1 Peripheral is configured in Slave mode.
  - SPI1_IRQn activated.
  - RXNE and TXE Interrupts SPI peripheral activated.


Example execution:

On BOARD MASTER, LED4 is blinking Fast (200ms) and wait User push-button action.
Press User push-button on BOARD MASTER start a Full-Duplex communication through IT.
On MASTER side, Clock will be generated on SCK line, Transmission(MOSI Line) and reception (MISO Line)
will be done at the same time.
SLAVE SPI will received  the Clock (SCK Line), so Transmission(MISO Line) and reception (MOSI Line) will be done also.

LED4 is On on both boards if data is well received.

In case of errors, LED4 is blinking Slowly (1s).

#### <b>Notes</b>
 1. You need to perform a reset on Master board, then perform it on Slave board
    to have the correct behaviour of this example.

### <b>Keywords</b>

Connectivity, SPI, Full-duplex, Transmission, Reception, Slave, MISO, MOSI, Interrupt

### <b>Directory contents</b>

  - SPI/SPI_TwoBoards_FullDuplex_IT_Slave_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - SPI/SPI_TwoBoards_FullDuplex_IT_Slave_Init/Inc/main.h                  Header for main.c module
  - SPI/SPI_TwoBoards_FullDuplex_IT_Slave_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - SPI/SPI_TwoBoards_FullDuplex_IT_Slave_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - SPI/SPI_TwoBoards_FullDuplex_IT_Slave_Init/Src/main.c                  Main program
  - SPI/SPI_TwoBoards_FullDuplex_IT_Slave_Init/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C031C6 Set-up
    - Connect Master board PB3 to Slave Board PB3 (connected to pin 4 of CN9 connector)
    - Connect Master board PB4 to Slave Board PB4 (connected to pin 6 of CN9 connector)
    - Connect Master board PB5 to Slave Board PB5 (connected to pin 7 of CN9 connector)
    - Connect Master board GND to Slave Board GND

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
    o Load the Master project in Master Board
    o Load the Slave project in Slave Board
 - Run the example