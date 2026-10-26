package UI_StallWidget.AS3
{
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.CustomPage;
	import ActionScript3.Common.Utils.ConfigConstants;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextArea;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.gfx.Extensions;


	public class StallBuyWidget extends MyPanel
	{
		private static const NUMBER_OF_SLOTS:int = 	10;
		
		public var txt_stall_name:TextField;
		
		public var slot_mc0:MyItemSlot;
		public var slot_mc1:MyItemSlot;
		public var slot_mc2:MyItemSlot;
		public var slot_mc3:MyItemSlot;
		public var slot_mc4:MyItemSlot;
		public var slot_mc5:MyItemSlot;
		public var slot_mc6:MyItemSlot;
		public var slot_mc7:MyItemSlot;
		public var slot_mc8:MyItemSlot;
		public var slot_mc9:MyItemSlot;
		
		//public var PageCtrl:CustomPage;
		
		public var btn_call_owner:Button;
		public var btn_follow:Button;
		public var btn_buy:Button;
		
		private var _ownerId:int;
		private var _bFollow:Boolean = true;
		
		private var _selectedSolt:MyItemSlot;

		override protected function configUI():void
		{ 
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			//ExternalInterface.call( "RegisterStallBuy", this);	
			btn_call_owner.addEventListener(ButtonEvent.CLICK, onCallOwner);
			btn_follow.addEventListener(ButtonEvent.CLICK, onFollowOwner);
			btn_buy.addEventListener(ButtonEvent.CLICK, onBuyItem);
			
			//slot selected state
			var slot:MyItemSlot;
			for(var i:int = 0; i <　NUMBER_OF_SLOTS; i++)
			{
				slot = (this['slot_mc' + i] as MyItemSlot);
				if(slot != null)
				{
					slot.addEventListener(ButtonEvent.CLICK, onSelectedSlot);
					slot.DisableDrag = true;
				}
			}
			_selectedSolt = null;
		}
		
		private function onSelectedSlot(evt:ButtonEvent):void
		{
			if(_selectedSolt != null)
			{
				if(_selectedSolt != evt.currentTarget)
				{
					_selectedSolt.selected = false;
					_selectedSolt = evt.currentTarget as MyItemSlot;
				}
			}
			else
			{
				_selectedSolt = evt.currentTarget as MyItemSlot;
			}
			
			if(_selectedSolt != null)
			{
				_selectedSolt.selected = true;
			}
		}

		public function UpdateStallBuyWidget( tData:Object )
		{
			SetWindowTitle(tData.WidgetName);
		}
		
		public function UCSetOwnerData(ownerName:String, ownerId:int):void
		{
			txt_stall_name.text = ownerName;
			_ownerId = ownerId;
		}
		
		public function UCSetButtonState(bFollow:Boolean):void
		{
			_bFollow = bFollow;
			btn_follow.label = _bFollow ? "标记":"取消标记";
		}
		
		public function UCCheckSettingItem(slotIndex:int):void
		{
			if(slotIndex >=0 && slotIndex < NUMBER_OF_SLOTS)
			{
				(this['slot_mc' + slotIndex] as StallSettingItem).checkGoldTextBoundary();
			}
		}
		
		private function onCallOwner(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASOnCallOwner", _ownerId);
		}
		
		private function onFollowOwner(evt:ButtonEvent):void
		{
			if(_bFollow)
			{
				ExternalInterface.call("ASOnFollowOwner", _ownerId);
			}
			else
			{
				ExternalInterface.call("ASCancelFollowOwner", _ownerId);
			}
		}
		
		private function onBuyItem(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASOnBuyItem");
		}

	}

}