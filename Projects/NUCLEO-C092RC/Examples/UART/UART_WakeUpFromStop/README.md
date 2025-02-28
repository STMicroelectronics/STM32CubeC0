## <b>UART_WakeUpFromStop Example Description</b>

This example shows how to configure an UART to wake up the MCU from STOP1 mode
when a given stimulus is received.

Board: NUCLEO-C092RC (embeds a STM32C092RCTx device)
Tx Pin: PA9(Pin 21 in CN10)
Rx Pin: PA10(Pin 33 in CN10)

Board 1 enters STOP1 mode and is awoken by Board 2 which sends
the proper data to wake up the board 1 MCU.
When the proper wake-up event is recognized, the WUF interrupt is triggered which wakes
up board 1.
To confirm its wake up, board 1 sends a confirmation message to board 2 which
checks it is the expected message.
This cycle is repeated 4 times to verify 4 different events
1°) wake-up by RXNE flag rising
2°) wake-up by Start Bit detection
3°) wake-up by 7-bit long address match
4°) wake-up by 4-bit long address match

WARNING: as both boards do not behave the same way, "BOARD_IN_STOP1_MODE" 
compilation switch is defined in UART/UART_WakeUpFromStop/Src/main.c and must be
enabled at compilation time before loading the executable in board 1 (that which
is set in STOP1 mode).
The stimuli-transmitting board (board 2) needs to be loaded with an executable
software obtained with BOARD_IN_STOP1_MODE disabled. 

At the very beginning, board 1 LED1 is ON then is turned off.
This means that board 1 has entered STOP1 mode.
Parallelly, board 2 LED1 is quickly blinking (100 ms period). The user has
just to wait for board 1 LED1 to be turned off then to press board 2 User push-button
to send the first wake-up stimulus to board 1.
This starts the test sequence and no more action is required from the user.
Indeed, a single User push-button press is needed to start the full 4 wake-up
events test sequence.

Board 1 LED1 behavior as described below allows to follow the 
test progress:

ON ____          _______          _______          _______          ____
       |        |       |        |       |        |       |        |    
OFF    |________|       |________|       |________|       |________|    
      Enter    Exit    Enter    Exit    Enter    Exit    Enter    Exit  
      Stop     Stop    Stop     Stop    Stop     Stop    Stop     Stop  
      Mode     Mode    Mode     Mode    Mode     Mode    Mode     Mode  
            (RXNE flag)      (Start Bit      (7-bit add.       (4-bit add.
                              Detection)        match)            match)
                               


Simultaneously, board 2 LED1 behavior shown below allows to follow the 
test progress on the other side:

  BLINKING   
ON ****________          _______          _______          _______          ____
               |        |       |        |       |        |       |        |    
OFF            |________|       |________|       |________|       |________|    
     USER     WkUp   2nd stim  WkUp   3rd stim  WkUp   4th stim  WkUp    LED ON  
     button   conf     sent    conf     sent    conf     sent    conf    to mark  
    pushed,   rcv'ed          rcv'ed           rcv'ed           rcv'ed   passed
  1st stimulus                                                            test 
     sent                                                                    
  (RXNE flag)      (Start Bit       (7-bit add.      (4-bit add.
                    Detection)         match)           match)
     
    
- If the test fails or if there is an initialization or transfer error, LED1
transmits a sequence of three dots, three dashes, three dots.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.

Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 48 MHz.



The UART is configured as follows:
    - BaudRate = 9600 baud  
    - Word Length = 8 bits (8 data bits, no parity bit)
    - One Stop Bit
    - Parity none
    - Hardware flow control disabled (RTS and CTS signals)

### <b>Notes</b>

 1. This example can not be used in DEBUG mode due to the fact that the 
    Cortex-M0+ core is no longer clocked during low power mode and so debugging 
    features are not available.

 2. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 3. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.
  
### <b>Keywords</b>

Connectivity, UART/USART, baud rate, RS-232, Wake Up, Low Power, full-duplex
Transmitter, Receiver, Asynchronous

### <b>Directory contents</b>

  - UART/UART_WakeUpFromStop/Inc/stm32c0xx_hal_conf.h    HAL configuration file
  - UART/UART_WakeUpFromStop/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - UART/UART_WakeUpFromStop/Inc/main.h                  Header for main.c module  
  - UART/UART_WakeUpFromStop/Src/stm32c0xx_it.c          Interrupt handlers
  - UART/UART_WakeUpFromStop/Src/main.c                  Main program
  - UART/UART_WakeUpFromStop/Src/stm32c0xx_hal_msp.c     HAL MSP module
  - UART/UART_WakeUpFromStop/Src/system_stm32c0xx.c      STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RCTx  devices.
    
  - This example has been tested with a couple of NUCLEO-C092RC boards embedding a 
    STM32C092RCTx device and can be easily tailored to any other supported device 
    and development board.
    
  - NUCLEO-C092RC set-up
    
    - Connect a wire between 1st board PA9(Pin 21 in CN10) pin (USART1 Tx) and 2nd board PA10(Pin 33 in CN10) pin (USART1 Rx)
    - Connect a wire between 1st board PA10(Pin 33 in CN10) pin (USART1 Rx) and 2nd board PA9(Pin 21 in CN10) pin (USART1 Tx)


### <b>How to use it ?</b>

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example