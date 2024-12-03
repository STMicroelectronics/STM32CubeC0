#!/bin/bash

# Absolute path to this script
if [ $# -ge 1 ] && [ -d $1 ]; then
    projectdir=$1
else
    projectdir=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
fi

# ==============================================================================
#                               General
# ==============================================================================
#Configure tools installation path
if [ "$OS" == "Windows_NT" ]; then
    stm32programmercli="C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"
    stm32tpccli="C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32TrustedPackageCreator_CLI.exe"
else
    stm32programmercli_path=~/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/
    PATH=$stm32programmercli_path:$PATH
    stm32programmercli="STM32_Programmer_CLI"
    stm32tpccli="STM32TrustedPackageCreator_CLI"
fi

# ==============================================================================
#                            OEMiSB boot path
# ==============================================================================
# Select application project below
oemisb_appli_path_project="Applications/ROT/OEMiSB_Appli"
oemisb_boot_path_project="Applications/ROT/OEMiSB_Boot"
# Select the Target Device STM32C071XX for 128K device, STM32C051XX for 64K device, STM32C092XX for 256K device
product_id=STM32C071XX
# ==============================================================================
# ==============================================================================
#               !!!! DOT NOT EDIT --- UPDATED AUTOMATICALLY !!!!
# ==============================================================================
PROJECT_GENERATED_BY_CUBEMX=false
cube_fw_path=$projectdir/../../../
rot_provisioning_path=$projectdir