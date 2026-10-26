set srcDir=h:\p4\08.Prog\Client\UE3\
set targDir=k:\BinRel\
set serverBin=H:\p4\08.Prog\NewServer\bin\commonconfig\

md %targDir%

set startTime=%time%

encode_files.py %serverBin%Scene %targDir%MMOGame\CookedPC\Scene
pause

encode_files.py %srcDir%MMOGame\Localization\INT %targDir%MMOGame\Localization\INT
encode_files.py %srcDir%MMOGame\Config %targDir%MMOGame\Config
encode_files.py %srcDir%Engine\Localization\INT %targDir%Engine\Localization\INT




encode_files.py %srcDir%Engine\Config %targDir%Engine\Config
encode_files.py %srcDir%Engine\Content %targDir%Engine\Content

encode_files.py %srcDir%Engine\Shaders\Binaries %targDir%Engine\Shaders\Binaries


encode_files.py %srcDir%MMOGame\CookedPC %targDir%MMOGame\CookedPC


@echo %startTime%  %time%
pause
