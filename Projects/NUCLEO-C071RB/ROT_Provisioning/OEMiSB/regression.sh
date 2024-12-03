#!/bin/bash -
echo "regression script started"
source ../env.sh

connect_no_reset="-c port=SWD mode=Hotplug"
connect_reset="-c port=SWD mode=UR"

rdp_0="-ob RDP=0xAA"
if [ "$product_id" == "STM32C071XX" ]; then
    remove_bank1_protect="-ob WRP1A_STRT=0x3f WRP1A_END=0"
fi

if [ "$product_id" == "STM32C051XX" ]; then
    remove_bank1_protect="-ob WRP1A_STRT=0x1f WRP1A_END=0"
fi
erase_all="-e all"
sec_size_protect="-ob SEC_SIZE=0"
default_ob="-ob BOOT_LOCK=0"

echo "Regression to RDP 0"
"$stm32programmercli" $connect_no_reset $rdp_0
ret=$?
if [ $ret != 0 ]; then
  "$stm32programmercli" $connect_reset $rdp_0
  ret=$?
  if [ $ret != 0 ]; then
    if [ "$1" != "AUTO" ]; then read -p "regression script failed, press a key" -n1 -s; fi
    exit 1
  fi
fi

echo "Remove bank1 protection"
"$stm32programmercli" $connect_reset $remove_bank1_protect
ret=$?
if [ $ret != 0 ]; then
  if [ "$1" != "AUTO" ]; then read -p "regression script failed, press a key" -n1 -s; fi
  exit 1
fi

echo "Remove SEC_SIZE protection"
"$stm32programmercli" $connect_reset $sec_size_protect
ret=$?
if [ $ret != 0 ]; then
  if [ "$1" != "AUTO" ]; then read -p "regression script failed, press a key" -n1 -s; fi
  exit 1
fi

echo "Set default OB"
"$stm32programmercli" $connect_reset $default_ob
ret=$?
if [ $ret != 0 ]; then
  if [ "$1" != "AUTO" ]; then read -p "regression script failed, press a key" -n1 -s; fi
  exit 1
fi
if [ "$1" != "AUTO" ]; then read -p "regression script Done, press a key" -n1 -s; fi
exit 0