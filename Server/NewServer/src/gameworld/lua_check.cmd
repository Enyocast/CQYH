@echo off
rem Syntax-checks one Lua script with luac. Used by lua.props (the "script" project) in place of
rem a plain "luac.exe -p -o x.out x.lua".
rem
rem Why a wrapper: Lua 5.1's luac cannot parse a leading UTF-8 byte-order mark
rem ("unexpected symbol near '<EF>'"), but the server's own script loader skips it
rem (see baselib/lua_script.cpp), so scripts saved with a BOM are valid and in use
rem (136 of the scripts under bin\commonconfig\script have one). To keep those files
rem unchanged, a script that fails is retried on a BOM-stripped temporary copy.
rem
rem   %1 = the script to check
rem Exit code 0 = valid, anything else = luac's syntax error.
setlocal
set "LUAC=%~dp0script\luac.exe"
set "SRC=%~1"

rem Fast path: most scripts have no BOM and pass straight away.
"%LUAC%" -p "%SRC%" 2>nul && exit /b 0

rem Retry without a BOM, if there is one.
set "TMPF=%TEMP%\luacheck_%RANDOM%_%~nx1"
powershell -NoProfile -NonInteractive -Command "$b=[IO.File]::ReadAllBytes($env:SRC); if ($b.Length -ge 3 -and $b[0] -eq 239 -and $b[1] -eq 187 -and $b[2] -eq 191) { $n=$b.Length-3; $o=New-Object byte[] $n; [Array]::Copy($b,3,$o,0,$n); [IO.File]::WriteAllBytes($env:TMPF,$o); exit 0 } else { exit 3 }"
if errorlevel 1 goto report

"%LUAC%" -p "%TMPF%"
set "RC=%ERRORLEVEL%"
del "%TMPF%" 2>nul
exit /b %RC%

:report
rem No BOM (or the retry could not run): report luac's real error against the original file.
"%LUAC%" -p "%SRC%"
exit /b %ERRORLEVEL%
