
call MMOGameVer.bat
@echo %mmoVer%

set mmoGame=AgeOfDawn(EB1)
set outISSFile=makeinstall.iss
set outExeFile=%mmoGame%%mmoVer%
set ReleaseDir=\\172.30.61.44\九天_qa版本\
set startTime1=%time%

@echo [Setup] > %outISSFile%
@echo AppName=%mmoGame% >> %outISSFile%
@echo AppVerName=%mmoVer% >> %outISSFile%
@echo AppVersion=1.0 >> %outISSFile%
@echo DefaultDirName=c:\%outExeFile% >> %outISSFile%
@echo DefaultGroupName=%mmoGame%%mmoVer% >> %outISSFile%
@echo SetupIconFile=..\UE3\BinariesRelease\InstallData\GameIcon.ico >> %outISSFile%
@echo UninstallDisplayIcon={app}\BinariesRelease\InstallData\Uninstall.ico >> %outISSFile%
@echo Compression=lzma2/max >> %outISSFile%
@echo CompressionThreads=8 >> %outISSFile%
@echo LZMANumBlockThreads=4 >> %outISSFile%

@echo SolidCompression=yes >> %outISSFile%
@echo OutputDir=. >> %outISSFile%
@echo OutputBaseFilename=%outExeFile% >> %outISSFile%
@echo WizardImageFile=.\ISSkin\Styles\Office2007Gray.bmp >> %outISSFile%
@echo WizardSmallImageFile=compiler:WizModernSmallImage-IS.bmp >> %outISSFile%
@echo DiskSpanning=yes >> %outISSFile%

rem ------------------------------------------------------------------------------------------------------------
@echo [Files] >> %outISSFile%
rem @echo Source: "Fonts\*"; DestDir: "{fonts}";Flags:onlyifdoesntexist uninsneveruninstall >> %outISSFile%
@echo Source: "..\UE3\BinariesRelease\Redist\*"; DestDir: "{app}\BinariesRelease\Redist\" >> %outISSFile%
@echo Source: "..\UE3\BinariesRelease\InstallData\*"; DestDir: "{app}\BinariesRelease\InstallData\" >> %outISSFile%
@echo Source: "directx_Jun2010_redist\*"; DestDir: "{app}\BinariesRelease\Redist\directx_Jun2010_redist\";Components:DX9 >> %outISSFile%
@echo Source: "..\UE3\BinariesRelease\Win32\*.exe"; DestDir: "{app}\BinariesRelease\Win32\";Excludes: "ExampleGame*.*,UDKGame*.*,*Debug*,*Shipping*" >> %outISSFile%
@echo Source: "..\UE3\BinariesRelease\Win32\*.dll"; DestDir: "{app}\BinariesRelease\Win32\";Excludes: "ExampleGame*.*,UDKGame*.*,*Debug*,*Shipping*" >> %outISSFile%
rem  @echo Source: "..\UE3\BinariesRelease\Win32\MMOGame.pdb"; DestDir: "{app}\BinariesRelease\Win32\" >> %outISSFile%
@echo Source: "..\UE3\BinariesRelease\Win32\*.config"; DestDir: "{app}\BinariesRelease\Win32\";Excludes: "ExampleGame*.*,UDKGame*.*,*Debug*,*Shipping*" >> %outISSFile%

@echo Source: "..\UE3\Engine\*"; DestDir: "{app}\Engine\";Flags:recursesubdirs >> %outISSFile%
rem @echo Source: "..\UE3\Engine\Localization\*"; DestDir: "{app}\Engine\Localization\";Flags:recursesubdirs >> %outISSFile%
rem @echo Source: "..\UE3\Engine\Shaders\*"; DestDir: "{app}\Engine\Shaders\";Flags:recursesubdirs;Excludes: "*.txt" >> %outISSFile%
rem @echo Source: "..\UE3\Engine\Content\*"; DestDir: "{app}\Engine\Content\";Flags:recursesubdirs;Excludes: "*.txt" >> %outISSFile%

@echo Source: "..\UE3\MMOGame\Config\*"; DestDir: "{app}\MMOGame\Config\";Excludes: "MMO*.ini,MMO*.txt" >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Localization\*"; DestDir: "{app}\MMOGame\Localization\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Movies\*"; DestDir: "{app}\MMOGame\Movies\" >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Splash\*"; DestDir: "{app}\MMOGame\Splash\";Flags:recursesubdirs >> %outISSFile%

rem @echo Source: "..\UE3\MMOGame\CookedPC\*"; DestDir: "{app}\MMOGame\CookedPC\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\Maps\_MMOMaps\Desert\*.udk"; DestDir: "{app}\MMOGame\Content\Maps\_MMOMaps\Desert\";Flags:recursesubdirs >> %outISSFile%

@echo Source: "..\UE3\MMOGame\Content\Maps\_MMOMaps\ArenaAndSeaPort\Arena01_CharacterSelection2.udk"; DestDir: "{app}\MMOGame\Content\Maps\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\Maps\HalfShowLevel.udk"; DestDir: "{app}\MMOGame\Content\Maps\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\Maps\PawnShowLevel.udk"; DestDir: "{app}\MMOGame\Content\Maps\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\Maps\LoadingTrans.udk"; DestDir: "{app}\MMOGame\Content\Maps\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\Maps\MMOLoadingMap.udk"; DestDir: "{app}\MMOGame\Content\Maps\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\Maps\UDKMaps\UT3\EnvyEntry.udk"; DestDir: "{app}\MMOGame\Content\Maps\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\*ShaderCache*.*"; DestDir: "{app}\MMOGame\Content\" >> %outISSFile%

