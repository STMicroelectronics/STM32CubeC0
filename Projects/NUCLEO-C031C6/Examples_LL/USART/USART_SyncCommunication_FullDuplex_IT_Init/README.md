## <b>USART_SyncCommunication_FullDuplex_IT_Init Example Description</b>

Configuration of GPIO, USART, DMA and SPI peripherals to transmit 
bytes between a USART and an SPI (in slave mode) in Interrupt mode. This example is based on the STM32C0xx USART LL API 
(the SPI uses the DMA to receive/transmit characters sent from/received by the USART). The peripheral 
initialization uses LL unitary service functions for optimization purposes (performance and size).

This example works with only one NUCLEO-C031C6.

USART1 Peripheral is acts as Master using IT.
SPI1 Peripheral is configured in Slave mode using DMA.
GPIO associated to User push-button is linked with EXTI.

Example execution:

LED4 is blinking Fast (200ms) and wait User push-button action.
Press User push-button on BOARD start a Full-Duplex communication from USART using IT.
On USART1 side, Clock will be generated on SCK line, Transmission done on TX, reception on RX.
On SPI1 side, reception is done through the MOSI Line, transmission on MISO line.

At end of transmission, both received buffers are compared to expected ones.

In case of both transfers successfully completed, LED4 is turned on.

In case of errors, LED4 is blinking Slowly (1s).

### <b>Keywords</b>

Connectivity, UART/USART, Synchronous, Interrupt, SPI interface, Receiver, Transmitter, full-duplex

### <b>Directory contents</b>

  - USART/USART_SyncCommunication_FullDuplex_IT_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - USART/USART_SyncCommunication_FullDuplex_IT_Init/Inc/main.h                  Header for main.c module
  - USART/USART_SyncCommunication_FullDuplex_IT_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - USART/USART_SyncCommunication_FullDuplex_IT_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - USART/USART_SyncCommunication_FullDuplex_IT_Init/Src/main.c                  Main program
  - USART/USART_SyncCommunication_FullDuplex_IT_Init/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C031C6 Set-up :

    - Connect USART1 SCK PA.12 to Slave SPI1 SCK PB.03
    - Connect USART1 TX PA.09 to Slave SPI1 MOSI PB.05
    - Connect USART1 RX PA.10 to Slave SPI1 MISO PB.04

Board connector:

 -  PA.12 :   connected to pin 38 of CN7 connector
 -  PA.09 :   connected to pin 21 of CN10 connector
 -  PA.10 :   connected to pin 33 of CN10 connector
 -  PB.03 :   connected to pin 31 of CN10 connector
 -  PB.05 :   connected to pin 25 of CN10 connector
 -  PB.04 :   connected to pin 27 of CN10 connector

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example