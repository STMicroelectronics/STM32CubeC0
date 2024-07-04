## <b>OEMiSB_Appli application Description</b>

This project provides a OEMiSB boot path application example. Boot is
performed through OEMiSB boot path after integrity checks of the project
firmware image.

The application will display a menu on the console. If data is
available, three menus are provided that allow reading, writing and
erasing data.

The maximum system clock frequency at 48Mhz is configured.

### <b>Keywords</b>

OEMiSB, boot path, Root Of Trust, Security, mcuboot

### <b>Directory contents</b>

-   OEMiSB_Appli/Src/main.c Main program
-   OEMiSB_Appli/Src/stm32c0xx_it.c Interrupt handlers
-   OEMiSB_Appli/Src/system_stm32c0xx.c System init file
-   OEMiSB_Appli/Src/main.h Main program header file
-   OEMiSB_Appli/Src/stm32c0xx_hal_conf.h HAL driver Configuration file
-   OEMiSB_Appli/Src/stm32c0xx_it.h Interrupt handlers header file

### <b>Hardware and Software environment</b>

-   This example runs on STM32C071xx devices.
-   This example has been tested with STMicroelectronics NUCLEO-C071RB
    board and can be easily tailored to any other supported device and
    development board.
-   To print the application menu in your UART console you have to
    configure it using these parameters: Speed: 115200, Data: 8bits,
    Parity: None, stop bits: 1, Flow control: none.

### <b>How to use it ?</b>

This project is targeted to boot through **OEMiSB boot path**.

Before compiling the project, you should first start the provisioning
process. During the provisioning process, the linker files of the
project will be automatically updated.

The **provisioning process** (ROT_Provisioning/OEMiSB/provisioning.bat)
is divided in 3 majors steps :

-   Step 1 : Product configuration

    -   Select RDP Level
    -   Select data area size

-   Step 2 : Image generation

    -   Build OEMiSB_Boot project
    -   Build OEMiSB_Appli project

-   Step 3 : Provisioning

    -   Programming the option bytes
    -   Flashing the images
    -   Setting the RDP level

After application startup, check in your "UART console" the menu is well
displayed:

    ======================================================================
    =              (C) COPYRIGHT 2023 STMicroelectronics                 =
    =                                                                    =
    =                          OEMiSB User App                           =
    ======================================================================

    ============================= Main Menu ==============================
      Read flash data ------------------------------------------ 1
      Write flash data ----------------------------------------- 2
      Erase flash data ----------------------------------------- 3
     Selection :

It is possible to read, write or erase data

#### <b>Notes:</b>

Two versions of ROT_AppliConfig are available: windows executable
and python version. By default, the windows executable is selected.
It is possible to switch to python version by:

-   installing python (Python 3.10 or newer) with the required
    modules listed in requirements.txt.

      pip install -r requirements.txt

-   having python in execution path variable

-   deleting main.exe in
        Utilities\\PC_Software\\ROT_AppliConfig\\dist
