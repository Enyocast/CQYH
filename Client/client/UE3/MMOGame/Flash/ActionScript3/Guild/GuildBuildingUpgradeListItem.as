//
// 家族查看列表节点
//
package ActionScript3.Guild
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	
	public class GuildBuildingUpgradeListItem extends ListItemTreeRenderer 
	{	
		public var guild_building_target_level_tf:TextField;
		public var guild_building_money_req_tf:TextField;
		public var guild_building_herb_req_tf:TextField;
		public var guild_building_wood_req_tf:TextField;
		public var guild_building_crystal_req_tf:TextField;
		public var guild_building_silver_req_tf:TextField;
		
		public function GuildBuildingUpgradeListItem()
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
				
				guild_building_target_level_tf.text = String(data.guild_building_target_level);
				guild_building_money_req_tf.text = String(data.guild_building_money_req);
				guild_building_herb_req_tf.text = String(data.guild_building_herb_req);
				guild_building_wood_req_tf.text = String(data.guild_building_wood_req);
				guild_building_crystal_req_tf.text = String(data.guild_building_crystal_req);
				guild_building_silver_req_tf.text = String(data.guild_building_silver_req);
			}
			else
			{
				visible = false;
			}	
		}
	}
}
























