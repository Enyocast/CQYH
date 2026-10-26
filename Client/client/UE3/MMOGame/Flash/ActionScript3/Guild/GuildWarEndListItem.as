//
// 家族总揽
//
package ActionScript3.Guild
{
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.display.MovieClip;

	public class GuildWarEndListItem extends ListItemTreeRenderer
	{
		public var player_tf:TextField;
		public var level_tf:TextField;
		public var post_tf:TextField;
		public var kill_tf:TextField;
		public var dead_tf:TextField;
		public var money_tf:TextField;
		public var roleHead_mc:MovieClip;
		
		public function GuildWarEndListItem():void
		{
			
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateData);
		}
		
		public function updateData(dat:Object):void
		{
			if (dat != null)
			{
				visible = true;
				player_tf.text = dat.member_name;
				level_tf.text = dat.member_level.toString();
				post_tf.text = dat.member_job.toString();
				kill_tf.text = dat.member_kill_count.toString();
				dead_tf.text = dat.member_dead_times.toString();
				money_tf.text = dat.member_achieve.toString();
			}
			else
			{
				visible = false;
			}	
		}
	}
}


























