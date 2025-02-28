## <b>I2C_TwoBoards_MultiMasterIT_Slave Example Description</b>
How to handle I2C data buffer communication between two boards, using an interrupt and two Masters and one Slave.

      - Board: NUCLEO-C092RC's (embeds a STM32C092RC device)
      - SCL Master1 Pin: PB8 (Arduino D15 CN5 pin 10, Morpho CN10 pin 3)
      - SDA Master1 Pin: PB9 (Arduino D14 CN5 pin 9, Morpho CN10 pin 5)
      - SCL Master2 Pin: PA7 (Arduino D12 CN5 pin 4, Morpho CN10 pin 15)
      - SDA Master2 Pin: PA6 (Arduino D11 CN5 pin 5, Morpho CN10 pin 13)
      - SCL Slave   Pin: PB8 (Arduino D15 CN5 pin 10, Morpho CN10 pin 3)
      - SDA Slave   Pin: PB9 (Arduino D14 CN5 pin 9, Morpho CN10 pin 5)
      Connect GND between each board.

   _________________________                       _________________________
  |           ______________|                     |______________           |
  |          |I2C1           |                     |          I2C1|          |
  |          |              |                     |              |          |
  |          |    MST1  SCL |_____________________| SCL          |          |
  |          |              |         |           |              |          |
  |          |              |         |           |              |          |
  |          |              |         |           |              |          |
  |          |    MST1  SDA |_________|___________| SDA          |          |
  |          |              |         |   |       |              |          |
  |          |______________|         |   |       |______________|          |
  |                         |         |   |       |                         |
  |                      GND|_________|___|_______|GND                      |
  |                         |         |   |       |_STM32_Board 2___________|
  |           ______________|         |   |
  |          |I2C2           |         |   |
  |          |              |         |   |
  |          |    MST2  SCL |_________|   |
  |          |              |             |
  |          |              |             |
  |          |              |             |
  |          |    MST2  SDA |_____________|
  |          |              |
  |          |______________|
  |                         |
  |                      GND|
  |_STM32_Board 1___________|

This projects provides a reference example through the LL API that can be used to build any firmware application.

This project is targeted to run on STM32C092RC device on NUCLEO-C092RC board from STMicroelectronics.

The reference template project configures the maximum system clock frequency at 48 MHz.

In this example, two instances I2C are used in Master mode on a single board to communicate with a Slave on another
board. The TIM peripheral is used to simulate a RTOS scheduling, between Master1 managed through main() and Master2
through the TimerUpdate_Callback(). Every millisecond, the timer will send an interrupt to give the Master2 the
upperhand for the communication with the Slave.

In a first step, I2C Master1, Master2 and Timer are initialized through the LL_I2C_Init() and LL_TIM_Init() functions
respectively. Each time the timer generate an interrupt, the associated callback TimerUpdate_Callback() is called and
a Master2 starts the communication by sending aTxBufferMaster2 through LL_I2C_TransmitData8()
to I2C Slave which receives aRxBuffer through LL_I2C_ReceiveData8().

Then when user press the User push-button on the Master Board, I2C Master1 starts the communication by sending
aTxBufferMaster1 through LL_I2C_TransmitData8() to I2C Slave which receives aRxBuffer through
LL_I2C_ReceiveData8().

Each time the Slave retrieve a buffer, associated variable are incremented.
User can easily add to live watch the variable nbMst1RxCplt and nbMst2RxCplt to catch the Multimaster buffer reception
on Slave side.

And user can easily add to live watch the variable Master1BusBusyCpt and Master2BusBusyCpt to catch the Multimaster
bandwidth detection on Master side.

NUCLEO-C092RC's LED can be used to monitor the transfer status:
 - LED1 toggle each time the timer period elapsed.
 - LED1 is slowly blinking (1 sec. period) in case of error in initialization or transmission process.

### <b>Keywords</b>
I2C, Master, Slave, TIM, Multimaster, Communication, Interrupt, Transmission, Reception

### <b>Directory contents</b>
  - I2C/I2C_TwoBoards_MultiMasterIT_Slave/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - I2C/I2C_TwoBoards_MultiMasterIT_Slave/Inc/main.h                  Header for main.c module
  - I2C/I2C_TwoBoards_MultiMasterIT_Slave/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_TwoBoards_MultiMasterIT_Slave/Src/stm32c0xx_it.c          Interrupt handlers
  - I2C/I2C_TwoBoards_MultiMasterIT_Slave/Src/main.c                  Main program
  - I2C/I2C_TwoBoards_MultiMasterIT_Slave/Src/system_stm32c0xx.c      STM32C0xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RC devices.

  - This example has been tested with NUCLEO-C092RC board and can be easily tailored to any other supported device and
    development board.

  - NUCLEO-C092RC Set-up
    - Connect Master board PB8 (Arduino D15 CN5 pin 10, Morpho CN10 pin 3) to Slave Board PB8
      (Arduino D15 CN5 pin 10, Morpho CN10 pin 3)
    - Connect Master board PB9 (Arduino D14 CN5 pin 9, Morpho CN10 pin 5) to Slave Board PB9
      (Arduino D14 CN5 pin 9, Morpho CN10 pin 5)
    - Connect Master board PA7 (Arduino D12 CN5 pin 4, Morpho CN10 pin 15) to Slave Board PB8
      (Arduino D15 CN5 pin 10, Morpho CN10 pin 3)
    - Connect Master board PA6 (Arduino D11 CN5 pin 5, Morpho CN10 pin 13) to Slave Board PB9
      (Arduino D14 CN5 pin 9, Morpho CN10 pin 5)
    - Connect Master board GND to Slave Board GND

### <b>How to use it ?</b>

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
