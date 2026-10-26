//
// 家族副本结束
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

	public class GuildDungeonEndPanel extends MyPanel
	{
		public var guild_dungeon_boss_tf:TextField;
		
		public var guild_dungeon_award_0_mc:MovieClip;
		public var guild_dungeon_award_1_mc:MovieClip;
		public var guild_dungeon_award_2_mc:MovieClip;
		public var guild_dungeon_award_3_mc:MovieClip;
		public var guild_dungeon_award_4_mc:MovieClip;
		public var guild_dungeon_award_5_mc:MovieClip;
		public var guild_dungeon_award_6_mc:MovieClip;
		public var guild_dungeon_award_7_mc:MovieClip;
		public var guild_dungeon_award_8_mc:MovieClip;
		public var guild_dungeon_award_9_mc:MovieClip;
		
		public var guild_dungeon_close_mc:Button;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			
			guild_dungeon_close_mc.addEventListener(MouseEvent.CLICK,onBtClickExit);
			
			guild_dungeon_boss_tf.text = "";
		}
		
		private function onBtClickExit(evt:MouseEvent):void
		{
			ExternalInterface.call("ASLeaveGuildDungeon");
			ExternalInterface.call("ASOnPanelClose" , this.PanelName);
		}
		
		public function onBtClickClose()
		{
			ExternalInterface.call("ASOnPanelClose" , this.PanelName);
		}
		
		public function UCUpdateGuildDungeonAwardList(data:Array)
		{
			if (data)
			{
				var awards_count:int = data.length;
				for (var i:int = 0; i < awards_count; ++ i)
				{
					var award_mc:MovieClip = this.getChildByName("guild_dungeon_award_" + i + "_mc") as MovieClip;
					var award_icon:MyItemSlot = award_mc.getChildByName("award_icon") as MyItemSlot;
					award_icon.SetData(1, data[i].guild_dun_award_icon_name, data[i].guild_dun_award_id, "", 0, -1, -1);
				}
			}
		}
		
		public function UCSetGuildDungeonBoss(boss:String)
		{
			guild_dungeon_boss_tf.text = boss;
		}
	}
}


























