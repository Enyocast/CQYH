package UI_Journey.AS3
{
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.gfx.TextEventEx;
	
	public class JourneyTraceAchievementReward extends UIComponent
	{
		public var achievement_name_tf:TextField;
		public var achievement_reward_desc_tf:TextField;
		public var achievement_reward_gain_button:Button;
		
		private var _achievement_reward_data:Object;
		
		public function JourneyTraceAchievementReward()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			achievement_name_tf.mouseEnabled = false;
			
			achievement_name_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			achievement_name_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			achievement_name_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			achievement_name_tf.styleSheet = new StyleSheet  ;
			achievement_name_tf.autoSize = flash.text.TextFieldAutoSize.NONE;
			achievement_name_tf.wordWrap = false;
			
			achievement_reward_gain_button.addEventListener(ButtonEvent.CLICK, onGainAchievementReward);
		}
		
		public function updateAchievementRewardData(data:Object):void
		{
			if(data == null)
			{
				return;
			}
			_achievement_reward_data = data;
			achievement_name_tf.htmlText = _achievement_reward_data.achievement_name;
			achievement_reward_desc_tf.text = _achievement_reward_data.achievement_reward_desc;
			achievement_reward_gain_button.enabled = true;
		}
		
		private function onGainAchievementReward(evt:ButtonEvent):void
		{
			if (_achievement_reward_data != null)
			{
				achievement_reward_gain_button.enabled = false;
				ExternalInterface.call("ASObtainAchievementReward", _achievement_reward_data.achievement_id);
			}
		}
		
		private function onLinkCallBack(e:TextEvent)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			
			ExternalInterface.call( "ASTrace", "ASLinkCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}
		
		
		private function onLinkOverCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			
			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}
		
		private function onLinkOutCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			
			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}
	}
}