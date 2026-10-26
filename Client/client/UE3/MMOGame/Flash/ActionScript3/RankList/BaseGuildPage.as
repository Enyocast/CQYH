package ActionScript3.RankList {
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollingList;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import scaleform.clik.data.DataProvider;
	import flash.external.ExternalInterface;
	
	public class BaseGuildPage extends UIComponent{
		
		public var category0_btn_mc:Button;
		public var category1_btn_mc:Button;
		public var category2_btn_mc:Button;
		public var category3_btn_mc:Button;
		
		public var tabTitle:MovieClip;
		public var content_list_mc:ScrollingList;
		override protected function configUI():void
		{
			super.configUI();
			var i:int=0;
			for(i=0;i<4;i++)
			{
				var cate:Button=this.getChildByName("category"+i+"_btn_mc") as Button;
				if(cate)
				{
					cate.itemid=i;
					cate.addEventListener(MouseEvent.CLICK, OnCategoryClick);
				}
/*				var mc:RadioButton=this.getChildByName("range"+i+"_radio_mc") as RadioButton;
				if(mc)
				{
					mc.itemid=i;
					mc.addEventListener(MouseEvent.CLICK, OnPersonRangeClick);
				}*/
			}
		}
		
		public function UpdateGuildListData( dat:Array ):void
		{
			if(visible && null != dat)
			{
				content_list_mc.dataProvider = new DataProvider(dat);
				content_list_mc.validateNow();
				content_list_mc.invalidateData();
			}
		}
		
		public function clear():void
		{
			if(category0_btn_mc)
			category0_btn_mc.selected=true;
		}
		
		protected function OnCategoryClick(evt:MouseEvent):void
		{
			var mc:Button=evt.target as Button;
			if(mc)
			{
				var index:int=int(mc.itemid);
				ExternalInterface.call("ASCategoryClick", index);
			}
		}
	}
	
}
