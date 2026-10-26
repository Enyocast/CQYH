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
	
	public class GuildWelfareInfoPanel extends UIComponent
	{
		public var guild_welfare_0_mc:MovieClip;
		public var guild_welfare_1_mc:MovieClip;
		public var guild_welfare_2_mc:MovieClip;
		public var guild_welfare_3_mc:MovieClip;
		public var guild_welfare_4_mc:MovieClip;
		public var guild_welfare_5_mc:MovieClip;
		public var guild_welfare_6_mc:MovieClip;
		public var guild_welfare_7_mc:MovieClip;
		public var guild_welfare_8_mc:MovieClip;
		public var guild_welfare_9_mc:MovieClip;
		public var guild_welfare_10_mc:MovieClip;
		public var guild_welfare_11_mc:MovieClip;
		public var guild_welfare_12_mc:MovieClip;
		public var guild_welfare_13_mc:MovieClip;
		public var guild_welfare_14_mc:MovieClip;
		public var guild_welfare_15_mc:MovieClip;
		public var guild_welfare_16_mc:MovieClip;
		public var guild_welfare_17_mc:MovieClip;
		public var guild_welfare_18_mc:MovieClip;
		public var guild_welfare_19_mc:MovieClip;
		
		public static const MAX_WELFARE_COUNT = 20;
		
		override protected function configUI():void
		{
			super.configUI();
			
			var i:int = 0;
			for (i = 0; i < MAX_WELFARE_COUNT; ++ i)
			{
				var item_mc:GuildWelfareItem = this.getChildByName("guild_welfare_" + i + "_mc") as GuildWelfareItem;
				
				item_mc.addEventListener(MouseEvent.CLICK, onBtClickWelfare);
				item_mc.addEventListener("rollOver", onItemRollOver);
				item_mc.addEventListener("rollOut", onItemRollOut);
				item_mc.select = false;
				/*
				// test
				var object_data:GuildWelfareData = new GuildWelfareData;
				object_data.guild_wel_icon_name = "icon.TGA";
				object_data.guild_wel_level = 0;
				object_data.guild_wel_top_level = 5;
				object_data.guild_wel_name = "福利" + i.toString();
				item_mc.updateItemData(object_data);
				*/
			}
		}
		
		public function onBtClickWelfare(e:Event)
		{
			var item_mc:GuildWelfareItem = e.currentTarget as GuildWelfareItem;
			if (item_mc != null)
			{
				var i:int = 0;
				for (i = 0; i < MAX_WELFARE_COUNT; ++ i)
				{
					var item_temp_mc:GuildWelfareItem = this.getChildByName("guild_welfare_" + i + "_mc") as GuildWelfareItem;
					item_temp_mc.select = false;
				}
				item_mc.select = true;
				ExternalInterface.call("ASShowWelfareUpgradePanel", item_mc.guild_welfare_id);
			}
		}
		
		public function onItemRollOver(e:Event)
		{
			var item_mc:GuildWelfareItem = e.currentTarget as GuildWelfareItem;
			item_mc.showTips();
		}
		
		public function onItemRollOut(e:Event)
		{
			var item_mc:GuildWelfareItem = e.currentTarget as GuildWelfareItem;
			item_mc.hideTips();
		}
		
		public function updateGuildWelfareList(data:Array)
		{
			var i:int = 0;
			for (i = 0; i < MAX_WELFARE_COUNT; i ++)
			{
				var item_mc:GuildWelfareItem = this.getChildByName("guild_welfare_" + i + "_mc") as GuildWelfareItem;
				item_mc.updateItemData(data[i]);
			}
		}
		
		public function updateGuildTerritoryInfo(data:Object)
		{
		}
	}
}
