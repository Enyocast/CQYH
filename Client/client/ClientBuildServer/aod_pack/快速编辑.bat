@echo off
if "%1"=="" goto nofile
@start "cmd" "%~dp0SD_NSIS\VNISEdit\VNISEdit.exe" "%1"
exit
:nofile
@echo on
@echo "请直接拖放文件到此BAT上！"
@pause
