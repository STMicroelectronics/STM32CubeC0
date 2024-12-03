@ECHO OFF

:: Enable delayed expansion
setlocal EnableDelayedExpansion
set "projectdir=%~dp0"
:: Getting the CubeProgammer_cli path
call ../env.bat
:: Application binary file
set appli_binary=%projectdir%..\..\%oemisb_appli_path_project%\Binary\OEMiSB_Appli.bin
set boot_binary=%projectdir%..\..\%oemisb_boot_path_project%\Binary\OEMiSB_Boot.bin
:: Sha.bin
set sha256=%projectdir%\Binary\sha256.bin

set SecSize=0x4
set bootaddress=0x8000000
set appliaddress=0x8002000
set shaaddress=0x8001FC0
:: CubeProgammer connection
set connect_no_reset=-c port=SWD mode=Hotplug
set connect_reset=-c port=SWD mode=UR

:: =============================================== Remove protections and initialize Option Bytes  ==========================================
if /i "%product_id%" == "STM32C071XX" (
set remove_protect_init=-ob WRP1A_STRT=0x3f WRP1A_END=0 SEC_SIZE=0 BOOT_LOCK=0
)
if /i "%product_id%" == "STM32C051XX" (
set remove_protect_init=-ob WRP1A_STRT=0x1f WRP1A_END=0 WRP1B_STRT=0x1f WRP1B_END=0 SEC_SIZE=0 BOOT_LOCK=0
)
if /i "%product_id%" == "STM32C092XX" (
set remove_protect_init=-ob WRP1A_STRT=0x7f WRP1A_END=0 WRP1B_STRT=0x7f WRP1B_END=0 SEC_SIZE=0 BOOT_LOCK=0
)
:: =============================================== Erase the user flash =====================================================================
set erase_all=-e all

:: ================================================ hardening ===============================================================================
set hide_protect=SEC_SIZE=%SecSize%

set isGeneratedByCubeMX=%PROJECT_GENERATED_BY_CUBEMX%
:: CubeProgammer path and input files
set state_change_log="provisioning.log"

set appli_main_h="%projectdir%..\..\Applications\ROT\OEMiSB_Appli\Inc\main.h"
set boot_main_h="%projectdir%..\..\Applications\ROT\OEMiSB_Boot\Inc\main.h"
set boot_cfg_h="%projectdir%..\..\Applications\ROT\OEMiSB_Boot\Inc\boot_cfg.h"
set icf_appli="%projectdir%..\..\Applications\ROT\OEMiSB_Appli\EWARM\stm32c071xx_flash.icf"
set sct_appli="%projectdir%..\..\Applications\ROT\OEMiSB_Appli\MDK-ARM\stm32c0xx_app.sct"

:: Initial configuration
set connect_no_reset=-c port=SWD mode=Hotplug
set connect_reset=-c port=SWD mode=UR

goto exe:
goto py:
:exe
::line for window executable
set "applicfg=%cube_fw_path%\Utilities\PC_Software\ROT_AppliConfig\dist\AppliCfg.exe"
set "python= "
if exist %applicfg% (
echo run config Appli with windows executable
goto prov
)
:py
::line for python
echo run config Appli with python script
set "applicfg=%cube_fw_path%\Utilities\PC_Software\ROT_AppliConfig\AppliCfg.py"
set "python=python "

:prov
echo =====
echo ===== Provisioning of OEMiSB boot path
echo ===== Application selected through env.bat:
echo ===== %oemisb_boot_path_project%
echo =====
echo.


echo Step 1 : Product configuration
:: ============================================================= RDP selection ==============================================================
:define_rdp_level
set "action=Define final RDP value"
echo    * %action%
set /p "RDP_level=      %USERREG% [ 0 | 1 | 2 ]: "

if /i "%RDP_level%" == "0" (
echo.
set rdp_value=0xAA
set rdp_str="OB_RDP_LEVEL_0"
goto next
)

if /i "%RDP_level%" == "1" (
echo.
set rdp_value=0xBB
set rdp_str="OB_RDP_LEVEL_1"
goto next
)

if /i "%RDP_level%" == "2" (
echo.
set rdp_value=0xCC
set rdp_str="OB_RDP_LEVEL_2"
goto next
)

echo        WRONG RDP level selected
set current_log_file="./*.log files "
echo;
goto define_rdp_level

:next
:: ========================================================= Data size selection ==============================================================

:define_data_size
set "action=Define data area size in Kbytes"
echo    * %action%
set /p "data_size=      %USERREG% [ 0 | 2 | 4 | 6 | 8 | 10 | 12 | 14 | 16 ]: "

if /i "%data_size%" == "0" (
echo.
set data_hex_val=0x0
set subregion_val=0xFF
goto next1
)

if /i "%data_size%" == "2" (
echo.
set data_hex_val=0x800
set subregion_val=0x7F
goto next1
)

if /i "%data_size%" == "4" (
echo.
set data_hex_val=0x1000
set subregion_val=0x3F
goto next1
)

if /i "%data_size%" == "6" (
echo.
set data_hex_val=0x1800
set subregion_val=0x1F
goto next1
)

if /i "%data_size%" == "8" (
echo.
set data_hex_val=0x2000
set subregion_val=0xF
goto next1
)

if /i "%data_size%" == "10" (
echo.
set data_hex_val=0x2800
set subregion_val=0x7
goto next1
)

if /i "%data_size%" == "12" (
echo.
set data_hex_val=0x3000
set subregion_val=0x3
goto next1
)

if /i "%data_size%" == "14" (
echo.
set data_hex_val=0x3800
set subregion_val=0x1
goto next1
)

if /i "%data_size%" == "16" (
echo.
set data_hex_val=0x4000
set subregion_val=0x0
goto next1
)

