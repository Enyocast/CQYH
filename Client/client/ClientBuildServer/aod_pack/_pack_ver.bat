set packDir=C:\AutoBuild\aod_pack\
set srcFileDir=C:\AutoBuild\edition\Shipping_Bin\
set patchDir=D:\xampp\htdocs\aodpatch\Install\%1\
set zipSrcDir=c:\zip_%1\s\
@echo %1 %patchDir%

md %patchDir%

rem set srcFileDir=C:\AutoBuild\edition\editor_bin\BinariesEditor\win32\
rem set srcFileDir=C:\AutoBuild\Source\08.Prog\Client\UE3\Launcher\
rem set srcFileDir=C:\AutoBuild\edition\client_bin\BinariesDev\

set startTm=%time%


rem %1 verId  %2 dir 
rem -----------------------------------------------
rem C:\AutoBuild\aod_pack\__pare_packdir.bat %1
rem set srcDir=C:\AutoBuild\edition\Shipping_Bin\CQYH\
set srcDir=d:\_ver\%1\CQYH\
set srcLauncerCfg=d:\_ver\%1_Launcer\

set packDirBin=C:\_pack_dir\bin\CQYH\
set packDirDat=C:\_pack_dir\zip\CQYH\
set srcZipDirDat=C:\_pack_dir\zip\

path %path%;"C:\Program Files (x86)\WinZip\"
set zipDir=c:\zip_%1\
set zipSplitDir=c:\zip_%1\s\

rd %zipDir%  /S /Q
rd %zipSplitDir%  /S /Q

md %zipDir%
md %zipSplitDir%

rem rd %packDirBin% /S /Q
rem rd %packDirDat% /S /Q

rem md %packDirBin%
rem md %packDirDat%
rem copy /Y
rem xcopy /S /F /Y /R /Q'

copy /Y %srcLauncerCfg%LocalVersion.xml %packDirBin%

robocopy %srcDir% %packDirBin% *.* /MT:128
rem pause

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
robocopy %srcDir%MMOGame\Movies\ %packDirBin%MMOGame\Movies\ *.* /E /MT:128
robocopy %srcDir%MMOGame\Splash\ %packDirBin%MMOGame\Splash\ *.* /E /MT:128
robocopy %srcDir%MMOGame\CookedPC\ %packDirBin%MMOGame\CookedPC\ *.u

robocopy %srcDir%MMOGame\CookedPC\ %packDirDat%MMOGame\CookedPC\ *.* /E /MT:128 /MIR
del /Q /F %packDirDat%MMOGame\CookedPC\*.u


wzzip -r -p -a %zipDir%CQYH.zip %srcZipDirDat%
wzzip -ys1843200 %zipDir%CQYH.zip %zipSplitDir%
rem -----------------------------------------------

rem C:\7-Zip\7z.exe a CQYH.7z %srcFileDir%*.*  -r -t7z  -v1800m

rem %packDir%7za\7za.exe a CQYH.zip %srcFileDir%*.*  -r -tzip  -v1800m

rem pause

rem move /Y *.zip.* %2

rem rename_zip.rename_zip('C:\zip_888\s')
%packDir%Python27\python.exe %packDir%7za\rename_zip.py %zipSrcDir%
%packDir%Python27\python.exe %packDir%7za\gen_vinfo_zip.py %zipSrcDir% %packDir%Client\VolumInfo.ini %1

rem pause

%packDir%SD_NSIS\makensis.exe %packDir%CQYH_Setup.nsi
rem %packDir%NSIS2.46\makensis.exe %packDir%CQYH_Setup.nsi
rem SD_NSIS NSIS2.46

move /Y %packDir%CQYH_Setup*.exe %patchDir%
move /Y %zipSrcDir%*.* %patchDir%

rd /S /Q %zipDir%

@echo %startTm% %time%