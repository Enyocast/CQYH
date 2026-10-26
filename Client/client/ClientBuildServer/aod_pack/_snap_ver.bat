rem _snap_ver.bat build_client.g_use_ver build_client.g_branch_name
@echo %1 %2

set startTm=%time%

set srcDir=C:\AutoBuild\edition\Shipping_Bin\CQYH\
set targDir=d:\_ver\%1\CQYH
set targetMPQ=d:\_ver\%1_MPQ\CQYH

set targLauncerCfg=d:\_ver\%1_Launcer\
set targPDB=d:\_ver\%1_PDB\

set pdbFile=C:\AutoBuild\Source\08.Prog%2\Client\UE3\Binaries\Win32\MMOGame-Win32_Shipping
md %targDir%
md %targLauncerCfg%
md %targPDB%

set packDirDat=C:\_pack_dir\zip\CQYH\

copy /Y %pdbFile%.pdb %targPDB%
copy /Y %pdbFile%.exe %targPDB%
rem rem pause

robocopy %srcDir% %targDir%\ *.* /MIR /MT:128
del /F /Q %targDir%\MMOGame\Config\MMO*.ini
del /F /Q %targDir%\MMOGame\Config\spell_var.db
rem pause

rd /S /Q %targDir%\MMOGame\Config\Mac
rd /S /Q %targDir%\MMOGame\Config\Mobile
rd /S /Q %targDir%\MMOGame\Config\PCServer
rd /S /Q %targDir%\MMOGame\Config\UnrealFrontend.DefaultProfiles
rem pause

move /Y %targDir%\LocalVersion.xml %targLauncerCfg%

robocopy %targDir%\ %targetMPQ%\ *.* /MIR /MT:128
robocopy %targetMPQ%\MMOGame\Splash\ %targetMPQ%\MMOGameTmp\Splash\ *.* /E
robocopy %targetMPQ%\MMOGame\Account\ %targetMPQ%\MMOGameTmp\Account\ *.* /E

rd /S /Q %targetMPQ%\MMOGame\Splash\
rd /S /Q %targetMPQ%\MMOGame\Account\
rem pause

md %targetMPQ%\MMOGamePAK
md %targetMPQ%\EnginePAK
PakPatcher.exe make %targetMPQ%\MMOGame %targetMPQ%\MMOGamePAK
PakPatcher.exe make %targetMPQ%\Engine %targetMPQ%\EnginePAK

rd /S /Q %targetMPQ%\MMOGame\
rem pause

robocopy %targetMPQ%\MMOGameTmp\ %targetMPQ%\MMOGame\ *.* /E

rd /S /Q %targetMPQ%\MMOGameTmp\
rem pause

rd /S /Q %targetMPQ%\Engine\
rem pause
rem rem pause

rem robocopy %srcDir%Binaries\ %targDir%Binaries\ *.* /E /MT:128
rem robocopy %srcDir%Engine\ %targDir%Engine\ *.* /E /MT:128
rem robocopy %srcDir%LauncherSkin2.0\ %targDir%LauncherSkin2.0\ *.* /E /MT:128
rem robocopy %srcDir%LauncherUpdate\ %targDir%LauncherUpdate\ *.* /E /MT:128
rem robocopy %srcDir%SDO\ %targDir%SDO\ *.* /E /MT:128
rem robocopy %srcDir%MMOGame\Config\ %targDir%MMOGame\Config\ *.* /E /MT:128
rem robocopy %srcDir%MMOGame\Content\CursorAni\ %targDir%MMOGame\Content\CursorAni\ *.* /E /MT:128
rem robocopy %srcDir%MMOGame\Localization\ %targDir%MMOGame\Localization\ *.* /E /MT:128
rem robocopy %srcDir%MMOGame\Movies\ %targDir%MMOGame\Movies\ *.* /E /MT:128
rem robocopy %srcDir%MMOGame\Splash\ %targDir%MMOGame\Splash\ *.* /E /MT:128
rem robocopy %srcDir%MMOGame\CookedPC\ %targDir%MMOGame\CookedPC\ *.* /E /MT:128 /MIR

rem -----------------------------------------------


rem rem pause

@echo %startTm% %time%