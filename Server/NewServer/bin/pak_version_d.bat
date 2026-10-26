Set VersionName=bin_92465debug

REM#########################################################
Set VersionPath=..\tools\maintaintool\bin\version\%VersionName%
IF NOT EXIST "%VersionPath%" ( md "%VersionPath%" )

REM## xcopy ".\asimov\asimov.*" 			%VersionPath%\asimov 		/E/I/R/Y

copy ".\sotsapi.dll"				%VersionPath%\ 			/Y
copy ".\RpcClt.dll"				%VersionPath%\ 			/Y
copy ".\gpkitsvr64.dll"				%VersionPath%\ 			/Y
copy ".\fcmsdk_X64.dll"			%VersionPath%\ 			/Y
xcopy ".\dyncodebin64\*.*"			%VersionPath%\dyncodebin64 	/E/I/R/Y

copy ".\start_server.bat"			%VersionPath%\ 			/Y	

xcopy ".\loginserver\database" 		%VersionPath%\loginserver\database 	/E/I/R/Y
xcopy ".\loginserver\oa_authorize" 		%VersionPath%\loginserver\oa_authorize 	/E/I/R/Y

xcopy ".\loginserver\loginserver64.*" 		%VersionPath%\loginserver 	/E/I/R/Y
xcopy ".\manageserver\manageserver64.*" 	%VersionPath%\manageserver 	/E/I/R/Y
xcopy ".\dbserver\dbserver64.*" 		%VersionPath%\dbserver 		/E/I/R/Y
xcopy ".\balanceserver\balanceserver64.*" 	%VersionPath%\balanceserver 	/E/I/R/Y
xcopy ".\datalogserver\datalogserver64.*" 	%VersionPath%\datalogserver 	/E/I/R/Y
xcopy ".\gameserver\gameserver64.*" 		%VersionPath%\gameserver 	/E/I/R/Y
xcopy ".\gateserver\gateserver64.*" 		%VersionPath%\gateserver 	/E/I/R/Y
xcopy ".\gmserver\gmserver64.*" 		%VersionPath%\gmserver 		/E/I/R/Y

xcopy ".\loginserver\loginserver64_d.*" 	%VersionPath%\loginserver 	/E/I/R/Y
xcopy ".\manageserver\manageserver64_d.*" 	%VersionPath%\manageserver 	/E/I/R/Y
xcopy ".\dbserver\dbserver64_d.*" 		%VersionPath%\dbserver 		/E/I/R/Y
xcopy ".\balanceserver\balanceserver64_d.*" 	%VersionPath%\balanceserver 	/E/I/R/Y
xcopy ".\datalogserver\datalogserver64_d.*" 	%VersionPath%\datalogserver 	/E/I/R/Y
xcopy ".\gameserver\gameserver64_d.*" 		%VersionPath%\gameserver 	/E/I/R/Y
xcopy ".\gateserver\gateserver64_d.*" 		%VersionPath%\gateserver 	/E/I/R/Y
xcopy ".\gmserver\gmserver64_d.*" 		%VersionPath%\gmserver 		/E/I/R/Y

copy ".\icuuc52.dll"				%VersionPath%\ 			/Y
copy ".\icudt52.dll"				%VersionPath%\ 			/Y
copy ".\icuin52.dll"				%VersionPath%\ 			/Y

copy ".\SdoBase.dll"				%VersionPath%\ 			/Y
copy ".\libeay64.dll"				%VersionPath%\ 			/Y
copy ".\libmysql64.dll"				%VersionPath%\ 			/Y	
copy ".\lua64.dll"				%VersionPath%\ 			/Y
copy ".\lua.dll"				%VersionPath%\ 			/Y
copy ".\Qt5Core.dll"				%VersionPath%\ 			/Y
copy ".\Qt5Gui.dll"				%VersionPath%\ 			/Y
copy ".\ssleay64.dll"				%VersionPath%\ 			/Y
copy ".\msvcp120.dll"				%VersionPath%\ 			/Y
copy ".\msvcr120.dll"				%VersionPath%\ 			/Y
copy ".\libGLESv2.dll"				%VersionPath%\ 			/Y	
copy ".\libEGL.dll"				%VersionPath%\			/Y


copy ".\SdoBased.dll"				%VersionPath%\ 			/Y
copy ".\libeay64_d.dll"				%VersionPath%\ 			/Y
copy ".\libmysql64_d.dll"			%VersionPath%\ 			/Y	
copy ".\lua64_d.dll"				%VersionPath%\ 			/Y
copy ".\lua_d.dll"				%VersionPath%\ 			/Y
copy ".\Qt5Cored.dll"				%VersionPath%\ 			/Y
copy ".\Qt5Gui4.dll"				%VersionPath%\ 			/Y
copy ".\ssleay64_d.dll"				%VersionPath%\ 			/Y
copy ".\msvcp120d.dll"				%VersionPath%\ 			/Y
copy ".\msvcr120d.dll"				%VersionPath%\ 			/Y
copy ".\libGLESv2d.dll"				%VersionPath%\ 			/Y	
copy ".\libEGLd.dll"				%VersionPath%\			/Y

REM#########################################################
			
copy ".\global_config.lua"			%VersionPath%\ 			/Y

xcopy ".\globalconfig\*.*"			%VersionPath%\globalconfig 	/E/I/R/Y
xcopy "..\tools\maintaintool\bin\area_config\globalconfig\*.*"			%VersionPath%\globalconfig 	/E/I/R/Y
	
xcopy ".\commonconfig\*.*"			%VersionPath%\commonconfig 	/E/I/R/Y

copy "pak.exe"			%VersionPath%\ 			/Y
		
cd	%VersionPath%
md	.\data

pak create commonconfig
move /Y	.\commonconfig.pak .\data	

pak create globalconfig
move /Y	.\globalconfig.pak .\data

del /Q "pak.exe"

rd .\commonconfig /S/Q
rd .\globalconfig /S/Q
REM ## md globalconfig_bak
REM ## move /Y .\globalconfig\gameworldconfig.lua .\globalconfig_bak\
REM ## move /Y .\globalconfig\guildconfig.lua .\globalconfig_bak\
REM ## move /Y .\globalconfig\newroleconfig.lua .\globalconfig_bak\
REM ## rd .\globalconfig /S/Q
REM ## move .\globalconfig_bak .\globalconfig
									
cd ..

del /Q %VersionName%.zip
..\7z.exe a %VersionName%.zip .\%VersionName%
 	