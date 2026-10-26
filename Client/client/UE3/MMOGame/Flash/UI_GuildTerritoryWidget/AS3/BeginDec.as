package UI_GuildTerritoryWidget.AS3 {
	
	import flash.display.MovieClip;
	import ActionScript3.MyScrollPanel;
	import flash.text.TextField;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.CheckBox;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.clik.data.DataProvider;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	public class BeginDec extends MyScrollPanel {
		
		public var guild_dungeon_desc_tf:TextField;
		public var guild_dungeon_list_mc:DropdownMenu;
		public var guild_dungeon_member_list_mc:DropdownMenu;
		public var guild_dungeon_proxy_cb_mc:CheckBox;
		
		public var guild_dungeon_building_tf:TextField;
		public var guild_dungeon_money_tf:TextField;
		public var guild_dungeon_member_count_tf:TextField;
		
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
		public var guild_dungeon_award_10_mc:MovieClip;
		public var guild_dungeon_award_11_mc:MovieClip;
		
		public var guild_dungeon_data:Array;
		public var guild_member_data:Array;
		
		override protected function configUI():void
		{
			super.configUI();
			guild_dungeon_list_mc.dataProvider = new DataProvider();
			guild_dungeon_list_mc.addEventListener(Event.CHANGE, onCbChangeSelectDungeon);
			guild_dungeon_list_mc.selectedIndex = 0;
			
			guild_dungeon_member_list_mc.dataProvider = new DataProvider();
			guild_dungeon_member_list_mc.selectedIndex = 0
			guild_dungeon_proxy_cb_mc.addEventListener(MouseEvent.CLICK, onToggleClickProxy);
		}
		
		private function onToggleClickProxy(evt:MouseEvent):void
		{
			guild_dungeon_member_list_mc.enabled = guild_dungeon_proxy_cb_mc.selected;
		}
		
	    private function onCbChangeSelectDungeon(e:Event):void
		{
			updateGuildDungeonData(guild_dungeon_list_mc.selectedIndex);
		}
		
		private function updateGuildDungeonData(index:int):void
		{
			if (guild_dungeon_data)
			{
				guild_dungeon_desc_tf.text = String(guild_dungeon_data[index].guild_dun_desc);
				guild_dungeon_building_tf.htmlText = String(guild_dungeon_data[index].guild_dun_building_lv_req);
				guild_dungeon_money_tf.htmlText = String(guild_dungeon_data[index].guild_dun_money_req);
				guild_dungeon_member_count_tf.htmlText = String(guild_dungeon_data[index].guild_dun_member_count_req);
				
				var dungeon_awards:Array = guild_dungeon_data[index].guild_dun_awards as Array;
				var awards_count:int = dungeon_awards.length;
				var i:int = 0;
				for (i = 0; i < awards_count; i ++)
				{
					var award_mc:MovieClip = this.getChildByName("guild_dungeon_award_" + i + "_mc") as MovieClip;
					var award_icon:MyItemSlot = award_mc.getChildByName("award_icon") as MyItemSlot;
					award_icon.SetData(1, dungeon_awards[i].guild_dun_award_icon_name, dungeon_awards[i].guild_dun_award_id, "", 0, -1, -1);
				}
			}
		}
		
		public function UpdateGuildDungeonList(data:Array):void
		{
				guild_dungeon_data = data;
				var dungeon_count:int = guild_dungeon_data.length;
				var dungeon_list:String = "";
				for (var i:int = 0; i < dungeon_count; ++ i)
				{
					dungeon_list += String(guild_dungeon_data[i].guild_dun_name);
					dungeon_list += "=";
				}

				guild_dungeon_list_mc.datastring = dungeon_list;
				guild_dungeon_list_mc.SplitData();
			
				if (dungeon_count > 0)
				{
					guild_dungeon_list_mc.selectedIndex = 0;
					updateGuildDungeonData(guild_dungeon_list_mc.selectedIndex);
				}
		}
		
		public function UpdateGuildMemberList(data:Array):void
		{
				guild_member_data = data;
						
				var member_count:int = guild_member_data.length;
				var member_list:String = "";
				for (var i:int = 0; i < member_count; ++ i)
				{
					member_list += String(guild_member_data[i].guild_mem_name);
					if (i < member_count - 1)
					{
						member_list += "=";
					}
				}

				guild_dungeon_member_list_mc.datastring = member_list;
				guild_dungeon_member_list_mc.SplitData();
			
				if (member_count > 0)
				{
					guild_dungeon_member_list_mc.selectedIndex = 0;
				}
				
				guild_dungeon_member_list_mc.enabled = guild_dungeon_proxy_cb_mc.selected;
		}
	}
	
}
