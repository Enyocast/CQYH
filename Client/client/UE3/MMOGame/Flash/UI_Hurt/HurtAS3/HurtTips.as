package UI_Hurt.HurtAS3 {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import ActionScript3.MyScrollBar;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import flash.external.ExternalInterface;
	
	public class HurtTips extends MyPanel {
		
		public var item_list:ScrollingList;
		private var _hurtItem:HurtItem;
		override protected function configUI():void {
			 super.configUI();
			_hurtItem = new HurtItem(item_list);
			ExternalInterface.call("ASRegisterHurtTips", this);
		}
		
		public function UCSetHurtViewPage_Detailed(dat:Array):void
		{
			ExternalInterface.call("ASTrace", "UCSetAuctionBuyPage_ListData" + dat.length);
			_hurtItem.updateListData(dat);
		}
	}
	
}
