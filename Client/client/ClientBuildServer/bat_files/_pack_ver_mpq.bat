call D:\_AutoBuild\bat_files\_var_cfg.bat %1_MPQ

set backCD=%cd%

@echo %1 %patchDir%

md %patchDir%

set startTm=%time%


rem %1 verId
rem -----------------------------------------------
rem C:\AutoBuild\aod_pack\__pare_packdir.bat %1
rem set srcDir=C:\AutoBuild\edition\Shipping_Bin\CQYH\
path %path%;"C:\Program Files (x86)\WinZip\"

@echo %srcZipDirDat%


copy /Y %srcLauncerCfg%LocalVersion.xml %srcDir%

call %packDir%Python27\python.exe %packDir%7za\gen_nsis_hdr.py %zipSplitDir% %packDir%Client\VolumInfo.ini %1 %packDir%aod_ver.nsh

call D:\_AutoBuild\aod_pack\auto_nsis.bat D:\_AutoBuild\aod_pack\CQYH_Setup.nsi d:\_ver\%1_MPQ\

move /Y %packDir%CQYH_Setup*.exe %patchDir%
move /Y %packDir%*.zip %patchDir%
move /Y %packDir%*.cab %patchDir%

rem osrd/S /Q %zipDir%

@echo %startTm% %time%
cd %backCD%