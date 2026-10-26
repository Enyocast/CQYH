REM ## used by guardserver to publish(update) version files
set VersionFileName=%1
set VersionNo=%VersionFileName:.zip=%

cd .\version

REM ####
..\7z.exe -y x %VersionFileName%
IF NOT EXIST ".\%VersionNo%" (
	cd ..
	echo "error: 7z extract %VersionFileName% failed!" > version.txt	
	GOTO :EOF
)

IF NOT EXIST ".\%VersionNo%\globalconfig" (
	mkdir ".\%VersionNo%\globalconfig"
)
copy %VersionFileName%-area_config.lua .\%VersionNo%\globalconfig\area_config.lua /Y
IF NOT %ERRORLEVEL% == 0 (
	cd ..
	echo "error: copy %VersionFileName%-area_config.lua failed!" > version.txt	
	GOTO :EOF
)

REM #### delete specific folder
cd ..

call :try_del dbserver
call :try_del manageserver
call :try_del gameserver
call :try_del gateserver
call :try_del datalogserver
call :try_del loginserver
call :try_del balanceserver
call :try_del gmserver

rd cache /S/Q
call :try_del data
del /Q global_config.lua
del /Q gpkitsvr64.dll
del /Q SdoBase.dll
del /Q sotsapi

IF NOT %ERRORLEVEL% == 0 (
	echo "error: remove server folder failed!" > version.txt	
	GOTO :EOF
)

xcopy version\%VersionNo%\* .\	/E/I/R/Y /EXCLUDE:version\version_exclude.txt
IF NOT %ERRORLEVEL% == 0 (
	echo "error: copy all files outer failed!" > version.txt	
	GOTO :EOF
)

echo %VersionFileName% > version.txt	

REM #### as current version info
echo %VersionFileName% > current_server_version.txt	
goto :EOF

REM #### sub routine
:try_del
setlocal
  IF EXIST %VersionNo% ( 
    del /Q %VersionNo%\*.*
    rd /Q %VersionNo% 
  )
endlocal&goto :EOF
