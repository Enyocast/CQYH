package ActionScript3.Guild {
	
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	
	public class SabacListItem extends ListItemTreeRenderer {
		
		public var list_name_tf:TextField;
		public var list_timer_tf:TextField;
		public var list_level_tf:TextField;
		public var list_member_count_tf:TextField;
		public var list_leader_tf:TextField;
		public var list_create_time_tf:TextField;

		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren=false;
			this.mouseEnabled=false;
			this.enabled=true;
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateItemData);
		}
		
		private function updateItemData(data:Object):void
		{
			if (data)
			{
				this.visible = true;
				
				list_name_tf.text = data.guild_name;
				list_timer_tf.text = data.guild_start_time;
				list_level_tf.text = String(data.guild_level);
				list_member_count_tf.text = String(data.guild_member_count);
				list_leader_tf.text = data.guild_leader_name;
				list_create_time_tf.text = data.guild_create_time;
			}
			else
			{
				this.visible = false;
			}	
		}
	}
	
}
