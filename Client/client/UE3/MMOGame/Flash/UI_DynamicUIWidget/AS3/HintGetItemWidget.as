package UI_DynamicUIWidget.AS3 {
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	
	public class HintGetItemWidget extends MyPanel {
 
		public var ItemInfo:MovieClip;

		override protected function configUI():void
		{
			super.configUI();
		}

		public function ShowGetItem(strName:String,strIconName:String )
		{
			this.visible = true;
			gotoAndPlay("GetItem");
		}
		
		public function CloseGetItem()
		{
			this.visible = false;
			gotoAndStop(1);
		}

	}
	
}
