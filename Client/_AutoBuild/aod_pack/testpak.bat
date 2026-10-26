set packDir=C:\AutoBuild\aod_pack\
set srcFileDir=C:\AutoBuild\edition\Shipping_Bin\

rem set srcFileDir=C:\AutoBuild\edition\editor_bin\BinariesEditor\win32\
rem set srcFileDir=C:\AutoBuild\Source\08.Prog\Client\UE3\Launcher\
rem set srcFileDir=C:\AutoBuild\edition\client_bin\BinariesDev\

set startTm=%time%

@echo %1 %2
rem %1 dir %2 verId 

md %2


rem C:\7-Zip\7z.exe a aod.7z %srcFileDir%*.*  -r -t7z  -v1800m

rem %packDir%7za\7za.exe a aod.zip %srcFileDir%*.*  -r -tzip  -v1800m

rem pause

move /Y *.zip.* %2


%packDir%Python27\python.exe %packDir%7za\gen_vinfo_zip.py %2 %packDir%Client\VolumInfo.ini %1

pause

%packDir%SD_NSIS\makensis.exe %packDir%AOD_Setup.nsi
rem %packDir%NSIS2.46\makensis.exe %packDir%AOD_Setup.nsi
rem SD_NSIS NSIS2.46

move /Y %packDir%AOD_Setup*.exe %2

@echo %startTm% %time%