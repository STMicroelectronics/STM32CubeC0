## <b>USART_Communication_Rx_IT_VCP_Init Example Description</b>

This example shows how to configure GPIO and USART peripheral for receiving characters
from HyperTerminal (PC) in Asynchronous mode using Interrupt mode. Peripheral initialization is done
using LL initialization function to demonstrate LL init usage.

USART Peripheral is configured in asynchronous mode (115200 bauds, 8 data bit, 1 start bit, 1 stop bit, no parity).
No HW flow control is used.
GPIO associated to User push-button is linked with EXTI.
USART RX Not Empty interrupt is enabled.
Virtual Com port feature of STLINK could be used for UART communication between board and PC.

Example execution:

When character is received on USART Rx line, a RXNE interrupt occurs.
USART IRQ Handler routine is then checking received character value.
On a specific value ('S' or 's'), LED4 is turned On.
Received character is echoed on Tx line.

On press on push button, LED4 is turned Off.

In case of errors, LED4 is blinking.

### <b>Keywords</b>

Connectivity, UART/USART, Asynchronous, RS-232, baud rate, Interrupt, HyperTerminal, Receiver, VCP

### <b>Directory contents</b>

  - USART/USART_Communication_Rx_IT_VCP_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - USART/USART_Communication_Rx_IT_VCP_Init/Inc/main.h                  Header for main.c module
  - USART/USART_Communication_Rx_IT_VCP_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - USART/USART_Communication_Rx_IT_VCP_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - USART/USART_Communication_Rx_IT_VCP_Init/Src/main.c                  Main program
  - USART/USART_Communication_Rx_IT_VCP_Init/Src/system_stm32c0xx.c      STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C031C6 Set-up :

    Please ensure that USART communication between the target MCU and ST-LINK MCU is properly enabled
    on HW board in order to support Virtual Com Port (Default HW SB configuration allows use of VCP)

    - Launch serial communication SW on PC (as HyperTerminal or TeraTerm) with proper configuration
      (115200 bauds, 8 bits data, 1 stop bit, no parity, no HW flow control).

    - Launch the program. Enter characters on PC communication SW side.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example