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
del /F /Q %targDir%\MMOGame\Config\pk_drop_rate.txt
del /F /Q %targDir%\MMOGame\Config\pk_drop_count.txt
del /F /Q %targDir%\MMOGame\Config\drop_npc_id.txt
del /F /Q %targDir%\MMOGame\Config\attribute_pool.txt
del /F /Q %targDir%\MMOGame\Config\activateSys.txt
del /F /Q %targDir%\MMOGame\Config\adventure.txt
del /F /Q %targDir%\MMOGame\Config\air_level.txt
del /F /Q %targDir%\MMOGame\Config\arena_score.txt
del /F /Q %targDir%\MMOGame\Config\decompose.txt
del /F /Q %targDir%\MMOGame\Config\gm_log_note.txt
del /F /Q %targDir%\MMOGame\Config\heavenBlood.txt
del /F /Q %targDir%\MMOGame\Config\hero_attribute1.txt
del /F /Q %targDir%\MMOGame\Config\hero_level.txt
del /F /Q %targDir%\MMOGame\Config\ItemStoreCategory.txt
del /F /Q %targDir%\MMOGame\Config\level_damage_mod.txt
del /F /Q %targDir%\MMOGame\Config\money.txt
del /F /Q %targDir%\MMOGame\Config\new_ai.txt
del /F /Q %targDir%\MMOGame\Config\npc_affix.txt
del /F /Q %targDir%\MMOGame\Config\npc_pattern.txt
del /F /Q %targDir%\MMOGame\Config\npc_relation.txt
del /F /Q %targDir%\MMOGame\Config\pet.txt
del /F /Q %targDir%\MMOGame\Config\spell_node.txt

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