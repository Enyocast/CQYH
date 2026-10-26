
for %%I in (*.swf) do ..\..\..\Binaries\Win32\MMOGame.exe gfximport UI_MyComponent\%%~nI.swf -nopause
pause