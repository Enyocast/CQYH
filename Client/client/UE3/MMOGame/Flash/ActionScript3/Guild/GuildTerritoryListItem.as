//
// 家族查看列表节点
//
package ActionScript3.Guild
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	
	public class GuildTerritoryListItem extends ListItemTreeRenderer 
	{	
		public var guild_upgrade_name_tf:TextField;
		public var guild_upgrade_type_tf:TextField;
		public var guild_upgrade_level_tf:TextField;
		public var guild_upgrade_target_level_tf:TextField;
		public var guild_upgrade_left_time_tf:TextField;
		public var guild_upgrade_finish_time_tf:TextField;
		public var guild_upgrade_icon_mc:MovieClip;
		
		public function GuildTerritoryListItem()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateItemData);
		}
		
		public function updateItemData(data:Object):void
		{
			if (data != null)
			{
				visible = true;
				
				guild_upgrade_icon_mc.source = data.guild_upgrade_icon;
				guild_upgrade_name_tf.text = data.guild_upgrade_name;
				guild_upgrade_type_tf.text = data.guild_upgrade_type_str;
				guild_upgrade_level_tf.text = String(data.guild_upgrade_level);
				guild_upgrade_target_level_tf.text = String(data.guild_upgrade_target_level);
				guild_upgrade_left_time_tf.text = String(data.guild_upgrade_left_time);
				guild_upgrade_finish_time_tf.text = String(data.guild_upgrade_finish_time);
			}
			else
			{
				visible = false;
			}	
		}
	}
}
























