class MMOGFXPlayer_Benchmark extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIBenchmarkPanel            _BenchmarkPanel;

function ASRegisterBenchmarkPanel( MMOUIBenchmarkPanel mc )
{
	_BenchmarkPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Benchmark);
	//ShowUI(class'MMOUIManager'.default.Panel_Benchmark, false);
}

DefaultProperties
{
	MovieInfoStr="UI_Benchmark.BenchmarkWidget"
	Priority=5
}
