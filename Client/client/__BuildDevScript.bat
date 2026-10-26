call "%VS100COMNTOOLS%vsvars32.bat"

UE3\Binaries\Win32\MMOGame.exe make -auto -NOPAUSEONSUCCESS -dev_release -full


rem devenv UE3\Development\Src\UE3.sln /Project protocol /Rebuild "Release|Mixed platforms" 
rem devenv UE3\Development\Src\UE3.sln /Rebuild "Release|Mixed platforms" 



rem UE3\Binaries\Win32\MMOGame.com make -auto -build_machine -dev_release -full
