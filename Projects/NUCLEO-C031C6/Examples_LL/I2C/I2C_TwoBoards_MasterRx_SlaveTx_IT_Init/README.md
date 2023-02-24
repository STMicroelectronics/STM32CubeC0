## <b>I2C_TwoBoards_MasterRx_SlaveTx_IT_Init Example Description</b> 

How to handle the reception of one data byte from an I2C slave device
by an I2C master device. Both devices operate in interrupt mode. The peripheral
is initialized with LL unitary service functions to optimize for performance
and size.

This example guides you through the different configuration steps by mean of LL API
to configure GPIO and I2C peripherals using two NUCLEO-C031C6.

       Boards: NUCLEO-C031C6 (embeds a STM32C031C6 device)
       - SCL Pin: PB.8 (CN10, pin 3)
       - SDA Pin: PB.9 (CN10, pin 5)

The project is split in two parts the Master Board and the Slave Board

- Master Board:
  I2C1 Peripheral is configured in Master mode with EXTI (Fast Mode @400kHz).
  And GPIO associated to User push-button is linked with EXTI.

- Slave Board:
  I2C1 Peripheral is configured in Slave mode with EXTI (Fast Mode @400kHz, Own address 7-bit enabled).

The user can choose between Master and Slave through "#define SLAVE_BOARD"
in the "main.h" file:

- Comment "#define SLAVE_BOARD" to select Master board.
- Uncomment "#define SLAVE_BOARD" to select Slave board.

The user can disable internal pull-up by opening ioc file.
For that, user can follow the procedure :

1- Double click on the I2C_TwoBoards_MasterRx_SlaveTx_IT_Init.ioc file
2- When CUBEMX tool is opened, select System Core category
3- Then in the configuration of GPIO/I2C1, change Pull-up to No pull-up and no pull-down for the both pins
4- Last step, generate new code thanks to button "GENERATE CODE"

The example is updated with no pull on each pin used for I2C communication

LED4 blinks quickly on BOARD MASTER to wait for User push-button press.

Example execution:

Press the User push-button on BOARD MASTER to initiate a read request by Master.
This action will generate an I2C start condition with the Slave address and a read bit condition.
When address Slave match code is received on I2C1 of BOARD SLAVE, an ADDR interrupt occurs.
I2C1 Slave IRQ Handler routine is then checking Address Match Code and direction Read.
This will allow Slave to enter in transmitter mode and then send a byte when TXIS interrupt occurs.
When byte is received on I2C1 of BOARD MASTER, an RXNE interrupt occurs.
When RXDR register is read, Master auto-generate a NACK and STOP condition
to inform the Slave that the transfer is finished.
The NACK condition generate a NACK interrupt in Slave side treated in the I2C1 Slave IRQ handler routine by a clear of NACK flag.
The STOP condition generate a STOP interrupt in both side (Slave and Master). Both I2C1 IRQ handler routine are then
clearing the STOP flag in both side.

LED4 is On :

- Slave side if transfer sequence is completed.
- Master side if data is well received.

In case of errors, LED4 is blinking slowly (1s).

### <b>Keywords</b>

Connectivity, Communication, I2C, Interrupt, Master Rx, Slave Tx, Transmission, Reception, Fast mode, SDA, SCL

### <b>Directory contents</b> 

  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT_Init/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT_Init/Inc/main.h                  Header for main.c module
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT_Init/Src/stm32c0xx_it.c          Interrupt handlers
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT_Init/Src/main.c                  Main program
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT_Init/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C031C6Tx devices.

  - This example has been tested with STM32C031C6Tx board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C031C6 Set-up

    - Connect GPIOs connected to Board Slave I2C1 SCL/SDA (PB.8 and PB.9)
    to respectively Board Master SCL and SDA pins of I2C1 (PB.8 and PB.9).
      - I2C1_SCL  PB.8 (CN10, pin 3) : connected to I2C1_SCL PB.8 (CN10, pin 3)
      - I2C1_SDA  PB.9 (CN10, pin 5) : connected to I2C1_SDA PB.9 (CN10, pin 5)
    - Connect Master board GND to Slave Board GND

  - Launch the program.
  - Press User push-button to initiate a read request by Master
      then Slave send a byte.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory (The user can choose between Master
   and Slave target through "#define SLAVE_BOARD" in the "main.h" file)
    o Comment "#define SLAVE_BOARD" and load the project in Master Board
    o Uncomment "#define SLAVE_BOARD" and load the project in Slave Board
 - Run the example