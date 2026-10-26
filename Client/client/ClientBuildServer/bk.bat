set bakDir=c:\_backup_build8089
robocopy .\python_client8089\ %bakDir%\python_client8089\ *.* /MIR
robocopy .\aod_pack\ %bakDir%\aod_pack\ *.* /MIR
robocopy .\bat_files\ %bakDir%\bat_files\ *.* /MIR

xcopy .\edition\ %bakDir%\edition\ /T /E /Y

copy /Y bk.bat %bakDir%\bk.bat