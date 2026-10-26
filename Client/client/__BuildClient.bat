call "%VS100COMNTOOLS%vsvars32.bat"

UE3\BinariesRelease\Win32\MMOGame.com make -auto -build_machine -full


devenv UE3\Development\Src\UE3.sln /Project protocol /Rebuild "Release|Mixed platforms" 
devenv UE3\Development\Src\UE3.sln /Rebuild "Release|Mixed platforms" 



UE3\BinariesRelease\Win32\MMOGame.com make -auto -build_machine -full
