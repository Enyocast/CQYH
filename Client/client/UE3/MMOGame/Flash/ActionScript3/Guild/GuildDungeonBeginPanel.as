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
	import UI_GuildTerritoryWidget.AS3.BeginDec;
	import scaleform.clik.controls.ScrollingView;
	import ActionScript3.Common.CustomScrollBar;

	public class GuildDungeonBeginPanel extends MyPanel
	{
		public var guild_dungeon_open_bt_mc:Button;
		public var content_mc:BeginDec;
		public var _scrollingView:ScrollingView;
		public var bar:CustomScrollBar;
		
		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			content_mc.height=546;
			_scrollingView.displayMc=content_mc;
			guild_dungeon_open_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickOpen);
		}
		
		private function onBtClickOpen(evt:MouseEvent):void
		{
			if (content_mc.guild_dungeon_data && content_mc.guild_member_data)
			{
				var dungeon_index:int = content_mc.guild_dungeon_list_mc.selectedIndex;
				var member_index:int = content_mc.guild_dungeon_member_list_mc.selectedIndex;
				var member_id:int = 0;
				if (content_mc.guild_dungeon_member_list_mc.enabled)
				{
					member_id = content_mc.guild_member_data[member_index].guild_mem_id;
				}
				ExternalInterface.call("ASOpenDungeon" , content_mc.guild_dungeon_data[dungeon_index].guild_dun_id, member_id);
			}
		}
		
		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
		
		public function UCUpdateGuildDungeonList(data:Array)
		{
			if (data)
			{
				content_mc.UpdateGuildDungeonList(data);
			}
		}
		
		public function UCUpdateGuildMemberList(data:Array)
		{
			if (data)
			{
				content_mc.UpdateGuildMemberList(data);
			}
		}
	}
}


























