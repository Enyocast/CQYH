@echo off
setlocal
rem Optional second stage: same as Launch_Editor_DX9.bat but with DirectX 11.
cd /d "%~dp0client\UE3\Binaries\Win32"
if not exist "MMOGame.exe" (
    echo ERROR: MMOGame.exe was not found in %CD%
    echo Run Setup-PrebuiltEditor.ps1 first.
    pause
    exit /b 1
)
"MMOGame.exe" editor -log -NoGADWarning -dx11 -LANGUAGE=ENG
endlocal