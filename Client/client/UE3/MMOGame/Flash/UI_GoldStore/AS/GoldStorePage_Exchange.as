package UI_GoldStore.AS 
{
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Common.TextInput_Advanced;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import UI_GoldStore.AS.moneyTypeIcon.GoldStoreMoneyIcon;
	import UI_GoldStore.AS.moneyTypeIcon.GoldStoreMoneyIconPool;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	
	/**
	 * 客户端下发的数据是以点券为单位的，UI界面显示又以元宝或者RMB为单位进行显示，100点券 = 1 元宝
	 * @author wangpenghe.phil
	 * 
	 */	
	public class GoldStorePage_Exchange extends UIComponent 
	{		
		public var tab_buy:RadioButton;
		public var tab_sell:RadioButton;
		
		public var btn_type_gold:RadioButton;
		public var btn_type_RMB:RadioButton;
		
		public var downArrow:Button;
		public var upArrow:Button;
		
		public var money_unit_price:TextInput_Advanced;
		public var money_unit_price_money_icon:GoldStoreMoneyIcon;
		
		public var txt_exchange_type:TextField;
		public var txt_input_exchange_amount:TextInput_Advanced;
		
		public var money_total_price:TextField;
		public var money_total_price_money_icon:GoldStoreMoneyIcon;
		
		public var item_list_sell:ScrollingList;
		public var item_list_buy:ScrollingList;
		public var btn_deal:Button;
		//-------------------------------------------------------//

		//public var btn_reset:Button;
		
		public var itemControl_sell:GoldStoreListItem_Control;
		public var itemControl_buy:GoldStoreListItem_Control;
		
		public var item_title:GoldStore_Title;
		
		public var txt_description:TextField;
		
		public var playerMoneyInfo:PlayerMoneyData;
		
		private static const GOLD_UNIT:int = 10000;
		private static const UNIT_PRICE_MAX_VALUE:Number = 99999;
		private static const MAX_NUMBER_OF_LIST_ITEM:int = 5;
		private static const DEFAULT_EXCHANGE_MONEY_NUMBER:int = 1;
		
		private var _moneyType:int 		 = 0;
		private var _exchangeType:int 	 = 0;
		private var _unitPriceCoupon:int = 0;
		private var _exchangeCount:int	 = 0;
		
		override protected function configUI():void
		{
			super.configUI();
			tab_buy.addEventListener(ButtonEvent.CLICK, onExchangeTypeChanged);
			tab_sell.addEventListener(ButtonEvent.CLICK, onExchangeTypeChanged);
			
			downArrow.addEventListener(ButtonEvent.CLICK, onUnitPriceDecreased);
			upArrow.addEventListener(ButtonEvent.CLICK, onUnitPriceIncreased);
			
			btn_type_gold.addEventListener(ButtonEvent.CLICK, onSwitchMoneyType);
			btn_type_RMB.addEventListener(ButtonEvent.CLICK, onSwitchMoneyType);
			
			btn_type_gold.visible = btn_type_RMB.visible = false;//wph@2015-10-30 人民币交易暂时屏蔽
			
			money_unit_price.textField.restrict = ConfigConstants.RESTRICT_OF_MONEY_INPUT + ".";
			money_unit_price.addEventListener(Event.CHANGE, onUnitPriceChanged);
			
			btn_deal.addEventListener(ButtonEvent.CLICK, onDeal);
			txt_input_exchange_amount.textField.restrict = ConfigConstants.RESTRICT_OF_MONEY_INPUT;
			txt_input_exchange_amount.addEventListener(Event.CHANGE, onExchangeAmountChanged);
			
			itemControl_sell = new GoldStoreListItem_Control(item_list_sell);
			itemControl_buy = new GoldStoreListItem_Control(item_list_buy);
			item_list_sell.addEventListener(ListEvent.ITEM_CLICK, OnItemClick,false, 0, true);
			item_list_buy.addEventListener(ListEvent.ITEM_CLICK, OnItemClick,false, 0, true);
			
			item_title.setLabel("单价","数量");
			txt_exchange_type.text = "数量";
			playerMoneyInfo = new PlayerMoneyData();
			switchExchangeType(GoldStoreUltils.EXCHANGE_TYPE_BUY);
			
			UCSetGoldStoreListBuying(null);
			UCSetGoldStoreListSelling(null);
			btn_type_gold.selected = true;
			onSwitchMoneyType(null);
		}
		
		public function GoldStorePage_Exchange() 
		{
			// constructor code
		}
		
		private function switchExchangeType(type:int):void
		{
			if(_exchangeType != type)
			{
				if(type == GoldStoreUltils.EXCHANGE_TYPE_BUY)
				{
					tab_buy.selected = true;
					tab_sell.selected = false;
					_exchangeType = GoldStoreUltils.EXCHANGE_TYPE_BUY;
					//txt_exchange_type.text = "买入";
					btn_deal.label = "下单买入";
				}
				else if(type == GoldStoreUltils.EXCHANGE_TYPE_SELL)
				{
					tab_buy.selected = false;
					tab_sell.selected = true;
					_exchangeType = GoldStoreUltils.EXCHANGE_TYPE_SELL;
					//txt_exchange_type.text = "卖出";
					btn_deal.label = "下单卖出";
				}
				ExternalInterface.call("ASOnExchangeTypeClick", _exchangeType);
			}
//			ExternalInterface.call("ASOnExchangeTypeChanged", _exchangeType);
//			UCSetDefaultPrice();
		}
		
		private function onExchangeAmountChanged(evt:Event):void
		{
			exchangeSettingChanged();
		}
		
		private function onUnitPriceChanged(evt:Event):void
		{
			var priceStr:String = money_unit_price.text;
			var priceCouponNum:int = 0;
			var firstDotIndx:int = priceStr.indexOf(".");
			
			if(firstDotIndx != -1)
			{
				priceStr = priceStr.substring(0, firstDotIndx + 3);//保留2位小数
				var lastDotIndex:int = priceStr.lastIndexOf(".");
				if(lastDotIndex != -1 && lastDotIndex != firstDotIndx)
				{
					priceStr = priceStr.substring(0, lastDotIndex)//删除多余小数点
				}
				money_unit_price.text = priceStr;
			}

			if(_moneyType == GoldStoreUltils.MONEY_TYPE_GOLD)
			{
				priceCouponNum = GoldStoreUltils.goldToCoupon(Number(priceStr));
				if(priceCouponNum > UNIT_PRICE_MAX_VALUE)
				{
					priceCouponNum = UNIT_PRICE_MAX_VALUE;
					priceStr = GoldStoreUltils.couponToGold(priceCouponNum, false);
					money_unit_price.text = priceStr;
				}
			}
			else if(_moneyType == GoldStoreUltils.MONEY_TYPE_RMB)
			{
				priceCouponNum = GoldStoreUltils.cashToCoupon(Number(priceStr));
				if(priceCouponNum > UNIT_PRICE_MAX_VALUE)
				{
					priceCouponNum = UNIT_PRICE_MAX_VALUE;
					priceStr = GoldStoreUltils.couponToCash(priceCouponNum, false);
					money_unit_price.text = priceStr;
				}
			}
			
			if(_unitPriceCoupon != priceCouponNum)
			{
				_unitPriceCoupon = priceCouponNum;
				exchangeSettingChanged();
			}
		}
		
		private function onExchangeTypeChanged(evt:ButtonEvent):void
		{
			if(tab_buy.selected && _exchangeType != GoldStoreUltils.EXCHANGE_TYPE_BUY)
			{
				onReset();
				switchExchangeType(GoldStoreUltils.EXCHANGE_TYPE_BUY);
			}
			else if(tab_sell.selected && _exchangeType != GoldStoreUltils.EXCHANGE_TYPE_SELL)
			{
				onReset();
				switchExchangeType(GoldStoreUltils.EXCHANGE_TYPE_SELL);
			}
		}
		
		private function onSwitchMoneyType(evt:ButtonEvent):void
		{
			if(_moneyType != GoldStoreUltils.MONEY_TYPE_GOLD && btn_type_gold.selected)
			{
				btn_type_RMB.selected = false;
				_moneyType = GoldStoreUltils.MONEY_TYPE_GOLD;
				GoldStoreMoneyIconPool.getInstance().switchMoneyIconType(_moneyType);
			}
			else if(_moneyType != GoldStoreUltils.MONEY_TYPE_RMB && btn_type_RMB.selected)
			{
				btn_type_gold.selected = false;
				_moneyType = GoldStoreUltils.MONEY_TYPE_RMB;
				GoldStoreMoneyIconPool.getInstance().switchMoneyIconType(_moneyType);
			}
		}
		
		private function onUnitPriceDecreased(evt:ButtonEvent):void
		{
			if(_unitPriceCoupon - GoldStoreUltils.UNIT_PRICE_CHANGED_STEP_VALUE >= 0)
			{
				_unitPriceCoupon = _unitPriceCoupon - GoldStoreUltils.UNIT_PRICE_CHANGED_STEP_VALUE;
				money_unit_price_money_icon.couponValue = _unitPriceCoupon;
				exchangeSettingChanged();
			}
		}
		
		private function onUnitPriceIncreased(evt:ButtonEvent):void
		{
			if(_unitPriceCoupon + GoldStoreUltils.UNIT_PRICE_CHANGED_STEP_VALUE <= UNIT_PRICE_MAX_VALUE)
			{
				_unitPriceCoupon = _unitPriceCoupon + GoldStoreUltils.UNIT_PRICE_CHANGED_STEP_VALUE;
				money_unit_price_money_icon.couponValue = _unitPriceCoupon;
				exchangeSettingChanged();
			}
		}
		
		public function onDeal():void
		{
			if(_exchangeType == GoldStoreUltils.EXCHANGE_TYPE_BUY)
			{
				var dat_buy:BuyInfoData = new BuyInfoData();
				dat_buy.buy_UnitPrice =  _unitPriceCoupon;
				dat_buy.buy_Number = Number(txt_input_exchange_amount.text);
				ExternalInterface.call("ASGoldStoreBuy", dat_buy, _moneyType);
			}
			else if(_exchangeType == GoldStoreUltils.EXCHANGE_TYPE_SELL)
			{
				var dat_sell:SellInfoData = new SellInfoData();
				dat_sell.sell_UnitPrice = _unitPriceCoupon;
				dat_sell.sell_Number = Number(txt_input_exchange_amount.text);
				dat_sell.sell_TotalPrice = int(money_total_price.text);

				ExternalInterface.call("ASGoldStoreSell", dat_sell, _moneyType);
			}
		}
		
		public function onReset():void
		{
			money_unit_price_money_icon.couponValue = 0;
			_unitPriceCoupon = 0;
			_exchangeCount   = 0;
			txt_input_exchange_amount.text = "0";
			money_total_price_money_icon.couponValue = 0;
			btn_deal.enabled = true;
			money_total_price.textColor = 0xFFCC00;
		}
		
		private function exchangeSettingChanged():void
		{
			var amount:Number = Number(txt_input_exchange_amount.text);
			var totalMoney:Number = amount * _unitPriceCoupon;
			if(_exchangeType == GoldStoreUltils.EXCHANGE_TYPE_BUY)
			{
				checkTotalPrice(totalMoney);
			}
			else if(_exchangeType == GoldStoreUltils.EXCHANGE_TYPE_SELL)
			{
				if(amount * GOLD_UNIT > playerMoneyInfo.player_money)
				{
					amount = Math.floor(playerMoneyInfo.player_money / GOLD_UNIT);//is Math.ceil correct?
					txt_input_exchange_amount.text = amount.toString();
					totalMoney = amount * _unitPriceCoupon;
					money_total_price.textColor = 0xFFCC00//0xffffff;
					btn_deal.enabled = true;
				}
			}
			money_total_price_money_icon.couponValue = totalMoney;
		}
		
		private function checkTotalPrice(totalMoney:Number):void
		{
			if(_moneyType == GoldStoreUltils.MONEY_TYPE_GOLD)
			{
				if(totalMoney <= playerMoneyInfo.player_RealMoney)
				{
					btn_deal.enabled = true;
					money_total_price.textColor = 0xFFCC00//0xffffff;
				}
				else
				{
					btn_deal.enabled = false;
					money_total_price.textColor = 0xff0000;
				}
			}
			else if(_moneyType == GoldStoreUltils.MONEY_TYPE_RMB)
			{
				if(totalMoney <= playerMoneyInfo.player_RealCash)
				{
					btn_deal.enabled = true;
					money_total_price.textColor = 0xFFCC00//0xffffff;
				}
				else
				{
					btn_deal.enabled = false;
					money_total_price.textColor = 0xff0000;
				}
			}

			money_total_price_money_icon.couponValue = totalMoney;
		}
		
		public function OnItemClick(event:ListEvent):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if(list)
			{
				if(list == item_list_buy)
				{
					switchExchangeType(GoldStoreUltils.EXCHANGE_TYPE_BUY);
				}
				else if(list == item_list_sell)
				{
					switchExchangeType(GoldStoreUltils.EXCHANGE_TYPE_SELL);
				}
			}
//			trace("GoldStorePage_Buy::onItemClick:　"　+　event.index);
//			var list:ScrollingList = event.target as ScrollingList;
//			
//			if (list != null)
//			{
//				var dp:DataProvider = list.dataProvider as DataProvider;
//				if (dp!=null)
//				{
//					var dat:GoldStoreItemData = dp.requestItemAt(event.index) as GoldStoreItemData;
//					if(dat != null)
//					{
//						_unitPriceCoupon = dat.Coupon;
//						_exchangeCount   = dat.Count;
//						money_unit_price_money_icon.couponValue = _unitPriceCoupon;
//						//check unit price
//						if(_unitPriceCoupon % 10 != 0)
//						{
//							throw new Error("OnItemClick:invalid unitPrice: " + _unitPriceCoupon);
//						}
//						txt_input_exchange_amount.text 			= _exchangeCount.toString();
//						if(dat.ExchangeType == GoldStoreUltils.EXCHANGE_TYPE_BUY)
//							switchExchangeType(GoldStoreUltils.EXCHANGE_TYPE_SELL);
//						else
//							switchExchangeType(GoldStoreUltils.EXCHANGE_TYPE_BUY);
//					}
//				}
//			}
		}
		
		public function UCSetGoldStoreListBuying(dat:Array):void
		{
			if(dat != null)
			{
				if(dat.length > MAX_NUMBER_OF_LIST_ITEM)
				{
					dat.length = MAX_NUMBER_OF_LIST_ITEM;
				}
				dat.reverse();
				for(var i:int = dat.length; i < MAX_NUMBER_OF_LIST_ITEM; i++)
				{
					dat.unshift(null);
				}
			}
			itemControl_buy.updateGoldStoreItemListData(dat);
		}
		
		public function UCSetGoldStoreListSelling(dat:Array):void
		{
			itemControl_sell.updateGoldStoreItemListData(dat);
		}
		
		public function UCSetPlayerMoney(dat:int):void
		{
			playerMoneyInfo.player_money = dat;
		}
		
		public function UCSetPlayerRealMoney(dat:int):void
		{
			playerMoneyInfo.player_RealMoney = dat;
		}
		
		public function UCSetPlayerRealCash(dat:Number):void
		{
			playerMoneyInfo.player_RealCash = dat;
		}
		
		public function UCSetAveragePrice(dat:int):void
		{
			playerMoneyInfo.averageMoney = dat;
		}
		
		public function UCResetGoldStorePage():void
		{
			onReset();
		}
		
		public function UCSetExchangePageDescription(desc:String):void
		{
			txt_description.htmlText = desc;
		}
		
		public function UCSetDefaultPrice(price:int, count:int):void
		{
			money_unit_price_money_icon.couponValue = price;
			txt_input_exchange_amount.text = DEFAULT_EXCHANGE_MONEY_NUMBER.toString();
			_unitPriceCoupon = price;
			exchangeSettingChanged();
		}
	}
	
}
