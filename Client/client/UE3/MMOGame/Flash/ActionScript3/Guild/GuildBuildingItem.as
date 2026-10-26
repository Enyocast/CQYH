//
// 家族建筑项
//
package ActionScript3.Guild
{
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.utils.Padding;
	import ActionScript3.Common.Utils.StyleType;
	
	public class GuildBuildingItem extends UIComponent 
	{	
		public var guild_building_icon_mc:MovieClip;
		public var guild_building_level_tf:TextField;
		public var guild_building_hover_mc:MovieClip;
		
		public var guild_building_type:int;
		public var guild_building_icon_last:String;
		public var guild_building_level_last:int;
		public var _mask:MovieClip;
		public var style:int=0;

		override protected function configUI():void
		{
			super.configUI();
			
			guild_building_icon_mc.source = null;
			guild_building_level_tf.text = "";

			guild_building_icon_last = "";
			guild_building_level_last = -1;
			hideTips();
			guild_building_type = 0;
		}
		
		public function showTips():void
		{
			//ExternalInterface.call("ASShowTips_Text", this);
			if(guild_building_hover_mc)
			 guild_building_hover_mc.visible = true;
		}
		
		public function hideTips():void
		{
			//ExternalInterface.call("ASRollOutItemSlot", this);
			if(guild_building_hover_mc)
			  guild_building_hover_mc.visible = false;
		}

		public function get select():Boolean
		{
			return false;
		}
		
		public function setIconGray(mc:MovieClip, gray:Boolean):void
		{
			if (! mc)
			{
				return;
			}
             
			mc.filters = null;
			if (gray)
			{
				mc.filters = [ StyleType.getInstance().getBlackFilter()];
			}
		}
		
		public function updateItemData(data:Object):void
		{
			if (data != null)
			{
				visible = true;
				guild_building_type = data.guild_building_type;
				if(guild_building_icon_last!=data.guild_building_icon)
				{
					guild_building_icon_mc.source = data.guild_building_icon;
					guild_building_icon_last = data.guild_building_icon;
				}
				if(guild_building_level_last!=data.guild_building_level)
				{
					setIconGray(guild_building_icon_mc, data.guild_building_level < 1);
					guild_building_level_last = data.guild_building_level;
				}
				guild_building_level_tf.text = String(data.guild_building_level);
			}
			else
			{
				visible = false;
				guild_building_type = 0;

			}
			
		}
	}
}
























