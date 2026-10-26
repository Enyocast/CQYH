REM ### cd E:\p4\08.Prog_CQ\NewServer

@echo off
set TGT=%1
set SRC=%~dp0
if not defined TGT (
	set /P TGT="please input a target dir name: "
)

if exist %TGT% (
	@echo target dir %TGT% has existed!
	goto :Error
)


mkdir %TGT%
copy /Y %SRC%\global_config.lua %TGT%\
copy /Y %SRC%\asimov*.bat %TGT%\
copy /Y %SRC%\Qt* %TGT%\
copy /Y %SRC%\lua* %TGT%\
copy /Y %SRC%\*.dll %TGT%\

REM ### mklink /J %TGT%\asimov %SRC%\asimov
xcopy /E/I/R/Y %SRC%\asimov %TGT%\asimov
mkdir %TGT%\commonconfig 
xcopy /E/I/R/Y %SRC%\commonconfig %TGT%\commonconfig 
mkdir %TGT%\globalconfig
xcopy /E/I/R/Y %SRC%\globalconfig %TGT%\globalconfig

del /Q %TGT%.zip
7z.exe a %TGT%.zip .\%TGT%\
goto :EOF

:Error
echo failed!
pause
