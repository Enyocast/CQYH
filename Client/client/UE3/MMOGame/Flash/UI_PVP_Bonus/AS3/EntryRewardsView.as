package UI_PVP_Bonus.AS3 
{
	import flash.display.MovieClip;
	
	import scaleform.clik.core.UIComponent;
	
	public class EntryRewardsView extends UIComponent
	{
		private static const NUMBER_OF_TOTAL_REWARD_RANK:int = 4;
		
		public var progress_bar_mc:MovieClip;
		public var rewardItem_0:RewardItem;
		public var rewardItem_1:RewardItem;
		public var rewardItem_2:RewardItem;
		public var rewardItem_3:RewardItem;
		
		private var _rewardRank:int = 0;
		
		public function EntryRewardsView()
		{
			super();
		}
		
		override protected function configUI():void
		{
			// TODO Auto Generated method stub
			super.configUI();
		}
		
		public function updateRewardsRank(curRank:int, progress:Number):void
		{
			if(curRank == 0 && progress == 0){
				progress_bar_mc.gotoAndStop(1);
			}else{
				var targetFrame:int = Math.floor(1 + 100 /(NUMBER_OF_TOTAL_REWARD_RANK) * (curRank + progress));
				progress_bar_mc.gotoAndStop(targetFrame);
				if(curRank > 0){
					(this['rewardItem_' + (curRank - 1)] as RewardItem).selected = true;
				}
			}
			if(_rewardRank > 0 && curRank != _rewardRank){
				(this['rewardItem_' + (_rewardRank - 1)] as RewardItem).selected = false;
			}
			_rewardRank = curRank;
		}
		
		public function updateRewardItemListData(data:Array):void
		{
			var rewardItemInst:RewardItem;
			if(data != null && data.length > 0){
				for(var i:int = 0; i < data.length; i++)
				{
					if(i < NUMBER_OF_TOTAL_REWARD_RANK)
					{
						rewardItemInst = (this['rewardItem_' + i] as RewardItem);
						if( rewardItemInst == null )
						{
							continue;
						}
						rewardItemInst.updateItemData(data[i]);
					}
				}
			}
		}
		
		//
		public function InitRewardItemSlot( idx:int, slotType:int, inPanelIdx:int ):void
		{
			var rewardItemInst:RewardItem = (this['rewardItem_' + idx] as RewardItem);
			if( rewardItemInst == null )
			{
				return;
			}
			rewardItemInst.InitRewardItemSlot( slotType, inPanelIdx );
		}
		
	}
}