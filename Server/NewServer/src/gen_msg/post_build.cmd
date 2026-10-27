@echo off
rem Post-build step for gen_msg: regenerates source/config files from the freshly built gen_msg.exe.
rem
rem Replaces the original inline post-build command, which
rem   - called Perforce ("p4 edit <file>") before every file, and
rem   - wrote into a "client" folder that sits next to NewServer in the original depot.
rem Neither exists in this repository (no Perforce; the client is in <repo>\Client\client).
rem
rem   %1 = full or relative path to gen_msg.exe
rem   %2 = optional: pass "true" to also regenerate the CLIENT files (see below)
rem
rem Each output is generated into a temporary file first and only copied over the real file
rem when gen_msg succeeded, produced output, and the content actually changed. A failed run
rem therefore never truncates a tracked source file, and unchanged files are left alone.
setlocal
for %%I in ("%~1") do set "GEN=%%~fI"
set "WRITE_CLIENT=%~2"
set "SERVER=%~dp0..\..\.."
set "CLIENT=%~dp0..\..\..\..\Client\client\UE3"

call :gen msg     "%SERVER%\Common\message\external_message_size.cpp" || exit /b 1
call :gen errcode "%SERVER%\Common\define\error_code_name.cpp"        || exit /b 1
call :gen btnode  "%SERVER%\NewServer\bin\bteditor\MMOBTNode.ini"     || exit /b 1
call :gen btevent "%SERVER%\NewServer\bin\bteditor\MMOBTEvent.ini"    || exit /b 1

rem Client outputs (ServerEnum.uc and the client copies of MMOBTNode.ini / MMOBTEvent.ini).
rem These are OFF by default: a server build should not rewrite files outside Server\, and the
rem committed client files are generated from the server enums, so regenerating them produces a
rem large diff in Client\. Enable with the MSBuild property GenMsgWriteClient=true
rem (e.g. msbuild /p:GenMsgWriteClient=true), and only when the Client tree sits next to Server.
if /i not "%WRITE_CLIENT%"=="true" exit /b 0
if exist "%CLIENT%\Development\Src\MMOGame\Classes\" (
    call :gen enum "%CLIENT%\Development\Src\MMOGame\Classes\ServerEnum.uc" || exit /b 1
)
if exist "%CLIENT%\MMOGame\Config\" (
    call :gen btnode  "%CLIENT%\MMOGame\Config\MMOBTNode.ini"  || exit /b 1
    call :gen btevent "%CLIENT%\MMOGame\Config\MMOBTEvent.ini" || exit /b 1
)
exit /b 0

rem :gen <gen_msg command> <target file>
:gen
set "TMPF=%TEMP%\gen_msg_%RANDOM%_%~1.tmp"
call "%GEN%" %~1 >"%TMPF%"
if errorlevel 1 (
    echo gen_msg %~1 failed
    del "%TMPF%" 2>nul
    exit /b 1
)
for %%F in ("%TMPF%") do if %%~zF==0 (
    echo gen_msg %~1 produced no output
    del "%TMPF%" 2>nul
    exit /b 1
)
if exist "%~2" (
    fc /b "%TMPF%" "%~2" >nul 2>&1
    if not errorlevel 1 (
        del "%TMPF%" 2>nul
        exit /b 0
    )
)
if exist "%~2" attrib -r "%~2" >nul 2>&1
copy /y "%TMPF%" "%~2" >nul
if errorlevel 1 (
    echo could not write %~2
    del "%TMPF%" 2>nul
    exit /b 1
)
del "%TMPF%" 2>nul
echo generated %~2
exit /b 0
