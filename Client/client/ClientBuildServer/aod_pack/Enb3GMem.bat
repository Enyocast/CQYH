@echo off
setlocal

if defined ProgramW6432 goto 64bit

if not exist %SystemRoot%\system32\bcdedit.exe goto withoutbcdedit

:withbcdedit
bcdedit /set increaseUserVa 2560
if %ERRORLEVEL% == 0 (
	echo 开启3G内存扩展成功!
	set result = 0
) else (
	echo 开启3G内存扩展模式失败，有可能会在游戏过程中出现程序当机，建议升级到64位系统！Windows错误号：%ERRORLEVEL%
	set result = 1s
)
goto exit

:64bit
echo 您的系统不需要开启3G内存扩展模式。
set result = 1
goto exit

:withoutbcdedit
echo 没能在您的系统中找到bcdedit.exe这个程序，无法开启3G内存扩展模式，建议升级到64位系统！
set result = 1
goto exit

:exit
exit /b %result%

