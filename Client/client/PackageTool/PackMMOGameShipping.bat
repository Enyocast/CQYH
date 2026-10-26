


set mmoGame=AgeOfDawn(CB1)
set isccDir=C:\AutoBuild\\Source\08.Prog\Client\PackageTool\

call %isccDir%MMOGameVer.bat
@echo %mmoVer%

set outISSFile=%isccDir%makeinstall.iss
set outExeFile=%mmoGame%%mmoVer%
rem set ReleaseDir=D:\xampp\htdocs\aodpatch\Install\
set ReleaseDir=c:\
set startTime1=%time%

rem @echo [LangOptions]
rem @echo LanguageName=<4E2D><6587><7B80><4F53>


@echo [Setup] > %outISSFile%
@echo AppName=%mmoGame% >> %outISSFile%
@echo AppVerName=%mmoVer% >> %outISSFile%
@echo AppVersion=1.0 >> %outISSFile%
@echo DefaultDirName=c:\%outExeFile% >> %outISSFile%
@echo DefaultGroupName=%mmoGame%%mmoVer% >> %outISSFile%
@echo SetupIconFile=..\UE3\Binaries\InstallData\GameIcon.ico >> %outISSFile%
@echo UninstallDisplayIcon={app}\AOD\Binaries\InstallData\Uninstall.ico >> %outISSFile%
@echo Compression=lzma2/max >> %outISSFile%
@echo CompressionThreads=24 >> %outISSFile%
@echo LZMANumBlockThreads=12 >> %outISSFile%

@echo SolidCompression=no >> %outISSFile%
@echo OutputDir=%ReleaseDir%%mmoVer%\ >> %outISSFile%
@echo OutputBaseFilename=%outExeFile% >> %outISSFile%
@echo WizardImageFile=ISSkin\Styles\Office2007Gray.bmp >> %outISSFile%
@echo WizardSmallImageFile=compiler:WizModernSmallImage-IS.bmp >> %outISSFile%
@echo DiskSpanning=yes >> %outISSFile%

rem ------------------------------------------------------------------------------------------------------------
@echo [Files] >> %outISSFile%
rem @echo Source: "Fonts\*"; DestDir: "{fonts}";Flags:onlyifdoesntexist uninsneveruninstall >> %outISSFile%
@echo Source: "..\UE3\Binaries\Redist\*"; DestDir: "{app}\AOD\Redist\" >> %outISSFile%
@echo Source: "..\UE3\Binaries\InstallData\*"; DestDir: "{app}\AOD\BinariesShipping\InstallData\" >> %outISSFile%
@echo Source: "directx_Jun2010_redist\*"; DestDir: "{app}\AOD\Redist\directx_Jun2010_redist\";Components:DX9 >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Flash\Fonts\*.ttf"; DestDir: "{fonts}"; FontInstall: "*"; Flags: onlyifdoesntexist uninsneveruninstall

@echo Source: "C:\AutoBuild\edition\Shipping_Bin\*"; DestDir: "{app}";Flags:recursesubdirs >> %outISSFile%
rem @echo Source: "..\UE3\BinariesShipping\Win32\MMOGame-Win32-Shipping.exe"; DestDir: "{app}\AOD\BinariesShipping\Win32\";Excludes: "ExampleGame*.*,UDKGame*.*,*Debug*,*Shipping*" >> %outISSFile%
rem @echo Source: "..\UE3\BinariesShipping\Win32\*.dll"; DestDir: "{app}\AOD\BinariesShipping\Win32\";Excludes:wxmsw28ud_*.*,p4*.*,AgentInterface*.*,WindowsTools*.*,StandaloneSymbolParser*.*" >> %outISSFile%
rem  @echo Source: "..\UE3\BinariesShipping\Win32\MMOGame.pdb"; DestDir: "{app}\AOD\BinariesShipping\Win32\" >> %outISSFile%
rem @echo Source: "..\UE3\BinariesShipping\Win32\*.config"; DestDir: "{app}\AOD\BinariesShipping\Win32\";Excludes: "ExampleGame*.*,UDKGame*.*,*Debug*,*Shipping*" >> %outISSFile%

