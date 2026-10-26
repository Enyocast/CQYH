package UI_TeamAuction.AS
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import ActionScript3.Slot.MySlot;

	public class AuctionListItem extends ListItemTreeRenderer
	{
		public var giveup_btn:Button;
		public var acution_tf:TextField;
		public var itemIndex_tf:TextField;
		public var itemName_tf:TextField;
		public var itemPrice_tf:TextField;
		public var state_tf:TextField;
		public var slot_mc:MySlot;
		public var itemIndex:int = -1;

		override protected function configUI():void
		{
			super.configUI();
			this.updateDataCallBack = updateData;
			giveup_btn.addEventListener(MouseEvent.CLICK, ClickGiveUp);
		}

		//放弃全部
		private function ClickGiveUp(e:MouseEvent):void 
		{
			ExternalInterface.call("ASTeamAuctionListGiveUp",itemIndex);
		}
		
		public function updateData(data:Object):void
		{
			if (data)
			{
				visible = true;

				itemPrice_tf.htmlText = data.itemPrice;
				
				itemName_tf.htmlText = data.itemName;
				state_tf.htmlText = data.state;
				itemIndex_tf.text =  ""+data.itemIndex;
				itemIndex		  =  data.itemId;
				giveup_btn.visible = data.giveup;
				//acution_tf.visible = data.acutionStateTextVisible;
				acution_tf.htmlText = data.acutionStateText;
				slot_mc.SetDataObj(data.slotData);
				
			}
			else
			{
				visible = false;
			}
		}

	}
}