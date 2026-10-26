rem _snap_ver.bat build_client.g_use_ver build_client.g_branch_name

@echo %1 %2 %3

set startTm=%time%

set srcDir=d:\_AutoBuild\edition\%2\Shipping_Bin\CQYH\
set targDir=d:\_ver\%1\CQYH
set targetMPQ=d:\_ver\%1_MPQ\CQYH

set targLauncerCfg=d:\_ver\%1_Launcer\
set targPDB=d:\_ver\%1_PDB_%3\

set pdbFile=d:\_AutoBuild\Source\08.Prog%2\Client\UE3\Binaries\Win32\MMOGame-Win32-Shipping
md %targDir%
md %targLauncerCfg%
md %targPDB%

set packDirDat=C:\_pack_dir\zip\CQYH\

copy /Y %pdbFile%.pdb %targPDB%
copy /Y %pdbFile%.exe %targPDB%

rem pause

robocopy %srcDir% %targDir%\ *.* /MIR /MT:128 /NFL /NDL /NS /NC
rem pause

del /F /Q %targDir%\MMOGame\Config\MMO*.ini
del /F /Q %targDir%\MMOGame\Config\spell_var.db
rem pause

rd /S /Q %targDir%\MMOGame\Config\Mac
rd /S /Q %targDir%\MMOGame\Config\Mobile
rd /S /Q %targDir%\MMOGame\Config\PCServer
rd /S /Q %targDir%\MMOGame\Config\UnrealFrontend.DefaultProfiles
rem pause

move /Y %targDir%\LocalVersion.xml %targLauncerCfg%

md %targetMPQ%
PakPatcher.exe ver %targDir%\ %targetMPQ%\

xcopy %targDir% %targetMPQ%\ /s /y /r /EXCLUDE:%~dp0_snap_ver_mpq_copy_exclude.txt
@echo %startTm% %time%