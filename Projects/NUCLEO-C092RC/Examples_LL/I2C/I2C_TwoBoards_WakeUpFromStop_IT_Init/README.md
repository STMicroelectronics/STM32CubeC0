## <b>I2C_TwoBoards_WakeUpFromStop_IT_Init Example Description</b>

How to handle the reception of a data byte from an I2C slave device in
Stop0 mode by an I2C master device, both using interrupt mode. The
peripheral is initialized with LL unitary service functions to optimize for
performance and size.

This example guides you through the different configuration steps by mean of LL API
to configure GPIO and I2C peripherals using two NUCLEO-C092RC.

    Boards: NUCLEO-C092RC (embeds a STM32C092RC device)
    SCL Pin: PB.8 (CN5 D15, pin 10)
    SDA Pin: PB.9 (CN5 D14, pin 9)

The project is split in two parts the Master Board and the Slave Board

- Master Board
  I2C1 Peripheral is configured in Master mode with EXTI (Clock 100Khz).
  And GPIO associated to User push-button is linked with EXTI.

- Slave Board
  I2C1 Peripheral is configured in Slave mode with EXTI (Clock 100Khz,
  Own address 7-bit enabled, WakeUpFromStop).

The user can choose between Master and Slave through "#define SLAVE_BOARD"
in the "main.h" file:

- Comment "#define SLAVE_BOARD" to select Master board.
- Uncomment "#define SLAVE_BOARD" to select Slave board.

The user can disable internal pull-up by opening ioc file.
For that, user can follow the procedure :

1. Double click on the I2C_TwoBoards_WakeUpFromStop_IT_Init.ioc file
2. When CUBEMX tool is opened, select System Core category
3. Then in the configuration of GPIO/I2C1, change Pull-up to No pull-up and no pull-down for the both pins
4. Last step, generate new code thanks to button "GENERATE CODE"

The example is updated with no pull on each pin used for I2C communication

A first program launch, BOARD SLAVE is in Stop0 mode and BOARD MASTER is waiting User action on User push-button.
LED1 blinks quickly on BOARD MASTER to wait for user-button press.

Example execution:
Press the User push-button on BOARD MASTER to initiate a read request by Master.
This action will generate an I2C start condition with the Slave address and a read bit condition.
When address Slave match code is received on I2C1 of BOARD SLAVE, a wake up is initiate and an ADDR interrupt occurs.
I2C1 Slave IRQ Handler routine is then checking Address Match Code and direction Read.
This will allow Slave to enter in transmitter mode and then send a byte when TXIS interrupt occurs.
When byte is received on I2C1 of BOARD MASTER, an RXNE interrupt occurs.
When RXDR register is read, Master auto-generate a NACK and STOP condition
to inform the Slave that the transfer is finished.
The NACK condition generate a NACK interrupt in Slave side treated in the I2C1 Slave IRQ handler routine by a clear of NACK flag.
The STOP condition generate a STOP interrupt in both side (Slave and Master). Both I2C1 IRQ handler routine are then
clearing the STOP flag in both side.

- LED1 is ON on Slave side if the byte is well transmitted.
- LED1 is ON on Master side if the expected byte is well received.

In case of errors, LED1 is blinking slowly (1s).

### <b>Keywords</b>

Connectivity, I2C, Communication, Transmission, Reception, SCL, SDA, Wake up, Interrupt

### <b>Directory contents</b>

  - I2C/I2C_TwoBoards_WakeUpFromStop_IT_Init/Inc/stm32c0xx_it.h         Interrupt handlers header file
  - I2C/I2C_TwoBoards_WakeUpFromStop_IT_Init/Inc/main.h                  Header for main.c module
  - I2C/I2C_TwoBoards_WakeUpFromStop_IT_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_TwoBoards_WakeUpFromStop_IT_Init/Src/stm32c0xx_it.c         Interrupt handlers
  - I2C/I2C_TwoBoards_WakeUpFromStop_IT_Init/Src/main.c                  Main program
  - I2C/I2C_TwoBoards_WakeUpFromStop_IT_Init/Src/system_stm32c0xx.c     STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RCTx devices.

  - This example has been tested with STM32C092RCTx board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C092RC Set-up
    - Connect GPIOs connected to Board Slave I2C1 SCL/SDA (PB.8 and PB.9)
    to respectively Board Master SCL and SDA pins of I2C1 (PB.8 and PB.9).
      - I2C1_SCL  PB.8 (CN5 D15, pin 10) : connected to I2C1_SCL PB.8 (CN5 D15, pin 10)
      - I2C1_SDA  PB.9 (CN5 D14, pin 9) : connected to I2C1_SDA PB.9 (CN5 D14, pin 9)
    - Connect Master board GND to Slave Board GND

  - Launch the program.
  - Press User push-button to initiate a read request by Master
      then Slave after wake up from Stop0 mode send a byte.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory (The user can choose between Master
   and Slave target through "#define SLAVE_BOARD" in the "main.h" file)
    - Comment "#define SLAVE_BOARD" and load the project in Master Board
    - Uncomment "#define SLAVE_BOARD" and load the project in Slave Board
 - Run the example

