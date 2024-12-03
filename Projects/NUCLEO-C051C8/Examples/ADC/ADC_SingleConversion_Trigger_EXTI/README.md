## <b>ADC_SingleConversion_Trigger_EXTI Example Description</b>

How to use ADC to convert a single channel at each trigger EXTI,
conversion performed using programming model: interrupt.
This example is based on the STM32C0xx ADC HAL API.

Example configuration:

ADC is configured to convert a single channel, in single conversion mode,
from trigger EXTI.

An EXTI line is connected to the user button through PC.13 and configured
to generate an interrupt on falling edge upon key press.

ADC interruption enabled: EOC (end of conversion of ADC group regular).

Example execution:

From the main program execution, a ADC software start is performed
at each press of User button, ADC group regular converts the selected channel.
When conversion is completed ADC interruption occurs.
IRQ handler callback function reads conversion data from ADC data register
and stores it into a variable.

LED4 is used to monitor program execution status:

- Normal operation: ADC group regular activity can be observed with LED toggle:
- The User push-button can be pressed at any time to wake-up the system.
- At each ADC conversion: LED toggle once (every 1sec)
- Error: LED remaining turned on

Debug: variables to monitor with debugger:

- "uhADCxConvertedData": ADC group regular buffer conversion data (resolution 12 bits)
- "uhADCxConvertedData_Voltage_mVolt": ADC group regular buffer conversion data computed to voltage value (unit: mV)

Connection needed:

Use an external power supply to generate a voltage in range [0V; 3.3V]
and connect it to analog input pin (cf pin below).

Connect ADC_EXTI11 input (PA11, Arduino A4 CN8 pin 5, Morpho CN7 pin36) to
User push-button output (PC13, Morpho CN7 pin23).

Note: If no power supply available, this pin can be let floating (in this case
      ADC conversion data will be undetermined).

Other peripherals used:

  1 GPIO for LED4

  1 GPIO for analog input: ADC channel 4 on pin PA.04 (Arduino A2 pin 3 CN8, Morpho connector CN7 pin 32)

  1 User push-button connected to pin PC.13 (EXTI_Line13)

### <b>Keywords</b>

ADC, analog digital converter, analog, conversion, voltage, channel, analog input, interruption, EXTI

### <b>Directory contents</b>

    - ADC/ADC_SingleConversion_Trigger_EXTI/Inc/stm32c0xx_hal_conf.h    HAL configuration file
    - ADC/ADC_SingleConversion_Trigger_EXTI/Inc/stm32c0xx_it.h          Interrupt handlers header file
    - ADC/ADC_SingleConversion_Trigger_EXTI/Inc/main.h                  Header for main.c module
    - ADC/ADC_SingleConversion_Trigger_EXTI/Src/stm32c0xx_it.c          Interrupt handlers
    - ADC/ADC_SingleConversion_Trigger_EXTI/Src/stm32c0xx_hal_msp.c     HAL MSP module
    - ADC/ADC_SingleConversion_Trigger_EXTI/Src/main.c                  Main program
    - ADC/ADC_SingleConversion_Trigger_EXTI/Src/system_stm32c0xx.c      STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C051C8Tx devices.

  - This example has been tested with NUCLEO-C051C8 board and can be
    easily tailored to any other supported device and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

