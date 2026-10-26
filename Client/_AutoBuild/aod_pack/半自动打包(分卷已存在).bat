@echo off
if "%PROCESSOR_ARCHITECTURE%"=="x86" (set "varArc=32") else (set "varArc=64")

if "%varArc%"=="32" goto start32
@echo 您的系统为64bit，将使用64位python帮助您完成打包过程
if "%1"=="" goto nofile
cd /d %~dp0
%~dp0SD_NSIS\Python27\python.exe %~dp0SD_NSIS\Python27\autoPatchHelper.py  -w "%1" 
@pause
goto _end_

:start32
@echo 您的系统为32bit，将使用32位python帮助您完成打包过程
if "%1"=="" goto nofile
cd /d %~dp0
%~dp0SD_NSIS\Python27\python.exe %~dp0SD_NSIS\Python27\autoPatchHelper.py  -w "%1" 
@pause
goto _end_


:nofile
@echo on
@echo 此bat仅为已存在的分卷包进行ini文件的书写和脚本的自动编译!
@echo 请将待编译的nsis脚本文件直接拖放文件到此BAT上！
@pause
:_end_