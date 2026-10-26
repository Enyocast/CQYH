set startTime1=%time%
echo "%VS100COMNTOOLS%vsvars32.bat"

rem devenv UE3\Development\Src\UE3.sln /Project protocol /Build "Shipping|Mixed platforms" 
devenv UE3\Development\Src\UE3.sln /Project "MMOGame Win32" /Build "Shipping|Mixed platforms" 

xcopy .\UE3\Binaries\Win32\*.* .\UE3\BinariesRelease\Win32\  /S /F /Y /R /EXCLUDE:UpdateBinExclude.txt
pause