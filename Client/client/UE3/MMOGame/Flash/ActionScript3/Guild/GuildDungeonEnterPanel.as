//
// 家族副本开始
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
	import scaleform.clik.controls.DropdownMenu;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.Common.CustomScrollBar;
	import UI_GuildTerritoryWidget.AS3.AwardDec;
	import scaleform.clik.controls.ScrollingView;

	public class GuildDungeonEnterPanel extends MyPanel
	{
		public var guild_dungeon_enter_bt_mc:Button;
		public var guild_dungeon_data:Object;
		public var content_mc:AwardDec;
		public var _scrollingView:ScrollingView;
		public var bar:CustomScrollBar;
		
		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			guild_dungeon_enter_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickEnter);
		}
		
		private function onBtClickEnter(evt:MouseEvent):void
		{
			ExternalInterface.call("ASEnterDungeon", guild_dungeon_data.guild_dun_id);
		}
		
		public function UCUpdateGuildDungeonData(data:Object):void
		{
			guild_dungeon_data = data;
			if (guild_dungeon_data != null)
			{
				content_mc.UpdateGuildDungeonData(guild_dungeon_data);
			}
		}
		
		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
	}
}


























