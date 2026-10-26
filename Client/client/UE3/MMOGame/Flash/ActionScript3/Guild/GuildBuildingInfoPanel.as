//
// 家族属地
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
	
	public class GuildBuildingInfoPanel extends UIComponent
	{
		public var guild_building_1_mc:GuildBuildingItem;
		public var guild_building_2_mc:GuildBuildingItem;
		public var guild_building_3_mc:GuildBuildingItem;
		public var guild_building_4_mc:GuildBuildingItem;
		public var guild_building_5_mc:GuildBuildingItem;
		public var guild_building_6_mc:GuildBuildingItem;
		public var guild_building_7_mc:GuildBuildingItem;
		public var guild_building_8_mc:GuildBuildingItem;
		public var guild_building_9_mc:GuildBuildingItem;
		public var guild_building_10_mc:GuildBuildingItem;
		public var guild_building_11_mc:GuildBuildingItem;
		public var guild_building_12_mc:GuildBuildingItem;
		public var guild_building_13_mc:GuildBuildingItem;
		public var guild_building_14_mc:GuildBuildingItem;
		public var guild_building_15_mc:GuildBuildingItem;
		
		//public var guild_building_18_mc:GuildBuildingItem;
		public var guild_building_19_mc:GuildBuildingItem;
		public var guild_building_20_mc:GuildBuildingItem;
		public var guild_building_21_mc:GuildBuildingItem;
		public var guild_building_22_mc:GuildBuildingItem;
		public var guild_building_23_mc:GuildBuildingItem;
		//public var guild_building_24_mc:GuildBuildingItem;
		
		public static const MAX_BUILDING_COUNT = 24;
		
		override protected function configUI():void
		{
			super.configUI();
			
			var i:int = 0;
			for (i = 1; i <= MAX_BUILDING_COUNT; i++)
			{
				var item_mc:GuildBuildingItem = this.getChildByName("guild_building_" + i + "_mc") as GuildBuildingItem;
				if(item_mc)
				{
					if (i > 7 && i < 12)
				    {
						item_mc.visible=false;
						continue;
				    }
					item_mc.addEventListener(MouseEvent.CLICK, onBtClickBuilding);
					item_mc.addEventListener(MouseEvent.ROLL_OVER, onItemRollOver);
					item_mc.addEventListener(MouseEvent.ROLL_OUT, onItemRollOut);
				}
				//item_mc.select = false;
				/*
				// test
				var object_data:GuildBuildingData = new GuildBuildingData;
				object_data.guild_building_icon = "icon.TGA";
				object_data.guild_building_level = 0;
				object_data.guild_building_top_level = 5;
				object_data.guild_building_name = "建筑" + i.toString();
				item_mc.updateItemData(object_data);
				*/
			}
		}
		
		private function onItemRollOver(e:MouseEvent):void
		{
			var item_mc:GuildBuildingItem = e.currentTarget as GuildBuildingItem;
			if (item_mc)
			{
				ExternalInterface.call("ASShowTips_Building", item_mc, item_mc.guild_building_type);
			}
		}
		
		private function onItemRollOut(e:MouseEvent):void
		{
			var item_mc:GuildBuildingItem = e.currentTarget as GuildBuildingItem;
			if (item_mc)
			{
				ExternalInterface.call("ASHideTips_Building", item_mc);
			}
		}
		
		private function onBtClickBuilding(e:MouseEvent):void
		{
			var item_mc:GuildBuildingItem = e.currentTarget as GuildBuildingItem;
			if (item_mc != null)
			{
/*				var i:int = 0;
				for (i = 1; i <= MAX_BUILDING_COUNT; ++ i)
				{
					if (i > 11 && i < 18)
					{
						continue;
					}
				
					var item_temp_mc:GuildBuildingItem = this.getChildByName("guild_building_" + i + "_mc") as GuildBuildingItem;
					//item_temp_mc.select = false;
				}*/
				//item_mc.select = true;
				
				ExternalInterface.call("ASShowBuildingUpgradePanel", item_mc.guild_building_type);
			}
		}
		
		public function updateGuildBuildingList(data:Array):void
		{
			var i:int = 0;
			for (i = 0; i < data.length; i++)
			{
				var item_mc:GuildBuildingItem = this.getChildByName("guild_building_" + data[i].guild_building_type + "_mc") as GuildBuildingItem;
				if (item_mc != null && item_mc.visible==true)
				{
					item_mc.updateItemData(data[i]);
				}
			}
		}
		
		public function updateGuildTerritoryInfo(data:Object)
		{
		}
	}
}
