set srcDir=C:\AutoBuild\edition\Shipping_Bin\CQYH\
set packDirBin=C:\_pack_dir\bin\CQYH\
set packDirDat=C:\_pack_dir\zip\CQYH\
set srcZipDirDat=C:\_pack_dir\zip\

path %path%;"C:\Program Files (x86)\WinZip\"
set zipDir=c:\zip_%1\
set zipSplitDir=c:\zip_%1\s\

rd %zipDir%  /S /Q
rd %zipSplitDir%  /S /Q

md %zipDir%
md %zipSplitDir%

rem rd %packDirBin% /S /Q
rem rd %packDirDat% /S /Q

rem md %packDirBin%
rem md %packDirDat%
rem copy /Y
rem xcopy /S /F /Y /R /Q'

robocopy %srcDir% %packDirBin% *.* /MT:128
rem pause

robocopy %srcDir%Binaries\ %packDirBin%Binaries\ *.* /MT:128

robocopy %srcDir%Binaries\ %packDirBin%Binaries\ *.* /E /MT:128
robocopy %srcDir%Engine\ %packDirBin%Engine\ *.* /E /MT:128
robocopy %srcDir%LauncherSkin2.0\ %packDirBin%LauncherSkin2.0\ *.* /E /MT:128
robocopy %srcDir%LauncherUpdate\ %packDirBin%LauncherUpdate\ *.* /E /MT:128
robocopy %srcDir%SDO\ %packDirBin%SDO\ *.* /E /MT:128
robocopy %srcDir%MMOGame\Config\ %packDirBin%MMOGame\Config\ *.* /E /MT:128
robocopy %srcDir%MMOGame\Content\CursorAni\ %packDirBin%MMOGame\Content\CursorAni\ *.* /E /MT:128
robocopy %srcDir%MMOGame\Localization\ %packDirBin%MMOGame\Localization\ *.* /E /MT:128
robocopy %srcDir%MMOGame\Movies\ %packDirBin%MMOGame\Movies\ *.* /E /MT:128
robocopy %srcDir%MMOGame\Splash\ %packDirBin%MMOGame\Splash\ *.* /E /MT:128
robocopy %srcDir%MMOGame\CookedPC\ %packDirBin%MMOGame\CookedPC\ *.u

robocopy %srcDir%MMOGame\CookedPC\ %packDirDat%MMOGame\CookedPC\ *.* /E /MT:128 /MIR
del /Q /F %packDirDat%MMOGame\CookedPC\*.u


wzzip -r -p -a %zipDir%CQYH.zip %srcZipDirDat%
wzzip -ys1843200 %zipDir%CQYH.zip %zipSplitDir%