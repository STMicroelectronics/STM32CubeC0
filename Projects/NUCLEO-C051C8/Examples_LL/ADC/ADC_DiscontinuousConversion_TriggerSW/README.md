## <b>ADC_DiscontinuousConversion_TriggerSW Example Description</b>

How to use an ADC peripheral to perform multiple conversion from different ADC channel,
one at a time after each software trigger.
This example is based on the STM32C0xx ADC LL API.
The peripheral initialization is done using LL unitary service functions
for optimization purposes (performance and size).

Example configuration:

ADC is configured in discontinuous conversion mode, from SW trigger.
Sequencer of ADC group regular (default group available on ADC of all STM32 devices)
is configured to convert 2 channels: 1 channel from GPIO, 1 internal channels:
internal voltage reference VrefInt.

Example execution:

ADC performs conversion of a channel among the 2 channels
of the scan sequence, successively at each conversion start (discontinuous mode enabled).

After each conversion ADC data is stored into the array "uhADCxConvertedData":
- uhADCxConvertedData[0]: ADC channel set on sequence rank 1 (GPIO as analog input)
- uhADCxConvertedData[1]: ADC channel set on sequence rank 2 (VrefInt)

When sequence is completed, ADC raw data are converted physical value then
it restarts from the beginning: first channel in the sequence.

ADC conversions raw data are computed to physical values
using LL ADC driver helper macro:
- Value of analog reference voltage (Vref+), connected to analog voltage supply Vdda (unit: mV)
- Value of voltage on GPIO pin (on which is mapped ADC channel, cf pin below) (unit: mV)
- Value of internal voltage reference VrefInt (unit: mV)

Note: For this example purpose, analog reference voltage (Vref+) is computed
      from ADC conversion of internal voltage reference VrefInt and used
      to compute other conversion data.
      This voltage should correspond to value of literal "VDDA_APPLI".
      This procedure can be performed when value of voltage Vref+
      is unknown in the application.
      (This is not the case in this example due to target board
      supplied by a LDO regulator providing a known constant voltage
      of value "VDDA_APPLI").
      In typical case of Vref+ connected to Vdd, it allows to
      deduce Vdd value.

LED1 is used to monitor program execution status:

- Normal operation: Activity of ADC scan sequence
  can be observed with LED toggle:
  - At each ADC conversion: LED toggle once (every 500ms)
- Error: LED remaining turned on

Debug: variables to monitor with debugger:
- "uhADCxConvertedData": ADC group regular conversion data
- "uhADCxConvertedData_VrefAnalog_mVolt":         Value of analog reference voltage (Vref+), connected to analog voltage supply Vdda (unit: mV)
- "uhADCxConvertedData_VoltageGPIO_mVolt":        Value of voltage on GPIO pin (on which is mapped ADC channel) (unit: mV)
- "uhADCxConvertedData_VrefInt_mVolt":            Value of internal voltage reference VrefInt (unit: mV)

Connection needed:

Use an external power supply to generate a voltage in range [0V; 3.3V]
and connect it to analog input pin (cf pin below).

Note: If no power supply available, this pin can be let floating (in this case
      ADC conversion data will be undetermined).

Other peripherals used:

  1 GPIO for LED1

  1 GPIO for analog input: ADC channel 4 on pin PA.04 (Arduino connector CN8 pin 3 A2, Morpho connector CN7 pin 32)

### <b>Keywords</b>

ADC, analog digital converter, analog, conversion, voltage, channel, analog input, trigger, analog watchdog, threshold, window

### <b>Directory contents</b>

  - ADC/ADC_DiscontinuousConversion_TriggerSW/Inc/stm32c0xx_it.h          Interrupt handlers header file
  - ADC/ADC_DiscontinuousConversion_TriggerSW/Inc/main.h                  Header for main.c module
  - ADC/ADC_DiscontinuousConversion_TriggerSW/Inc/stm32_assert.h          Template file to include assert_failed function
  - ADC/ADC_DiscontinuousConversion_TriggerSW/Src/stm32c0xx_it.c          Interrupt handlers
  - ADC/ADC_DiscontinuousConversion_TriggerSW/Src/main.c                  Main program
  - ADC/ADC_DiscontinuousConversion_TriggerSW/Src/system_stm32c0xx.c      STM32C0xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32C051C8Tx devices.

  - This example has been tested with NUCLEO-C051C8 board and can be
    easily tailored to any other supported device and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

