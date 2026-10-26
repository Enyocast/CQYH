package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.text.TextField;
	import scaleform.clik.controls.CheckBox;
	import flash.events.MouseEvent;
	import flash.events.Event;
	
	
	public class ListItem_HangItem extends ListItemTreeRenderer {
		
		public var textName:TextField;
		public var chk_jp:CheckBox;
		public var chk_auto:CheckBox;
		public var chk_showname:CheckBox;
		public var itemData:HangItemData;
		public var auto:Boolean;
		public var showName:Boolean;

		override protected function configUI():void
		{
			super.configUI();
			chk_jp.addEventListener(Event.SELECT,bestHandler);
			chk_auto.addEventListener(Event.SELECT,autoHandler);
			chk_showname.addEventListener(Event.SELECT,showNameHandler);
			setUpdateDataCallBack(UpdateData);
		}
		
		private function bestHandler(evt:Event):void
		{
			itemData.isBest=chk_jp.selected;
		}
		
		private function autoHandler(evt:Event):void
		{
			itemData.isAuto=chk_auto.selected;
			if(itemData.isAuto==false)
			{
				auto=true;
			}
		}
		
		private function showNameHandler(evt:Event):void
		{
			itemData.isShowName=chk_showname.selected;
			if(itemData.isShowName==false)
			{
				showName=true;
			}
		}
		
		public function UpdateData(dat:Object):void
		{
			auto=false;
			showName=false;
			if (dat)
			{  
				itemData=dat as HangItemData;
				textName.text = itemData.itemName;
				chk_jp.selected=itemData.isBest;
				chk_auto.selected=itemData.isAuto;
				chk_showname.selected=itemData.isShowName;
				this.visible=itemData.visible;
			}
			else
			{
				this.visible = false;
			}
		}
	}
	
}
