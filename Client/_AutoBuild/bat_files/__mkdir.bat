@echo start copy directory structure
@echo %1
@echo %2

xcopy %1 %2 /T /E /Y

rem pause