//
// 家族总揽
//
package ActionScript3.Guild
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;

	public class GuildPendingMemberListItem extends ListItemTreeRenderer
	{
		public var guild_info_pending_member_name_tf:TextField;
		public var guild_info_pending_member_level_tf:TextField;
		public var guild_info_pending_member_job_tf:TextField;
		public var guild_info_pending_member_time_tf:TextField;
		
		public function GuildPendingMemberListItem()
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
				
				guild_info_pending_member_name_tf.text = data.member_name;
				guild_info_pending_member_level_tf.text = String(data.member_level);
				guild_info_pending_member_job_tf.text = data.member_job;
				guild_info_pending_member_time_tf.text = data.member_time;
			}
			else
			{
				visible = false;
			}	
		}
	}
}


























