REM this is our layer of indirection so we can "patch the patcher"
REM %1 should be the client spec to sync to

p4.exe -c %1 sync //depot/UnrealEngine3/ExampleGame/Build/...

call examplegame-syncWorker.bat %1
