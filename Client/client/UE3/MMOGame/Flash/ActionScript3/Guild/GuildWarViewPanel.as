//
// 家族查看
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
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import ActionScript3.MyCloseButton;

	public class GuildWarViewPanel extends MyPanel
	{
		public var guild_view_name_tf : TextField;
		public var guild_view_leader_tf : TextField;
		public var guild_view_level_tf : TextField;
		public var guild_view_prosperity_tf : TextField;
		public var guild_view_enounce_tf : TextField;
		
		public var guild_view_challange_mc : MovieClip;
		public var guild_view_close_mc : MovieClip;
		
		public var guild_building_1_mc : MovieClip;
		public var guild_building_2_mc : MovieClip;
		public var guild_building_3_mc : MovieClip;
		public var guild_building_4_mc : MovieClip;
		public var guild_building_5_mc : MovieClip;
		public var guild_building_6_mc : MovieClip;
		public var guild_building_7_mc : MovieClip;
		public var guild_building_8_mc : MovieClip;
		public var guild_building_9_mc : MovieClip;
		public var guild_building_10_mc : MovieClip;
		public var guild_building_11_mc : MovieClip;
		public var guild_building_12_mc : MovieClip;
		public var guild_building_13_mc : MovieClip;
		public var guild_building_14_mc : MovieClip;
		public var guild_building_15_mc : MovieClip;
		public var guild_building_18_mc : MovieClip;
		public var guild_building_19_mc : MovieClip;
		public var guild_building_20_mc : MovieClip;
		public var guild_building_21_mc : MovieClip;
		public var guild_building_22_mc : MovieClip;
		public var guild_building_23_mc : MovieClip;
		public var guild_building_24_mc : MovieClip;
		
		public var guild_id:int;
		
		public static const MAX_BUILDING_COUNT = 24;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			guild_id = 0;
			guild_view_challange_mc.addEventListener(MouseEvent.CLICK, onBtClickChallange);
			guild_view_close_mc.addEventListener(MouseEvent.CLICK, onBtClickClose);
			
			var i:int = 0;
			for (i = 1; i <= MAX_BUILDING_COUNT; ++ i)
			{
				if (i == 16 || i == 17)
				{
					continue;
				}
				var item_mc:GuildBuildingItem = this.getChildByName("guild_building_" + i + "_mc") as GuildBuildingItem;
				
				item_mc.addEventListener("rollOver", onItemRollOver);
				item_mc.addEventListener("rollOut", onItemRollOut);
				//item_mc.select = false;
				/*
				// test
				var object_data:GuildBuildingData = new GuildBuildingData;
				object_data.guild_building_icon = "icon.TGA";
				object_data.guild_building_level = 1;
				object_data.guild_building_top_level = 5;
				item_mc.updateItemData(object_data);
				*/
			}
		}

		public function onItemRollOver(e:Event)
		{
			var item_mc:GuildBuildingItem = e.currentTarget as GuildBuildingItem;
			item_mc.showTips();
		}
		
		public function onItemRollOut(e:Event)
		{
			var item_mc:GuildBuildingItem = e.currentTarget as GuildBuildingItem;
			item_mc.hideTips();
		}
		
		public function onBtClickChallange()
		{
			ExternalInterface.call("ASMatchChallenge", guild_id);
		}
		
		public function onBtClickClose()
		{
			ExternalInterface.call("ASOnPanelClose" , this.PanelName);
		}
		
		public function UCUpdateGuildViewInfo(data:Object)
		{
			guild_id = data.guild_id;
			guild_view_name_tf.text = data.guild_name;
			guild_view_leader_tf.text = data.guild_leader_name;
			guild_view_level_tf.text = data.guild_level;
			guild_view_prosperity_tf.text = data.guild_prosperity;
			guild_view_enounce_tf.text = data.guild_announce;
		}
		
		public function UCUpdateGuildBuildingList(data:Array)
		{
			var i:int = 0;
			for (i = 0; i < data.length; ++ i)
			{
				var item_mc:GuildBuildingItem = this.getChildByName("guild_building_" + data[i].guild_building_type + "_mc") as GuildBuildingItem;
				if (item_mc != null)
				{
					item_mc.updateItemData(data[i]);
				}
			}
		}
		
		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
	}
}


























