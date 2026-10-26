package UI_DynamicUIWidget.AS3 {
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	
	public class WeatherChangePanel extends MyPanel {
		
        public var weather_change_mc:MovieClip;

		override protected  function configUI():void 
		{			
			super.configUI();
			this.enabled=false;
			this.mouseChildren=false;
			this.visible = false;
		}
		
		public function UCSetWeatherChangeString(content:String)
		{
			var weather_tf:TextField = weather_change_mc.getChildByName("tF_hintScene") as TextField;
			weather_tf.text = content;
			
			this.gotoAndPlay(1);
		}
		
		public function onPlayEnd()
		{
			ExternalInterface.call("ASOnPanelClose",this.name);
			stop();
			ExternalInterface.call("ASWeatherChangePlayEnd");
		}

	}
	
}
