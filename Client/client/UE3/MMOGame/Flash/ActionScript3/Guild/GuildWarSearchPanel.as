//
// 家族创建
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
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import scaleform.clik.controls.TextInput;
	
	import ActionScript3.MyPanel;

	public class GuildWarSearchPanel extends MyPanel
	{
		public var guild_war_search_mc:MovieClip;
		public var guild_war_searching_mc:MovieClip;
		public var guild_war_search_consume_mc:TextField;
		public var guild_war_search_count_mc:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
			guild_war_search_mc.addEventListener(MouseEvent.CLICK, onBtClickOk);
			
			guild_war_search_consume_mc.text = ""
			guild_war_search_count_mc.htmlText = "";
			guild_war_searching_mc.visible = false;
			guild_war_searching_mc.enabled = false;
		}
		
		public function updateGuildWarSearchInfo(data:Object)
		{
			guild_war_search_consume_mc.htmlText = String(data.guild_war_search_consume);
			guild_war_search_count_mc.htmlText = String(data.guild_war_search_count);
		}
		
		public function updateGuildWarSearchState(data:Object)
		{
			guild_war_search_mc.visible = !Boolean(data.guild_war_searching);
			guild_war_searching_mc.visible = Boolean(data.guild_war_searching);
		}
		
		public function onBtClickOk()
		{
			ExternalInterface.call("ASSearchGuild");
		}
	}
}


























