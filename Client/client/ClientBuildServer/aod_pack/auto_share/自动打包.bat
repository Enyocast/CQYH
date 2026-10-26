set packDir=C:\AutoBuild\aod_pack\
set srcFileDir=C:\AutoBuild\edition\Shipping_Bin\

%packDir%7za\7za.exe a aod.7z %srcFileDir%*.*  -r -t7z -v1g


%packDir%Python27\python.exe %packDir%\7za\gen_vinfo.py %packDir% %packDir%Client\VolumInfo.ini

%packDir%SD_NSIS\makensis.exe CQYH_Setup.nsi

pause