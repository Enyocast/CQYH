package UI_GoldStore.AS
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	
	import ActionScript3.MoneyInput;
	import ActionScript3.Slot.MySlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.gfx.MouseEventEx;
	
	public class GoldStoreListItem_SellInfo extends GoldStoreListItemBase 
	{
		public var time_txt_mc:TextField;
		
		private const HOUR:int = 3600;
		private const MINUTE:int = 60;
		private const MINUTE_FLAG:int = 59;
		private const RED:uint = 0xFF0000;
		private const WHITE:uint = 0xFFFFFF;
		
		public function GoldStoreListItem_Buy()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			time_txt_mc.mouseEnabled=false;
		}
		
		override function updateData(dat:Object):void
		{	
			var itemData:GoldStoreItemData = dat as GoldStoreItemData;
			if(itemData != null)
			{
				visible = true;
				unitPrice_txt_mc.text = GoldStoreUltils.couponToGold(itemData.Coupon);
				txt_num_of_sell.text = itemData.Count.toString() + GoldStoreUltils.MONEY_UNIT;
			//	money_Count.setMoney(itemData.Count * money_Unit);
				FormatTime(itemData.times);
			}
			else
			{
				visible = false;
			}
		}
		
		public function FormatTime(timeLeft:int):void
		{
			var minutes:int = Math.floor(timeLeft/MINUTE);
			
			if(minutes > MINUTE_FLAG)
			{
				SetHour(timeLeft);
			}
			else if (minutes <= MINUTE_FLAG)
			{
				SetMinute(timeLeft);
			}
			
		}
		
		public function SetHour(timeLeft:int):void
		{
			var hour:int = (timeLeft/HOUR);
			var val:String = hour.toString()+"小时";
			SetTimeLeft(val,WHITE);
		}
		
		public function SetMinute(timeLeft:int):void
		{
			var minute:int = Math.ceil((timeLeft/MINUTE)%MINUTE);
			if(CheckMinute(minute))
			{
				var val:String = minute.toString()+"分钟"
				SetTimeLeft(val,RED);
			}
			else
			{
				SetHour(timeLeft);
			}
			
		}
		
		public function CheckMinute(minute:int):Boolean
		{
			if(minute > MINUTE_FLAG)
			{
				return false;
			}
			return true;
		}
		
		public function SetTimeLeft(val:String,color:uint):void
		{
			time_txt_mc.text = val;
			time_txt_mc.textColor =  color;
		}		
	}
	
}
