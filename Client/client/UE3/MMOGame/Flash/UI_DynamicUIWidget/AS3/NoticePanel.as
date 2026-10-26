package UI_DynamicUIWidget.AS3 {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import ActionScript3.Common.Events.ParamEvent;
	import flash.text.TextFieldAutoSize;

	public class NoticePanel extends MyPanel {
		
		public var tf_content:TextField;
		public function NoticePanel() {
			// constructor code
		}
		override protected  function configUI():void 
		{
			ShowMode="BCB";
			super.configUI();
			this.enabled=false;
			this.mouseChildren=false;
			stageChangeHandler(null);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=(cavasWidth-this.width)>>1;
		}
		
		public function UCSetNoticeContents(type:int,content:String):void
		{
			tf_content.htmlText=content;
			tf_content.autoSize=TextFieldAutoSize.LEFT;
			this.width=tf_content.textWidth+8;
			this.x=(cavasWidth-this.width)>>1;
		}
	}
	
}
