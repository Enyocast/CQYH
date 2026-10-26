call d:\_AutoBuild\bat_files\_var_cfg.bat %1_MPQ

set backCD=%cd%
set NewInstalToolPath=%packDir%\SD_NSIS\InstallTool

@echo %1 %patchDir%

md %patchDir%

set startTm=%time%


rem %1 verId
rem -----------------------------------------------
rem C:\AutoBuild\aod_pack\__pare_packdir.bat %1
rem set srcDir=C:\AutoBuild\edition\Shipping_Bin\CQYH\
path %path%;"C:\Program Files (x86)\WinZip\"

@echo %srcZipDirDat%

set srcLauncerCfg=d:\_ver\%1_Launcer\
copy /Y %srcLauncerCfg%LocalVersion.xml %srcDir%

call %packDir%\auto_nsis_newtool.bat %packDir% d:\_ver\%1_MPQ\ %1

cd %NewInstalToolPath%
call InstallMaker.bat

move /Y %packDir%\SD_NSIS\InstallTool\Inst.exe %patchDir%
move /Y %packDir%*.zip %patchDir%
move /Y %packDir%*.cab %patchDir%

rem osrd/S /Q %zipDir%

@echo %startTm% %time%
cd %backCD%