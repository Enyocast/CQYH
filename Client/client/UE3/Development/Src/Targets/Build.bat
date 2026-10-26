@ECHO off
REM %1 is the game name
REM %2 is the platform name
REM %3 is the configuration name

IF EXIST ..\Intermediate\UnrealBuildTool\Shipping\UnrealBuildTool.exe (
         ..\Intermediate\UnrealBuildTool\Shipping\UnrealBuildTool.exe %*
) ELSE (
	ECHO UnrealBuildTool.exe not found in ..\Intermediate\UnrealBuildTool\Shipping\UnrealBuildTool.exe 
	EXIT /B 999
)
