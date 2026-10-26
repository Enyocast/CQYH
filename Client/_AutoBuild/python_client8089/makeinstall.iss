[Setup] 
AppName=AgeOfDawn(CB1) 
AppVerName= 
AppVersion=1.0 
DefaultDirName=c:\AgeOfDawn(CB1) 
DefaultGroupName=AgeOfDawn(CB1) 
SetupIconFile=..\UE3\Binaries\InstallData\GameIcon.ico 
UninstallDisplayIcon={app}\AOD\Binaries\InstallData\Uninstall.ico 
Compression=lzma2/max 
CompressionThreads=24 
LZMANumBlockThreads=12 
SolidCompression=yes 
OutputDir=D:\xampp\htdocs\aodpatch\Install\\ 
OutputBaseFilename=AgeOfDawn(CB1) 
WizardImageFile=.\ISSkin\Styles\Office2007Gray.bmp 
WizardSmallImageFile=compiler:WizModernSmallImage-IS.bmp 
DiskSpanning=yes 
[Files] 
Source: "..\UE3\Binaries\Redist\*"; DestDir: "{app}\AOD\Redist\" 
Source: "..\UE3\Binaries\InstallData\*"; DestDir: "{app}\AOD\BinariesShipping\InstallData\" 
Source: ".\directx_Jun2010_redist\*"; DestDir: "{app}\AOD\Redist\directx_Jun2010_redist\";Components:DX9 
Source: "C:\AutoBuild\edition\Shipping_Bin\*.*"; DestDir: "{app}" 
Source: .\ISSkin\ISSkin.dll; DestDir: {app}; Flags: dontcopy 
Source: .\ISSkin\Styles\Office2007.cjstyles; DestDir: {tmp}; Flags: dontcopy 
[Code] 
procedure LoadSkin(lpszPath: String; lpszIniFileName: String); 
external 'LoadSkin@files:isskin.dll stdcall'; 
procedure UnloadSkin(); 
external 'UnloadSkin@files:isskin.dll stdcall'; 
function ShowWindow(hWnd: Integer; uType: Integer): Integer; 
external 'ShowWindow@user32.dll stdcall'; 
function InitializeSetup(): Boolean; 
begin 
  ExtractTemporaryFile('Office2007.cjstyles'); 
  LoadSkin(ExpandConstant('{tmp}\Office2007.cjstyles'), 'NormalBlack.ini'); 
  Result := True; 
end;  
procedure DeinitializeSetup();  
begin  
 ShowWindow(StrToInt(ExpandConstant('{wizardhwnd}')), 0);  
 UnloadSkin();  
end;   
[Components] 
Name:UDKRedist;Description:"安装运行库";Types:full 
Name:DotNetFX;Description:"安装.net运行库";Types:full 
Name:DX9;Description:"安装DirectX";Types:full 
[Icons] 
Name: "{group}\AgeOfDawn(CB1)"; Filename: "{app}\AOD\BinariesShipping\Win32\MMOGame-Win32-Shipping.exe";Parameters:"–seekfreeloading -FINAL_RELEASE -nohomedir -LANGUAGE=CHN" 
Name: "{group}\删除 AgeOfDawn(CB1)"; Filename: "{uninstallexe}" 
[Run] 
Filename: "{app}\AOD\BinariesShipping\InstallData\dotNetFx40_Full_x86_x64.exe";Components:DotNetFX 
Filename: "{app}\AOD\Redist\UE3Redist.exe";Components:UDKRedist 
Filename: "{app}\AOD\Redist\directx_Jun2010_redist\DXSETUP.exe";Components:DX9;Parameters:"/silent" 
[UninstallDelete] 
Type: files; Name: "{app}\AOD\*" 
