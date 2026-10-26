package UI_GuildTerritoryWidget.AS3 {
	
	import flash.display.MovieClip;
	import ActionScript3.MyScrollPanel;
	import flash.text.TextField;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	
	public class AwardDec extends MyScrollPanel{
		
		public var guild_dungeon_desc_tf:TextField;
		public var guild_dungeon_level_tf:TextField;
		public var guild_dungeon_member_tf:TextField;
		public var guild_dungeon_active_tf:TextField;
		public var guild_dungeon_intro_tf:TextField;
		
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
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function UpdateGuildDungeonData(guild_dungeon_data:Object):void
		{
			guild_dungeon_desc_tf.text = String(guild_dungeon_data.guild_dun_desc);
			guild_dungeon_level_tf.htmlText = String(guild_dungeon_data.guild_dun_building_lv_req);
			guild_dungeon_member_tf.htmlText = String(guild_dungeon_data.guild_dun_member_count_req);
			guild_dungeon_active_tf.htmlText = String(guild_dungeon_data.guild_dun_active_req);
			
			var dungeon_awards:Array = guild_dungeon_data.guild_dun_awards as Array;
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
	
}
