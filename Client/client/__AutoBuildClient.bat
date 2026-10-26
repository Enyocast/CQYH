set startTime1=%time%
call "%VS100COMNTOOLS%vsvars32.bat"

rem p4 edit //heaven/Dev/08.Prog/Client/UE3/BinariesRelease/Win32/MMOGame.exe
rem p4 edit //heaven/Dev/08.Prog/Client/UE3/BinariesRelease/Win64/MMOGame.exe
p4 edit //heaven/Dev/08.Prog/Client/UE3/BinariesRelease/Win32/...
p4 edit //heaven/Dev/08.Prog/Client/UE3/BinariesRelease/Win64/...
p4 edit //heaven/Dev/08.Prog/Client/UE3/MMOGame/ScriptFinalRelease/...

UE3\BinariesRelease\Win32\MMOGame.exe make -auto -NOPAUSEONSUCCESS -final_release -full


rem devenv UE3\Development\Src\UE3.sln /Project protocol /Rebuild "Release|Mixed platforms" 
devenv UE3\Development\Src\UE3.sln /Project "MMOGame Win32" /Rebuild "Release|Mixed platforms" 
devenv UE3\Development\Src\UE3.sln /Project "MMOGame Win64" /Rebuild "Release|Mixed platforms" 


xcopy .\UE3\Binaries\Win32\*.* .\UE3\BinariesRelease\Win32\  /S /F /Y /R /EXCLUDE:UpdateBinExclude.txt
xcopy .\UE3\Binaries\Win32\*.* .\UE3\BinariesRelease\Win64\  /S /F /Y /R /EXCLUDE:UpdateBinExclude.txt

UE3\BinariesRelease\Win32\MMOGame.exe make -auto -NOPAUSEONSUCCESS -final_release -full

set startTime2=%time%

p4 revert -a
p4 submit -d AutoBuild

set notifyFile=.\PackageTool\build_notify.py
set msg=客户端散装版本更新！\r\n开始时间：%startTime1% \r\n完成时间：%startTime2%
@echo #coding:utf-8 > %notifyFile%
@echo import rtx >> %notifyFile%
@echo rtx.send_msg('%msg%') >> %notifyFile%
.\PackageTool\Python27\python.exe %notifyFile%
