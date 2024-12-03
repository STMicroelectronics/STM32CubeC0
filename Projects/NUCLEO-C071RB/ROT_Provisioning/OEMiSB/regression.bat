@echo off
call ../env.bat

:: Enable delayed expansion
setlocal EnableDelayedExpansion

:: Initial configuration
set connect_no_reset=-c port=SWD mode=Hotplug
set connect_reset=-c port=SWD mode=UR

::Remove protections and Initialize option bytes

if /i "%product_id%" == "STM32C071XX" (
set remove_bank1_protect=-ob WRP1A_STRT=0x3f WRP1A_END=0
)
if /i "%product_id%" == "STM32C051XX" (
set remove_bank1_protect=-ob WRP1A_STRT=0x1f WRP1A_END=0
)
set rdp_0=-ob RDP=0xAA
set sec_size_protect=-ob SEC_SIZE=0
set default_ob=-ob BOOT_LOCK=0
set erase_all=-e all

::RDP Regression
echo Regression to RDP 0
%stm32programmercli% %connect_reset% %rdp_0%
IF !errorlevel! NEQ 0 goto :step_error

::Remove Bank1 Protections
echo  Remove Bank1 protection
%stm32programmercli% %connect_reset% %remove_bank1_protect%
IF !errorlevel! NEQ 0 goto :step_error

::Remove SEC_SIZE protection
echo Remove SEC_SIZE protection
%stm32programmercli% %connect_reset% %sec_size_protect%
IF !errorlevel! NEQ 0 goto :step_error

::Set Default OB
echo Set Default OB (BOOT_LOCK)
%stm32programmercli% %connect_reset% %default_ob%
IF !errorlevel! NEQ 0 goto :step_error

echo regression script done, press key
IF [%1] NEQ [AUTO] pause
exit 0

:step_error
echo regression script failed, press key
IF [%1] NEQ [AUTO] pause
exit 1
