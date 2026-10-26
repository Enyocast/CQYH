package UI_GoldStore.AS 
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	
	public class GoldStorePage_OrderList extends UIComponent 
	{		
		private const STATE_PAGE_BUY:int = 1;
		private const STATE_PAGE_SELL:int = 2;
		
		private const ORDER_STATE_VALID:int = 1;
		
		public var playerMoneyInfo:PlayerMoneyData;
		public var btn_canelSell:Button;
		public var item_list:ScrollingList;
		public var txt_description:TextField;
		
		private var _listData:DataProvider;
		
		override protected function configUI():void
		{
			super.configUI();
			btn_canelSell.enabled = false;
			btn_canelSell.addEventListener(MouseEvent.CLICK, onCancelSellClick);
			playerMoneyInfo = new PlayerMoneyData();
			_listData = new DataProvider();
			//onBuyClick(null);
			item_list.addEventListener(ListEvent.ITEM_CLICK, OnItemClick,false, 0, true);
		}
		
		public function GoldStorePage_OrderList() 
		{
			// constructor code
		}
		
		private function OnItemClick(evt:ListEvent):void
		{
			var list:ScrollingList = evt.target as ScrollingList;
			
			if (list != null)
			{
				var dp:DataProvider = list.dataProvider as DataProvider;
				if (dp!=null)
				{
					var dat:GoldStoreItemData = dp.requestItemAt(evt.index) as GoldStoreItemData;
					if(dat != null)
					{
						btn_canelSell.enabled = (dat.orderState == ORDER_STATE_VALID);
					}
				}
			}
		}
		
		public function onCancelSellClick()
		{
			var index:int  = getSelectedItemDataIndex();
			if(index != -1)
			{
				ExternalInterface.call("ASGoldStoreCancelSell", index);
			}
		}
		
		public function UCSetGoldStoreCancelSell(dat:Array)
		{
			updateList(dat);
		}
		
		public function UCSetGoldStore_OrderList(dat:Array)
		{
			updateList(dat);
		}
		
		public function UCSetGoldStore_OrderList_Text(str:String)
		{
			txt_description.text = str;
		}
		
		public function UCSetGoldStoreListSelling_My(dat:Array)
		{
//			updateList(dat);
		}
		
		public function updateList(dat:Array)
		{
//			if(dat == null || dat.length == 0)
//			{
//				return;
//			}
			_listData.cleanUp();
			_listData.setSource(dat);
			item_list.dataProvider = _listData;
			item_list.validateNow();
			item_list.invalidateData();
			
			//update cancel button
			var itemDat:GoldStoreItemData = getSelectedItemData();
			if(itemDat != null)
			{
				btn_canelSell.enabled = (itemDat.orderState == ORDER_STATE_VALID);
			}
		}
		
		//for cancel action
		public function getSelectedItemData():GoldStoreItemData
		{
			var dp:DataProvider = item_list.dataProvider as DataProvider;
			if(dp != null){
				var selectedIndex:int = item_list.selectedIndex;
				if(selectedIndex >=0 && selectedIndex < dp.length){
					return dp[selectedIndex] as GoldStoreItemData;
				}
			}
			return null;
		}
		
		public function getSelectedItemDataIndex():int
		{
			var dp:DataProvider = item_list.dataProvider as DataProvider;
			if(dp != null){
				var selectedIndex:int = item_list.selectedIndex;
				if(selectedIndex >=0 && selectedIndex < dp.length){
					//return dp[selectedIndex] as GoldStoreItemData;
					return selectedIndex;
				}
			}
			return -1;
		}
		
		public function UCSetPlayerMoney(dat:int)
		{
			playerMoneyInfo.player_money = dat;
			
		}
		public function UCSetPlayerRealMoney(dat:int)
		{
			playerMoneyInfo.player_RealMoney = dat;
		}
		public function UCSetAveragePrice(dat:int)
		{
			playerMoneyInfo.averageMoney = dat;
		}
		
		public function UCSetMyOrderCount(dat:int)
		{
//			if(money_buyNumber){
//				money_buyNumber.text = (dat).toString();
//			}
		}
		
		public function UCSetMySellCount(sellDat:int)
		{
//			if(money_sellNumber){
//				money_sellNumber.text = (sellDat).toString();
//			}
		}
		
		public function selectMyOrder()
		{
//			btn_all_buy.selected = false;
//			btn_all_sell.selected = false;
//			ExternalInterface.call("ASGoldStoreShowMyOrder",1);
		}
	}
}
