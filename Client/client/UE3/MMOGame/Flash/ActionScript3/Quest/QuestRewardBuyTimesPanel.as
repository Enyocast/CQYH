package ActionScript3.Quest
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.gfx.Extensions;
	import ActionScript3.MyScrollBar;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.TextInput;

	public class QuestRewardBuyTimesPanel extends MyPanel
	{
		//public var MyWindowsFrame_mc:MovieClip;
		public var quest_reward_sub_times_mc:Button;
		public var quest_reward_add_times_mc:Button;
		public var quest_reward_times_mc:TextInput;
		public var quest_reward_buy_times_consume_mc:TextField;
		public var quest_reward_ok_mc:Button;
		public var quest_reward_cancel_mc:Button;
		
		public var quest_reward_left_times:int;
		public var quest_reward_cur_times:int;
		
		public function QuestRewardBuyTimesPanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			this.SetWindowTitle("购买可做任务");
			quest_reward_sub_times_mc.addEventListener(MouseEvent.CLICK, onBtClickSubTimes);
			quest_reward_add_times_mc.addEventListener(MouseEvent.CLICK, onBtClickAddTimes);
			quest_reward_ok_mc.addEventListener(MouseEvent.CLICK, onBtClickOk);
			quest_reward_cancel_mc.addEventListener(MouseEvent.CLICK, onBtClickCancel);
			btn_close.addEventListener(MouseEvent.CLICK, onBtClickClose);
			
			quest_reward_times_mc.addEventListener(KeyboardEvent.KEY_UP, onInputOver, false, 0, true);
			quest_reward_times_mc.text = "0";
			quest_reward_times_mc.textField.restrict = "0-9";
			quest_reward_left_times = 0;
			quest_reward_cur_times = 0;
			
			quest_reward_buy_times_consume_mc.text = "";
			quest_reward_buy_times_consume_mc.htmlText = "0";

		}
		
		public function onBtClickSubTimes()
		{
			if (quest_reward_cur_times > 0)
			{
				quest_reward_cur_times -= 1;
				quest_reward_times_mc.text = String(quest_reward_cur_times);
				ExternalInterface.call("ASUpdateRewardQuestBuyTimes", quest_reward_cur_times);
			}
		}
		
		public function onBtClickAddTimes()
		{
			if (quest_reward_cur_times < quest_reward_left_times)
			{
				quest_reward_cur_times += 1;
				quest_reward_times_mc.text = String(quest_reward_cur_times);
				ExternalInterface.call("ASUpdateRewardQuestBuyTimes", quest_reward_cur_times);
			}
		}
		
		public function onBtClickOk()
		{
			ExternalInterface.call("ASBuyTimes", quest_reward_cur_times);
			
			quest_reward_times_mc.text = "0";
			quest_reward_cur_times = 0;
			quest_reward_buy_times_consume_mc.text = "";
			quest_reward_buy_times_consume_mc.htmlText = "0";
			this.visible = false;
			ExternalInterface.call("ASOnPanelClose",PanelName);
		}
		
		public function onBtClickCancel()
		{
			quest_reward_times_mc.text = "0";
			quest_reward_cur_times = 0;
			quest_reward_buy_times_consume_mc.text = "";
			quest_reward_buy_times_consume_mc.htmlText = "0";
			this.visible = false;
			ExternalInterface.call("ASOnPanelClose",PanelName);
		}
		
		public function onBtClickClose()
		{
			quest_reward_times_mc.text = "0";
			quest_reward_cur_times = 0;
			quest_reward_buy_times_consume_mc.text = "";
			quest_reward_buy_times_consume_mc.htmlText = "0";
			this.visible = false;
			ExternalInterface.call("ASOnPanelClose",PanelName);
		}
		
		protected function onInputOver(event:KeyboardEvent):void 
		{            
            var control:TextInput = event.target.parent as TextInput;
			
			quest_reward_cur_times = int(quest_reward_times_mc.text);
			if (quest_reward_cur_times < 0)
			{
				quest_reward_cur_times = 0;
				control.text = String(0);
			}
			if (quest_reward_cur_times > quest_reward_left_times)
			{
				quest_reward_cur_times = quest_reward_left_times;
				control.text = String(quest_reward_left_times);
			}
				
			ExternalInterface.call("ASUpdateRewardQuestBuyTimes", quest_reward_cur_times);
        }
		
		public function UCUpdateRewardQuestBuyLeftTimes(leftTimes:int):void
		{
			quest_reward_left_times = leftTimes;
		}
		
		public function UCUpdateRewardQuestBuyTimesConsume(consume:String):void
		{
			quest_reward_buy_times_consume_mc.htmlText = consume;
		}
	}
}