@echo Source: "..\UE3\MMOGame\ScriptFinalRelease\*.*"; DestDir: "{app}\MMOGame\ScriptFinalRelease\";Flags:recursesubdirs >> %outISSFile%



@echo Source: "..\UE3\MMOGame\Content\MapsGlobalInfo\*"; DestDir: "{app}\MMOGame\Content\MapsGlobalInfo\";Excludes: "*.teleport" >> %outISSFile%
rem @echo Source: "..\UE3\MMOGame\Content\MMOContent\CookedPC\*.upk"; DestDir: "{app}\MMOGame\MMOContent\" >> %outISSFile%


rem @echo Source: "..\UE3\MMOGame\Content\MMOContent\Test\MMO_Player.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\Test\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\UDKContent\UT3\Pickups\Pickups.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\Test\";Flags:recursesubdirs >> %outISSFile%
rem @echo Source: "..\UE3\MMOGame\Content\MMOContent\Test\Demo_Characters.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\Test\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\MMO_DefaultPP.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\";Flags:recursesubdirs >> %outISSFile%
rem @echo Source: "..\UE3\MMOGame\Content\MMOContent\Element.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\MMOEditor.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\";Flags:recursesubdirs >> %outISSFile%
rem @echo Source: "..\UE3\MMOGame\Content\MMOContent\MMOEditorMeshes.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\";Flags:recursesubdirs >> %outISSFile%


rem @echo Source: "..\UE3\MMOGame\Content\MMOContent\OldFiles\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\OldFiles\";Flags:recursesubdirs >> %outISSFile%

@echo Source: "..\UE3\MMOGame\Content\MMOContent\01_Scene\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\01_Scene\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\02_Characters\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\02_Characters\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\02_Creature\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\02_Creature\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\02_Item\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\02_Item\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\03_FX\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\03_FX\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\04_MaterialTemplate\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\04_MaterialTemplate\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\05.Archetype\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\05.Archetype\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\05_Item_Armor\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\05_Item_Armor\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\05_Items\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\05_Items\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\06_Ability\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\06_Ability\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\07.Quest\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\07.Quest\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\07_AIData\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\07_AIData\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\07_NPC\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\07_NPC\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\07_Player\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\07_Player\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\07_Quest\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\07_Quest\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\08.UI\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\08.UI\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\08_Buff\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\08_Buff\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\09.CamAnim\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\09.CamAnim\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\09_Missile\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\09_Missile\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\10.Sounds\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\10.Sounds\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\10_AVATAR\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\10_AVATAR\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\10_EquipMesh\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\10_EquipMesh\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\11.GameplayModel\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\11.GameplayModel\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\12_Shop\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\12_Shop\";Flags:recursesubdirs >> %outISSFile%
@echo Source: "..\UE3\MMOGame\Content\MMOContent\13_ApexDestructible\*.upk"; DestDir: "{app}\MMOGame\Content\MMOContent\13_ApexDestructible\";Flags:recursesubdirs >> %outISSFile%

@echo Source: .\ISSkin\ISSkin.dll; DestDir: {app}; Flags: dontcopy >> %outISSFile%
@echo Source: .\ISSkin\Styles\Office2007.cjstyles; DestDir: {tmp}; Flags: dontcopy >> %outISSFile%
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
rem @echo Name: "{group}\%mmoGame%%mmoVer%"; Filename: "{app}\BinariesRelease\Win32\MMOGame.exe";Parameters:"-seekfreeloading" >> %outISSFile%
@echo Name: "{group}\%mmoGame%%mmoVer%"; Filename: "{app}\BinariesRelease\Win32\MMOGame.exe";Parameters:"-FINAL_RELEASE" >> %outISSFile%
@echo Name: "{group}\删除 %outExeFile%"; Filename: "{uninstallexe}" >> %outISSFile%
rem ------------------------------------------------------------------------------------------------------------
@echo [Run] >> %outISSFile%
@echo Filename: "{app}\BinariesRelease\InstallData\dotNetFx40_Full_x86_x64.exe";Components:DotNetFX >> %outISSFile%
@echo Filename: "{app}\BinariesRelease\Redist\UE3Redist.exe";Components:UDKRedist >> %outISSFile%
@echo Filename: "{app}\BinariesRelease\Redist\directx_Jun2010_redist\DXSETUP.exe";Components:DX9;Parameters:"/silent" >> %outISSFile%
rem ------------------------------------------------------------------------------------------------------------
@echo [UninstallDelete] >> %outISSFile%
@echo Type: files; Name: "{app}\*" >> %outISSFile%

rem pause

.\InnoSetup\ISCC.exe %outISSFile%

set startTime2=%time%


md %ReleaseDir%%mmoVer%\
xcopy %outExeFile%*.* %ReleaseDir%%mmoVer%\ /Y

md %ReleaseDir%PDB\%mmoVer%\
xcopy ..\UE3\BinariesRelease\Win32\MMOGame.pdb %ReleaseDir%PDB\%mmoVer%\ /Y

rem xcopy %outExeFile%.exe %ReleaseDir% /Y

set startTime3=%time%
set targDir=%ReleaseDir% %mmoVer%
set msg=客户端打包版本完成:%mmoVer%\r\n开始时间：%startTime1% \r\n打包完成时间：%startTime2% \r\n复制到服务器时间：%startTime3% \r\n %targDir% 

@echo #coding:utf-8 > notify.py
@echo import rtx >> notify.py
@echo rtx.send_msg('%msg%') >> notify.py
.\Python27\python.exe notify.py
