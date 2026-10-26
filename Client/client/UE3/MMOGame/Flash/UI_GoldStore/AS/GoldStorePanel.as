
package UI_GoldStore.AS
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.setTimeout;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButtonNew;
	import ActionScript3.Common.TextFieldScroller;
	
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;

	public class GoldStorePanel extends MyPanel
	{
		public var tab_exchange:RadioButton;
		public var tab_deal:RadioButton;
		public var tab_record_list:RadioButton;
		
		public var btn_freshen:Button;
//		public var txt_averagePrice:TextField;
		
		public var page_exchange:GoldStorePage_Exchange;
		public var page_OrderList:GoldStorePage_OrderList;
		public var page_record_list_mc:GoldStorePage_RecordList;
		
		public var page_recharge:GoldStorePage_Recharge;
		public var playerMoneyInfo:PlayerMoneyData;
		public var notice_tips_mc:GoldStoreNoticeTips;
		//add notice for all pages
		public var bg_mc_0:MovieClip;
		public var bg_mc_1:MovieClip;
		
		override protected  function configUI():void 
		{		
			this.ShowMode="BC";
			super.configUI();
			SetWindowTitle("金币交易行");
			tab_exchange.addEventListener(MouseEvent.CLICK, onClickPage_Exchange );
			tab_deal.addEventListener(MouseEvent.CLICK, onClickPage_Deal );
			tab_record_list.addEventListener(MouseEvent.CLICK, onClickPage_RecordList );
			btn_freshen.addEventListener(MouseEvent.CLICK, onFreshListView);
			notice_tips_mc.visible = false;
			//ExternalInterface.call("ASRegisterGoldStore", this);
			showPageByIndex(0);
			//test();
		}
		
		public function ASShowNoticeTips(bShow:Boolean):void
		{
			notice_tips_mc.visible = bShow;
		}
		
		public function UCShowPageByIndex(idx:int)
		{
			showPageByIndex(idx);
		}
		public function onClickPage_Exchange():void 
		{
			showPageByIndex(0);
		}
		
		public function onClickPage_RecordList():void 
		{
			showPageByIndex(1);
		}
		
		public function onClickPage_Deal():void 
		{
			showPageByIndex(2);
		}
		
		public function showPageByIndex(idx:int):void 
		{
			page_exchange.visible = (idx == 0);
			page_record_list_mc.visible = (idx == 1);
			page_OrderList.visible = (idx == 2);
			
			tab_exchange.selected = (idx == 0);
			tab_record_list.selected = (idx == 1);
			tab_deal.selected = (idx == 2);
			
			
			page_recharge.visible =  bg_mc_0.visible = bg_mc_1.visible = (idx == 0);
			
			//page_Deal should update after this call, but maybe haven't now.
			ExternalInterface.call("ASGoldStoreClickTabPage", idx);
		}
		
		public function onFreshListView():void 
		{
			//this.test();
			var type:int = -1;
			if(tab_deal.selected == true)
			{
				//need confirm
				ExternalInterface.call("ASFreshListView", 2);
			}else{
				type = tab_exchange.selected ? 0 : 1;
				ExternalInterface.call("ASFreshListView",type);
			}
		}
		
		public function UCSetGoldStore_ListBuying(dat:Array):void 
		{
			page_exchange.UCSetGoldStoreListBuying(dat);
		}
		
		public function UCSetGoldStore_ListSelling(dat:Array):void 
		{
			page_exchange.UCSetGoldStoreListSelling(dat);
		}
		
		public function UCSetGoldStore_CancelSell(dat:Array):void 
		{
			page_OrderList.UCSetGoldStoreCancelSell(dat);
		}
		
		public function UCSetGoldStore_OrderList(dat:Array):void 
		{
			page_OrderList.UCSetGoldStore_OrderList(dat);
		}
		
		public function UCSetGoldStore_ListSelling_My(dat:Array):void 
		{
			//page_Deal.UCSetGoldStoreListSelling_My(dat);
		}
		
		public function UCSetGoldStore_ListBuying_My(dat:Array):void
		{
			//page_Deal.UCSetGoldStoreListSelling_My(dat);
		}
		
		public function UCSetGoldStore_RecordList(dat:Array):void
		{
			page_record_list_mc.UCSetGoldStore_RecordList(dat);
		}
		
		public function UCSetPlayerMoney(dat:int):void 
		{
			page_exchange.UCSetPlayerMoney(dat);
			page_OrderList.UCSetPlayerMoney(dat);
			page_recharge.UCSetPlayerMoney(dat);
		}
		
		public function UCSetPlayerRealMoney(dat:int):void 
		{
			page_exchange.UCSetPlayerRealMoney(dat);
			page_OrderList.UCSetPlayerRealMoney(dat);
			page_recharge.UCSetPlayerRealMoney(dat);
		}
		
		public function UCSetPlayerRealCash(dat:Number):void 
		{
			page_exchange.UCSetPlayerRealCash(dat);
			page_recharge.UCSetPlayerRealCash(dat);
		}
		
		public function UCSetAveragePrice(dat:int):void 
		{
//			txt_averagePrice.text = GoldStoreUltils.couponToGold(dat); //#22955 wph@2015-11-17
			page_exchange.UCSetAveragePrice(dat);
			page_OrderList.UCSetAveragePrice(dat);
		}
		
		public function UCSetMyOrderCount(dat:int):void 
		{
			page_OrderList.UCSetMyOrderCount(dat);
		}
		
		public function UCSetMySellCount(sellDat:int):void 
		{
			page_OrderList.UCSetMySellCount(sellDat);
		}
		
		public function UCResetGoldStorePage():void 
		{
			page_exchange.UCResetGoldStorePage();
		}
		
		//interface
		public function UCSetNoticeInfo(info:String, explan:String, recordExplan:String, orderExplan:String = ""):void
		{
			page_exchange.UCSetExchangePageDescription(explan);
			page_record_list_mc.UCSetGoldStore_RecordList_Text(recordExplan);
			page_OrderList.UCSetGoldStore_OrderList_Text(orderExplan);
		}
		
		public function test():void 
		{
			UCSetPlayerMoney(1000001);
			UCSetPlayerRealMoney(0);
			UCSetPlayerRealCash(500);
			UCSetAveragePrice(100);
			var dat:Array = createTestItemList(2);//new Array();
			UCSetGoldStore_RecordList(dat);
			UCSetGoldStore_OrderList(dat);
			UCSetGoldStore_ListBuying(createTestItemList(2));
			UCSetGoldStore_ListSelling(createTestItemList(1));
			UCSetNoticeInfo("","","","订单列表保存七天内前100条记录");
		}
		
		public function createTestItemList(exchangeType:int):Array
		{					
			var itemsData:Array = new Array();
			
			for (var i:int = 0; i < 3; i++)
			{
				var dat:GoldStoreItemData = new GoldStoreItemData();
				dat.GoldStoreID = i;
				//dat.UnitPrice = i+100;
				dat.Coupon = 100 + (exchangeType - 1) * 5 + i * Math.pow(-1, exchangeType);
				dat.Count = 10+i;
				dat.CurCount = (8 + i) * Math.random();
				dat.times = 2400;
				dat.dealTime =  0.001 * (new Date()).time;
				dat.orderTime = 0.001 * (new Date()).time;
				dat.orderState = 1;
				dat.ExchangeType = exchangeType;
				dat.ExchangeTypeStr = dat.ExchangeType == 1 ? "买入" : "卖 出";
				itemsData.push(dat);
			}
			return itemsData;
		}
		
		public function UCSetDefaultPrice(price:int, count:int)
		{
			page_exchange.UCSetDefaultPrice(price,count);
		}
		
	}
}