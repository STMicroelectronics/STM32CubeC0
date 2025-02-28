## <b>ADC_SingleConversion_TriggerSW_IT_Init Example Description</b>

How to use ADC to convert a single channel at each SW start,
conversion performed using programming model: interrupt.
This example is based on the STM32C0xx ADC LL API.
The peripheral initialization is done using LL unitary service functions
for optimization purposes (performance and size).

Example configuration:
ADC is configured to convert a single channel, in single conversion mode,
from SW trigger.
ADC interruption enabled: EOC (end of conversion of ADC group regular).

Example execution:
From the main program execution, a ADC software start is performed
every second, ADC group regular converts the selected channel.
When conversion is completed ADC interruption occurs.
IRQ handler callback function reads conversion data from ADC data register
and stores it into a variable.

LED1 is used to monitor program execution status:

- Normal operation: ADC group regular activity can be observed with LED toggle:
  - At each ADC conversion: LED toggle once (every 1sec)
- Error: LED remaining turned on

Debug: variables to monitor with debugger:

- "uhADCxConvertedData": ADC group regular buffer conversion data (resolution 12 bits)
- "uhADCxConvertedData_Voltage_mVolt": ADC group regular buffer conversion data computed to voltage value (unit: mV)

Connection needed:
Use an external power supply to generate a voltage in range [0V; 3.3V]
and connect it to analog input pin (cf pin below).

**Note:** If no power supply available, this pin can be let floating (in this case
ADC conversion data will be undetermined).

Other peripherals used:

 - 1 GPIO for LED1
 - 1 GPIO for analog input: ADC channel 4 on pin PA.04 (Arduino connector CN8 pin 3 A2, Morpho connector CN7 pin 32)

### <b>Keywords</b>

ADC, analog digital converter, analog, conversion, voltage, channel, analog input, interruption

### <b>Directory contents</b>

    - ADC/ADC_SingleConversion_TriggerSW_IT_Init/Inc/stm32c0xx_it.h         Interrupt handlers header file
    - ADC/ADC_SingleConversion_TriggerSW_IT_Init/Inc/main.h                  Header for main.c module
    - ADC/ADC_SingleConversion_TriggerSW_IT_Init/Inc/stm32_assert.h          Template file to include assert_failed function
    - ADC/ADC_SingleConversion_TriggerSW_IT_Init/Src/stm32c0xx_it.c         Interrupt handlers
    - ADC/ADC_SingleConversion_TriggerSW_IT_Init/Src/main.c                  Main program
    - ADC/ADC_SingleConversion_TriggerSW_IT_Init/Src/system_stm32c0xx.c     STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C092RCTx devices.

  - This example has been tested with NUCLEO-C092RC board and can be
    easily tailored to any other supported device and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

