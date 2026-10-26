//
// 家族总揽
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
	
	public class GuildBuildingUpgradePanel extends UIComponent
	{
		public var guild_building_icon_mc:MovieClip;
		public var guild_building_level_tf:TextField;
		public var guild_building_desc_tf:TextField;
		public var guild_building_cur_level_tf:TextField;
		public var guild_building_next_level_tf:TextField;
		public var guild_building_top_level_tf:TextField;
		public var guild_money_tf:TextField;
		public var guild_herb_tf:TextField;
		public var guild_wood_tf:TextField;
		public var guild_crystal_tf:TextField;
		public var guild_silver_tf:TextField;
		public var guild_upgrade_time_tf:TextField;
		public var guild_building_pre_tf:TextField;
		
		public var guild_building_keepup_tf:TextField;
		public var guild_building_output_tf:TextField;
		public var guild_building_output_cap_tf:TextField;
		
		public var guild_building_list_mc:ScrollingList;
		public var guild_building_upgrade_list_head_mc:GuildBuildingUpgradeListHead;
		public var guild_building_upgrade_bt_mc:Button;
		public var guild_building_list_head_0_mc:Button;
		public var guild_building_list_head_1_mc:Button;
		
		public var guild_building_data:Object;
		
		override protected function configUI():void
		{
			super.configUI();
			
			guild_building_list_mc.selectedIndex = 0;
			guild_building_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onBuildingListItemChange, false, 0, true);
			guild_building_list_mc.addEventListener(ListEvent.ITEM_CLICK, onBuildingListItemClick, false, 0, true);
			guild_building_list_mc.addEventListener(ListEvent.ITEM_ROLL_OVER, onBuildingListItemRollOver, false, 0, true);
			guild_building_list_mc.addEventListener(ListEvent.ITEM_ROLL_OUT, onBuildingListItemRollOut, false, 0, true);
			
			guild_building_upgrade_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickUpgrade);
		}
		
		public function onBuildingListItemChange( event:Event ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}
		
		public function onBuildingListItemClick(event:ListEvent):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:TreeDataProvider = list.dataProvider as TreeDataProvider;
				if (provider!=null)
				{
					var data:Object = provider.requestItemAt(event.index);
					if (data != null)
					{
						updateGuildBuildingInfo(data);
					}
				}
				
				list.invalidateData();
			}
		}
		
		public function onBuildingListItemRollOver(event:ListEvent):void
		{
		}

		public function onBuildingListItemRollOut(event:ListEvent):void
		{
		}
		
		public function onBtClickUpgrade()
		{
			if (guild_building_data != null)
			{
				ExternalInterface.call("ASUpgradeBuilding", guild_building_data.guild_building_id);
			}
		}
		
		public function updateGuildBuildingList(data:Array)
		{
			guild_building_list_mc.dataProvider = new TreeDataProvider(data);
			guild_building_list_mc.validateNow();
			guild_building_list_mc.invalidateData();
		}
		
		public function updateGuildBuildingInfo(data:Object)
		{
			guild_building_data = data;
			
			if (guild_building_data != null)
			{
				guild_building_icon_mc.source = guild_building_data.guild_building_icon;
				guild_building_desc_tf.text = String(guild_building_data.guild_building_desc);
				guild_building_level_tf.text = String(guild_building_data.guild_building_level);
				guild_building_cur_level_tf.text = String(guild_building_data.guild_building_level);
				guild_building_next_level_tf.text = String(guild_building_data.guild_building_next_level);
				guild_building_top_level_tf.text = String(guild_building_data.guild_building_top_level);
				
				guild_upgrade_time_tf.text = String(guild_building_data.guild_building_update_time);
				
				guild_building_keepup_tf.text = String(guild_building_data.guild_building_keepup);
				guild_building_output_tf.text = String(guild_building_data.guild_building_output);
				if (String(guild_building_data.guild_building_output) == "")
				{
					guild_building_output_cap_tf.visible = false;
				}
				else
				{
					guild_building_output_cap_tf.visible = true;
				}
				/*
				guild_money_tf.htmlText = guild_building_data.guild_building_money_req;
				guild_herb_tf.htmlText = guild_building_data.guild_building_herb_req;
				guild_wood_tf.htmlText = guild_building_data.guild_building_wood_req;
				guild_crystal_tf.htmlText = guild_building_data.guild_building_crystal_req;
				guild_silver_tf.htmlText = guild_building_data.guild_building_silver_req;
				guild_building_pre_tf.htmlText = guild_building_data.guild_building_pre;
				*/
				var colorText:String;
				var building_req:int = guild_building_data.guild_building_pre_building_level_req;
				if (building_req > 0)
				{
					colorText = guild_building_data.guild_building_pre_building_level_req > guild_building_data.guild_building_pre_building_level ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
					guild_building_pre_tf.htmlText = guild_building_data.guild_building_pre_building + ":"  + colorText + String(guild_building_data.guild_building_pre_building_level_req) + "级" + "</font>";
				}
				
				colorText = guild_building_data.guild_building_money_req > guild_building_data.guild_money ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_money_tf.htmlText = colorText + String(guild_building_data.guild_building_money_req) + "</font>";
				
				colorText = guild_building_data.guild_building_herb_req > guild_building_data.guild_herb ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_herb_tf.htmlText = colorText + String(guild_building_data.guild_building_herb_req) + "</font>";
				
				colorText = guild_building_data.guild_building_wood_req > guild_building_data.guild_wood ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_wood_tf.htmlText = colorText + String(guild_building_data.guild_building_wood_req) + "</font>";
				
				colorText = guild_building_data.guild_building_crystal_req > guild_building_data.guild_crystal ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_crystal_tf.htmlText = colorText + String(guild_building_data.guild_building_crystal_req) + "</font>";
				
				colorText = guild_building_data.guild_building_silver_req > guild_building_data.guild_silver ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_silver_tf.htmlText = colorText + String(guild_building_data.guild_building_silver_req) + "</font>";
			}
			else
			{
				guild_building_icon_mc.source = "";
				guild_building_level_tf.text = "";
				guild_building_desc_tf.text = "";
				guild_building_cur_level_tf.text = "";
				guild_building_next_level_tf.text = "";
				guild_building_top_level_tf.text = "";
				guild_money_tf.htmlText = "";
				guild_herb_tf.htmlText = "";
				guild_wood_tf.htmlText = "";
				guild_crystal_tf.htmlText = "";
				guild_silver_tf.htmlText = "";
				guild_upgrade_time_tf.text = "";
				guild_building_pre_tf.htmlText = "";
				
				guild_building_keepup_tf.text = "";
				guild_building_output_tf.text = "";
				guild_building_output_cap_tf.visible = false;
			}
		}
	}
}
