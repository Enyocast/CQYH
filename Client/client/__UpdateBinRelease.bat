p4 edit //heaven/Dev/08.Prog/Client/UE3/BinariesRelease/Win32/...
p4 edit //heaven/Dev/08.Prog/Client/UE3/BinariesRelease/UnrealEdCSharp.dll

xcopy .\UE3\Binaries\Win32\*.* .\UE3\BinariesRelease\Win32\  /S /F /Y /R /EXCLUDE:UpdateBinExclude.txt
xcopy .\UE3\Binaries\Win32\MMOGame.pdb .\UE3\BinariesRelease\Win32\  /S /F /Y /R
xcopy .\UE3\Binaries\UnrealEdCSharp.dll .\UE3\BinariesRelease\  /S /F /Y /R