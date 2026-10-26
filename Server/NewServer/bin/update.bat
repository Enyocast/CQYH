echo off
echo 清除缓存数据
del cache /S/F/Q
echo 开始更新服务器程序
call :update manageserver
call :update dbserver
call :update gameserver
call :update gateserver
call :update datalogserver
call :update loginserver
call :update balanceserver
call :update gmserver
pause
goto :EOF


:update
setlocal
cd wget
del "%164_d.exe" /F/Q
wget "http://172.30.66.36/build/cq/%1/%164_d.exe"
cd ..
md %1
del "%1\%164_d.exe" /F/Q
move /Y "wget\%164_d.exe" ".\%1\"
if exist "%1\%164_d.exe" (
	echo 更新%1成功！
) else (
	echo 更新%1失败！
	pause
)
endlocal&goto :EOF