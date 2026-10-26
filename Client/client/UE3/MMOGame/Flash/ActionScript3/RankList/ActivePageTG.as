package ActionScript3.RankList {
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.ScrollingList;
	import flash.external.ExternalInterface;
	import scaleform.clik.data.DataProvider;
	
	public class ActivePageTG extends UIComponent {

		public var tabTitle:MovieClip;
		public var category0_btn_mc:Button;
		public var category1_btn_mc:Button;
		public var category2_btn_mc:Button;
		public var category3_btn_mc:Button;
		public var content_list_mc:ScrollingList;
		public const rlType:int = 18;
		public var IsShowRank:Boolean=false;//是否显示排名
		override protected function configUI():void
		{
			super.configUI();
			(tabTitle.getChildByName("tf_num") as TextField).text="层数";
            (tabTitle.getChildByName("tf_dec") as TextField).text="时间";
			var i:int=0;
			for(i=0;i<4;i++)
			{
				var cate:Button=this.getChildByName("category"+i+"_btn_mc") as Button;
				if(cate)
				{
					cate.itemid = i ;
					cate.addEventListener(MouseEvent.CLICK, OnCategoryClick);
				}
			}
		}
		
		private function OnCategoryClick(evt:MouseEvent):void
		{
			if(IsShowRank==true)
			{
				var mc:Button=evt.target as Button;
			    if(mc)
			    {
				   var index:int=int(mc.itemid);
				   ExternalInterface.call("ASCategoryClick", index);
			     }
			}
		}
		
		public function clear():void
		{//还原数据
		   category0_btn_mc.selected=true;
			//super.clear();
		}
		public function setRdo(idx:int):void
		{
			if(idx == 0)
			{
				category0_btn_mc.selected = true;
			}
			else if(idx == 1)
			{
				category1_btn_mc.selected = true;
			}
			else if(idx == 4)
			{
				category2_btn_mc.selected = true;
			}
		}
		public function UpdateData( dat:Array ):void
		{
			content_list_mc.dataProvider = new DataProvider(dat);
			content_list_mc.validateNow();
			content_list_mc.invalidateData();
		}
	}
	
}
