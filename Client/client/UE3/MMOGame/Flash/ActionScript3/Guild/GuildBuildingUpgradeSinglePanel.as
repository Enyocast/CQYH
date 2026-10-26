//
// 公会建筑升级
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
	
	public class GuildBuildingUpgradeSinglePanel extends MyPanel
	{
		public var guild_building_icon_mc:MovieClip;
		public var guild_building_desc_tf:TextField;
		public var guild_building_cur_level_tf:TextField;
		public var guild_building_next_level_tf:TextField;
		public var guild_building_top_level_tf:TextField;
		public var guild_building_upgrade_time_tf:TextField;
		//public var guild_building_keepup_tf:TextField;
		//public var guild_building_cur_output_cap_tf:TextField;
		//public var guild_building_cur_output_tf:TextField;
		//public var guild_building_next_output_cap_tf:TextField;
		//public var guild_building_next_output_tf:TextField;
		public var tf_name:TextField;
		
		public var guild_money_mc:MovieClip;
		public var guild_herb_mc:MovieClip;
		public var guild_wood_mc:MovieClip;
		public var guild_crystal_mc:MovieClip;
		public var guild_silver_mc:MovieClip;
		
		public var guild_building_pre_building_mc:MovieClip;
		public var guild_building_pre_building_level_tf:TextField;
		
		public var guild_building_upgrade_bt_mc:Button;
		public var guild_building_destroy_bt_mc:Button;
		public var mc_title:MovieClip;
		public var guild_building_data:Object;
		public var tf_dec:TextField;
		public var mc_dec:MovieClip;
		
		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			this.SetWindowTitle("建筑升级");
			guild_building_upgrade_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickUpgrade);
			guild_building_destroy_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickDestroy);
		}
		
		private function onBtClickUpgrade(evt:MouseEvent):void
		{
			if (guild_building_data != null)
			{
				ExternalInterface.call("ASUpgradeBuildingSingle", guild_building_data.guild_building_id_high, guild_building_data.guild_building_id_low, guild_building_data.guild_building_npc_id);
				ExternalInterface.call("ASOnPanelClose" , this.PanelName);
			}
		}
		
		private function onBtClickDestroy(evt:MouseEvent):void
		{
			if (guild_building_data != null)
			{
				ExternalInterface.call("ASDestroyBuildingSingle", guild_building_data.guild_building_id_high, guild_building_data.guild_building_id_low, guild_building_data.guild_building_npc_id);
				ExternalInterface.call("ASOnPanelClose" , this.PanelName);
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
				mc.filters = [StyleType.getInstance().getBlackFilter()];
			}
		}
		
		public function UCUpdateGuildBuildingData(data:Object):void
		{
			guild_building_data = data;
			
			guild_building_icon_mc.source = "";
			guild_building_desc_tf.text = "";
			guild_building_cur_level_tf.text = "";
			guild_building_next_level_tf.text = "";
			guild_building_top_level_tf.text = "";
			tf_name.text="";
			mc_dec.visible=false;
			guild_money_mc.visible=true;
			guild_herb_mc.visible=true;
			guild_wood_mc.visible=true;
			guild_crystal_mc.visible=true;
			guild_silver_mc.visible=true;
			mc_title.visible=true;
			guild_building_pre_building_mc.visible=true;
			guild_building_pre_building_level_tf.visible=true;
			guild_building_upgrade_time_tf.text = "";
			
			guild_building_pre_building_mc.source = null;
			guild_building_pre_building_level_tf.htmlText = "";
			
			//guild_building_keepup_tf.text = "";
/*			guild_building_cur_output_tf.text = "";
			guild_building_cur_output_cap_tf.visible = false;
			guild_building_next_output_tf.text = "";
			guild_building_next_output_cap_tf.visible = false;
			*/
			var guild_res_name_tf:TextField = guild_money_mc.getChildByName("guild_res_name_tf") as TextField;
			var guild_res_num_tf:TextField = guild_money_mc.getChildByName("guild_res_num_tf") as TextField;
			var guild_res_icon_mc:MovieClip = guild_money_mc.getChildByName("guild_res_icon_mc") as MovieClip;
			guild_res_name_tf.text = "";
			guild_res_icon_mc.source = null;
			guild_res_num_tf.htmlText = "";
			
			guild_res_name_tf = guild_herb_mc.getChildByName("guild_res_name_tf") as TextField;
			guild_res_num_tf = guild_herb_mc.getChildByName("guild_res_num_tf") as TextField;
			guild_res_icon_mc = guild_herb_mc.getChildByName("guild_res_icon_mc") as MovieClip;
			guild_res_name_tf.text = "";
			guild_res_icon_mc.source = null;
			guild_res_num_tf.htmlText = "";
			
			guild_res_name_tf = guild_wood_mc.getChildByName("guild_res_name_tf") as TextField;
			guild_res_num_tf = guild_wood_mc.getChildByName("guild_res_num_tf") as TextField;
			guild_res_icon_mc = guild_wood_mc.getChildByName("guild_res_icon_mc") as MovieClip;
			guild_res_name_tf.text = "";
			guild_res_icon_mc.source = null;
			guild_res_num_tf.htmlText = "";
			
			guild_res_name_tf = guild_crystal_mc.getChildByName("guild_res_name_tf") as TextField;
			guild_res_num_tf = guild_crystal_mc.getChildByName("guild_res_num_tf") as TextField;
			guild_res_icon_mc = guild_crystal_mc.getChildByName("guild_res_icon_mc") as MovieClip;
			guild_res_name_tf.text = "";
			guild_res_icon_mc.source = null;
			guild_res_num_tf.htmlText = "";
			
			guild_res_name_tf = guild_silver_mc.getChildByName("guild_res_name_tf") as TextField;
			guild_res_num_tf = guild_silver_mc.getChildByName("guild_res_num_tf") as TextField;
			guild_res_icon_mc = guild_silver_mc.getChildByName("guild_res_icon_mc") as MovieClip;
			guild_res_name_tf.text = "";
			guild_res_icon_mc.source = null;
			guild_res_num_tf.htmlText = "";
			
			if (guild_building_data != null)
			{	
			    tf_name.text=data.guild_building_name;
				guild_building_icon_mc.source = guild_building_data.guild_building_icon;
				guild_building_desc_tf.text = String(guild_building_data.guild_building_desc);
				guild_building_cur_level_tf.text = String(guild_building_data.guild_building_level);
				guild_building_next_level_tf.text = String(guild_building_data.guild_building_next_level);
				guild_building_top_level_tf.text = String(guild_building_data.guild_building_top_level);
				
				guild_building_upgrade_time_tf.text = String(guild_building_data.guild_building_update_time);
				
				//guild_building_keepup_tf.text = String(guild_building_data.guild_building_keepup);
				
/*				guild_building_cur_output_tf.text = String(guild_building_data.guild_building_cur_output);
				if (String(guild_building_data.guild_building_cur_output) == "")
				{
					guild_building_cur_output_cap_tf.visible = false;
				}
				else
				{
					guild_building_cur_output_cap_tf.visible = true;
				}*/
/*				
				guild_building_next_output_tf.text = String(guild_building_data.guild_building_next_output);
				if (String(guild_building_data.guild_building_next_output) == "")
				{
					guild_building_next_output_cap_tf.visible = false;
				}
				else
				{
					guild_building_next_output_cap_tf.visible = true;
				}*/
			
				var colorText:String;
				guild_res_name_tf = guild_money_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_money_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_money_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_money_name;
				guild_res_icon_mc.source = data.guild_money_icon;
				colorText = data.guild_building_money_req > data.guild_money ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_building_money_req) + "</font>";
				
				guild_res_name_tf = guild_herb_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_herb_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_herb_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_herb_name;
				guild_res_icon_mc.source = data.guild_herb_icon;
				colorText = data.guild_building_herb_req > data.guild_herb ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_building_herb_req) + "</font>";
				
				guild_res_name_tf = guild_wood_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_wood_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_wood_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_wood_name;
				guild_res_icon_mc.source = data.guild_wood_icon;
				colorText = data.guild_building_wood_req > data.guild_wood ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_building_wood_req) + "</font>";
				
				guild_res_name_tf = guild_crystal_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_crystal_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_crystal_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_crystal_name;
				guild_res_icon_mc.source = data.guild_crystal_icon;
				colorText = data.guild_building_crystal_req > data.guild_crystal ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_building_crystal_req) + "</font>";
				
				guild_res_name_tf = guild_silver_mc.getChildByName("guild_res_name_tf") as TextField;
				guild_res_num_tf = guild_silver_mc.getChildByName("guild_res_num_tf") as TextField;
				guild_res_icon_mc = guild_silver_mc.getChildByName("guild_res_icon_mc") as MovieClip;
				guild_res_name_tf.text = data.guild_silver_name;
				guild_res_icon_mc.source = data.guild_silver_icon;
				colorText = data.guild_building_silver_req > data.guild_silver ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
				guild_res_num_tf.htmlText = colorText + String(data.guild_building_silver_req) + "</font>";
				
				guild_building_pre_building_mc.source = null;
				guild_building_pre_building_level_tf.htmlText = "";
				var building_req:int = data.guild_building_pre_building_level_req;

				tf_dec.text="升级材料";
				if (data.guild_building_level >= data.guild_building_top_level)
				{
						guild_building_pre_building_mc.visible=false;
						guild_building_pre_building_level_tf.visible=false;
						mc_title.visible=false;
						tf_dec.text="提示";
						guild_money_mc.visible=false;
						guild_herb_mc.visible=false;
						guild_wood_mc.visible=false;
						guild_crystal_mc.visible=false;
						guild_silver_mc.visible=false;
						mc_dec.visible=true;
						guild_building_pre_building_mc.visible=false;
				        guild_building_pre_building_level_tf.visible=false;
				}
				else
				{
				    if(data.guild_building_type==1) 
				    {
					    mc_title.visible=false;
					    guild_building_pre_building_mc.visible=false;
				        guild_building_pre_building_level_tf.visible=false;
				    }
					else
					{
						guild_building_pre_building_mc.source = String(data.guild_building_pre_building_icon);
					    colorText = data.guild_building_pre_building_level_req > data.guild_building_pre_building_level ? "<font color='#FF0000'>" : "<font color='#FFFFFF'>";
					    guild_building_pre_building_level_tf.htmlText = data.guild_building_pre_building + ":"  + colorText + String(data.guild_building_pre_building_level_req) + "级" + "</font>";
					}
				}
			}
		}
	}
}
