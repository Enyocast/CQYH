package UI_GoldStore.AS
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;

	public class GoldStoreListItem_OrderList extends GoldStoreListItem_RecordList
	{
		public var txt_deal_state:TextField;
		public var time_txt_mc:TextField;
		
		private const HOUR:int = 3600;
		private const MINUTE:int = 60;
		private const MINUTE_FLAG:int = 59;
		private const RED:uint = 0xFF0000;
		private const WHITE:uint = 0xFFFFFF;
		
		private static const ORDER_STATE_STRING:Array = ["无效", "未成交", "主动撤单", "系统撤单", "成交"];
		private static const ORDER_STATE_VALID:int = 1;
		private static const ORDER_STATE_STRING_PARTIAL:String = "部分成交";
		
		public function GoldStoreListItem_OrderList()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			this.addEventListener(MouseEvent.ROLL_OVER, onShowOrderItemTips);
			this.addEventListener(MouseEvent.ROLL_OUT, onHideOrderItemTips);
		}
		
		private function onShowOrderItemTips(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_OrderItem", this);
		}
		
		private function onHideOrderItemTips(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_OrderItem");
		}
		
		override public function setData(data:Object):void
		{
			super.setData(data);
			var itemData:GoldStoreItemData = data as GoldStoreItemData;
			if(itemData != null)
			{
				if(itemData.orderState >= 0 && itemData.orderState < ORDER_STATE_STRING.length)
				{
					if(itemData.orderState == ORDER_STATE_VALID && (itemData.CurCount < itemData.Count))
					{
						txt_deal_state.text = ORDER_STATE_STRING_PARTIAL;
						txt_num_of_sell.text = itemData.CurCount.toString() + GoldStoreUltils.MONEY_UNIT;//override GoldStoreListItem_RecordList
					}
					else
					{
						txt_deal_state.text = ORDER_STATE_STRING[itemData.orderState];
					}
				}
				else
				{
					txt_deal_state.text = ORDER_STATE_STRING[0];
				}
				formatLeftTimeString(itemData.times);
				this.itemid = itemData.GoldStoreID;
			}
		}
		
		private function formatLeftTimeString(timeLeft:int):void
		{
			var minutes:int = Math.floor(timeLeft/MINUTE);
			
			if(minutes <= 0)
			{
				SetTimeLeft("-",RED);
			}
			else if(minutes > MINUTE_FLAG)
			{
				SetHour(timeLeft);
			}
			else if (minutes <= MINUTE_FLAG)
			{
				SetMinute(timeLeft);
			}
			
		}
		
		private function SetHour(timeLeft:int):void
		{
			var hour:int = (timeLeft/HOUR);
			var val:String = hour.toString()+"小时";
			SetTimeLeft(val,WHITE);
		}
		
		private function SetMinute(timeLeft:int):void
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
		
		private function CheckMinute(minute:int):Boolean
		{
			if(minute > MINUTE_FLAG)
			{
				return false;
			}
			return true;
		}
		
		private function SetTimeLeft(val:String,color:uint):void
		{
			time_txt_mc.text = val;
			time_txt_mc.textColor =  color;
		}
			
	}
}