//
// 家族申请（结盟/敌对）
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.data.DataProvider;

	public class GuildForeignApplyPanel extends BaseGuildInput
	{
		public var guild_apply_name_cap_tf:TextField;
		public var guild_apply_time_cap_tf:TextField;
		public var guild_apply_money_cap_tf:TextField;

		public var guild_apply_time_mc:DropdownMenu;
		public var guild_apply_money_tf:TextField;

		public var guild_apply_type:int;
		public var guild_time_type:int;

		const c_guild_apply_ally = 1;
		const c_guild_apply_enemy = 2;

		override protected function configUI():void
		{
			super.configUI();
			guild_apply_time_mc.dataProvider = new DataProvider(["1天","3天","7天","30天"]);
			guild_apply_time_mc.addEventListener(Event.CHANGE,onChangeSelect);
			guild_apply_time_mc.selectedIndex = 0;
			guild_apply_money_tf.htmlText = "";
			show();
		}
		
		public function show():void
		{
			txt_name.textField.maxChars=12;
			updateTextFormat(true);
			txt_name.defaultText="(最多8个中文)";
		}
		
		public function setApplyType(type:int):void
		{
			guild_apply_type = type;
			if ((guild_apply_type == c_guild_apply_ally))
			{
				this.SetWindowTitle("申请结盟");
		        guild_apply_name_cap_tf.text = "结盟公会名称";
		        guild_apply_time_cap_tf.text = "结盟时间";
		        guild_apply_money_cap_tf.text = "结盟费用";
			}
			else
			{
				this.SetWindowTitle("申请敌对");
		        guild_apply_name_cap_tf.text = "敌对公会名称";
		        guild_apply_time_cap_tf.text = "敌对时间";
		        guild_apply_money_cap_tf.text = "敌对费用";
			}
			guild_apply_time_mc.selectedIndex = 0;
			guild_apply_money_tf.htmlText = "";
			ExternalInterface.call("ASForeignApplyDayType", guild_apply_type, guild_apply_time_mc.selectedIndex);
		}

		private function onChangeSelect(e:Event):void
		{
			ExternalInterface.call("ASForeignApplyDayType", guild_apply_type, guild_apply_time_mc.selectedIndex);
			/*
			switch (guild_apply_time_mc.selectedIndex)
			{
			case 0 :
				guild_apply_money_tf.text = "1000";
				break;
			case 1 :
				guild_apply_money_tf.text = "5000";
				break;
			case 2 :
				guild_apply_money_tf.text = "20000";
				break;
			case 3 :
				guild_apply_money_tf.text = "100000";
				break;
			}
			*/
		}

		override protected function onBtClickOk(evt:MouseEvent):void
		{
			if ((guild_apply_type == c_guild_apply_ally))
			{
				ExternalInterface.call("ASApplyAlly",txt_name.text,guild_apply_time_mc.selectedIndex);
			}
			else
			{
				ExternalInterface.call("ASApplyEnemy",txt_name.text,guild_apply_time_mc.selectedIndex);
			}

			onBtClickClose(null);
		}

		public function updateConsume(money:String):void
		{
			guild_apply_money_tf.htmlText = money;
		}
	}
}