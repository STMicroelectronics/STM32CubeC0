## <b>OEMiSB_Boot application Description</b>

This project provides an OEMiSB example. OEMiSB boot path performs
authenticity checks of the project firmware image.

This project shows how to implement an OEMiSB.

The maximum system clock frequency at 48Mhz is configured.

### <b>Keywords</b>

OEMiSB, boot path, Root Of Trust, Security

### <b>Directory contents</b>

-   OEMiSB_Boot/Src/boot.c Platform initialization
-   OEMiSB_Boot/Src/entropy.c Entropy gathering utility
-   OEMiSB_Boot/Src/low_level_rng.c Random generator interface
-   OEMiSB_Boot/Src/low_level_security.c Security low level services
-   OEMiSB_Boot/Src/main.c Main program
-   OEMiSB_Boot/Src/stm32c0xx_it.c Interrupt handlers
-   OEMiSB_Boot/Src/system_stm32c0xx.c System init file
-   OEMiSB_Boot/Src/stm32c0xx_hal_msp.c HAL MSP Module
-   OEMiSB_Boot/Inc/boot.h Header file for boot.c
-   OEMiSB_Boot/Inc/entropy.h Header file for boot.c
-   OEMiSB_Boot/Inc/boot_cfg.h Configuration file
-   OEMiSB_Boot/Inc/boot_hal_flowcontrol.h Header file for flow control
    code in boot_hal.c
-   OEMiSB_Boot/Inc/low_level_rng.h Header file for low_level_rng.c
-   OEMiSB_Boot/Inc/low_level_security.h Header file for
    low_level_security.c
-   OEMiSB_Boot/Inc/main.h Main program header file
-   OEMiSB_Boot/Inc/mbed-crypto_config.h Mbed-crypto configuration file
-   OEMiSB_Boot/Inc/stm32c0xx_hal_conf.h HAL driver configuration file
-   OEMiSB_Boot/Inc/stm32c0xx_it.h Interrupt handlers header file

### <b>Hardware and Software environment</b>

-   This example runs on STM32C092xx devices.
-   This example can be generated by following these steps:

-   Copy the project from the folder NUCLEO-C071RB into matching folder in folder NUCLEO-C092RC
-   Copy the provisioning scripts from the folder NUCLEO-C071RB into matching folder in folder NUCLEO-C092RC
-   Go to main.h and enable the compilation switch DEVICE_256K_FLASH_ENABLE.

-   For IAR IDE:
    1. Go to "Options" and select "General Options" then in the "Target" field Select "device" to choose your device.
    2. Go to "Options" and select "C/C++ Compiler" then "Preprocessor" tab and change the compilation symbol (STM32C092xx instead of STM32C071xx)
    3. Copy startup_stm32c092xx.s into the project folder from Firmware/Drivers/CMSIS/Device/ST/STM32C0xx/Source/Template/iar
    4. Select the startup_stm32c092xx.s in the IDE.

-   For KEIL IDE:
    1. Go to "Options" and select "Device" tab to choose your device.
    2. Go to "Options" and select "C/C++ (AC6)" then in the "Define" field in "Preprocessor Symbols" change the compilation symbol (STM32C092xx instead of STM32C071xx)
    3. Copy the startup_stm32c092xx.s into the project folder from Firmware/Drivers/CMSIS/Device/ST/STM32C0xx/Source/Template/arm
    4. Select the startup_stm32c092xx.s in the IDE.

-   For CUBE IDE:
    1. Go to "Properties" and select "MPU settings" and select the target device.
    2. Go to "Properties" and select "C/C++ Build" tab then "Settings" and change the compilation symbol (STM32C092xx instead of STM32C071xx).
    3. Copy the startup_stm32c092xx.s in to the project folder from Firmware/Drivers/CMSIS/Device/ST/STM32C0xx/Source/Template/gcc
    4. Select the startup_stm32c092xx.s in the IDE

-   To get debug print in your UART console you have to configure it
    using these parameters: Speed: 115200, Data: 8bits, Parity: None,
    stop bits: 1, Flow control: none.
### <b>How to use it?</b>

In order to build the OEMiSB_Boot project, you must do the following:

-   Open your preferred toolchain
-   Rebuild the project

Then refer to OEMiSB_Appli readme for example of application booted
through OEMiSB boot path.