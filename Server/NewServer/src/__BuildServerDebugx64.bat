call "%VS120COMNTOOLS%vsvars32.bat"

devenv universe.sln /Rebuild "Debug|x64" 

p4 revert -a

pause