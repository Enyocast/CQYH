//
// 家族福利
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
	import flash.filters.ColorMatrixFilter;
	import fl.motion.ColorMatrix;
	import flash.geom.ColorTransform;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Utils.StyleType;
	
	public class GuildWelfareUpgradePanel extends MyPanel
	{
		public var guild_welfare_icon_mc:MovieClip;
		public var guild_welfare_desc_tf:TextField;
		public var guild_welfare_cur_level_tf:TextField;
		public var guild_welfare_next_level_tf:TextField;
		public var guild_welfare_top_level_tf:TextField;
		public var guild_upgrade_time_tf:TextField;
		
		public var guild_welfare_pre_building_mc:MovieClip;
		public var guild_welfare_pre_building_level_tf:TextField;
		
		public var guild_money_mc:MovieClip;
		public var guild_herb_mc:MovieClip;
		public var guild_wood_mc:MovieClip;
		public var guild_crystal_mc:MovieClip;
		public var guild_silver_mc:MovieClip;
		
		//public var guild_upgrade_time_tf:TextField;
		
		public var guild_welfare_upgrade_bt_mc:MovieClip;
		
		public var guild_territory_data:Object;
		public var guild_welfare_data:Object;
		public var guild_dec:MovieClip;
		override protected function configUI():void
		{
			super.configUI();
			guild_welfare_icon_mc=guild_dec.guild_welfare_icon_mc;
			guild_welfare_desc_tf=guild_dec.guild_welfare_desc_tf;
			guild_welfare_upgrade_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickUpgrade);
			UCUpdateGuildWelfareData(null);
			
			// Test
			//guild_welfare_icon_mc.source = "1_109.TGA"
			//setIconGray(guild_welfare_icon_mc, false);
			/*
			var list:Array = new Array();
			for (var i:int = 0; i < 50; i ++)
			{
				var item_data:Object = new Object;
				item_data.index = i;
				item_data.type = 0;
				item_data.deepth =0;
				item_data.visible = true;
				item_data.label = "福利" + i;
				
				item_data.guild_welfare_icon = "1_109.TGA";
				item_data.guild_welfare_name = "福利" + i;
				item_data.guild_welfare_level = 1;
				
				list.push(item_data);
			}

			updateGuildWelfareList(list);
			*/
		}
		
		public function onBtClickUpgrade()
		{
			if (guild_welfare_data != null)
			{
				ExternalInterface.call("ASUpgradeWelfare", guild_welfare_data.guild_welfare_id);
			}
		}
		
		public function setIconGray(mc:MovieClip, gray:Boolean)
		{
			if (! mc)
			{
				return;
			}

			mc.filters = null;
			if (gray)
			{
				mc.filters = [ StyleType.getInstance().getGrayFilter() ];
			}
		}
		
		public function UCUpdateGuildWelfareData(data:Object):void
		{
			guild_welfare_data = data;
			
			guild_welfare_icon_mc.source = null;
			guild_welfare_desc_tf.text = "";
			guild_welfare_cur_level_tf.text = "0";
			guild_welfare_next_level_tf.text = "0";
			guild_welfare_top_level_tf.text = "0";
			
			guild_welfare_pre_building_level_tf.text = "";
			guild_welfare_pre_building_level_tf.htmlText = "";
			
			guild_upgrade_time_tf.text = "0";
				
			if (guild_welfare_data != null)
			{
				guild_welfare_icon_mc.source = guild_welfare_data.guild_welfare_icon;
				setIconGray(guild_welfare_icon_mc, guild_welfare_data.guild_welfare_level < 1);
				
				guild_welfare_desc_tf.text = guild_welfare_data.guild_welfare_desc;
				
				guild_welfare_cur_level_tf.text = String(guild_welfare_data.guild_welfare_level);
				guild_welfare_next_level_tf.text = String(guild_welfare_data.guild_welfare_next_level);
				guild_welfare_top_level_tf.text = String(guild_welfare_data.guild_welfare_top_level);
				
				var colorText:String;
				var guild_res_name_tf:TextField = guild_money_mc.getChildByName("guild_res_name_tf") as TextField;
				var guild_res_num_tf:TextField = guild_money_mc.getChildByName("guild_res_num_tf") as TextField;
				var guild_res_icon_mc:MovieClip = guild_money_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_money_name;
				guild_res_icon_mc.source = data.guild_money_icon;
				colorText = data.guild_welfare_money_req > data.guild_money ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_welfare_money_req) + "</font>";
				
				guild_res_name_tf = guild_herb_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_herb_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_herb_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_herb_name;
				guild_res_icon_mc.source = data.guild_herb_icon;
				colorText = data.guild_welfare_herb_req > data.guild_herb ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_welfare_herb_req) + "</font>";
				
				guild_res_name_tf = guild_wood_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_wood_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_wood_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_wood_name;
				guild_res_icon_mc.source = data.guild_wood_icon;
				colorText = data.guild_welfare_wood_req > data.guild_wood ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_welfare_wood_req) + "</font>";
				
				guild_res_name_tf = guild_crystal_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_crystal_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_crystal_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_crystal_name;
				guild_res_icon_mc.source = data.guild_crystal_icon;
				colorText = data.guild_welfare_crystal_req > data.guild_crystal ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_welfare_crystal_req) + "</font>";
				
				guild_res_name_tf = guild_silver_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_silver_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_silver_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_silver_name;
				guild_res_icon_mc.source = data.guild_silver_icon;
				colorText = data.guild_welfare_silver_req > data.guild_silver ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_welfare_silver_req) + "</font>";
				
				guild_welfare_pre_building_mc.source = null;
				guild_welfare_pre_building_level_tf.htmlText = "";
				var building_req:int = data.guild_welfare_pre_building_level_req;
				if (building_req > 0)
				{
					guild_welfare_pre_building_mc.source = String(data.guild_welfare_pre_building_icon);
					colorText = data.guild_welfare_pre_building_level_req > data.guild_welfare_pre_building_level ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
					guild_welfare_pre_building_level_tf.htmlText = data.guild_welfare_pre_building + ":"  + colorText + String(data.guild_welfare_pre_building_level_req) + "级" + "</font>";
				}
				
				guild_upgrade_time_tf.text = String(guild_welfare_data.guild_welfare_up_time);
			}
		}
	}
}
