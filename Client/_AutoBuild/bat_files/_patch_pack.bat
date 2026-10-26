set packDir=d:\_AutoBuild\aod_pack\
set patchDir=D:\xampp\htdocs\aodpatch\patch\%1-%2\
set destLauncher=D:\_ver\%2_Launcer\
xcopy %destLauncher%LocalVersion.xml %packDir%\patchmake\ /s /y
call %packDir%Python27\python.exe %packDir%7za\gen_patch_nsis_hdr.py %1 %2 %3 %packDir%\patchmake\aod_patch_ver.nsh
call %packDir%patchmake\nsis\makensis.exe %packDir%\patchmake\CQYH_Patch_Setup.nsi
move %packDir%\patchmake\ %patchDir%\ CQYH_Setup*.exe /MIR /NFL /NDL /NS /NC /S /MOV