## <b>USART_WakeUpFromStop_Init Example Description</b>
  
Configuration of GPIO and USART1 peripherals to allow the characters received on USART_RX pin to wake up the MCU from low-power mode. 
This example is based on the STM32C0xx USART1 LL API. The peripheral 
initialization uses LL unitary service functions for optimization purposes (performance and size).

USART1 Peripheral is configured in asynchronous mode (9600 bauds, 8 data bit, 1 start bit, 1 stop bit, no parity).
No HW flow control is used.
USART1 Clock is based on HSI.

Example execution:

After startup from reset and system configuration, LED4 is blinking quickly during 3 sec,
then MCU  enters "Stop 0" mode (LED4 off).
On first  character reception by the USART1 from PC Com port (ex: using HyperTerminal)
after "Stop 0" Mode period, MCU wakes up from "Stop 0" Mode.
Received character value is checked :

- On a specific value ('S' or 's'), LED4 is turned On and program ends.
- If different from 'S' or 's', program performs a quick LED4 blinks during 3 sec and
  enters again "Stop 0" mode, waiting for next character to wake up.

In case of errors, LED4 is slowly blinking (1 sec period).

### <b>Keywords</b>

Connectivity, UART/USART, Asynchronous, RS-232, baud rate, Interrupt, HyperTerminal,
Receiver, Asynchronous, Low Power, Wake Up

### <b>Directory contents</b>

  - USART/USART_WakeUpFromStop_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - USART/USART_WakeUpFromStop_Init/Inc/main.h                  Header for main.c module
  - USART/USART_WakeUpFromStop_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - USART/USART_WakeUpFromStop_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - USART/USART_WakeUpFromStop_Init/Src/main.c                  Main program
  - USART/USART_WakeUpFromStop_Init/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with NUCLEO-C031C6 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C031C6 Set-up :

    - Connect STM32 MCU board USART1 TX pin (GPIO PA9 connected to PA.09 connected to pin 21 in CN10)
      to PC COM port RX signal

    - Connect STM32 MCU board USART1 RX pin (GPIO PA10 connected to PA.10 connected to pin 33 in CN10)
      to PC COM port TX signal

    - Connect STM32 MCU board GND to PC COM port GND signal

    - Launch serial communication SW on PC (as HyperTerminal or TeraTerm) with proper configuration 
      (9600 bauds, 8 bits data, 1 stop bit, no parity, no HW flow control). 

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example