
set client_build_UE3_path=%1
set cookedSrcDir=%2
set targCookVerDir=%3

@echo %1 %2 %3
rem pause

rd /S /Q %targCookVerDir%

rem 先复制到临时目录
robocopy  %client_build_UE3_path%..\..\NewServer\bin\commonconfig\   %cookedSrcDir%..\..\NewServer\bin\commonconfig\ *.* /MIR /MT:128

@echo %client_build_UE3_path%..\..\NewServer\bin\commonconfig\  %cookedSrcDir%..\..\NewServer\bin\commonconfig\

rem pause

encode_files.py  %cookedSrcDir%MMOGame\Config\    %targCookVerDir%MMOGame\Config\
rem pause

encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\setting\    %targCookVerDir%MMOGame\Config\
rem #暂时全复制encode_files.py  tmpCfgDir       %targCookVerDir%MMOGame\Config\
rem pause

encode_files.py  %cookedSrcDir%MMOGame\CookedPC\    %targCookVerDir%MMOGame\CookedPC\

encode_files.py  %cookedSrcDir%MMOGame\Localization\INT\    %targCookVerDir%MMOGame\Localization\INT\

encode_files.py  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\
rem #del    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\*.upk   /F /Q
encode_files.py  %cookedSrcDir%Engine\Config\    %targCookVerDir%Engine\Config\
rem #encode_files.py  %cookedSrcDir%Engine\Content\     %targCookVerDir%Engine\Content\
encode_files.py  %cookedSrcDir%Engine\Localization\INT\    %targCookVerDir%Engine\Localization\INT\
encode_files.py  %cookedSrcDir%Engine\Shaders\Binaries\    %targCookVerDir%Engine\Shaders\Binaries\


encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg02_4\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg02_4\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg02_5\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg02_5\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg02_6\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg02_6\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg03\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg03\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg03_1\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg03_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg03_2\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg03_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg04\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg04\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Pb02\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg05\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg05\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg05_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg05_2\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg05_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirPb01\    %targCookVerDir%MMOGame\CookedPC\scene\MirPb01\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirPb02\    %targCookVerDir%MMOGame\CookedPC\scene\MirPb02\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirPb03\    %targCookVerDir%MMOGame\CookedPC\scene\MirPb03\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_1\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_2\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg02\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg02\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg02_1\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg02_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg02_2\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg02_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg02_3\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg02_3\

encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Pb02\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Pb02\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_1\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_2\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_2\
rem # 12月版本时清除以下两行
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\DesertDungeon02\    %targCookVerDir%MMOGame\CookedPC\scene\DesertDungeon02\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\SeaDg03\    %targCookVerDir%MMOGame\CookedPC\scene\SeaDg03\

encode_files.py  %cookedSrcDir%ShippingIPCfg\    %targCookVerDir%MMOGame\Config\

rem #encode_files.py  %cookedSrcDir%MMOGame\Account\surveyfile\    %targCookVerDir%MMOGame\Account\surveyfile\
robocopy  %cookedSrcDir%MMOGame\Account\surveyfile\    %targCookVerDir%MMOGame\Account\surveyfile\ *.* /E

robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.npc /MT:128 /E
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.navipoints /MT:128 /E
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.search /MT:128 /E
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.spawngroup /MT:128 /E
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.teleport /MT:128 /E
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.volume /MT:128 /E

rem #rem pause

robocopy  %cookedSrcDir%MMOGame\Content\CursorAni\    %targCookVerDir%MMOGame\Content\CursorAni\ *.* /MT:128 /E
rem #robocopy  %cookedSrcDir%MMOGame\Movies\    %targCookVerDir%MMOGame\Movies\ *.* /MT:128 /E
encode_files.py  %cookedSrcDir%MMOGame\Movies\    %targCookVerDir%MMOGame\Movies\
copy  %cookedSrcDir%MMOGame\Movies\FirstLogin.bik    %targCookVerDir%MMOGame\Movies\FirstLogin.bik /Y