@echo Source: ISSkin\ISSkin.dll; DestDir: {app}; Flags: dontcopy >> %outISSFile%
@echo Source: ISSkin\Styles\Office2007.cjstyles; DestDir: {tmp}; Flags: dontcopy >> %outISSFile%
rem ------------------------------------------------------------------------------------------------------------
@echo [Code] >> %outISSFile%
@echo procedure LoadSkin(lpszPath: String; lpszIniFileName: String); >> %outISSFile%
@echo external 'LoadSkin@files:isskin.dll stdcall'; >> %outISSFile%
@echo procedure UnloadSkin(); >> %outISSFile%
@echo external 'UnloadSkin@files:isskin.dll stdcall'; >> %outISSFile%
@echo function ShowWindow(hWnd: Integer; uType: Integer): Integer; >> %outISSFile%
@echo external 'ShowWindow@user32.dll stdcall'; >> %outISSFile%
@echo function InitializeSetup(): Boolean; >> %outISSFile%
@echo begin >> %outISSFile%
@echo   ExtractTemporaryFile('Office2007.cjstyles'); >> %outISSFile%
@echo   LoadSkin(ExpandConstant('{tmp}\Office2007.cjstyles'), 'NormalBlack.ini'); >> %outISSFile%
@echo   Result := True; >> %outISSFile%
@echo end;  >> %outISSFile%
@echo procedure DeinitializeSetup();  >> %outISSFile%
@echo begin  >> %outISSFile%
@echo  ShowWindow(StrToInt(ExpandConstant('{wizardhwnd}')), 0);  >> %outISSFile%
@echo  UnloadSkin();  >> %outISSFile%
@echo end;   >> %outISSFile%
rem ------------------------------------------------------------------------------------------------------------
@echo [Components] >> %outISSFile%
@echo Name:UDKRedist;Description:"安装运行库";Types:full >> %outISSFile%
@echo Name:DotNetFX;Description:"安装.net运行库";Types:full >> %outISSFile%
@echo Name:DX9;Description:"安装DirectX";Types:full >> %outISSFile%
rem ------------------------------------------------------------------------------------------------------------
@echo [Icons] >> %outISSFile%
rem @echo Name: "{group}\%mmoGame%%mmoVer%"; Filename: "{app}\AOD\BinariesShipping\Win32\MMOGame.exe";Parameters:"-seekfreeloading" >> %outISSFile%
@echo Name: "{group}\%mmoGame%%mmoVer%"; Filename: "{app}\AOD\BinariesShipping\Win32\MMOGame-Win32-Shipping.exe";Parameters:"–seekfreeloading -FINAL_RELEASE -nohomedir -LANGUAGE=CHN" >> %outISSFile%
@echo Name: "{group}\删除 %outExeFile%"; Filename: "{uninstallexe}" >> %outISSFile%
rem ------------------------------------------------------------------------------------------------------------
@echo [Run] >> %outISSFile%
@echo Filename: "{app}\AOD\BinariesShipping\InstallData\dotNetFx40_Full_x86_x64.exe";Components:DotNetFX >> %outISSFile%
@echo Filename: "{app}\AOD\Redist\UE3Redist.exe";Components:UDKRedist >> %outISSFile%
@echo Filename: "{app}\AOD\Redist\directx_Jun2010_redist\DXSETUP.exe";Components:DX9;Parameters:"/silent" >> %outISSFile%
rem ------------------------------------------------------------------------------------------------------------
@echo [UninstallDelete] >> %outISSFile%
@echo Type: files; Name: "{app}\AOD\*" >> %outISSFile%

rem pause
md %ReleaseDir%%mmoVer%\
%isccDir%InnoSetup\ISCC.exe %outISSFile%

set startTime2=%time%


rem md %ReleaseDir%%mmoVer%\
rem xcopy %outExeFile%*.* %ReleaseDir%%mmoVer%\ /Y

rem md %ReleaseDir%PDB\%mmoVer%\
rem xcopy ..\UE3\BinariesShipping\Win32\MMOGame.pdb %ReleaseDir%PDB\%mmoVer%\ /Y

rem xcopy %outExeFile%.exe %ReleaseDir% /Y

set startTime3=%time%
set targDir=%ReleaseDir% %mmoVer%
set msg=客户端打包版本完成:%mmoVer%\r\n开始时间：%startTime1% \r\n打包完成时间：%startTime2% \r\n复制到服务器时间：%startTime3% \r\n %targDir% 

@echo #coding:utf-8 > notify.py
@echo import rtx >> notify.py
@echo rtx.send_msg('%msg%') >> notify.py
rem .\Python27\python.exe notify.py
