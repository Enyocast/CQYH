package UI_PVP_Bonus.AS3
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Battle.BattleFreeSelect;
	import ActionScript3.Slot.MySlot;
	import ActionScript3.Slot.ItemSlotData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	
	public class BattleRewardBoard extends UIComponent
	{
		private static const NUMBER_OF_SLOT_INSTANCE:int = 3;
		private static const NUMBER_OF_REWARD_RANK:int = 4;
		
		public var close_btn:Button;
		public var txt_rank_0:TextField;
		public var txt_rank_1:TextField;
		public var txt_rank_2:TextField;
		public var txt_rank_3:TextField;
		public var txt_reward_number_0:TextField;
		public var txt_reward_number_1:TextField;
		public var txt_reward_number_2:TextField;
		public var txt_reward_number_3:TextField;
		
		public var battle_result_mc:BattleResultAll;
		public var txt_no_result:TextField;
		public var txt_battle_info_0:TextField;
		public var txt_battle_info_1:TextField;
		public var txt_battle_info_2:TextField;
		public var txt_battle_info_3:TextField;
		
		public var reward_slot_0:MySlot;
		public var reward_slot_1:MySlot;
		public var reward_slot_2:MySlot;
		public var txt_number_of_reward_coins:TextField;
		
		public function BattleRewardBoard()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			close_btn.addEventListener(MouseEvent.CLICK, onClosePanel);
			validChildrenInstance();
		}
		
		protected function validChildrenInstance():void
		{
			txt_no_result = battle_result_mc.getChildByName('txt_no_result') as TextField;
			txt_battle_info_0 = battle_result_mc.getChildByName('txt_battle_info_0') as TextField;
			txt_battle_info_1 = battle_result_mc.getChildByName('txt_battle_info_1') as TextField;
			txt_battle_info_2 = battle_result_mc.getChildByName('txt_battle_info_2') as TextField;
			txt_battle_info_3 = battle_result_mc.getChildByName('txt_battle_info_3') as TextField;
			
			txt_number_of_reward_coins = battle_result_mc.getChildByName('txt_number_of_reward_coins') as TextField;
			
			reward_slot_0 = battle_result_mc.getChildByName('reward_slot_0') as MySlot;
			reward_slot_1 = battle_result_mc.getChildByName('reward_slot_1') as MySlot;
			reward_slot_2 = battle_result_mc.getChildByName('reward_slot_2') as MySlot;
			
			//
			for(var i:int = 0; i < NUMBER_OF_SLOT_INSTANCE; i++)
			{
				var rewardItemSlot:MySlot = (this['reward_slot_' + i] as MySlot);
				if( rewardItemSlot != null )
				{
					rewardItemSlot.CurrentSlotRenderClass = "NormalItemSlotRender";
					var curSlotData:ItemSlotData = rewardItemSlot.SlotData as ItemSlotData;
					if( curSlotData == null )
					{
						rewardItemSlot.SetDataObj( new ItemSlotData );
					}
				}
			}
		}
		
		public function updateRewardsRankInfo(rankData:Array):void
		{
			if(rankData != null && rankData.length > 0){
				for(var i:int = 0; i < rankData.length; i++)
				{
					if(i < NUMBER_OF_REWARD_RANK)
					{
						(this['txt_reward_number_' + i] as TextField).htmlText = rankData[i];
					}
				}
			}
		}
		
		public function updateBattleResult($data:Object):void
		{
			var resultData:BattleResultData = $data as BattleResultData;
			if(resultData != null){
				var battleState:int = resultData.battleState;
				battle_result_mc.gotoAndStop('result_' + battleState);
				validChildrenInstance();
				//未参赛
				if(battleState == 0){
					if(txt_no_result != null){
						txt_no_result.text = resultData.battleInfo;
					}
				}else{
					if(txt_battle_info_0 && txt_battle_info_1 && txt_battle_info_2){
						txt_battle_info_0.text = resultData.topStreak;
						txt_battle_info_1.text = resultData.myStreak;
						txt_battle_info_2.text = resultData.rewardInfo;
					}
					var hasRewardData:Boolean = false;
					//有奖励
					var curOperateSlot:MySlot;
					if( resultData.battleReward ){
						var len:int = resultData.battleReward.length;
						var itemSlotIdx:int = 0;
						
						txt_number_of_reward_coins = battle_result_mc.getChildByName('txt_number_of_reward_coins') as TextField;
						if( txt_number_of_reward_coins != null )
						{
							txt_number_of_reward_coins.visible = false;
						}
						
						for(var i:int = 0; i < len; i++)
						{
							var rewardData:BattleRewardData = resultData.battleReward[i] as BattleRewardData;
							if( rewardData == null ){
								continue;
							}
							
							hasRewardData = true;
							
							//ExternalInterface.call('ASTrace', "Get Arena Award - "+ rewardData.itemID +","+rewardData.iconName );
							
							if( rewardData.itemID < 10 ){
								//是钱
								if(txt_number_of_reward_coins != null){
									txt_number_of_reward_coins.visible = true;
									txt_number_of_reward_coins.htmlText = rewardData.iconName;
								}
							}
							else{
								//是物品
								if(itemSlotIdx < NUMBER_OF_SLOT_INSTANCE){
									curOperateSlot = (this['reward_slot_' + itemSlotIdx] as MySlot);
									if( curOperateSlot )
									{
										curOperateSlot.visible = true;
									}
									SetRewardItem( curOperateSlot, rewardData.itemID, rewardData.iconName, rewardData.itemQuility );
									
									++itemSlotIdx;
								}
							}
						}
						
						//
						for( i = itemSlotIdx; i < NUMBER_OF_SLOT_INSTANCE; i++ )
						{
							curOperateSlot = (this['reward_slot_' + i] as MySlot);
							if( curOperateSlot )
							{
								curOperateSlot.visible = false;
							}
						}
					}
					
					//无奖励
					if( txt_battle_info_3 != null ){
						if(!hasRewardData){
							txt_battle_info_3.text = "无";
							txt_battle_info_3.visible = true;
						}else{
							txt_battle_info_3.visible = false;
						}
					}
				}
			}
		}
		
		protected function onClosePanel(event:MouseEvent):void
		{
			ExternalInterface.call("onCloseBattleResultPanel");
			//test
			(parent as MainPanel).UCSetBattleInfoBoardVisible(false);
		}
		
		public function SetRewardItem(slotItem:MySlot, inItemID:int, iconName:String, quilityColor:int ):void
		{
			if( slotItem == null )
			{
				return;
			}
			
			var curSlotData:ItemSlotData = slotItem.SlotData as ItemSlotData;
			if( curSlotData == null )
			{
				ExternalInterface.call("ASTrace","==============WeaponSkillPanel SetSkillItem slotItem.SlotData is NULL");
				return;
			}
			curSlotData.itemColor=quilityColor;
			slotItem.CanDrag=false;
			curSlotData.HaveData=true;
			curSlotData.iconName="img://" + iconName;
			curSlotData.itemTemplateID=inItemID;
			//SlotData.slotType=slotItem.SlotType;//主意S大小写（坑爹的）
			//SlotData.EquipID=slotItem.EquipID;
			//slotItem.SetDataObj(curSlotData);
			slotItem.UpdateData();
		}
		
		public function InitRewardItemSlot( idx:int, slotType:int, inPanelIdx:int ):void
		{
			var rewardItemSlot:MySlot = (this['reward_slot_' + idx] as MySlot);
			if( rewardItemSlot != null )
			{
				var curSlotData:ItemSlotData = rewardItemSlot.SlotData as ItemSlotData;
				if( curSlotData != null )
				{
					curSlotData.slotType = slotType;
					curSlotData.EquipID = inPanelIdx;
					curSlotData.containerID = -1;
					curSlotData.slotID = -1;
				}
			}
		}
		
		//
	}
}