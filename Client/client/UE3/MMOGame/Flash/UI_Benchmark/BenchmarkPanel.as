package UI_Benchmark{
	
	import ActionScript3.MyPanel;
	
	
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.TextInput;
	import flash.display.MovieClip;
	
	public class BenchmarkPanel extends MyPanel
	{
		public var txt_avg_fps:TextField;
		public var txt_max_fps:TextField;
		public var txt_cpu_info:TextField;
		public var txt_mem_info:TextField;
		public var txt_gpu_info:TextField;
		public var txt_screen_res:TextField;
		public var rank_mc:MovieClip;
		
		override protected  function configUI():void 
		{			
			trace("------BenchmarkPanel  super.configUI:");
			super.configUI();			
			
			ExternalInterface.call("ASRegisterBenchmarkPanel", this);
						
			if(0)
			{				
				UCUpdateBenchmarkInfo(60, 88, "Intel i7 950 @ 3.07GHz", "8.00GB", "ATI HD6970", "1280x720");
			}
		}
		
		
		public function UCUpdateBenchmarkInfo(avgFPS:int, maxFPS:int, cpuInfo:String, memInfo:String, gpuInfo:String, scrRes:String):void
		{
			txt_avg_fps.text = avgFPS.toString();
			txt_max_fps.text = maxFPS.toString();
			txt_cpu_info.text = cpuInfo;
			txt_mem_info.text = memInfo;
			txt_gpu_info.text = gpuInfo;
			txt_screen_res.text = scrRes;
			
			/*
			if(avgFPS < 30)
			{
				rank_mc.gotoAndStop(3);
			}			
			else if(avgFPS >= 60)
			{
				rank_mc.gotoAndStop(1);
			}
			else
			{
				rank_mc.gotoAndStop(2);				
			}
			*/
		}
	}

}