echo        WRONG Data size selected
set current_log_file="./*.log files "
echo;
goto define_data_size

:next1
set tmp_file="%projectdir%\tmp.c"
echo DATA_SIZE=%data_hex_val% > %tmp_file%
echo DATA_MPU_SUB_REG=%subregion_val% >> %tmp_file%
%python%%applicfg% definevalue -l %tmp_file% -m DATA_SIZE -n DATA_SIZE %boot_main_h%
%python%%applicfg% definevalue -l %tmp_file% -m DATA_SIZE -n DATA_SIZE %appli_main_h%
%python%%applicfg% definevalue -l %tmp_file% -m DATA_MPU_SUB_REG -n DATA_MPU_SUB_REG %boot_main_h%
%python%%applicfg% linker -l %tmp_file% -m DATA_SIZE -n FLASH_DATA_AREA_SIZE %icf_appli%
%python%%applicfg% linker -l %tmp_file% -m DATA_SIZE -n FLASH_DATA_AREA_SIZE %sct_appli%
%python%%applicfg% modifyfilevalue --variable OEMISB_OB_RDP_LEVEL_VALUE --value %rdp_str% %boot_cfg_h% --str

if /i "%product_id%" == "STM32C071XX" (
set /a "wrpend= 0x3F - data_hex_val/0x800"
)

if /i "%product_id%" == "STM32C051XX" (
set /a "wrpend= 0x1F - data_hex_val/0x800"
)

if /i "%product_id%" == "STM32C092XX" (
set /a "wrpend= 0x7F - data_hex_val/0x800"
)
set write_protect=WRP1A_STRT=0x0 WRP1A_END=%wrpend%

:: ========================================================= Project generation steps ========================================================
echo Step 2 : Projects generation
echo    * Boot project generation
echo        Open the OEMiSB_Boot project with preferred toolchain and rebuild all files.
echo        Press any key to continue...
echo.
if [%1] neq [AUTO] pause >nul

echo    * Application project generation
echo        Open the OEMiSB_Appli project with preferred toolchain and rebuild all files.
echo        Press any key to continue...
echo.
if [%1] neq [AUTO] pause >nul

:: ================================================= Option Bytes and flash programming =====================================================
echo Step 3 : Product programming
set "action=Programming the option bytes and flashing binaries ..."
set current_log_file=%ob_flash_log%


set "action=Remove protection and flash erase"
echo    * %action%
%stm32programmercli% %connect_reset% -ob RDP=0xAA >> %state_change_log%
IF !errorlevel! NEQ 0 goto :step_error

%stm32programmercli% %connect_reset% %remove_protect_init% %erase_all% >> %state_change_log%
IF !errorlevel! NEQ 0 goto :step_error

:: ==================================================== Download Binaries ====================================================================
echo.
set "action=Project flash programming"
echo    * %action%

set "action=OEMiSB application programming"
echo        - %action%
%stm32programmercli% %connect_reset% -d %appli_binary% %appliaddress% -v >> %state_change_log%
IF !errorlevel! NEQ 0 goto :step_error
set "action=OEMiSB_Appli Written"
echo %action% >> ob_flash_programming.log



set "action=OEMiSB boot programming"
echo        - %action%
%stm32programmercli% %connect_reset% -d %boot_binary% %bootaddress% -v >> %state_change_log%
IF !errorlevel! NEQ 0 goto :step_error

set "action=OEMiSB_Boot Written"
echo %action% >> %state_change_log%

set "action=OEMiSB application SHA256 programming"
echo        - %action%
%python%%applicfg% hashcontent tmp.bin -i %appli_binary% -t "8000" -d %sha256%
%stm32programmercli% %connect_reset% -d %projectdir%..\..\ROT_Provisioning\OEMiSB\Binary\sha256.bin %shaaddress% -v --skipErase >> %state_change_log%
IF !errorlevel! NEQ 0 goto :step_error
set "action=SHA Appli Written"
echo %action% >> ob_flash_programming.log

:: ========================================================= Option Bytes programming ======================================================== 
echo.
echo    * Configure Option Bytes:
echo        - Write Protection
echo        - Hide Protection
echo        - Boot Lock
echo        Press any key to continue...
if [%1] neq [AUTO] pause >nul
%stm32programmercli% %connect_reset% -ob %write_protect% %hide_protect% BOOT_LOCK=1 >> %state_change_log%
if !errorlevel! neq 0 goto :step_error
echo.

set "action=Configure Option Bytes Done"
echo %action% >> %state_change_log%

:: Set the RDP of the STM32C0 product
set "action=Setting the final RDP Level %RDP_level%"
set current_log_file=%state_change_log%
echo    * %action%
%stm32programmercli% %connect_reset% -ob RDP=%rdp_value% >> %state_change_log%
:: cub prog issue: not able to return to level0 from level1
:: Error: Expected value for Option Byte "rdp": 0xAA, found: 0x0
:: Error: Option Byte Programming failed
echo.
if "%rdp_value%" == "0xAA" ( goto final_execution )
echo    * Please unplug USB cable and plug it again to recover SWD Connection.
echo        Press any key to continue...
echo.
if [%1] neq [AUTO] pause >nul
:: In the final product state, the connection with the board is lost and the return value of the command cannot be verified
goto final_execution

:: ============================================================= End functions =============================================================
:: All the steps to set the STM32C0 product were executed correctly
:final_execution
echo =====
echo ===== The board is correctly configured.
echo =====
cmd /k
exit 0

:: Error when external script is executed
:step_error
echo.
echo =====
echo ===== Error while executing "%action%".
echo ===== See %current_log_file% for details. Then try again.
echo =====
cmd /k
exit 1