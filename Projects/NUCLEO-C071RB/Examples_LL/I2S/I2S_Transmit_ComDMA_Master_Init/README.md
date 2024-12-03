## <b>I2S_Transmit_ComDMA_Master_Init Example Description</b>
How to handle an I2S transmission using DMA protocol in Master mode.

      - Board: NUCLEO-C071RB's (embeds a STM32C071RB device)
      - I2S_CK Pin: PA1 (Arduino A1 CN8 pin 2, Morpho CN7 pin 30)
      - I2S_SD Pin: PA2 (Morpho CN10 pin 18)
      - I2S_WS Pin: PA4 (Arduino A2 CN8 pin 3, Morpho CN7 pin 32)
      Connect each pin to an oscilloscope (ideally digital probe with several wires and able to interpret I2S
      standards) to check the signals behavior.
      Connect GND between the oscilloscope and the board.

This project provides a reference example through LL I2S API.
This project is targeted to run on STM32C071xx device.
This project configures the system clock (SYSCLK) with the SystemClock_Config() function to run at 48MHz.

The I2S peripheral configuration and I2S resources (CLOCK, GPIO and NVIC) are ensured by the MX_I2S_Init() function.
The DMA CLOCK and NVIC are set in the MX_DMA_INIT() function.
The LED1 is initialized through the MX_GPIO_INIT() function.

The functions LL_DMA_ConfigTransfer(), LL_DMA_ConfigAddresses and LL_DMA_SetDataLength() are used to configure the DMA
channel. The DMA interrupts Transfer Complete and Transfer Error are then enabled.

On the I2S side, the DMA transmit request is enabled through the LL_I2S_EnableDMAReq_TX() function. The I2S is
then enabled.

When enabling the DMA channel, the transmission process can be launched.

For this example the buffer transmitted comes from an extract of an audio sample (artofgardens-instr by Dan
O'Connor). Be aware that in sounds samples, there is a header giving information about the audio (here, the
header is of 44 bytes since the sample was in a wav format). The I2S configuration is given in this header:
the length of format data (bytes 17-20), the audio format (bytes 21-22), the audio frequency (bytes 25-28) and
the bits per sample (bytes 35-36) giving the format PCM Short with a data length 16bits and a frequency of 8KHz.

To check if the transmission is successful, use the oscilloscope to see the behavior of the lines. If a logic analyser
is used and can decode I2S_CK/I2S_SD/I2S_WS lines, the user should be able to see the data in the audio sample buffer.

NUCLEO-C071RB's LEDs can be used to monitor the transfer status:
- LED1 is on if the transmission has been completed without issue.
- LED1 toggled slowly when an error occurred in the transmission process.

### <b>Keywords</b>
I2S, DMA, Oscilloscope, Signal, Transmission.

### <b>Directory contents</b>

  - I2S_Transmit_ComDMA_Master_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - I2S_Transmit_ComDMA_Master_Init/Inc/main.h                  Header for main.c module
  - I2S_Transmit_ComDMA_Master_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2S_Transmit_ComDMA_Master_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - I2S_Transmit_ComDMA_Master_Init/Src/main.c                  Main program
  - I2S_Transmit_ComDMA_Master_Init/Src/system_stm32c0xx.c      STM32C0x system source file
  - I2S_Transmit_ComDMA_Master_Init/Src/audio_sample.c          Audio sample file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C071xx devices.

  - This example has been tested with STMicroelectronics NUCLEO-C071RB
    boards and can be easily tailored to any other supported device
    and development board.

  - NUCLEO-C071RB Set-up
    - Connect the oscilloscope (ideally digital probe with several wires to have all signals) to each pin I2S.
    - Connect the GND of oscilloscope to the GND of the board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example