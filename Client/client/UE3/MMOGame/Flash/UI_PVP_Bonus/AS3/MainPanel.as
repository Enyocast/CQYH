package UI_PVP_Bonus.AS3
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	
	import scaleform.clik.controls.Button;
	
	public class MainPanel extends MyPanel
	{
		private static const STATE_REGISTRATION:int = 0;
		private static const STATE_ENTRY:int 		= 1;
		private static const STATE_COMPETITIVE:int 	= 2;
		private static const STATE_AWARD:int 	 	= 3;
		
		public var txt_tips_top:TextField;
		public var txt_tips_bottom:TextField;
		public var txt_additional_tip_top:TextField;
		public var txt_name:TextField;
		public var txt_bet:TextField;
		public var txt_num_of_total_bonus:TextField;
		public var txt_num_of_total_cost:TextField;
		public var view_bonus_btn:Button;
		public var ticket_cost_mc:MovieClip;
		public var action_btn:Button;
		public var txt_num_of_bet:TextField;
		public var battle_reward_board:BattleRewardBoard;
		public var entry_rewards_view:EntryRewardsView;
		
		protected var _curState:int;
		public var isLocalTest:Boolean = false;
		
		public function MainPanel()
		{
			super();
		}
		
		override protected function configUI():void
		{
			// TODO Auto Generated method stub
			super.configUI();
			//tF_windowTitle = window_mc.getChildByName('tF_windowTitle') as TextField;
			txt_num_of_bet = ticket_cost_mc.getChildByName('txt_num_of_bet') as TextField;
			view_bonus_btn.addEventListener(MouseEvent.CLICK, onViewBonusButtonClick);
			action_btn.addEventListener(MouseEvent.CLICK, onActionButtonClick);
			//battle_reward_board.visible = false;
			
			ExternalInterface.call( "RegisterArenaEntrance", this );
			
			//------test-----------------//
			if(isLocalTest){
				testInterface();
			}
		}
		
		protected function testInterface():void
		{
			for( var i:int = 0; i < 4; ++i ){
				InitRewardViewItemSlot( i, 10, i );
			}
			
			InitResultRewardItemSlot( 0, 10, 11 );
			updateState(STATE_REGISTRATION);
		}
		
		protected function updateState(state:int):void
		{
			_curState = state;
			switch(state){
				case STATE_REGISTRATION:
					//UCSetTitleOfWindow('公平竞技场');
					UCSetTopTipsText("您的最高连胜：");
					UCSetTopTipAdditionalText("十八连胜");
					UCSetTotalBonusText("1,000万");
					UCSetTotalCostText('20万');
					UCSetPlayerNameText("测试玩家七个字");
					UCSetBottomTipsText("参赛报名需花费");
					UCSetTicketCostText('5,000');
					UCSetActionButton('报名参赛');
					//UCSetRewardRanksData([800,2250,3750,5000]);
					UCSetEntryRewardsRank(2,0.8);
					//data 3 int ,2 string
					var testDataArray:Array = new Array();
					var newRewardViewItemData:RewardItemData;
					for(var i:int = 0; i < 4; i++)
					{
						newRewardViewItemData = new RewardItemData();
						newRewardViewItemData.itemID = 100 + i;
						newRewardViewItemData.iconName = "0.TGA";
						newRewardViewItemData.description = "奖品"+i+","+"OO"+","+"XX";
						newRewardViewItemData.rewardMnyRequire = (i+1)*10000+"万";
						testDataArray.push( newRewardViewItemData );
					}
					UCSetRewardItemListData(testDataArray);
					
					UCSetBattleRewardsRankInfo(['1025万','125万','25万','5万']);
					UCSetBattleResult(getTestResult(0));
					break;
				case STATE_ENTRY:
					UCSetBottomTipsText("报名已成功");
					UCSetTicketCostText('', false);
					UCSetActionButton('取消参赛');
					UCSetBattleResult(getTestResult(2));
					UCSetEntryRewardsRank(1,0.3);
					
					break;
				case STATE_COMPETITIVE:
					break;
				case STATE_AWARD:
					break;
			}
		}
		
		protected function getTestResult(state:int):BattleResultData
		{
			var result:BattleResultData = new BattleResultData();
			result.battleState = state;
			var newRewardData:BattleRewardData;
			switch(state){
				case 0:
					result.battleInfo = "比赛结果尚未产生";
					break;
				case 1:
					result.topStreak = '20';
					result.myStreak = "未参赛";
					result.rewardInfo = "无";
					break;
				case 2:
					result.topStreak = '20';
					result.myStreak = "12";
					result.rewardInfo = "未获奖";
					if( result.battleReward == null ){
						result.battleReward = new Array();
					}
					trace("================", result.battleReward);
					for(var i:int = 0; i < 1; i++)
					{
						newRewardData = new BattleRewardData();
						newRewardData.itemID = 100 + i;
						newRewardData.iconName = "0.TGA";
						newRewardData.itemNum = 1+i;
						newRewardData.itemQuility = 1;
						result.battleReward.push( newRewardData );
					}
					break;
				case 3:
					result.topStreak = '20';
					result.myStreak = "19";
					result.rewardInfo = "一等奖";
					if( result.battleReward == null ){
						result.battleReward = new Array();
					}
					
					var newRewardMoneyData:BattleRewardData = new BattleRewardData();
					newRewardMoneyData.itemID = 0;
					newRewardMoneyData.iconName = "3333";
					result.battleReward.push( newRewardMoneyData );
					
					for(var j:int = 0; j < 3; j++)
					{
						newRewardData = new BattleRewardData();
						newRewardData.itemID = 100 + j;
						newRewardData.iconName = "1.tga";
						newRewardData.itemNum = 1+j;
						newRewardData.itemQuility = 1;
						result.battleReward.push( newRewardData );
					}
					break;
			}
			return result;
		}
		
		protected function onViewBonusButtonClick(event:MouseEvent):void
		{
			var isToShow:Boolean = !battle_reward_board.visible;
			ExternalInterface.call('ASToggleShowBonusPanel', isToShow );
			UCSetBattleInfoBoardVisible( isToShow );
		}
		
		protected function onActionButtonClick(event:MouseEvent):void
		{
			//todo  if need call different function when button state changed?
			ExternalInterface.call('ASOnActionButtonClick');
			if(isLocalTest){
				switch(_curState){
					case STATE_REGISTRATION:
						updateState(STATE_ENTRY);
						break;
					case STATE_ENTRY:
						UCSetBattleResult(getTestResult(3));
						break;
					case STATE_COMPETITIVE:
						break;
					case STATE_AWARD:
						break;
				}
				//show battle result panel 
				//UCSetBattleInfoBoardVisible(true);
			}
		}
		
		//===================================================================================================================
		public function UCSetTopTipsText(info:String):void
		{
			txt_tips_top.htmlText = info;
		}
		
		//===================================================================================================================
		public function UCSetTopTipAdditionalText(info:String, visible:Boolean = true):void
		{
			txt_additional_tip_top.htmlText = info;
			txt_additional_tip_top.visible = visible;
		}
		
		//===================================================================================================================
		public function UCSetTotalBonusText(totalBonusStr:String):void
		{
			txt_num_of_total_bonus.htmlText = totalBonusStr;
		}
		
		//===================================================================================================================
		public function UCSetTotalCostText(totalCostStr:String):void
		{
			txt_num_of_total_cost.htmlText = totalCostStr;
		}
		
		//===================================================================================================================
		public function UCSetPlayerNameText(name:String):void
		{
			txt_name.text = name;
		}
		
		//===================================================================================================================
		public function UCSetRewardItemListData(listData:Array):void
		{
			entry_rewards_view.updateRewardItemListData(listData);
		}
		
		//===================================================================================================================
		public function UCSetEntryRewardsRank(curRank:int, progress:Number):void
		{
			entry_rewards_view.updateRewardsRank(curRank, progress);
		}
		
		//Battle info board
		//===================================================================================================================
		public function UCSetBattleInfoBoardVisible(visible:Boolean):void
		{
			battle_reward_board.visible = visible;
		}
		
		//===================================================================================================================
		public function UCSetBattleRewardsRankInfo(rankData:Array):void
		{
			battle_reward_board.updateRewardsRankInfo(rankData);
		}
		
		//===================================================================================================================
		public function UCSetBattleResult(resultData:Object):void
		{
			battle_reward_board.updateBattleResult(resultData);
		}
		
		//===================================================================================================================
		public function UCSetBottomTipsText(info:String):void
		{
			txt_tips_bottom.htmlText = info;
		}
		
		//===================================================================================================================
		public function UCSetTicketCostText(costStr:String, $visible:Boolean = true):void
		{
			txt_num_of_bet.htmlText = costStr;
			ticket_cost_mc.visible = $visible;
		}
		
		//===================================================================================================================
		public function UCSetActionButton(lableStr:String, $visible:Boolean = true):void
		{
			action_btn.label = lableStr;
			action_btn.visible = $visible;
		}
		
		//===================================================================================================================
		public function InitRewardViewItemSlot( idx:int, slotType:int, inPanelIdx:int ):void
		{
			entry_rewards_view.InitRewardItemSlot(idx, slotType, inPanelIdx);
		}
		//===================================================================================================================
		public function InitResultRewardItemSlot( idx:int, slotType:int, inPanelIdx:int ):void
		{
			battle_reward_board.InitRewardItemSlot(idx, slotType, inPanelIdx);
		}
	}
}