package ActionScript3.RankList {
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import flash.text.TextField;
	import scaleform.clik.events.ButtonEvent;
	
	public class BasePersonPage extends UIComponent {

		public var category0_btn_mc:Button;
		public var category1_btn_mc:Button;
		public var category2_btn_mc:Button;
		public var category3_btn_mc:Button;
		public var category4_btn_mc:Button;

		//public var pagectrl_mc:MovieClip;
		public var tabTitle:MovieClip;
		
		public var content_list_mc:ScrollingList;
		override protected function configUI():void
		{
			super.configUI();
			var i:int=0;
/*			for(i=0;i<7;i++)
			{
				var mc:RadioButton=this.getChildByName("range"+i+"_radio_mc") as RadioButton;
				if(mc)
				{
					mc.itemid=i;
					mc.addEventListener(MouseEvent.CLICK, OnPersonRangeClick);
				}
			}
			var prevPage:Button = pagectrl_mc.getChildByName("btn_prev") as Button;
			if(null != prevPage)
				prevPage.addEventListener(MouseEvent.CLICK, OnPrevPageClick);
			var nextPage:Button = pagectrl_mc.getChildByName("btn_next") as Button;
			if(null != nextPage)
				nextPage.addEventListener(MouseEvent.CLICK, OnNextPageClick);*/
			for(i=0;i<5;i++)
			{
				var cate:Button=this.getChildByName("category"+i+"_btn_mc") as Button;
				if(cate)
				{
					cate.itemid=i;
					cate.addEventListener(MouseEvent.CLICK, OnCategoryClick);
				}
			}
		}
						
		public function UpdatePersonListData( dat:Array ):void
		{
			if(visible && null != dat)
			{
				content_list_mc.dataProvider = new DataProvider(dat);
				content_list_mc.validateNow();
				content_list_mc.invalidateData();
			}
		}
		
		public function clear():void
		{//还原数据 
			
			//(pagectrl_mc.getChildByName("tF_pageNum") as TextField).text="1/5";
		}
		
/*		//更新我的排名
		public function updateMyRank(Rank:String,CurrentRank:int,LastRank:int):void
		{
			if(myrank_mc)
			{
				myrank_mc.updateData(Rank,CurrentRank,LastRank);
			}
		}*/
		
		private function OnPersonRangeClick(evt:MouseEvent):void
		{
			var mc:RadioButton=evt.target as RadioButton;
			if(mc)
			{
				var index:int=int(mc.itemid);
				ExternalInterface.call("ASRangeClick", index);
			}
		}
		
		private function OnCategoryClick(evt:MouseEvent):void
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
