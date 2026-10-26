//
// 家族申请结盟信息列表节点
//
package ActionScript3.Guild
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;

	public class GuildAllyInfoListItem extends ListItemTreeRenderer
	{
		public var guild_apply_ally_name_tf:TextField;
		public var guild_apply_ally_level_tf:TextField;
		public var guild_apply_ally_count_tf:TextField;
		public var guild_apply_ally_leader_tf:TextField;
		public var guild_apply_ally_left_time_tf:TextField;
		
		public function GuildAllyInfoListItem()
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
				
				guild_apply_ally_name_tf.text = data.guild_name;
				guild_apply_ally_level_tf.text = String(data.guild_level)
				guild_apply_ally_count_tf.text = String(data.guild_member_count);
				guild_apply_ally_leader_tf.text = data.guild_leader_name;
				guild_apply_ally_left_time_tf.text = data.guild_left_time;
			}
			else
			{
				visible = false;
			}	
		}
	}
}


























