package UI_StallWidget.AS3
{
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	
	import ActionScript3.MoneyIcon;
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Utils.ConfigConstants;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.events.ComponentEvent;
	import scaleform.clik.managers.PopUpManager;

	public class StallMsgBox extends MyPanel
	{
		public var yesButton_mc:Button;
		public var noButton_mc:Button;
		public var tF_Name:TextField;
		public var tF_Price:TextInput;
		public var tF_Number:TextInput;
		
		public var SellItem:MyItemSlot;
		public var upArrow:Button;
		public var downArrow:Button;
		public var MaxCount:Number;
		public var MaxPrice:Number;
		public var TaxRate:Number = 0;
	//	public var tF_Money:TextField;
		public var tf_totalPrice:TextField;
		public var tf_tax_rate:TextField;
		public var tf_tax_money:TextField;
		
		var ConSlotId:Number;
		var ItemSlotId:Number;
		var StallSlotId:Number;
		
		private static const HUNDRED_MILLION_YI:int = 100000000;
		private static const TEN_THOUSAND_WAN:int   = 10000;
		private static const TAX_RATE:Number        = 5;

		override protected function configUI():void
		{
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
		//	ExternalInterface.call( "RegisterStallMsgBox", this);
			tF_Name.text = "";
			tF_Number.text = String(0);
			tF_Number.textField.restrict = "0-9";
			tF_Price.text = String(0);
			tF_Price.textField.restrict = "0-9";
			MaxCount = 20;
			MaxPrice = 1999999999;
			tF_Price.addEventListener( "change",OnInputChanged);
			tF_Number.addEventListener( "change",OnInputChanged);

			tF_Price.addEventListener( "input",OnInputChanged);
			tF_Number.addEventListener( "input",OnInputChanged);
			downArrow.addEventListener( "click",MinusCount);
			upArrow.addEventListener( "click",AddCount);
			yesButton_mc.addEventListener( "click", StallSetYes );
			noButton_mc.addEventListener( "click", StallSetNo );
			
			TaxRate = TAX_RATE;
			SetWindowTitle("物品出售");
		}
		
		public function InitPanel(tData:Object)
		{
			yesButton_mc.label = tData.TextOk;
			noButton_mc.label = tData.TextCancel;
			tF_Price.text = String(tData.Price);
			tF_Name.text = tData.ItemName;
			tF_Number.text = String(tData.Count);
			ConSlotId = tData.ConSlot;
			ItemSlotId = tData.ItemSlot;
			StallSlotId = tData.StallSlot;
			if(tData.TaxRate != null)
			{
				TaxRate = tData.TaxRate;
			}

			//买
			if(tData.PanelType == 0)
			{
				tF_Price.enabled = false;
			}
			else
			{
				tF_Price.enabled = true;
			}
			
			MaxCount = tData.MaxCount;
			
			tf_tax_rate.htmlText = (TaxRate).toString() + "%";
			
			TotalPrice();
			
		}
		
		public function UCSetTaxRate($taxRate:int):void
		{
			TaxRate = $taxRate;
			tf_tax_rate.htmlText = (TaxRate).toString() + "%";
			TotalPrice();
		}
		
		public function UCSetItemPrice($price:Number):void
		{
			tF_Price.text = String($price);
			TotalPrice();
		}

		function StallSetYes()
		{
			var count:Number = Number(tF_Number.text);
			var price:Number = Number(tF_Price.text);
			
			ExternalInterface.call("ASStallSettingMsgBoxYes", StallSlotId, ConSlotId, ItemSlotId, count, price);
		}
		
		function StallSetNo()
		{
			ExternalInterface.call("ASStallSettingMsgBoxNo");
		}

		function AddCount()
		{
			var i:Number;
			i = Number(tF_Number.text);
			if ( i < MaxCount )
			{
				++i;
			}
			tF_Number.text = String(i);
			TotalPrice();
		}

		function MinusCount()
		{
			var i:Number;
			i = Number(tF_Number.text);
			if ( i >0 )
			{
				i--;
			}
			tF_Number.text = String(i);
			TotalPrice();

		}

		function CheckButtonStatus()
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
			if (i >= MaxCount)
			{
				upArrow.enabled = false;
			}
			else
			{
				upArrow.enabled = true;
			}
		}

		function TotalPrice()
		{
			var num:Number;
			var price:Number = 0;
			var total:Number;
			var tax:Number;
			
			if(tF_Price.text == "")
			{
				price = -1;
			}
			else
			{
				price = Number(tF_Price.text);
				if ( price < 0 )
				{
					price = 0;
				}
			}
			num = Number(tF_Number.text);
			
			if(price > MaxPrice)
			{
				price = MaxPrice;
			}
			
			if ( num < 0 )
			{
				num = 0;
			}
			else if ( num >  MaxCount )
			{
				num = MaxCount;
			}
			tF_Number.text = String(num);
			
			if(price == -1)
			{
				total = 0;
				tF_Price.text = "";
			}
			else
			{
				total = price * num;
				tF_Price.text = String(price);
			}
			//tf_totalPrice.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
			//tf_totalPrice.wordWrap 	= 			true;
			//tf_totalPrice.height 	= 			tf_totalPrice.textHeight;
			tf_totalPrice.htmlText 	= 	formatMoneyNumberStr(total);
			tf_tax_money.htmlText 	= 	formatMoneyNumberStr(Math.ceil(total * TaxRate * 0.01));
			
			CheckButtonStatus();

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

		function OnInputChanged()
		{
			TotalPrice();
		}
	}
}