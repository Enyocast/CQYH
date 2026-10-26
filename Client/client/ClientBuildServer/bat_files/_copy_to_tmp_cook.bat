set client_build_UE3_path=%1
set tmpCookDir=%2

robocopy %client_build_UE3_path% %tmpCookDir% *.* /MIR /MT:128 /NFL /NDL /NC /S
robocopy %client_build_UE3_path% %tmpCookDir% *.* /MIR /MT:128 /NFL /NDL /NC /S
robocopy  %client_build_UE3_path%..\..\NewServer\bin\commonconfig\   %tmpCookDir%..\..\NewServer\bin\commonconfig\ *.* /MIR /MT:128 /NFL /NDL /NC /S
robocopy  %client_build_UE3_path%..\..\Common\   %tmpCookDir%..\..\Common\ *.* /MIR /MT:128 /NFL /NDL /NC /S

attrib -R /S %tmpCookDir%*.*