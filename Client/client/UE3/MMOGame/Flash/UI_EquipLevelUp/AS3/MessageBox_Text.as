package UI_EquipLevelUp.AS3
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.geom.Rectangle;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	
	public class MessageBox_Text extends MyPanel
	{
		public var txt_title:TextField;
		public var txt_content:TextField;
		public var btn_confirm:Button;
		
		private var _contentArea:Rectangle;
		
		public function MessageBox_Text()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			_contentArea = new Rectangle(txt_content.x, txt_content.y, txt_content.width, txt_content.height);
		}
		
		private function setContent(content:String):void
		{
			txt_content.text = content;
			var bottomPos:Number = (txt_content.getCharBoundaries(content.length - 1)).bottom;
			txt_content.y = _contentArea.y + (_contentArea.height - bottomPos) * 0.5;
		}
		
		public function setData(data:UpgradeResultData):void
		{
			if(data == null) return;
			txt_title.text = data.messageTitle;
			setContent(data.messageContent);
		}
	}
}