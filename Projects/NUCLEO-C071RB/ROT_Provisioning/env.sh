#!/bin/bash

# Absolute path to this script
if [ $# -ge 1 ] && [ -d $1 ]; then
    projectdir=$1
else
    projectdir=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
fi

#=================================================================================================
# Managing HOST OS diversity : begin
#=================================================================================================
OS=$(uname)

echo ${OS} | grep -i -e windows -e mingw >/dev/null
if [ $? == 0 ]; then
  echo ""
  echo " =========================================="
  echo "| For Windows OS, please use .bat scripts. |"
  echo " =========================================="
  echo ""
  echo "       Press any key to continue..."
  echo
  read -p "" -n1 -s
  exit 0
fi

if [ "$OS" == "Linux" ]; then
  echo "HOST OS : Linux detected"
elif [ "$OS" == "Darwin" ]; then
  echo "HOST OS : MacOS detected"
else
  echo "!!!HOST OS not supported : >$OS<!!!"
  exit 1
fi

#=================================================================================================
# Managing HOST OS diversity : end
#=================================================================================================

# ==============================================================================
#                               General
# ==============================================================================
#Configure tools installation path
if [ "$OS" == "Windows_NT" ]; then
    stm32programmercli="C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"
    stm32tpccli="C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32TrustedPackageCreator_CLI.exe"
else
    stm32programmercli_path="C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin"
    PATH=$stm32programmercli_path:$PATH
    stm32programmercli="C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"
    stm32tpccli="C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32TrustedPackageCreator_CLI.exe"
fi

# ==============================================================================
#                            OEMiSB boot path
# ==============================================================================
# Select application project below
# Give relative path of application and boot from NUCLEO-C071RB folder
oemisb_appli_path_project="Applications/ROT/OEMiSB_Appli"
oemisb_boot_path_project="Applications/ROT/OEMiSB_Boot"
# Select the Target Device STM32C071XX for 128K device, STM32C051XX for 64K device, STM32C092XX for 256K device
product_id=STM32C071XX
# ==============================================================================
# ==============================================================================
#               !!!! DOT NOT EDIT --- UPDATED AUTOMATICALLY !!!!
# ==============================================================================
cube_fw_path=$projectdir/../../../
rot_provisioning_path=$projectdir
