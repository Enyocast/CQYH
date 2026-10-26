//
// 家族外交信息
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
	import scaleform.clik.utils.Padding;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;

	public class GuildForeignInfoPanel extends UIComponent
	{
		public var guild_foreign_info_ally_list_mc : ScrollingList;
		public var guild_foreign_info_enemy_list_mc : ScrollingList;
		
		public var guild_foreign_apply_ally_mc:Button;
		public var guild_foreign_apply_enemy_mc:Button;
		
		public var guild_foreign_apply_panel_mc:GuildForeignApplyPanel;
		const c_guild_apply_ally = 1;
		const c_guild_apply_enemy = 2;
		
		public var guild_foreign_info_ally_data : Object;
		public var guild_foreign_info_enemy_data : Object;
		public var tab

		override protected function configUI():void
		{
			super.configUI();

			guild_foreign_apply_ally_mc.addEventListener(MouseEvent.CLICK, onBtClickApplyAlly);
			guild_foreign_apply_enemy_mc.addEventListener(MouseEvent.CLICK, onBtClickApplyEnemy);
			
			guild_foreign_info_ally_list_mc.selectedIndex = 0;
			guild_foreign_info_ally_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onAllyListItemChange, false, 0, true);
			guild_foreign_info_ally_list_mc.addEventListener(ListEvent.ITEM_CLICK, onAllyListItemClick, false, 0, true);

			guild_foreign_info_enemy_list_mc.selectedIndex = 0;
			guild_foreign_info_enemy_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onEnemyListItemChange, false, 0, true);
			guild_foreign_info_enemy_list_mc.addEventListener(ListEvent.ITEM_CLICK, onEnemyListItemClick, false, 0, true);
			
			
			// test
/*			var item_data_array:Array = new Array();
			for (var i:int = 0; i < 10; i++)
			{
				var item_data:Object = new Object;
				item_data.guild_name = "联盟列表"+i;
				item_data.guild_level = 1;
				item_data.guild_member_count = 10;
				item_data.guild_left_time = 10;
				item_data_array.push(item_data);
			}
			updateGuildAllyList(item_data_array);
			updateGuildEnemyList(item_data_array);*/
			
			guild_foreign_apply_panel_mc.visible = false;
		}
		
		public function onAllyListItemChange( event:ListEvent ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}
		
		public function onAllyListItemClick(event:ListEvent):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:DataProvider = list.dataProvider as DataProvider;
				if (provider!=null)
				{
					guild_foreign_info_ally_data = provider.requestItemAt(event.index);
				}
				
				list.invalidateData();
			}
		}
		
		public function onEnemyListItemChange( event:ListEvent ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}
		
		public function onEnemyListItemClick(event:ListEvent):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:DataProvider = list.dataProvider as DataProvider;
				if (provider!=null)
				{
					guild_foreign_info_enemy_data = provider.requestItemAt(event.index);
				}
				
				list.invalidateData();
			}
		}

		public function onBtClickApplyAlly()
		{
			guild_foreign_apply_panel_mc.setApplyType(c_guild_apply_ally);
			guild_foreign_apply_panel_mc.show();
			guild_foreign_apply_panel_mc.visible = true;
		}
		
		public function onBtClickApplyEnemy()
		{
			guild_foreign_apply_panel_mc.setApplyType(c_guild_apply_enemy);
			guild_foreign_apply_panel_mc.show();
			guild_foreign_apply_panel_mc.visible = true;
		}
		
		public function updateGuildAllyList(data:Array)
		{
			guild_foreign_info_ally_list_mc.dataProvider = new DataProvider(data);
			guild_foreign_info_ally_list_mc.validateNow();
			guild_foreign_info_ally_list_mc.invalidateData();
		}
		
		public function updateGuildEnemyList(data:Array)
		{
			guild_foreign_info_enemy_list_mc.dataProvider = new DataProvider(data);
			guild_foreign_info_enemy_list_mc.validateNow();
			guild_foreign_info_enemy_list_mc.invalidateData();
		}
		
		public function updateGuildBaseInfo(data:Object)
		{
			guild_foreign_apply_ally_mc.enabled = data.guild_rights_foreign;
			guild_foreign_apply_enemy_mc.enabled = data.guild_rights_foreign;
		}
		
		public function updateForeignApplyConsume(money:String)
		{
			guild_foreign_apply_panel_mc.updateConsume(money);
		}
	}
}


























