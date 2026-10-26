package UI_StallWidget.AS3
{
	import flash.text.TextField;
	
	import scaleform.clik.controls.ListItemRenderer;
	
	public class StallRecordListItem extends ListItemRenderer
	{
		public var txt_time:TextField;
	//	public var txt_action:TextField;
		public var txt_item_name:TextField;
		public var txt_gain:TextField;
		
		public function StallRecordListItem()
		{
			super();
		}
		
		override public function setData(data:Object):void
		{
			super.setData(data);
			if(data != null)
			{
				txt_time.text = _data['time'];
		//		txt_action.text = _data['action'];
				txt_item_name.htmlText = _data['item_name'];
				txt_gain.htmlText = _data['gain'];
				this.visible = true;
			}
			else
			{
				this.visible = false;
			}
		}
		
	}
}