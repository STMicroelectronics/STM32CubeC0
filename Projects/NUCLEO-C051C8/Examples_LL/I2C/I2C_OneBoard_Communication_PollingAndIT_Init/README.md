## <b>I2C_OneBoard_Communication_PollingAndIT_Init Example Description</b>

How to transmit data bytes from an I2C master device using polling mode
to an I2C slave device using interrupt mode. The peripheral is initialized
with LL unitary service functions to optimize for performance and size.

This example guides you through the different configuration steps by mean of LL API
to configure GPIO and I2C peripherals using only one NUCLEO-C051C8.

The user can disable internal pull-up by opening ioc file.

For that, user can follow the procedure :

1. Double click on the I2C_OneBoard_Communication_PollingAndIT_Init.ioc file
2. When CUBEMX tool is opened, select System Core category
3. Then in the configuration of GPIO/I2C1, change Pull-up to No pull-up and no pull-down for the both pins
4. Same action in the configuration of GPIO/I2C2, change Pull-up to No pull-up and no pull-down for the both pins
5. Last step, generate new code thanks to button "GENERATE CODE"

The example is updated with no pull on each pin used for I2C communication

I2C1 Peripheral is configured in Slave mode with EXTI (Clock 400Khz, Own address 7-bit enabled). 
I2C2 Peripheral is configured in Master mode (Clock 400Khz). 
GPIO associated to User push-button is linked with EXTI.

LED4 blinks quickly to wait for user-button press.

Example execution:

Press the User push-button to initiate a write request by Master through Handle_I2C_Master() routine.
This action will generate an I2C start condition with the Slave address and a write bit condition. 
When address Slave match code is received on I2C1, an ADDR interrupt occurs. 
I2C1 IRQ Handler routine is then checking Address Match Code and direction Write. 
This will allow Slave to enter in receiver mode and then acknowledge Master to send the bytes. 
When acknowledge is received on I2C2, a TXIS event occurs. 
This will allow Master to transmit a byte to the Slave. 
Each time a byte is received on I2C1 (Slave), an RXNE interrupt occurs until a STOP condition. 
And so each time the Slave acknowledge the byte received a TXIS event occurs on Master side. 
Master auto-generate a Stop condition when size of data to transmit is achieved.

The STOP condition generate a STOP interrupt and initiate the end of reception on Slave side. 
I2C1 IRQ handler and Handle_I2C_Master() routine are then clearing the STOP flag in both side.

LED4 is On if data are well received.

In case of errors, LED4 is blinking slowly (1s).

### <b>Keywords</b>

Connectivity, Communication, I2C, Interrupt, Polling, Master, Slave, Transmission, Reception, Fast mode


### <b>Directory contents</b>

    - I2C/I2C_OneBoard_Communication_PollingAndIT_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
    - I2C/I2C_OneBoard_Communication_PollingAndIT_Init/Inc/main.h                  Header for main.c module
    - I2C/I2C_OneBoard_Communication_PollingAndIT_Init/Inc/stm32_assert.h          Template file to include assert_failed function
    - I2C/I2C_OneBoard_Communication_PollingAndIT_Init/Src/stm32c0xx_it.c          Interrupt handlers
    - I2C/I2C_OneBoard_Communication_PollingAndIT_Init/Src/main.c                  Main program
    - I2C/I2C_OneBoard_Communication_PollingAndIT_Init/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C051C8Tx devices.

  - This example has been tested with NUCLEO-C051C8 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C051C8 Set-up
    - Connect GPIOs connected to I2C1 SCL/SDA (PB.8 and PB.9)
    to respectively SCL and SDA pins of I2C2 (PB.13 and PB.14).
      - I2C1_SCL  PB.8 (CN5, pin 10 D15) : connected to I2C2_SCL PB.13 (CN10, pin 30)
      - I2C1_SDA  PB.9 (CN5, pin 9 D14) : connected to I2C2_SDA PB.14 (CN10, pin 28)

  - Launch the program.
  - Press User push-button to initiate a write request by Master
      then Slave receive bytes.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

