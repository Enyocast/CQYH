set packDir=C:\AutoBuild\aod_pack\
set srcFileDir=C:\AutoBuild\edition\Shipping_Bin\
rem set newSrcFileDir=C:\AutoBuild\edition\Shipping_Bin\CQYH

set curDir=%CD%
cd /d %srcFileDir%
rem ren CQYH CQYH
cd %curDir%
rem pause

rem set srcFileDir=C:\AutoBuild\edition\editor_bin\BinariesEditor\win32\
rem %1 verId  %2 Date_Time
@echo %1 %2

attrib -R -A -S -H /S /D %srcFileDir%*.*

md %2


rem %packDir%7za\7za.exe a CQYH.7z %srcFileDir%*.*  -r -t7z  -v1800m
C:\7-Zip\7z.exe a CQYH.7z %srcFileDir%*.*  -r -t7z  -v1800m
rem %packDir%7za\7za.exe a CQYH.zip %srcFileDir%*.*  -r -tzip  -v1800m

rem pause

move /Y *.7z.* %2


%packDir%Python27\python.exe %packDir%\7za\gen_vinfo.py %2 %packDir%Client\VolumInfo.ini %1

rem pause

%packDir%SD_NSIS\makensis.exe %packDir%CQYH_Setup.nsi


move /Y %packDir%CQYH_Setup*.exe %2