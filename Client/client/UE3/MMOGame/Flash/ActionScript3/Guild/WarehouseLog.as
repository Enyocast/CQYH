package ActionScript3.Guild {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import scaleform.clik.controls.ScrollBar;
	import ActionScript3.MyPanel;
	
	
	public class WarehouseLog extends MyPanel {
		
		public var MoreButton:Button;
		public var OperateInfo:TextField;
		public var TextScrollbar:ScrollBar;
		
		override protected function configUI():void
		{
			MyWindowsFrame_mc.btn_close.visible=false;
			TextScrollbar.visible=false;
		}
		
		public function updateData(txt:String):void
		{
			if(txt.length>0)
			{
				TextScrollbar.visible=true;
			}
			else
			{
				TextScrollbar.visible=false;
			}
			OperateInfo.htmlText = txt;
		}
	}
	
}
