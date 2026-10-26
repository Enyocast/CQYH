set srcDir=C:\AutoBuild\edition\Shipping_Bin\CQYH\
set packDirBin=C:\_pack_dir\bin\CQYH\
set packDirDat=C:\_pack_dir\CQYH\

rd %packDirBin% /S /Q
rd %packDirDat% /S /Q

md %packDirBin%
md %packDirDat%
rem copy /Y
rem xcopy /S /F /Y /R /Q'
robocopy %srcDir%Binaries\*.* %packDirBin%Binaries\
robocopy %srcDir%Binaries\*.* %packDirBin%Binaries\ /E
robocopy %srcDir%Engine\*.* %packDirBin%Engine\ /E
robocopy %srcDir%LauncherSkin2.0\*.* %packDirBin%LauncherSkin2.0\ /E
robocopy %srcDir%LauncherUpdate\*.* %packDirBin%LauncherUpdate\ /E
robocopy %srcDir%SDO\*.* %packDirBin%SDO\ /E
robocopy %srcDir%MMOGame\Config\*.* %packDirBin%MMOGame\Config\ /E
robocopy %srcDir%MMOGame\Content\CursorAni\*.* %packDirBin%MMOGame\Content\CursorAni\ /E
robocopy %srcDir%MMOGame\Localization\*.* %packDirBin%MMOGame\Localization\ /E
robocopy %srcDir%MMOGame\Movies\*.* %packDirBin%MMOGame\Movies\ /E
robocopy %srcDir%MMOGame\Splash\*.* %packDirBin%MMOGame\Splash\ /E
robocopy %srcDir%MMOGame\CookedPC\*.u %packDirBin%MMOGame\CookedPC\

robocopy %srcDir%MMOGame\CookedPC\*.* %packDirDat%MMOGame\CookedPC\ /E
del /Q /F %packDirDat%MMOGame\CookedPC\*.u

