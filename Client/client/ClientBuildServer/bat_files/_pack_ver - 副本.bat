call D:\_AutoBuild\bat_files\_var_cfg.bat %1

@echo %1 %patchDir%

md %patchDir%

set startTm=%time%


rem %1 verId
rem -----------------------------------------------
rem C:\AutoBuild\aod_pack\__pare_packdir.bat %1
rem set srcDir=C:\AutoBuild\edition\Shipping_Bin\CQYH\
path %path%;"C:\Program Files (x86)\WinZip\"

@echo %srcZipDirDat%
rem pause

rd %srcZipDirDat%..\ /S /Q


rem osrd%zipDir%  /S /Q
rem osrd%zipSplitDir%  /S /Q

md %zipDir%
md %zipSplitDir%

rem rem osrd%packDirBin% /S /Q
rem rem osrd%packDirDat% /S /Q

md %packDirBin%
md %packDirDat%
rem copy /Y
rem xcopy /S /F /Y /R /Q'

copy /Y %srcLauncerCfg%LocalVersion.xml %packDirBin%

rem robocopy %srcDir% %packDirBin% *.* /MT:128
rem pause

rem 下面这行复制Launcher.exe
robocopy %srcDir% %packDirBin% *.*


robocopy %srcDir%Binaries\ %packDirBin%Binaries\ *.* /E /MT:128
robocopy %srcDir%Engine\ %packDirBin%Engine\ *.* /E /MT:128
robocopy %srcDir%LauncherSkin2.0\ %packDirBin%LauncherSkin2.0\ *.* /E /MT:128
robocopy %srcDir%LauncherUpdate\ %packDirBin%LauncherUpdate\ *.* /E /MT:128
robocopy %srcDir%LauncherConfigs\ %packDirBin%LauncherConfigs\ *.* /E /MT:128
robocopy %srcDir%LauncherModules\ %packDirBin%LauncherModules\ *.* /E /MT:128
robocopy %srcDir%SDO\ %packDirBin%SDO\ *.* /E /MT:128

robocopy %srcDir%MMOGame\Account\ %packDirBin%MMOGame\Account\ *.* /E /MT:128
robocopy %srcDir%MMOGame\Config\ %packDirBin%MMOGame\Config\ *.* /E /MT:128
robocopy %srcDir%MMOGame\Content\CursorAni\ %packDirBin%MMOGame\Content\CursorAni\ *.* /E /MT:128
robocopy %srcDir%MMOGame\Localization\ %packDirBin%MMOGame\Localization\ *.* /E /MT:128

robocopy %srcDir%MMOGame\Splash\ %packDirBin%MMOGame\Splash\ *.* /E /MT:128
rem 全ZIP robocopy %srcDir%MMOGame\CookedPC\ %packDirBin%MMOGame\CookedPC\ *.u

robocopy %srcDir%MMOGame\Movies\ %packDirDat%MMOGame\Movies\ *.* /E /MT:128
robocopy %srcDir%MMOGame\CookedPC\ %packDirDat%MMOGame\CookedPC\ *.* /E /MT:128 /MIR
rem 全ZIP del /Q /F %packDirDat%MMOGame\CookedPC\*.u

attrib -R %packDirDat%*.* /S /D
attrib -R %packDirBin%*.* /S /D

wzzip -r -p -a %zipDir%CQYH.zip %srcZipDirDat%
wzzip -ys1843200 %zipDir%CQYH.zip %zipSplitDir%
rem -----------------------------------------------

rem C:\7-Zip\7z.exe a CQYH.7z %srcFileDir%*.*  -r -t7z  -v1800m

rem %packDir%7za\7za.exe a CQYH.zip %srcFileDir%*.*  -r -tzip  -v1800m


rem rename_zip.rename_zip('C:\zip_888\s')
call %packDir%Python27\python.exe %packDir%7za\rename_zip.py %zipSplitDir%

rem C:\\AutoBuild\\aod_pack\\aod_ver.nsh
call %packDir%Python27\python.exe %packDir%7za\gen_vinfo_zip.py %zipSplitDir% %packDir%Client\VolumInfo.ini %1 %packDir%aod_ver.nsh
puase

rem pause

%packDir%SD_NSIS\makensis.exe %packDir%CQYH_Setup.nsi
rem %packDir%NSIS2.46\makensis.exe %packDir%CQYH_Setup.nsi
rem SD_NSIS NSIS2.46

move /Y %packDir%CQYH_Setup*.exe %patchDir%
move /Y %zipSplitDir%*.* %patchDir%

rem osrd/S /Q %zipDir%

@echo %startTm% %time%