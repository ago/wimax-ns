@echo off

set db_file=WiMAX_DB.bin
set db_def_file=WiMAX_def.bin
set source_dir=%~dp0
set AppSrv=WiMAXAppSrv
set DMAgentSrv=DMAgent
set wimaxcu=WiMAXCU.exe
set cupath="%ProgramFiles%\Intel\WiMax\Bin\"
set retries=30
set retr_index=0
set tmp_file=%temp%\tmp.txt

echo -------------------------------------------
echo Replacing Wimax Operator Data Base; 
echo -------------------------------------------
echo Source data base: %source_dir%
echo -------------------------------------------

echo Stopping Services
set retr_index=0
echo Killing CU
taskkill /im %wimaxcu%
sc stop %DMAgentSrv% > nul
:stopDMAgentSrv
sc query %DMAgentSrv% | find /I "stopped" > nul
if %errorlevel% equ 0 goto nextStopDMAgentSrv
if %retr_index% equ %retries% (
	echo Error stopping %DMAgentSrv%.
	goto :end
)
rem Delay one second using ping
ping 127.0.0.1 -n 3 > nul
set /A retr_index+=1
goto stopDMAgentSrv
:nextStopDMAgentSrv

set retr_index=0
sc stop %AppSrv% > nul
:stopAppSrv
sc query %AppSrv% | find /I "stopped" > nul
if %errorlevel% equ 0 goto nextStopAppSrv
if %retr_index% equ %retries% (
	echo Error stopping %AppSrv%.
	goto :end
)
rem Delay one second using ping
ping 127.0.0.1 -n 3 > nul
set /A retr_index+=1
goto stopAppSrv
:nextStopAppSrv
rem Get target_dir
reg query HKLM\SOFTWARE\Intel\WiMAX /v BinDir | find /I "BinDir" > %tmp_file%
for /F "tokens=2,*" %%A in (%tmp_file%) do set target_dir=%%B
del %tmp_file%
echo Target dir: %target_dir%
echo setting DB file attributes to R/W
attrib -H -R "%target_dir%%db_def_file%"
attrib -H -R "%target_dir%%db_file%"
echo Replacing data base
copy /b  /y .\%db_file% "%target_dir%%db_file%"
copy /b  /y .\%db_file% "%target_dir%%db_def_file%"
echo Restoring DB file attributes to R/O (for default file)
attrib +H +R "%target_dir%%db_def_file%"

echo Restarting Services
set retr_index=0
sc start %AppSrv% > nul
:startAppSrv
sc query %AppSrv% | find /I "running" > nul
if %errorlevel% equ 0 goto nextStartAppSrv
if %retr_index% equ %retries% (
	echo Error starting %AppSrv%.
	goto :end
)
rem Delay one second using ping
ping 127.0.0.1 -n 3 > nul
set /A retr_index+=1
goto startAppSrv
:nextStartAppSrv

set retr_index=0
sc start %DMAgentSrv% > nul
:startDMAgentSrv
sc query %DMAgentSrv% | find /I "running" > nul
if %errorlevel% equ 0 goto nextStartDMAgentSrv
if %retr_index% equ %retries% (
	echo Error starting %DMAgentSrv%.
	goto :end
)
rem Delay one second using ping
ping 127.0.0.1 -n 3 > nul
set /A retr_index+=1
goto startDMAgentSrv
:nextStartDMAgentSrv

echo Restarting CU
%cupath%\%wimaxcu%

echo Done

:end
rem Cleanup
set db_file=
set db_def_file=
set source_dir=
set target_dir=
set AppSrv=
set DMAgentSrv=
set retries=
set retr_index=
set tmp_file=
set wimaxcu=
set cupath=

pause