robocopy  %cookedSrcDir%MMOGame\Splash\PC\    %targCookVerDir%MMOGame\Splash\PC\ Splash.png
robocopy  %cookedSrcDir%SDO\    %targCookVerDir%SDO\ *.* /MT:128 /E
robocopy  %cookedSrcDir%Launcher\    %targCookVerDir%\ *.* /MT:128 /E
xcopy  %cookedSrcDir%LauncherRelease\*.*    %targCookVerDir%\    /S /F /Y /R /Q
robocopy  %cookedSrcDir%Binaries\Win32\GPK\    %targCookVerDir%Binaries\Win32\GPK\ *.* /MT:128 /E
rem #xcopy  %cookedSrcDir%Binaries\Win32\*.dll    %targCookVerDir%Binaries\Win32\    /S /F /Y /R /Q

copy  %cookedSrcDir%Binaries\Win32\MMOGame-Win32-Shipping.exe    %targCookVerDir%Binaries\Win32\MMOGame-Win32-Shipping.exe /Y

rem copy  %cookedSrcDir%Binaries\Win32\msvcp100.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\msvcr100.dll    %targCookVerDir%Binaries\Win32\ /Y

copy  %cookedSrcDir%Binaries\Win32\D3DCOMPILER_43.DLL    %targCookVerDir%Binaries\Win32\D3DCOMPILER_43.DLL /Y
copy  %cookedSrcDir%Binaries\Win32\D3DX9_43.DLL    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\D3DX11_43.DLL    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\X3DAUDIO1_7.DLL    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\XAPOFX1_5.DLL    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\xinput1_3.dll.DLL    %targCookVerDir%Binaries\Win32\ /Y

copy  %cookedSrcDir%Binaries\Win32\NVTT.DLL    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\LIBVORBISFILE.DLL    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\APEXFRAMEWORKCHECKED_X86.DLL    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\BINKW32.DLL    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\webManager.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\GPKitClt.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\PhysX3GpuCHECKED_x86.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\PhysXCooking.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\PhysXCore.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\PhysXDevice.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\PhysXExtensions.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\PhysXLoader.dll    %targCookVerDir%Binaries\Win32\ /Y

copy  %cookedSrcDir%Binaries\AutoReporter.exe    %targCookVerDir%Binaries\ /Y
copy  %cookedSrcDir%Binaries\AutoReporter.exe.config    %targCookVerDir%Binaries\ /Y
copy  %cookedSrcDir%Binaries\AutoReporter.XmlSerializers.dll    %targCookVerDir%Binaries\ /Y

robocopy  %cookedSrcDir%Binaries\Win32\GPK\    %targCookVerDir%Binaries\Win32\GPK\ *.* /E

rem robocopy  %cookedSrcDir%Binaries\Win32\    %targCookVerDir%Binaries\Win32\ Apex*.dll /MT:128 /E
rem copy  %cookedSrcDir%Binaries\Win32\cudart32_41_22.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\EasyHook32.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\libogg.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\libresample.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\libvorbis.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\ogg.dll    %targCookVerDir%Binaries\Win32\ /Y

rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_adv_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_aui_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_core_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_html_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_richtext_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_xml_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_xrc_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\xinput1_3.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\D3DCompiler_43.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\D3DX9_43.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\d3dx11_43.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\X3DAudio1_7.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\XAPOFX1_5.dll    %targCookVerDir%Binaries\Win32\ /Y

del  %targCookVerDir%MMOGame\Config\*.xlsx   /F /Q
del  %targCookVerDir%MMOGame\Config\*.xls   /F /Q
del  %targCookVerDir%MMOGame\Config\*.xlsm   /F /Q
del  %targCookVerDir%MMOGame\Config\*.db   /F /Q
del  %targCookVerDir%MMOGame\Config\*.csv   /F /Q
del  %targCookVerDir%MMOGame\Config\*.exe   /F /Q
del  %targCookVerDir%MMOGame\Config\MMO*.ini   /F /Q
rem #rem pause
del  %targCookVerDir%MMOGame\Config\modifier_tree.mdf   /F /Q
copy  shippingVerIni       %targCookVerDir%Binaries\ver.ini /Y