package UI_DailySignIn.AS3
{
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.ItemGrid;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import UI_TradeP2P.TradeP2PAS3.HtmlButton;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;
	
	public class DailySignInPanel extends MyPanel
	{
		public var txt_sign_in_info:TextField;
		public var txt_require:TextField;
		public var item_grid_mc:ItemGrid;
		public var btn_signIn:Button;
		
		private static const NUMBER_OF_SIGN_IN_REWARD_ITEM:int = 28;
		private var _slotType:int;
		private var _curDayIdx:int;//1-28
		
		public function DailySignInPanel()
		{
			super();
		}
		
		override protected function configUI():void
		{
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			btn_signIn.addEventListener(ButtonEvent.CLICK, onGetSignInReward);
			SetWindowTitle("每日签到");
			var initData:Array = [];
			initData.length = NUMBER_OF_SIGN_IN_REWARD_ITEM;
			UCSetRewardDatas(initData);
		//	localTest(11);
		}
		
		private function localTest(dayIdx:int):void
		{
			UCSetCurSignInDay(dayIdx);
			UCSetSignInRequires("达到7级的玩家每天可以领取签到奖励");
			UCSetCurrentSignedIn("本月累计签到: " + (dayIdx - 1) + "天");
			UCSetRewardDatas(getTestRewardData());
		}
		
		private function onGetSignInReward(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASTryGetSignReward");
		//	localTest(12);
		}
		
		public function UCSetRewardDatas(data:Array):void
		{
			if(data && data.length > 0)
			{
				var dlen:int = data.length;
				var itemData:DailySignInRewardItemData;
				for(var i:int = 0; i < dlen; i++)
				{
					itemData = data[i] as DailySignInRewardItemData;
					if(itemData != null)
					{
						itemData.SlotType = _slotType;
						if(i + 1 == _curDayIdx)
						{
							itemData.IsCurSignInDay = true;
						}
					}
				}
			}
			item_grid_mc.setData(data);
		}
		
		public function UCInitSignInRewardSlot(slotType:int):void
		{
			_slotType = slotType;
		}
		
		public function UCSetCurSignInDay(dayIdx:int):void
		{
			_curDayIdx = dayIdx;
		}
		
		public function UCSetSignInRequires(requires:String):void
		{
			txt_require.text = requires;
		}
		
		public function UCSetCurrentSignedIn(curSignedIn:String):void
		{
			txt_sign_in_info.text = curSignedIn;
		}
		
		//---------------------------------------//
		private function getTestRewardData():Array
		{
			var rewardData:Array = [];
			var rewardItemData:DailySignInRewardItemData;
			for(var i:int = 0; i < 28; i++)
			{
				rewardItemData = new DailySignInRewardItemData();
				rewardItemData.SignInIdx = i + 1;
				rewardItemData.ItemID = i + 1;
				rewardItemData.ItemNum = ( i + 1 )* 5;
				rewardItemData.IconName = "" + ( i % 9 ) + ".tga";
				rewardItemData.IsGotten = i < _curDayIdx - 1;
				rewardData.push(rewardItemData);
			}
			return rewardData;
		}
	}
}