@ECHO OFF

:: ==============================================================================
::                               General
:: ==============================================================================
:: Configure tools installation path
set stm32programmercli="C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"
set stm32tpccli="C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32TrustedPackageCreator_CLI.exe"

:: ==============================================================================
::                            OEMiSB boot path
:: ==============================================================================
:: Select application project below
:: Give relative path of application and boot from NUCLEO-C071RB folder
set oemisb_appli_path_project=Applications/ROT/OEMiSB_Appli
set oemisb_boot_path_project=Applications/ROT/OEMiSB_Boot

::Select the Target Device STM32C071XX for 128K device, STM32C051XX for 64K device, STM32C092XX for 256K device
set product_id=STM32C071XX
:: ==============================================================================

:: ==============================================================================
::               !!!! DOT NOT EDIT --- UPDATED AUTOMATICALLY !!!!
:: ==============================================================================
set cube_fw_path=%~dp0..\..\..\
set rot_provisioning_path=%~dp0
