set packDir=C:\AutoBuild\aod_pack\
set srcFileDir=C:\AutoBuild\edition\Shipping_Bin\

rem set srcFileDir=C:\AutoBuild\edition\editor_bin\BinariesEditor\win32\
rem set srcFileDir=C:\AutoBuild\Source\08.Prog\Client\UE3\Launcher\
rem set srcFileDir=C:\AutoBuild\edition\client_bin\BinariesDev\

set startTm=%time%

@echo %1 %2
rem %1 dir %2 verId 

md %2


%packDir%7za\7za.exe a aod.7z %srcFileDir%*.*  -r -t7z  -v1024m

rem %packDir%7za\7za.exe a aod.zip %srcFileDir%*.*  -r -tzip  -v1800m

pause

move /Y *.7z.* %2


%packDir%Python27\python.exe %packDir%\7za\gen_vinfo.py %2 %packDir%Client\VolumInfo.ini %1

%packDir%SD_NSIS\makensis.exe %packDir%CQYH_Setup.nsi
rem %packDir%NSIS2.46\makensis.exe %packDir%CQYH_Setup.nsi
rem SD_NSIS NSIS2.46

move /Y %packDir%CQYH_Setup*.exe %2

@echo %startTm% %time%