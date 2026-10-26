set targCookVerDir=C:\AutoBuild\edition\Shipping_Bin\CQYH\
set client_build_UE3_path=C:\AutoBuild\Source\08.Prog\Client\UE3\

set startTm=%time%

del %targCookVerDir%*.* /s /q


robocopy %client_build_UE3_path%MMOGame\CookedPC\ %targCookVerDir%MMOGame\CookedPC\ *.* /MT:128 /MIR

@echo %startTm% %time%
pause