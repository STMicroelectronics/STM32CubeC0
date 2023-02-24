## <b>USART_Communication_Tx_Init Example Description</b>

This example shows how to configure GPIO and USART peripherals to send characters
asynchronously to an HyperTerminal (PC) in Polling mode. If the transfer could not
be completed within the allocated time, a timeout allows to exit from the sequence
with a Timeout error code. This example is based on STM32C0xx USART LL API. Peripheral
initialization is done using LL unitary services functions for optimization purpose
(performance and size).

USART Peripheral is configured in asynchronous mode (115200 bauds, 8 data bit, 1 start bit, 1 stop bit, no parity).
No HW flow control is used.
GPIO associated to User push-button is linked with EXTI.
Virtual Com port feature of STLINK could be used for UART communication between board and PC.

Example execution:

On press on push button , first character of buffer to be transmitted is written into USART Transmit Data Register (TDR)
Program then starts polling on USART TXE flag before sending next character.
On last character, program polls on TC flag to ensure transmit of last character is completed.

At completion of Tx Buffer sending, LED4 is turned On.

In case of errors, LED4 is blinking (1sec period).

Program is written so that, any new press on User push-button will lead to new transmission of complete buffer.

### <b>Keywords</b>

Connectivity, UART/USART, Asynchronous, RS-232, baud rate, Polling, HyperTerminal, Transmitter

### <b>Directory contents</b>

  - USART/USART_Communication_Tx_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - USART/USART_Communication_Tx_Init/Inc/main.h                  Header for main.c module
  - USART/USART_Communication_Tx_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - USART/USART_Communication_Tx_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - USART/USART_Communication_Tx_Init/Src/main.c                  Main program
  - USART/USART_Communication_Tx_Init/Src/system_stm32c0xx.c      STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C031C6 Set-up :

    Connect USART1 TX/RX to respectively RX and TX pins of PC UART (could be done through a USB to UART adapter) :

    - Connect STM32 MCU board USART1 TX pin (GPIO PA.09 connected to pin 21 in CN10)
      to PC COM port RX signal
    - Connect STM32 MCU board USART1 RX pin (GPIO PA.10 connected to pin 33 in CN10)
      to PC COM port TX signal
    - Connect STM32 MCU board GND to PC COM port GND signal

  - Launch serial communication SW on PC (as HyperTerminal or TeraTerm) with proper configuration
    (115200 bauds, 8 bits data, 1 stop bit, no parity, no HW flow control).

  - Launch the program. Press on User push button on board to initiate data transfer.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example