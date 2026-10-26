package UI_TeamWidget.AS{
	
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import ActionScript3.controls.StateUIComponent;
	
	public class TeamFBListItemTitle extends StateUIComponent
	{
		public var text_0:TextField;
		public var text_1:TextField;
		public var text_2:TextField;
		
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function setDataObject(data:Object):void
		{
			text_0.text = data.text_0;
			text_1.text = data.text_1;
			text_2.text = data.text_2;
		}
	}
	
}