
##  <b>Tx_Thread_MsgQueue Application Description</b>

This application provides an example of Azure RTOS ThreadX stack usage, it shows how to develop an application using the ThreadX message queue APIs.
It demonstrates how to send and receive messages between threads using ThreadX message queue APIs. In addition, it shows how to use the event chaining feature.
The main entry function tx_application_define() is then called by ThreadX during kernel start, at this stage, the application creates 3 threads with different
priorities and 2 message queues :

  - MsgSenderThreadOne (Priority : 5; Preemption Threshold : 5)
  - MsgSenderThreadTwo (Priority : 5; Preemption Threshold : 5)
  - MsgReceiverThread (Priority : 10; Preemption Threshold : 10)
  - MsgQueueOne (shared by MsgSenderThreadOne and MsgReceiverThread)
  - MsgQueueTwo (shared by MsgSenderThreadTwo and MsgReceiverThread)

<i> MsgSenderThreadOne</i> puts the message <i>TOGGLE_LED</i> on <i>MsgQueueOne</i> each 200 ms.

<i>MsgSenderThreadTwo</i> puts the message <i>TOGGLE_LED</i> on <i>MsgQueueTwo</i> each 500 ms.

<i>MsgReceiverThread</i> listen on both message queues :

  - When a message is available on <i>MsgQueueOne</i>, the <i>GREEN LED</i> is Toggled and following message is printed to the serial port:
    - MsgReceiverThread_Entry: MsgQueueOne is available

  - When a message is available on <i>MsgQueueTwo</i>, the <i>GREEN LED</i> is Toggled and following message is printed to the serial port:
    - MsgReceiverThread_Entry: MsgQueueTwo is available

####  <b>Expected success behavior</b>

<i>GREEN_LED</i> toggles and following messages are printed to the serial port if the application is running successfully.

    - MsgReceiverThread_Entry: MsgQueueOne is available
    - MsgReceiverThread_Entry: MsgQueueTwo is available

#### <b>Error behaviors</b>

On failure, an error message is printed to the serial port while the <i>GREEN_LED</i> is turned OFF.

#### <b>Assumptions if any</b>
None

#### <b>Known limitations </b>
None

###  <b>Notes</b>

To optimize the application footprint, the following ThreadX configuration options should be enabled in the tx_user.h file:

    #define TX_DISABLE_PREEMPTION_THRESHOLD

    #define TX_DISABLE_NOTIFY_CALLBACKS

    #define TX_DISABLE_REDUNDANT_CLEARING

    #define TX_DISABLE_STACK_FILLING

    #define TX_NOT_INTERRUPTABLE

    #define TX_TIMER_PROCESS_IN_ISR

    #define TX_DISABLE_ERROR_CHECKING

#### <b>ThreadX usage hints</b>

 - ThreadX uses the Systick as time base, thus it is mandatory that the HAL uses a separate time base through the TIM IPs.
 - ThreadX is configured with 100 ticks/sec by default, this should be taken into account when using delays or timeouts at application. It is always possible to reconfigure it, by updating the "TX_TIMER_TICKS_PER_SECOND" define in the "tx_user.h" file. The update should be reflected in "tx_initialize_low_level.S" file too..
 - ThreadX is disabling all interrupts during kernel start-up to avoid any unexpected behavior, therefore all system related calls (HAL, BSP) should be done either at the beginning of the application or inside the thread entry functions.
 - ThreadX offers the "tx_application_define()" function, that is automatically called by the tx_kernel_enter() API.
   It is highly recommended to use it to create all applications ThreadX related resources (threads, semaphores, memory pools...) but it should not in any way contain a system API call (HAL or BSP).
 - Using dynamic memory allocation requires to apply some changes to the linker file.
   ThreadX needs to pass a pointer to the first free memory location in RAM to the tx_application_define() function,
   using the "first_unused_memory" argument.
   This requires changes in the linker files to expose this memory location.
    + For EWARM add the following section into the .icf file:
     ```
     place in RAM_region    { last section FREE_MEM };
     ```
    + For MDK-ARM:
    ```
    either define the RW_IRAM1 region in the ".sct" file
    or modify the line below in "tx_low_level_initilize.s to match the memory region being used
        LDR r1, =|Image$$RW_IRAM1$$ZI$$Limit|
    ```
    + For STM32CubeIDE add the following section into the .ld file:
    ```
    ._threadx_heap :
      {
         . = ALIGN(8);
         __RAM_segment_used_end__ = .;
         . = . + 64K;
         . = ALIGN(8);
       } >RAM_D1 AT> RAM_D1
    ```

    The simplest way to provide memory for ThreadX is to define a new section, see ._threadx_heap above.
    In the example above the ThreadX heap size is set to 64KBytes.
    The ._threadx_heap must be located between the .bss and the ._user_heap_stack sections in the linker script.
    Caution: Make sure that ThreadX does not need more than the provided heap memory (64KBytes in this example).
    Read more in STM32CubeIDE User Guide, chapter: "Linker script".

    + The "tx_initialize_low_level.S" should be also modified to enable the "USE_DYNAMIC_MEMORY_ALLOCATION" flag.

### <b>Keywords</b>

RTOS, ThreadX, Threading, Message Queue, Event chaining

### <b>Hardware and Software environment</b>

  - This application runs on STM32C051C8Tx devices
  - This application has been tested with STMicroelectronics NUCLEO-C051C8 board revision MB1717-C051C8-C01
    and can be easily tailored to any other supported device and development board.
  - A virtual COM port appears in the HyperTerminal:
    - Hyperterminal configuration:
      + Data Length = 8 Bits
      + One Stop Bit
      + No parity
      + BaudRate = 115200 baud
      + Flow control: None


###  <b>How to use it ?</b>

In order to make the program work, you must do the following:

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application
