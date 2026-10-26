package ActionScript3.UndergroundTrade
{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ScrollingList;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.interfaces.IDataProvider;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	
	import ActionScript3.UndergroundTrade.UTListItemRender;
	import ActionScript3.UndergroundTrade.UTListItemData;
	
	public class MySignPanel extends UIComponent
	{
		public var equipname_btn_mc:Button;
		public var level_btn_mc:Button;
		public var signer_btn_mc:Button;
		public var price_btn_mc:Button;
		public var lefttime_btn_mc:Button;
		public var mysign_list_mc:ScrollingList;
		
		public var bid_btn_mc:Button;
		public var gold_txt_mc:TextField;
		public var prevpage_btn_mc:Button;
		public var nextpage_btn_mc:Button;
		public var page_txt_mc:TextField;
		
		public function MySignPanel()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			trace("------MySignPanel  super.configUI:");
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
			UpdateMysignData(searchItemData);
		}
		
		private function InitData():void
		{
			if(null != equipname_btn_mc)
				equipname_btn_mc.label = "装备名字";
			if(null != level_btn_mc)
				level_btn_mc.label = "等级";
			if(null != signer_btn_mc)
				signer_btn_mc.label = "签名人";
			if(null != price_btn_mc)
				price_btn_mc.label = "当前价格";
			if(null != lefttime_btn_mc)
				lefttime_btn_mc.label = "剩余时间";
			
			if(null != mysign_list_mc)
			{
				mysign_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnMysignListItemClick);
			}
			
			if(null != bid_btn_mc)
			{
				bid_btn_mc.label = "竞标";
				bid_btn_mc.addEventListener(MouseEvent.CLICK, OnBid);
			}
			
			if(null != prevpage_btn_mc)
				prevpage_btn_mc.addEventListener(MouseEvent.CLICK, OnPrevPage);
			if(null != nextpage_btn_mc)
				nextpage_btn_mc.addEventListener(MouseEvent.CLICK, OnNextPage);
		}
		
		function OnMysignListItemClick(e:ListEvent):void
		{
			var listItem:UTListItemRender = e.itemRenderer as UTListItemRender;
			//if(null != listItemSearch)
				//listItemSearch.SearchListItemData.
		}
		
		function OnBid():void
		{
			
		}
		
		function OnPrevPage():void
		{
			
		}
		
		function OnNextPage():void
		{
			
		}
		
		public function UpdateMysignData( data:Array ):void
		{
			if(null != data && mysign_list_mc != null)
			{
				mysign_list_mc.dataProvider = new DataProvider(data);
				mysign_list_mc.validateNow();
				mysign_list_mc.invalidateData();
			}
			else
				trace("MysignPanel->UpdateMysignData failed!");
		}
	}
	
}
