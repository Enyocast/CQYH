package UI_StallWidget.AS3
{
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Utils.ConfigConstants;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.events.ButtonEvent;
	
	public class StallBuyMsgBox extends MyPanel
	{
		public var yesButton_mc:Button;
		public var noButton_mc:Button;
		
		public var BuyItem:MyItemSlot;
		public var tF_Name:TextField;
		public var tF_Price:TextField;
		public var tF_Max_Num:TextField;
		public var tF_Number:TextInput;
		public var tF_total_Price:TextField;
		public var upArrow:Button;
		public var downArrow:Button;
		
		private var _price:Number;
		private var _maxCount:Number;
		
		var ConSlotId:Number;
		var ItemSlotId:Number;
		var StallSlotId:Number;
		
		private static const HUNDRED_MILLION_YI:int = 100000000;
		private static const TEN_THOUSAND_WAN:int   = 10000;
		
		public function StallBuyMsgBox()
		{
			super();
		}
		
		override protected function configUI():void
		{
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			tF_Number.textField.restrict = ConfigConstants.RESTRICT_OF_MONEY_INPUT;
			
			tF_Number.addEventListener(Event.CHANGE, onInputChanged);
			
			downArrow.addEventListener(ButtonEvent.CLICK, minusCount);
			upArrow.addEventListener(ButtonEvent.CLICK, addCount);
			
			yesButton_mc.addEventListener(ButtonEvent.CLICK, StallBuyYes);
			noButton_mc.addEventListener(ButtonEvent.CLICK, StallBuyNo);
			SetWindowTitle("购买物品");
			this.visible = false;
		}
		
		public function InitPanel(tData:Object)
		{
			yesButton_mc.label = tData.TextOk;
			noButton_mc.label = tData.TextCancel;

			_price = tData.Price;
			tF_Name.text = tData.ItemName;

			ConSlotId = tData.ConSlot;
			ItemSlotId = tData.ItemSlot;
			StallSlotId = tData.StallSlot;
			
			_maxCount = tData.MaxCount;
			tF_Max_Num.text = _maxCount.toString();
			tF_Number.text = String(tData.Count);
			
			totalPrice();
			this.visible = true;
		}
		
		private function onInputChanged(e:Event):void
		{
			totalPrice();
		}
		
		private function addCount(evt:ButtonEvent):void
		{
			var i:Number;
			i = Number(tF_Number.text);
			if ( i < _maxCount )
			{
				++i;
			}
			tF_Number.text = String(i);
			totalPrice();
		}
		
		private function minusCount(evt:ButtonEvent):void
		{
			var i:Number;
			i = Number(tF_Number.text);
			if ( i > 0 )
			{
				i--;
			}
			tF_Number.text = String(i);
			totalPrice();
		}
		
		private function StallBuyYes(evt:ButtonEvent):void
		{
			var count:Number = Number(tF_Number.text);
			var price:Number = Number(tF_Price.text);
			ExternalInterface.call("ASStallBuyYes", StallSlotId, count);
		}
		
		private function StallBuyNo(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASStallBuyNo");
		}
		
		private function totalPrice():void
		{
			var num:Number;
			var total:Number;
			var tax:Number;
			
			num = Number(tF_Number.text);
			
			if ( num < 0 )
			{
				num = 0;
			}
			else if ( num >  _maxCount )
			{
				num = _maxCount;
			}
			
			tF_Number.text = String(num);
			
			if(_price < 0)
			{
				_price = 0;
				total = 0;
			}
			else
			{
				total = _price * num;
			}
			
			tF_Price.htmlText			=   formatMoneyNumberStr(_price);
			tF_total_Price.htmlText 	= 	formatMoneyNumberStr(total);
			
			checkButtonStatus();
			
		}
		
		private function checkButtonStatus():void
		{
			var i:Number;
			i = Number(tF_Number.text);
			if (i <= 1)
			{
				downArrow.enabled = false;
			}
			else
			{
				downArrow.enabled = true;
				
			}
			if (i >= _maxCount)
			{
				upArrow.enabled = false;
			}
			else
			{
				upArrow.enabled = true;
			}
		}
		
		private function formatMoneyNumberStr(total:Number):String
		{
			var res:String = "";
			if( total >= TEN_THOUSAND_WAN )
			{
				if(total >= HUNDRED_MILLION_YI)
				{
					res += Math.floor(total / HUNDRED_MILLION_YI ).toString();
					res += "亿";
				}
				if(total % HUNDRED_MILLION_YI >= TEN_THOUSAND_WAN)
				{
					res += Math.floor(total % HUNDRED_MILLION_YI / TEN_THOUSAND_WAN ).toString();
					res += "万";
				}
			}
			
			if(total % TEN_THOUSAND_WAN > 0 || total == 0)
				res += (total % TEN_THOUSAND_WAN).toString();
			
			res += String("<IMG  SRC='img://MMO_UIIcon.MoneyIcon.MoneyCash_S'>");
			
			return res;
		}
	}
}