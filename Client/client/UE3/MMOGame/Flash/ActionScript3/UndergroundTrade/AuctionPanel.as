package ActionScript3.UndergroundTrade
{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.interfaces.IDataProvider;
	
	import ActionScript3.UndergroundTrade.UTListItemRender;
	import ActionScript3.UndergroundTrade.UTListItemData;
	
	public class AuctionPanel extends UIComponent 
	{
		public var continuebid_btn_mc:Button;
		public var prevsellpage_btn_mc:Button;
		public var nextsellpage_btn_mc:Button;
		public var sellpage_txt_mc:TextField;
		public var prevbidpage_btn_mc:Button;
		public var nextbidpage_btn_mc:Button;
		public var bidpage_txt_mc:TextField;
		
		public var equipnamesell_btn_mc:Button;
		public var levelsell_btn_mc:Button;
		public var signersell_btn_mc:Button;
		public var statussell_btn_mc:Button;
		public var lefttimesell_btn_mc:Button;
		
		public var equipnamebid_btn_mc:Button;
		public var levelbid_btn_mc:Button;
		public var signerbid_btn_mc:Button;
		public var pricebid_btn_mc:Button;
		public var lefttimebid_btn_mc:Button;
		
		public var mysell_list_mc:ScrollingList;
		public var mybid_list_mc:ScrollingList;
		
		public function AuctionPanel()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			trace("------AuctionPanel  super.configUI:");
			super.configUI();
			
			InitData();
			
			var searchItemData:Array = new Array();
			for(var index:int = 0; index < 15; ++index)
			{
				var data:UTListItemData = new UTListItemData;
				data.iconName = "" ;
				data.equipName = "屠龙刀" + index;
				data.level = index.toString() ;
				data.signer = "张无忌" + index;
				data.all = (3000 + index).toString();
				data.leftTime = "2013-12-" + index;
				searchItemData.push(data);
			}
			UpdateMySellListData(searchItemData);
			UpdateMyBidListData(searchItemData);
		}
		
		private function InitData():void
		{
			if(null != continuebid_btn_mc)
			{
				continuebid_btn_mc.label = "继续竞拍";
				continuebid_btn_mc.addEventListener(MouseEvent.CLICK, OnContinueBidClick);
			}
			
			if(null != mysell_list_mc)
				mysell_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnMysellListItemClick);
			if(null != mybid_list_mc)
				mybid_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnMyBidListItemClick);
			
			if(null != prevsellpage_btn_mc)
				prevsellpage_btn_mc.addEventListener(MouseEvent.CLICK, OnPrevSellPageClick);
			if(null != nextsellpage_btn_mc)
				nextsellpage_btn_mc.addEventListener(MouseEvent.CLICK, OnNextSellPageClick);
			if(null != prevbidpage_btn_mc)
				prevbidpage_btn_mc.addEventListener(MouseEvent.CLICK, OnPrevBidPageClick);
			if(null != nextbidpage_btn_mc)
				nextbidpage_btn_mc.addEventListener(MouseEvent.CLICK, OnNextBidPageClick);
				
			if(null != equipnamesell_btn_mc)
				equipnamesell_btn_mc.label = "装备名字";
			if(null != levelsell_btn_mc)
				levelsell_btn_mc.label = "等级";
			if(null != signersell_btn_mc)
				signersell_btn_mc.label = "签名人";
			if(null != statussell_btn_mc)
				statussell_btn_mc.label = "状态";
			if(null != lefttimesell_btn_mc)
				lefttimesell_btn_mc.label = "剩余时间";
				
			if(null != equipnamebid_btn_mc)
				equipnamebid_btn_mc.label = "装备名字";
			if(null != levelbid_btn_mc)
				levelbid_btn_mc.label = "等级";
			if(null != signerbid_btn_mc)
				signerbid_btn_mc.label = "签名人";
			if(null != pricebid_btn_mc)
				pricebid_btn_mc.label = "当前价格";
			if(null != lefttimebid_btn_mc)
				lefttimebid_btn_mc.label = "剩余时间";
		}
		
		function OnContinueBidClick():void
		{
			
		}
		
		function OnPrevSellPageClick():void
		{
			
		}
		
		function OnNextSellPageClick():void
		{
			
		}
		
		function OnPrevBidPageClick():void
		{
			
		}
		
		function OnNextBidPageClick():void
		{
			
		}
		
		function OnMysellListItemClick(e:ListEvent):void
		{
			//var listItemSearch:ListItemSearch = e.itemRenderer as ListItemSearch;
			//if(null != listItemSearch)
				//listItemSearch.SearchListItemData.
		}
		
		public function UpdateMySellListData( data:Array ):void
		{
			if(null != data && mysell_list_mc != null)
			{
				mysell_list_mc.dataProvider = new DataProvider(data);
				mysell_list_mc.validateNow();
				mysell_list_mc.invalidateData();
			}
			else
				trace("AuctionPanel->UpdateMySellListData failed!");
		}
		
		function OnMyBidListItemClick(e:ListEvent):void
		{
			//var listItemSearch:ListItemSearch = e.itemRenderer as ListItemSearch;
			//if(null != listItemSearch)
				//listItemSearch.SearchListItemData.
		}
		
		public function UpdateMyBidListData( data:Array ):void
		{
			if(null != data && mybid_list_mc != null)
			{
				mybid_list_mc.dataProvider = new DataProvider(data);
				mybid_list_mc.validateNow();
				mybid_list_mc.invalidateData();
			}
			else
				trace("AuctionPanel->UpdateMyBidListData failed!");
		}
	}
	
	
	
}
