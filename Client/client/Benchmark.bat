xcopy .\UE3\Binaries\*.* .\Benchmark\Binaries\  /S /F /Y /R /EXCLUDE:BenchmarkExcludeBinary.txt
xcopy .\UE3\Binaries\Win32\*.* .\Benchmark\Binaries\Win32\  /S /F /Y /R /EXCLUDE:BenchmarkExcludeWin32.txt
xcopy .\UE3\Engine\*.* .\Benchmark\Engine\  /S /F /Y /R
xcopy .\UE3\MMOGame\*.* .\Benchmark\MMOGame\  /S /F /Y /R /EXCLUDE:BenchmarkExcludeGame.txt
xcopy .\UE3\MMOGame\Content\*.* .\Benchmark\MMOGame\Content\  /S /F /Y /R /EXCLUDE:BenchmarkExcludeContent.txt

xcopy .\UE3\MMOGame\Content\Maps\MMODemo\*.* .\Benchmark\MMOGame\Content\Maps\MMODemo\ /S /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\01_Scene\*.* .\Benchmark\MMOGame\Content\MMOContent\01_Scene\ /S /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Creature\*.* .\Benchmark\MMOGame\Content\MMOContent\02_Creature\ /S /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\03_FX\*.* .\Benchmark\MMOGame\Content\MMOContent\03_FX\ /S /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\03_Water\*.* .\Benchmark\MMOGame\Content\MMOContent\03_Water\ /S /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\04_MaterialTemplate\*.* .\Benchmark\MMOGame\Content\MMOContent\04_MaterialTemplate\ /S /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\05.Archetype\*.* .\Benchmark\MMOGame\Content\MMOContent\05.Archetype\ /S /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\11.GameplayModel\*.* .\Benchmark\MMOGame\Content\MMOContent\11.GameplayModel\ /S /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\Tech_Test\*.* .\Benchmark\MMOGame\Content\MMOContent\Tech_Test\ /S /F /Y /R
xcopy .\UE3\MMOGame\Content\MapsGlobalInfo\*.* .\Benchmark\MMOGame\Content\MapsGlobalInfo\ /S /F /Y /R

xcopy .\UE3\MMOGame\Content\UDKContent\TestPackages\SoftBody.upk .\Benchmark\MMOGame\Content\UDKContent\TestPackages\ /F /Y /R
xcopy .\UE3\MMOGame\Content\UDKContent\Shared\Effects\UDK_LUT.upk .\Benchmark\MMOGame\Content\UDKContent\Shared\Effects\ /F /Y /R
xcopy .\UE3\MMOGame\Content\UDKContent\UT3\Effects\UN_LensTypes.upk .\Benchmark\MMOGame\Content\UDKContent\UT3\Effects\ /F /Y /R
xcopy .\UE3\MMOGame\Content\UDKContent\UT3\Environments\UN_Sky.upk .\Benchmark\MMOGame\Content\UDKContent\UT3\Environments\ /F /Y /R

xcopy .\UE3\MMOGame\Content\MMOContent\MMO_DefaultPP.upk .\Benchmark\MMOGame\Content\MMOContent\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Characters\Female\MA\MA_F_Flame_All.upk .\Benchmark\MMOGame\Content\MMOContent\02_Characters\Female\MA\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Characters\Female\MA\MA_F_Animation.upk .\Benchmark\MMOGame\Content\MMOContent\02_Characters\Female\MA\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Characters\Female\MA\MA_F_Body\T_MA_F_Hair_01.upk .\Benchmark\MMOGame\Content\MMOContent\02_Characters\Female\MA\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Characters\Female\MA\MA_F_Body\T_MA_F_Face_01.upk .\Benchmark\MMOGame\Content\MMOContent\02_Characters\Female\MA\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Item\Shoulder\Cloth\Shoulder_Cloth_Elftutor_L.upk .\Benchmark\MMOGame\Content\MMOContent\02_Item\Shoulder\Cloth\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Item\Female\Chest\Cloth\Chest01_Cloth_Elftutor.upk .\Benchmark\MMOGame\Content\MMOContent\02_Item\Female\Chest\Cloth\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Item\Female\Gloves\Cloth\Gloves01_Cloth_Elftutor.upk .\Benchmark\MMOGame\Content\MMOContent\02_Item\Female\Gloves\Cloth\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Item\Female\Belts\Cloth\Belts01_Cloth_Elftutor.upk .\Benchmark\MMOGame\Content\MMOContent\02_Item\Female\Belts\Cloth\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Characters\Female\MA\MA_F_Body\T_MA_F_Skin_01.upk .\Benchmark\MMOGame\Content\MMOContent\02_Characters\Female\MA\MA_F_Body\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Item\Female\Boots\Cloth\Boots01_Cloth_Elftutor.upk .\Benchmark\MMOGame\Content\MMOContent\02_Item\Female\Boots\Cloth\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\02_Item\Weapon\Wands\Wand_Flame1H.upk .\Benchmark\MMOGame\Content\MMOContent\02_Item\Weapon\Wands\ /F /Y /R

xcopy .\UE3\MMOGame\Content\MMOContent\08.UI\UI_Benchmark.upk .\Benchmark\MMOGame\Content\MMOContent\08.UI\ /F /Y /R
xcopy .\UE3\MMOGame\Content\MMOContent\08.UI\UI_MMOFonts.upk .\Benchmark\MMOGame\Content\MMOContent\08.UI\ /F /Y /R

delpdb.bat