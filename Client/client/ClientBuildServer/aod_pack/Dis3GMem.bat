@echo off
setlocal

if defined ProgramW6432 goto 64bit

if not exist %SystemRoot%\system32\bcdedit.exe goto withoutbcdedit

:withbcdedit
bcdedit /deletevalue increaseUserVa
if %ERRORLEVEL% == 0 (
	echo 关闭3G内存扩展成功
	set result = 0
) else (
	echo 无法关闭3G内存扩展模式！Windows错误号：%ERRORLEVEL%
	set result = 1
)
goto exit


:64bit
echo 您的系统不需要关闭3G内存扩展模式。
set result = 1
goto exit

:withoutbcdedit
echo 没能在您的系统中找到bcdedit.exe这个程序，无法关闭3G内存扩展模式，建议升级到64位系统！
set result = 1
goto exit

:exit
exit /b %result%