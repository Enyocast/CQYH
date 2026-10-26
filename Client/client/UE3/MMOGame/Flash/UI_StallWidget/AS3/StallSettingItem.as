package UI_StallWidget.AS3
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.utils.setTimeout;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	
	public class StallSettingItem extends MyItemSlot
	{
		public var tF_Gold:TextField;
		public var tF_Gold_Total:TextField;
		
		public function StallSettingItem()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			_select_border.visible = false;
		}
		
		
//		override public function SetData( inquantity:Number, iniconName:String , initemIndex:int, initemtype:String, initemColor:int, incontainerID:int, inslotID:int ):void
//		{
//			super.SetData(inquantity, iniconName, initemIndex, initemtype, initemColor, incontainerID, inslotID);
//			setTimeout(checkGoldTextBoundary, 50);
//		}
		
		public function checkGoldTextBoundary():void
		{
			var info:String = tF_Gold.text;
			var len:int = info.length;
			var checkIndex:int = tF_Gold.getCharIndexAtPoint(60, 12);
			if(checkIndex < len - 1 && checkIndex != -1)
			{
				info = info.substring(0, checkIndex) + "...";
				tF_Gold.text = info;
			}
			
			var info_Total:String = tF_Gold_Total.text;
			var len_Total:int = info_Total.length;
			var checkIndex_Total:int = tF_Gold_Total.getCharIndexAtPoint(60, 12);
			if(checkIndex_Total < len_Total - 1 && checkIndex_Total != -1)
			{
				info_Total = info_Total.substring(0, checkIndex_Total) + "...";
				tF_Gold_Total.text = info_Total;
			}
		}
		
		override public function set selected(value:Boolean):void
		{
			//super.selected = value;	// 这行代码会导致选中后显示不对
//			if(_select_border==null)
//			{
//				_select_border = (getChildByName("_select_border") as MovieClip);
//			}
//			if(_select_border)
//			{
//				_select_border.visible = value;
//			}
		}
	}
}