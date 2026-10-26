REM %1 should be the client spec to sync to

set $P4PASSWD=p4 login -p

REM default label to sync to
set LABEL_TO_SYNC_TO=latestUnrealEngine3_Example


p4.exe -c %1 sync //depot/UnrealEngine3/Binaries/...@%LABEL_TO_SYNC_TO%
p4.exe -c %1 sync //depot/UnrealEngine3/....exe@%LABEL_TO_SYNC_TO%
p4.exe -c %1 sync //depot/UnrealEngine3/....xex@%LABEL_TO_SYNC_TO%
p4.exe -c %1 sync //depot/UnrealEngine3/....pe@%LABEL_TO_SYNC_TO%

p4.exe -c %1 sync //depot/UnrealEngine3/Engine/...@%LABEL_TO_SYNC_TO%
p4.exe -c %1 sync //depot/UnrealEngine3/Engine/Content/...
p4.exe -c %1 sync //depot/UnrealEngine3/Engine/Content/UI/...@%LABEL_TO_SYNC_TO%

p4.exe -c %1 sync //depot/UnrealEngine3/ExampleGame/Config/...@%LABEL_TO_SYNC_TO%
p4.exe -c %1 sync //depot/UnrealEngine3/ExampleGame/Script/...@%LABEL_TO_SYNC_TO%
p4.exe -c %1 sync //depot/UnrealEngine3/ExampleGame/ScriptFinalRelease/...@%LABEL_TO_SYNC_TO%

del /f  ..\..\ExampleGame\Content\LocalShaderCache*.*

REM always get the latest content
p4.exe -c %1 sync //depot/UnrealEngine3/ExampleGame/__Trashcan/...
p4.exe -c %1 sync //depot/UnrealEngine3/ExampleGame/Content/...
p4.exe -c %1 sync //depot/UnrealEngine3/ExampleGame/Localization/...

p4.exe -c %1 sync //depot/UnrealEngine3/ExampleGame/Content/RefShaderCache...@%LABEL_TO_SYNC_TO%
p4.exe -c %1 sync //depot/UnrealEngine3/ExampleGame/Content/RefContentTagsIndex...@%LABEL_TO_SYNC_TO%
