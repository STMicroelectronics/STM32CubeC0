## <b>I2C_TwoBoards_AdvComIT Example Description</b>

How to handle several I2C data buffer transmission/reception between
a master and a slave device, using an interrupt.

    Board: NUCLEO-C092RC (embeds a STM32C092RC device)
    - SCL Pin: PB8 (Arduino SCL/D15 CN5 pin 10, Morpho CN10 pin3)
    - SDA Pin: PB9 (Arduino SDA/D14 CN5 pin 9, Morpho CN10 pin5)

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.

Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 48 MHz.

The I2C peripheral configuration is ensured by the HAL_I2C_Init() function.
This later is calling the HAL_I2C_MspInit()function which core is implementing
the configuration of the needed I2C resources according to the used hardware (CLOCK, 
GPIO and NVIC). You may update this function to change I2C configuration.

The I2C communication is then initiated.

The project is split in two parts: the Master Board and the Slave Board.

- Master Board:
  The HAL_I2C_Master_Receive_IT() and the HAL_I2C_Master_Transmit_IT() functions 
  allow respectively the reception and the transmission of a predefined data buffer
  in Master mode using interrupt.

- Slave Board:
  The HAL_I2C_Slave_Receive_IT() and the HAL_I2C_Slave_Transmit_IT() functions 
  allow respectively the reception and the transmission of a predefined data buffer
  in Slave mode using interrupt.

The user can choose between Master and Slave through "#define MASTER_BOARD"
in the "main.c" file:

- If the Master board is used, the "#define MASTER_BOARD" must be uncommented.
- If the Slave board is used the "#define MASTER_BOARD" must be commented.

For this example two buffers are used :

- aTxBuffer buffer contains the data to be transmitted 
- aRxBuffer buffer is used to save the received data

Note that both buffers have same size

On Master board side:

 - Wait User push-button to be pressed (used for only synchronization at startup)
 - Request write operation by sending specific command "MASTER_REQ_WRITE" to Slave
 - Send the number of data to be written
 - Transmit aTxBuffer buffer to slave
 - Request read operation by sending specific command "MASTER_REQ_READ" to Slave
 - Send the number of data to be read
 - Receive data from Slave in aRxBuffer
 - Check the correctness of data and Toggle LED1 when data is received correctly,
   otherwise LED2 is turned ON and communication is stopped (using infinite loop)

On Slave board side:

 - Receive request from Master
 - Receive the request operation from Master and depending on the operation type (write or read):
   - If Master requests write operation:
      - Receive number of data to be written by Master
      - Receive data from master in aRxBuffer
      - Check the correctness of data and Toggle LED1 when data is received correctly,
        otherwise LED2 is turned ON and communication is stopped (using infinite loop)
   - If Master request read operation:
      - Receive number of data to be written to Master
      - Transmit aTxBuffer buffer to master
   
These operations are repeated periodically and the start of communication is triggered 
by pushing the key button of the Master board.  

#### <b>Notes</b>

 1. In Master side, only Acknowledge failure error is handled. When this error
    occurs Master restart the current operation until Slave acknowledges it's
    address.

 2. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 3. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Connectivity, Communication, I2C, Interrupt, Master, Slave, Transmission, Reception, Fast mode,
Command, Acknowledge

### <b>Directory contents</b> 

  - I2C/I2C_TwoBoards_AdvComIT/Inc/stm32c0xx_hal_conf.h    HAL configuration file
  - I2C/I2C_TwoBoards_AdvComIT/Inc/stm32c0xx_it.h          I2C interrupt handlers header file
  - I2C/I2C_TwoBoards_AdvComIT/Inc/main.h                  Header for main.c module
  - I2C/I2C_TwoBoards_AdvComIT/Src/stm32c0xx_it.c          I2C interrupt handlers
  - I2C/I2C_TwoBoards_AdvComIT/Src/main.c                  Main program
  - I2C/I2C_TwoBoards_AdvComIT/Src/system_stm32c0xx.c      STM32C0xx system source file
  - I2C/I2C_TwoBoards_AdvComIT/Src/stm32c0xx_hal_msp.c     HAL MSP file

### <b>Hardware and Software environment</b>

  - This example runs on STM32U3xx devices.

  - This example has been tested with NUCLEO-C092RC board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-C092RC Set-up

    - Connect I2C_SCL line of Master board (PB8, Arduino SCL/D15 CN5 pin 10, Morpho CN10 pin3) to I2C_SCL line of Slave Board (PB8, Arduino SCL/D15 CN5 pin 10, Morpho CN10 pin3).
    - Connect I2C_SDA line of Master board (PB9, Arduino SDA/D14 CN5 pin 9, Morpho CN10 pin5) to I2C_SDA line of Slave Board (PB9, Arduino SDA/D14 CN5 pin 9, Morpho CN10 pin5).
    - Connect GND of Master board to GND of Slave Board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
    - Uncomment "#define MASTER_BOARD" and load the project in Master Board
    - Comment "#define MASTER_BOARD" and load the project in Slave Board
 - Run the example

