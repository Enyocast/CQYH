package  UI_PVP_Bonus.AS3
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Slot.ItemSlotData;
	import ActionScript3.Slot.MySlot;
	
	import UI_PVP_Bonus.AS3.RewardItemData;
	
	import scaleform.clik.core.UIComponent;
	
	public class RewardItem extends UIComponent
	{
		private const LABEL_NORMAL_STATE:String = "normal";
		private const LABEL_ON_STATE:String 	= "on";
			
		public var reward_item_info_mc:MovieClip;
		//children of reward_item_info_mc
		public var txt_num_of_coins:TextField;
		public var txt_other:TextField;
		public var reward_slot:MySlot;
		
		public function RewardItem()
		{
			super();
		}
		
		public function set selected(value:Boolean):void
		{
			if(value){
				this.gotoAndStop(LABEL_ON_STATE);
			}else{
				this.gotoAndStop(LABEL_NORMAL_STATE);
			}
			validChildrenInstance();
		}
		
		override protected function configUI():void
		{
			// TODO Auto Generated method stub
			super.configUI();
			validChildrenInstance();
		}
		
		protected function validChildrenInstance():void
		{
			reward_item_info_mc = this.getChildByName('reward_item_info_mc') as MovieClip;
			if(reward_item_info_mc != null){
				txt_num_of_coins = reward_item_info_mc.getChildByName('txt_num_of_coins') as TextField;
				txt_other 		 = reward_item_info_mc.getChildByName('txt_other') as TextField;
				reward_slot      = reward_item_info_mc.getChildByName('reward_slot') as MySlot;
			}
			
			//
			if( reward_slot != null )
			{
				//set defaultRender class
				reward_slot.CurrentSlotRenderClass = 'NormalItemSlotRender';
				var curSlotData:ItemSlotData = reward_slot.SlotData as ItemSlotData;
				if( curSlotData == null )
				{
					reward_slot.SetDataObj( new ItemSlotData );
				}
			}
		}
		
		public function updateItemData(data:Object):void
		{
			var rewardData:RewardItemData = data as RewardItemData;
			if( rewardData == null )
			{
				return;
			}
			
			txt_num_of_coins.htmlText = rewardData.rewardMnyRequire;
			
			txt_other.htmlText = rewardData.description;
			//
			SetRewardItemSlot( rewardData.itemID, rewardData.iconName, rewardData.itemQuility );
		}
		
		public function SetRewardItemSlot( inItemID:int, iconName:String, quilityColor:int ):void
		{
			if( reward_slot == null )
			{
				return;
			}
			
			var curSlotData:ItemSlotData = reward_slot.SlotData as ItemSlotData;
			if( curSlotData == null )
			{
				ExternalInterface.call("ASTrace","==============WeaponSkillPanel SetSkillItem slotItem.SlotData is NULL");
				return;
			}
			curSlotData.itemColor=quilityColor;
			reward_slot.CanDrag=false;
			curSlotData.HaveData=true;
			curSlotData.iconName="img://" + iconName;
			curSlotData.itemTemplateID=inItemID;
			//SlotData.slotType=slotItem.SlotType;//主意S大小写（坑爹的）
			//SlotData.EquipID=slotItem.EquipID;
			//slotItem.SetDataObj(curSlotData);
			reward_slot.UpdateData();
		}
		
		//
		public function InitRewardItemSlot( slotType:int, inPanelIdx:int ):void
		{
			if( reward_slot == null )
			{
				return;
			}
			
			var curSlotData:ItemSlotData = reward_slot.SlotData as ItemSlotData;
			if( curSlotData != null )
			{
				curSlotData.slotType = slotType;
				curSlotData.EquipID = inPanelIdx;
				curSlotData.containerID = -1;
				curSlotData.slotID = -1;
			}
		}
	}
}