//
// 家族总揽
//
package ActionScript3.Guild
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.geom.Point;

	public class GuildFullMemberListItem extends ListItemTreeRenderer
	{
		public var guild_info_full_member_name_tf:TextField;
		public var guild_info_full_member_level_tf:TextField;
		public var guild_info_full_member_job_tf:TextField;
		public var guild_info_full_member_post_tf:TextField;
		public var guild_info_full_member_map_tf:TextField;
		public var guild_info_full_member_time_tf:TextField;
		public var guild_info_data:Object;
		
		override protected function configUI():void
		{
			super.configUI();
			
			this.addEventListener(MouseEvent.CLICK, onMouseCLick);
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateItemData);
		}
		
		function onMouseCLick(e:Event)
		{
			if (guild_info_data != null)
			{
				if((e as MouseEventEx).buttonIdx == 1)
				{
					var pos:Point = new Point;
					pos.x = root.mouseX;
					pos.y = root.mouseY;
					ExternalInterface.call( "ASFullMemberRightClick", pos.x, pos.y, guild_info_data.member_id);
				}
			}
		}
		
		public function updateItemData(data:Object):void
		{
			if (data != null)
			{
				visible = true;
				guild_info_data = data;
				
				var htmlHead:String;
				if (data.member_self)
				{
					htmlHead = "<font color='#00FF00'>";
				}
				else if (data.member_online)
				{
					htmlHead = "<font color='#FFFFFF'>";
				}
				else
				{
					htmlHead = "<font color='#AAAAAA'>";
				}
				
				guild_info_full_member_name_tf.htmlText = htmlHead + data.member_name + "</font>";
				guild_info_full_member_level_tf.htmlText = htmlHead + String(data.member_level) + "</font>";
				guild_info_full_member_job_tf.htmlText = htmlHead + data.member_job + "</font>";
				guild_info_full_member_post_tf.htmlText = htmlHead + data.member_post + "</font>";
				guild_info_full_member_map_tf.htmlText = htmlHead + data.member_map + "</font>";
				guild_info_full_member_time_tf.htmlText = htmlHead + data.member_time + "</font>";
			}
			else
			{
				visible = false;
			}	
		}
	}
}


























