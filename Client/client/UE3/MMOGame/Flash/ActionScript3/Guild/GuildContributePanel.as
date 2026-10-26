//
// 家族申请（结盟/敌对）
//
package ActionScript3.Guild
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;

	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import scaleform.clik.controls.TextInput;

	public class GuildContributePanel extends MyPanel
	{
		public var guild_con_type_cb_mc:DropdownMenu;
		public var guild_con_count_mc:TextInput;

		public var guild_con_ok_mc:Button;
		public var guild_con_cancel_mc:Button;
		
		const c_guild_con_wood = 261;
		const c_guild_con_herb = 262;
		const c_guild_con_crystal = 263;
		const c_guild_con_silver = 264;

		override protected function configUI():void
		{
			super.configUI();
			guild_con_type_cb_mc.dataProvider = new DataProvider();
			guild_con_type_cb_mc.selectedIndex = 0;
			btn_close.RemoveAddedEventListener();
			btn_close.addEventListener(MouseEvent.CLICK,onBtClickClose);
			guild_con_ok_mc.addEventListener(MouseEvent.CLICK,onBtClickOk);
			guild_con_cancel_mc.addEventListener(MouseEvent.CLICK,onBtClickClose);
			guild_con_count_mc.text = "0";
			guild_con_count_mc.textField.restrict="0-9";
		}
		
		private function onBtClickClose(evt:MouseEvent):void
		{
			guild_con_count_mc.text = "0";
			guild_con_type_cb_mc.selectedIndex = c_guild_con_wood;
			this.visible = false;
		}

		private function onBtClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASContribute", guild_con_type_cb_mc.selectedIndex, int(guild_con_count_mc.text));
			onBtClickClose(null);
		}
		
		public function updateContributeType(data_list:Array):void
		{
			guild_con_type_cb_mc.dataList = data_list;
			guild_con_type_cb_mc.SplitData();
			guild_con_type_cb_mc.selectedIndex = 0;
		}
	}
}