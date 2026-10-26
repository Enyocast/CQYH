set packDir=C:\AutoBuild\aod_pack\
set destStoreDir=D:\xampp\htdocs\aodpatch\Install\%1\
set zipSrcDir=c:\zip_%1\s\
@echo %1 %destStoreDir%

md %destStoreDir%

set startTm=%time%


rem %1 verId  %2 dir 
rem -----------------------------------------------

set srcDir=d:\_ver\%1_MPQ\CQYH\
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

rem robocopy %srcDir% %packDirBin% *.* /MT:128
rem pause

rem robocopy %srcDir% %packDirBin% *.*

robocopy %srcDir%Binaries\ %packDirBin%Binaries\ *.* /E /MT:128
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

robocopy %srcDir%EnginePAK\ %packDirDat%EnginePAK\ *.* /E /MT:128
robocopy %srcDir%MMOGamePAK\ %packDirDat%MMOGamePAK\ *.* /E /MT:128 /MIR

rem del /Q /F %packDirDat%MMOGame\CookedPC\*.u


wzzip -r -p -a %zipDir%CQYH.zip %srcZipDirDat%
wzzip -ys1843200 %zipDir%CQYH.zip %zipSplitDir%
rem -----------------------------------------------

rem pause

%packDir%Python27\python.exe %packDir%7za\rename_zip.py %zipSrcDir%
%packDir%Python27\python.exe %packDir%7za\gen_vinfo_zip.py %zipSrcDir% %packDir%Client\VolumInfo.ini %1

rem pause

%packDir%SD_NSIS\makensis.exe %packDir%CQYH_Setup.nsi
rem %packDir%NSIS2.46\makensis.exe %packDir%CQYH_Setup.nsi
rem SD_NSIS NSIS2.46

move /Y %packDir%CQYH_Setup*.exe %destStoreDir%
move /Y %zipSrcDir%*.* %destStoreDir%

rd /S /Q %zipDir%

@echo %startTm% %time%