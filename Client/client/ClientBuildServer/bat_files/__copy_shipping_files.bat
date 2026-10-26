
set client_build_UE3_path=%1
set cookedSrcDir=%2
set targCookVerDir=%3

@echo %1 %2 %3

rem pause

rd /S /Q %targCookVerDir%

rem 先复制到临时目录
robocopy  %client_build_UE3_path%..\..\NewServer\bin\commonconfig\   %cookedSrcDir%..\..\NewServer\bin\commonconfig\ *.* /MIR /MT:128 /NFL

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

rem 修改以下路径要注意看到
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_4\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_4\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_5\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_5\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_6\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_6\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_1\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_2\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_3\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_3\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg04\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg04\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_1\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_2\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirPb01\    %targCookVerDir%MMOGame\CookedPC\scene\MirPb01\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Pb02\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Pb02\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Pb03\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Pb03\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_1\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_2\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_1\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_2\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_3\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_3\

encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirAct01\    %targCookVerDir%MMOGame\CookedPC\scene\MirAct01\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirAct02\    %targCookVerDir%MMOGame\CookedPC\scene\MirAct02\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirAct03\    %targCookVerDir%MMOGame\CookedPC\scene\MirAct03\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirAct04\    %targCookVerDir%MMOGame\CookedPC\scene\MirAct04\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirCt01\    %targCookVerDir%MMOGame\CookedPC\scene\MirCt01\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_1\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_2\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_3\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01_3\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_4\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01_4\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_5\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg01_5\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_1\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_2\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_3\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_3\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_4\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_4\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_5\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_5\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_6\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_6\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg_03\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_1\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_2\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_3\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_3\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg04\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg04\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_1\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_2\    %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg08\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg08\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg08_1\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg08_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg08_2\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg08_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg08_3\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg08_3\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg09\    %targCookVerDir%MMOGame\CookedPC\scene\MirDg09\


rem @echo Copy new files...
rem pause

encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirAct05_1\	%targCookVerDir%MMOGame\CookedPC\scene\MirAct05_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirAct05_2\	%targCookVerDir%MMOGame\CookedPC\scene\MirAct05_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirAct05_3\	%targCookVerDir%MMOGame\CookedPC\scene\MirAct05_3\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirAct05_4\	%targCookVerDir%MMOGame\CookedPC\scene\MirAct05_4\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirAct06\		%targCookVerDir%MMOGame\CookedPC\scene\MirAct06\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_6\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg01_6\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_7\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg01_7\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg01_8\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg01_8\
rem encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg02_6_1\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg02_6_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_10\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_10\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_11\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_11\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_12\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_12\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_13\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_13\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_14\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_14\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_3\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_3\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_4\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_4\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_5\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_5\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_6\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_6\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_7\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_7\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_8\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_8\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg05_9\	%targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg05_9\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg07\		%targCookVerDir%MMOGame\CookedPC\scene\MirDg07\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg07_1\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg07_1\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg07_2\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg07_2\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg07_3\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg07_3\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg07_4\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg07_4\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg07_5\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg07_5\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg07_6\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg07_6\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg07_7\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg07_7\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirDg07_8\	%targCookVerDir%MMOGame\CookedPC\scene\MirDg07_8\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirGd01\		%targCookVerDir%MMOGame\CookedPC\scene\MirGd01\
encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\MirGd01_1\	%targCookVerDir%MMOGame\CookedPC\scene\MirGd01_1\


rem # 12月版本时清除以下两行
rem encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\DesertDungeon02\    %targCookVerDir%MMOGame\CookedPC\scene\DesertDungeon02\
rem encode_files.py  %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\SeaDg03\    %targCookVerDir%MMOGame\CookedPC\scene\SeaDg03\

encode_files.py  %cookedSrcDir%ShippingIPCfg\    %targCookVerDir%MMOGame\Config\

rem #encode_files.py  %cookedSrcDir%MMOGame\Account\surveyfile\    %targCookVerDir%MMOGame\Account\surveyfile\
robocopy  %cookedSrcDir%MMOGame\Account\surveyfile\    %targCookVerDir%MMOGame\Account\surveyfile\ *.* /E /NFL

robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.npc /MT:128 /E /NFL
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.navipoints /MT:128 /E /NFL
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.search /MT:128 /E /NFL
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.spawngroup /MT:128 /E /NFL
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.teleport /MT:128 /E /NFL
robocopy  %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\    %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.volume /MT:128 /E /NFL

rem #rem pause

robocopy  %cookedSrcDir%MMOGame\Content\CursorAni\    %targCookVerDir%MMOGame\Content\CursorAni\ *.* /MT:128 /E /NFL
rem #robocopy  %cookedSrcDir%MMOGame\Movies\    %targCookVerDir%MMOGame\Movies\ *.* /MT:128 /E
encode_files.py  %cookedSrcDir%MMOGame\Movies\    %targCookVerDir%MMOGame\Movies\
copy  %cookedSrcDir%MMOGame\Movies\FirstLogin.bik    %targCookVerDir%MMOGame\Movies\FirstLogin.bik /Y
copy  %cookedSrcDir%MMOGame\Movies\01.bik    %targCookVerDir%MMOGame\Movies\01.bik /Y
copy  %cookedSrcDir%MMOGame\Movies\02.bik    %targCookVerDir%MMOGame\Movies\02.bik /Y
copy  %cookedSrcDir%MMOGame\Movies\03.bik    %targCookVerDir%MMOGame\Movies\03.bik /Y
copy  %cookedSrcDir%MMOGame\Movies\04.bik    %targCookVerDir%MMOGame\Movies\04.bik /Y
copy  %cookedSrcDir%MMOGame\Movies\05.bik    %targCookVerDir%MMOGame\Movies\05.bik /Y
copy  %cookedSrcDir%MMOGame\Movies\06.bik    %targCookVerDir%MMOGame\Movies\06.bik /Y

robocopy  %cookedSrcDir%MMOGame\Splash\PC\    %targCookVerDir%MMOGame\Splash\PC\ Splash.png
robocopy  %cookedSrcDir%SDO\    %targCookVerDir%SDO\ *.* /MT:128 /E /NFL
robocopy  %cookedSrcDir%Launcher\    %targCookVerDir%\ *.* /MT:128 /E /NFL
robocopy  %cookedSrcDir%LauncherRelease\ %targCookVerDir%\ *.*  /E /NFL
robocopy  %cookedSrcDir%Binaries\Win32\GPK\    %targCookVerDir%Binaries\Win32\GPK\ *.* /MT:128 /E /NFL
rem #xcopy  %cookedSrcDir%Binaries\Win32\*.dll    %targCookVerDir%Binaries\Win32\    /S /F /Y /R /Q
copy  %cookedSrcDir%Binaries\Win32\MMOGame-Win32-Shipping.exe    %targCookVerDir%Binaries\Win32\MMOGame-Win32-Shipping.exe /Y
robocopy  %cookedSrcDir%Binaries\    %targCookVerDir%Binaries\ AutoReporter*.*
robocopy  %cookedSrcDir%Binaries\Win32\    %targCookVerDir%Binaries\Win32\ Apex*.dll /MT:128 /E
copy  %cookedSrcDir%Binaries\Win32\cudart32_41_22.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\EasyHook32.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\GPKitClt.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\libogg.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\libresample.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\libvorbis.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\libvorbisfile.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\nvtt.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\ogg.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\PhysX3GpuCHECKED_x86.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\PhysXCooking.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\PhysXCore.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\PhysXDevice.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\PhysXExtensions.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\PhysXLoader.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_adv_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_aui_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_core_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_html_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_richtext_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_xml_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
rem copy  %cookedSrcDir%Binaries\Win32\wxmsw28u_xrc_vc_custom.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\binkw32.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\webManager.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\xinput1_3.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\D3DCompiler_43.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\D3DX9_43.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\d3dx11_43.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\X3DAudio1_7.dll    %targCookVerDir%Binaries\Win32\ /Y
rem #copy  %cookedSrcDir%Binaries\Win32\XAPOFX1_5.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\msvcp100.dll    %targCookVerDir%Binaries\Win32\ /Y
copy  %cookedSrcDir%Binaries\Win32\msvcr100.dll    %targCookVerDir%Binaries\Win32\ /Y
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