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
	import scaleform.clik.controls.UILoader;
	
	public class GuildTerritoryInfoPanel extends UIComponent
	{
		public var guild_level_tf:TextField;
		
		public var guild_money_mc:MovieClip;
		public var guild_herb_mc:MovieClip;
		public var guild_wood_mc:MovieClip;
		public var guild_crystal_mc:MovieClip;
		public var guild_silver_mc:MovieClip;
		
		//public var guild_upkeep_tf:TextField;
		//public var guild_prosperity_tf:TextField;
		
		public var guild_territory_list_mc:ScrollingList;
		public var guild_upgrade_cancel_bt_mc:Button;//取消升级
		
		public var guild_contribute_bt_mc:Button;//资源捐献
		public var guild_territory_contribute_mc:MovieClip;
		
		public var guild_upgrade_data:Object;
		
		public var guild_herb_tips_mc:MovieClip;
		public var guild_wood_tips_mc:MovieClip;
		public var guild_crystal_tips_mc:MovieClip;
		public var guild_silver_tips_mc:MovieClip;
		public var guild_money_tips_mc:MovieClip;
		//public var guild_upkeep_tips_mc:MovieClip;
		public var guild_level_tips_mc:MovieClip;
		//public var guild_prosperity_tips_mc:MovieClip;

		public var guild_con_type_list:Array = new Array();
		public var tabTitle:MovieClip;

		override protected function configUI():void
		{
			super.configUI();
			
			guild_money_mc.guild_res_name_tf.text = "资金";
			guild_herb_mc.guild_res_name_tf.text = "粮食";
			guild_wood_mc.guild_res_name_tf.text = "木材";
			guild_crystal_mc.guild_res_name_tf.text = "石料";
			guild_silver_mc.guild_res_name_tf.text = "铁矿";
			guild_territory_list_mc.selectedIndex = 0;
			guild_territory_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			guild_territory_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);
			
			guild_upgrade_cancel_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickCancelUpgrade);
			guild_upgrade_cancel_bt_mc.visible = false;
			
			guild_contribute_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickContribute);
			guild_territory_contribute_mc.visible = false;
			guild_contribute_bt_mc.visible= false;
			
			guild_con_type_list.push("粮食");
			guild_con_type_list.push("木材");
			guild_con_type_list.push("石料");
			guild_con_type_list.push("铁矿");
		}
		
		public function onListItemChange( event:ListEvent ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}
		
		public function onListItemClick(event:ListEvent):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:TreeDataProvider = list.dataProvider as TreeDataProvider;
				if (provider!=null)
				{
					provider.handleListItemClick(event);
					guild_upgrade_data = provider.requestItemAt(event.index);
				}
				
				list.invalidateData();
			}
		}
		
		private function onBtClickCancelUpgrade(evt:MouseEvent):void
		{
			if (guild_upgrade_data != null)
			{
				if (guild_upgrade_data.guild_upgrade_type == 0)
				{
					ExternalInterface.call("ASCancelUpgradeBuilding", guild_upgrade_data.guild_upgrade_id_high, guild_upgrade_data.guild_upgrade_id_low);
				}
				else
				{
					ExternalInterface.call("ASCancelUpgradeWelfare", guild_upgrade_data.guild_upgrade_id_low);
				}
			}
		}
		
		private function onBtClickContribute(evt:MouseEvent):void
		{
			guild_territory_contribute_mc.visible = true;
		}
		
		public function updateGuildTerritoryInfo(data:Object):void
		{
			guild_level_tf.text = "0";
			//guild_upkeep_tf.text = "0";
			//guild_prosperity_tf.text = "0";
			guild_money_mc.guild_res_num_tf.text = "0";
			guild_herb_mc.guild_res_num_tf.text = "0";
			guild_wood_mc.guild_res_num_tf.text = "0";
			guild_crystal_mc.guild_res_num_tf.text = "0";
			guild_silver_mc.guild_res_num_tf.text = "0";
			
			if (data != null)
			{
				guild_level_tf.text = String(data.guild_level);
				//guild_upkeep_tf.text = String(data.guild_keepup);
				//guild_prosperity_tf.text = String(data.guild_prosperity);
				
				var guild_res_name_tf:TextField = guild_money_mc.getChildByName("guild_res_name_tf") as TextField;
				var guild_res_num_tf:TextField = guild_money_mc.getChildByName("guild_res_num_tf") as TextField;
				var guild_res_icon_mc:UILoader = guild_money_mc.getChildByName("guild_res_icon_mc") as UILoader;
				guild_res_name_tf.text = data.guild_money_name;
				guild_res_icon_mc.source = data.guild_money_icon;
				guild_res_num_tf.autoSize=TextFieldAutoSize.LEFT;
				guild_res_num_tf.text = String(data.guild_money) + "/" + String(data.guild_money_max);
				
				guild_res_name_tf = guild_herb_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_herb_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_herb_mc.getChildByName("guild_res_icon_mc") as UILoader;
				guild_res_name_tf.text = data.guild_herb_name;
				guild_res_icon_mc.source = data.guild_herb_icon;
				guild_res_num_tf.autoSize=TextFieldAutoSize.LEFT;
				guild_res_num_tf.text = String(data.guild_herb) + "/" + String(data.guild_herb_max);
				
				guild_res_name_tf = guild_wood_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_wood_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_wood_mc.getChildByName("guild_res_icon_mc") as UILoader;
				guild_res_name_tf.text = data.guild_wood_name;
				guild_res_icon_mc.source = data.guild_wood_icon;
				guild_res_num_tf.autoSize=TextFieldAutoSize.LEFT;
				guild_res_num_tf.text = String(data.guild_wood) + "/" + String(data.guild_wood_max);
				
				guild_res_name_tf = guild_crystal_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_crystal_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_crystal_mc.getChildByName("guild_res_icon_mc") as UILoader;
				guild_res_name_tf.text = data.guild_crystal_name;
				guild_res_icon_mc.source = data.guild_crystal_icon;
				guild_res_num_tf.autoSize=TextFieldAutoSize.LEFT;
				guild_res_num_tf.text = String(data.guild_crystal) + "/" + String(data.guild_crystal_max);
				
				guild_res_name_tf = guild_silver_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_silver_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_silver_mc.getChildByName("guild_res_icon_mc") as UILoader;
				guild_res_name_tf.text = data.guild_silver_name;
				guild_res_icon_mc.source = data.guild_silver_icon;
				guild_res_num_tf.autoSize=TextFieldAutoSize.LEFT;
				guild_res_num_tf.text = String(data.guild_silver) + "/" + String(data.guild_silver_max);
				
				guild_territory_contribute_mc.updateContributeType(guild_con_type_list);
			}
		}
		
		public function updateGuildTerritoryUpgradeList(data:Array)
		{
			guild_territory_list_mc.dataProvider = new TreeDataProvider(data);
			guild_territory_list_mc.validateNow();
			guild_territory_list_mc.invalidateData();
			
			guild_upgrade_cancel_bt_mc.visible = data.length > 0;
		}
	}
}
