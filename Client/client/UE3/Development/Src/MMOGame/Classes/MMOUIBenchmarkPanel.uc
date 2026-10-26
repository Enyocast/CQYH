class MMOUIBenchmarkPanel extends MMOUIBase
	native(UI);


event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}


event InitOnce()
{
	super.InitOnce();	
}

// event OnShow(bool show)
// {
// 	NativeUpdateInfo();
// }
// 
// native final function NativeUpdateInfo();

event CallUpdateInfo(int avgFPS, int maxFPS, string cpuInfo, string memInfo, string gpuInfo, string scrRes)
{
	ActionScriptVoid("UCUpdateBenchmarkInfo");
}

DefaultProperties
{
}
