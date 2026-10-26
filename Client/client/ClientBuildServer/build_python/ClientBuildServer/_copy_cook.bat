set cookedSrcDir=d:\_cook\Client\UE3\
set targCookVerDir=d:\_cook_ok\
set srcSvrCfg=NewServer\bin\commonconfig\
set buildBranch=C:\AutoBuild\Source\08.Prog_Stable\

rd %targCookVerDir% /Q /S

robocopy   %buildBranch%NewServer\bin\commonconfig\ %targCookVerDir%..\NewServer\bin\commonconfig\ *.* /MIR /MT:128

encode_files.py   %cookedSrcDir%MMOGame\Config\   %targCookVerDir%MMOGame\Config\
encode_files.py   %cookedSrcDir%..\..\NewServer\bin\commonconfig\setting\   %targCookVerDir%MMOGame\Config\


encode_files.py   %cookedSrcDir%MMOGame\CookedPC\   %targCookVerDir%MMOGame\CookedPC\

encode_files.py   %cookedSrcDir%MMOGame\Localization\INT\   %targCookVerDir%MMOGame\Localization\INT\

encode_files.py   %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\   %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\
encode_files.py   %cookedSrcDir%Engine\Config\   %targCookVerDir%Engine\Config\
encode_files.py   %cookedSrcDir%Engine\Localization\INT\   %targCookVerDir%Engine\Localization\INT\
encode_files.py   %cookedSrcDir%Engine\Shaders\Binaries\   %targCookVerDir%Engine\Shaders\Binaries\

encode_files.py   %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Pb02\   %targCookVerDir%MMOGame\CookedPC\scene\Mir_Pb02\
encode_files.py   %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03\   %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03\
encode_files.py   %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_1\   %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_1\
encode_files.py   %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\Mir_Dg03_2\   %targCookVerDir%MMOGame\CookedPC\scene\Mir_Dg03_2\
encode_files.py   %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\DesertDungeon02\   %targCookVerDir%MMOGame\CookedPC\scene\DesertDungeon02\
encode_files.py   %cookedSrcDir%..\..\NewServer\bin\commonconfig\scene\SeaDg03\   %targCookVerDir%MMOGame\CookedPC\scene\SeaDg03\

encode_files.py   %cookedSrcDir%ShippingIPCfg\   %targCookVerDir%MMOGame\Config\

robocopy   %cookedSrcDir%MMOGame\Account\surveyfile\   %targCookVerDir%MMOGame\Account\surveyfile\ *.* /E

robocopy   %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\   %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.npc /MT:128 /E
robocopy   %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\   %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.navipoints /MT:128 /E
robocopy   %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\   %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.search /MT:128 /E
robocopy   %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\   %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.spawngroup /MT:128 /E
robocopy   %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\   %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.teleport /MT:128 /E
robocopy   %cookedSrcDir%MMOGame\Content\MapsGlobalInfo\   %targCookVerDir%MMOGame\CookedPC\MapsGlobalInfo\ *.volume /MT:128 /E

robocopy   %cookedSrcDir%MMOGame\Content\CursorAni\   %targCookVerDir%MMOGame\Content\CursorAni\ *.* /MT:128 /E
encode_files.py   %cookedSrcDir%MMOGame\Movies\   %targCookVerDir%MMOGame\Movies\
copy   %cookedSrcDir%MMOGame\Movies\FirstLogin.bik   %targCookVerDir%MMOGame\Movies\FirstLogin.bik /Y

robocopy   %cookedSrcDir%MMOGame\Splash\   %targCookVerDir%MMOGame\Splash\ *.* /MT:128 /E
robocopy   %cookedSrcDir%SDO\   %targCookVerDir%SDO\ *.* /MT:128 /E
robocopy   %cookedSrcDir%Launcher\   %targCookVerDir%\ *.* /MT:128 /E
xcopy   %cookedSrcDir%LauncherRelease\*.*   %targCookVerDir%\   /S /F /Y /R /Q
robocopy   %cookedSrcDir%Binaries\Win32\GPK\   %targCookVerDir%Binaries\Win32\GPK\ *.* /MT:128 /E
copy   %cookedSrcDir%Binaries\Win32\MMOGame-Win32-Shipping.exe   %targCookVerDir%Binaries\Win32\MMOGame.exe /Y
robocopy   %cookedSrcDir%Binaries\   %targCookVerDir%Binaries\ AutoReporter*.*
robocopy   %cookedSrcDir%Binaries\Win32\   %targCookVerDir%Binaries\Win32\ Apex*.dll /MT:128 /E
copy   %cookedSrcDir%Binaries\Win32\cudart32_41_22.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\EasyHook32.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\GPKitClt.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\libogg.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\libresample.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\libvorbis.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\libvorbisfile.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\nvtt.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\ogg.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\PhysX3GpuCHECKED_x86.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\PhysXCooking.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\PhysXCore.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\PhysXDevice.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\PhysXExtensions.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\PhysXLoader.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\wxmsw28u_adv_vc_custom.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\wxmsw28u_aui_vc_custom.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\wxmsw28u_core_vc_custom.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\wxmsw28u_html_vc_custom.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\wxmsw28u_richtext_vc_custom.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\wxmsw28u_vc_custom.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\wxmsw28u_xml_vc_custom.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\wxmsw28u_xrc_vc_custom.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\binkw32.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\webManager.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\msvcp100.dll   %targCookVerDir%Binaries\Win32\ /Y
copy   %cookedSrcDir%Binaries\Win32\msvcr100.dll   %targCookVerDir%Binaries\Win32\ /Y
del   %targCookVerDir%MMOGame\Config\*.xlsx  /F /Q
del   %targCookVerDir%MMOGame\Config\*.xls  /F /Q
del   %targCookVerDir%MMOGame\Config\*.xlsm  /F /Q
del   %targCookVerDir%MMOGame\Config\*.db  /F /Q
del   %targCookVerDir%MMOGame\Config\*.csv  /F /Q
del   %targCookVerDir%MMOGame\Config\*.exe  /F /Q
del   %targCookVerDir%MMOGame\Config\MMO*.ini  /F /Q
del   %targCookVerDir%MMOGame\Config\modifier_tree.mdf  /F /Q
rem copy   shippingVerIni     %targCookVerDir%Binaries\ver.ini /Y