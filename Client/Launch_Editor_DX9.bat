@echo off
setlocal
rem Starts the prebuilt Mir Eternal (UE3) map editor. See "Opening the client in the UE3 editor" in the README.
rem Use DX9 first. Do not save, build, cook or run ESMAP/ESSCENE during a first inspection.
cd /d "%~dp0client\UE3\Binaries\Win32"
if not exist "MMOGame.exe" (
    echo ERROR: MMOGame.exe was not found in %CD%
    echo Run Setup-PrebuiltEditor.ps1 first.
    pause
    exit /b 1
)
"MMOGame.exe" editor -log -NoGADWarning -dx9 -LANGUAGE=ENG
endlocal