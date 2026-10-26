//
// 家族资金捐献
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import scaleform.clik.controls.TextInput;
	import flash.events.KeyboardEvent;
	import flash.events.Event;
	import scaleform.clik.managers.FocusHandler;

	public class GuildMoneyContributePanel extends BaseGuildAlert
	{
		public var guild_money_contribute_input_mc:TextInput;
		public var guild_money_contribute_intro_mc:TextField;
		public var guild_money_contribute_max:int;
		
		const c_guild_con_money = 258;
		
		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("资金捐献");
			guild_money_contribute_input_mc.textField.restrict="0-9";
			guild_money_contribute_input_mc.addEventListener(Event.CHANGE,changeHandler);
			guild_money_contribute_max = 4294967295;
			guild_money_contribute_intro_mc.text = "";
		}
		
		public function show():void
		{
			FocusHandler.getInstance().setFocus(guild_money_contribute_input_mc.textField);
		}
		override protected function onBtClickClose(evt:MouseEvent):void
		{
			guild_money_contribute_input_mc.text = "";
			super.onBtClickClose(evt);
		}
		
		override protected function onBtClickOk(evt:MouseEvent):void
		{
			var money:int = int(guild_money_contribute_input_mc.text);
			ExternalInterface.call("ASContribute", c_guild_con_money, money);
			onBtClickClose(null);
		}

		public function updateContributeInfo(money:int, inro:String):void
		{
			guild_money_contribute_max = money;
			guild_money_contribute_intro_mc.text = inro;
		}
		
		protected function changeHandler(evt:Event):void 
		{ 
            var contribute:int = int(guild_money_contribute_input_mc.text);
			if (contribute < 0)
			{
				guild_money_contribute_input_mc.text = "0";
			}
			if (contribute > guild_money_contribute_max)
			{
				guild_money_contribute_input_mc.text = guild_money_contribute_max.toString();
			}
        }
	}
}


























