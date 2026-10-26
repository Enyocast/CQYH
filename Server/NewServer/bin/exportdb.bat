:: 
set count=20000
set startNum=70000000
::
::
if exist startNum.txt( set /p var=<startNum.txt )
::
set /a startNum2=%startNum%+%count%
echo %startNum2% > startNum.txt
::
@echo start from %var%
start exportdb\exportdb.exe %startNum% %count%
::start exportdb\exportdb.exe %startNum% %count% 8 20000
pause