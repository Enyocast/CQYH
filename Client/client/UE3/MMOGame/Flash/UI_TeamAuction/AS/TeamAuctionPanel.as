package UI_TeamAuction.AS
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import ActionScript3.Slot.MySlot;

	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;

	import UI_TeamAuction.AS.AuctionListData;
	import ActionScript3.Slot.MySlotData;
	import scaleform.clik.controls.TextInput;
	import flash.text.TextField;

	public class TeamAuctionPanel extends MyPanel
	{
		public var slot_mc:MySlot;
		public var num_tf:TextField;
		public var name_tf:TextField;
		public var itemName_tf:TextField;
		public var itemIndex_tf:TextField;
		public var price_tf:TextField;
		public var price_acution_tf:TextInput;
		public var progressBar_mc:ProgressBar;
		public var btn_acution:Button;
		public var btn_giveup:Button;
		public var btn_acutionList:Button;
		public var bidMoneyUp_btn:Button;
		public var bidMoneyDown_btn:Button;

		override protected function configUI():void
		{
			super.configUI();
			
			SetWindowTitle("组队拍卖");
			
			price_acution_tf.textField.restrict="0-9";
			btn_acution.addEventListener(MouseEvent.CLICK , clickBid , false , 0 , true );
			btn_giveup.addEventListener(MouseEvent.CLICK , clickGiveup , false , 0 , true );
			btn_acutionList.addEventListener(MouseEvent.CLICK , clickItemList , false , 0 , true );
			bidMoneyUp_btn.addEventListener(MouseEvent.CLICK , clickBidMoneyUp , false , 0 , true );
			bidMoneyDown_btn.addEventListener(MouseEvent.CLICK , clickBidMoneyDown , false , 0 , true );			
		}
		
		private function clickBid(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamAuctionBid" , int( price_acution_tf.text ) );
		}
		
		private function clickGiveup(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamAuctionGiveup" );
		}
		
		private function clickItemList(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamAuctionClickItemList" );
		}
		
		private function clickBidMoneyUp(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamAuctionClickBidMoneyUp" , int( price_acution_tf.text ) );
		}
		
		private function clickBidMoneyDown(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamAuctionClickBidMoneyDown" , int( price_acution_tf.text ) );
		}
		
		public function SetInputPrice( price:int):void
		{
			price_acution_tf.text = String(price);
		}

		public function updateData(data:Object):void
		{
			slot_mc.SetDataObj(data.slotData);
			num_tf.htmlText = data.numAcution;
			itemName_tf.htmlText = data.itemName;
			itemIndex_tf.text = data.itemIndex;			
			updateDataFast(data);
		}

		public function updateDataFast(data:Object):void
		{
			name_tf.htmlText = data.nameAcution;

			price_tf.htmlText = data.maxPrice;
			
			progressBar_mc.setupProgress(data.curTime ,data.tolTime);

		}
		
		//待拍数
		public function updateItemNum( num:String ):void
		{
			btn_acutionList.label = num;
		}
/*
		public function test():void
		{
			var dat = new AuctionContralData  ;
			dat.itemName = "印度神油";
			dat.itemIndex = 1;
			dat.itemListNum = 9;

			dat.numAcution = 4;
			dat.nameAcution = "李大牛";
			dat.maxPrice = 100000;
			

			dat.curTime = 20;
			dat.tolTime = 20;
			
			var slotData:MySlotData = new MySlotData;
			slotData.HaveData = true;
			slotData.iconName = "img://icon.png";
			//slotData.quantity = 3;
			//= { itemColor:4 , itemTemplateID:11 ,   EquipID:1 , slotIndex:0 , slotType:1};
			
			dat.slotData = slotData;

			updateData(dat);
			
		}*/

	}
}