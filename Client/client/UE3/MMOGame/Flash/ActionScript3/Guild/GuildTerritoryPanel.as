//
// 家族
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
	import ActionScript3.MyTipButtonNew;
	import scaleform.clik.controls.RadioButton;

	public class GuildTerritoryPanel extends MyPanel
	{
		public var guild_territory_info_tab_mc:RadioButton;
		public var guild_building_upgrade_tab_mc:RadioButton;
		//public var guild_welfare_upgrade_tab_mc:RadioButton;

		public var guild_territory_info_mc:MovieClip;
		public var guild_building_info_mc:MovieClip;
		//public var guild_welfare_info_mc:MovieClip;
		
		public var com_bg:MovieClip;

		public static const guild_page_territory_info = 1;
		public static const guild_page_building_upgrade = 2;
		public static const guild_page_welfare_upgrade = 3;
		public var guild_page:int;

		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			guild_territory_info_tab_mc.addEventListener(MouseEvent.CLICK,onTabClickTerrInfo);
			guild_building_upgrade_tab_mc.addEventListener(MouseEvent.CLICK,onTabClickBuildingUpgrade);
			//guild_welfare_upgrade_tab_mc.addEventListener(MouseEvent.CLICK,onTabClickWelfareUpgrade);
			
			guild_territory_info_tab_mc.selected = true;
			guild_building_upgrade_tab_mc.selected = false;
			//guild_welfare_upgrade_tab_mc.selected = false;
			
			guild_territory_info_mc.visible = true;
			guild_building_info_mc.visible = false;
			//guild_welfare_info_mc.visible = false;
			
			// clear
			UCUpdateGuildTerritoryUpgradeList([]);
		    UCUpdateGuildBuildingList([]);
		    //UCUpdateGuildWelfareList(new Array);
		}

		// event
		private function onTabClickTerrInfo(evt:MouseEvent):void
		{
			guild_territory_info_mc.visible = true;
			guild_building_info_mc.visible = false;
			com_bg.height=410;
			//guild_welfare_info_mc.visible = false;
		}

		private function onTabClickBuildingUpgrade(evt:MouseEvent):void
		{
			guild_territory_info_mc.visible = false;
			guild_building_info_mc.visible = true;
			com_bg.height=445;
			//guild_welfare_info_mc.visible = false;
		}

/*		public function onTabClickWelfareUpgrade()
		{
			guild_territory_info_mc.visible = false;
			guild_building_info_mc.visible = false;
			guild_welfare_info_mc.visible = true;
		}*/

		// UC
		public function UCUpdateGuildTerritoryInfo(data:Object):void
		{
			guild_territory_info_mc.updateGuildTerritoryInfo(data);
			//guild_welfare_info_mc.updateGuildTerritoryInfo(data);
		}

		public function UCUpdateGuildTerritoryUpgradeList(data:Array):void
		{
			guild_territory_info_mc.updateGuildTerritoryUpgradeList(data);
		}

		public function UCUpdateGuildBuildingList(data:Array):void
		{
			guild_building_info_mc.updateGuildBuildingList(data);
		}
		
		public function UCUpdateGuildWelfareList(data:Array):void
		{
			//guild_welfare_info_mc.updateGuildWelfareList(data);
		}
		
		public function UCSetWindowTitle(title:String):void
		{
			SetWindowTitle(title);
		}
	}
}