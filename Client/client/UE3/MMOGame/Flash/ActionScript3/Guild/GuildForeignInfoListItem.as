//
// 家族外交信息列表节点
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

	public class GuildForeignInfoListItem extends ListItemTreeRenderer
	{
		public var guild_foreign_name_tf:TextField;
		public var guild_foreign_level_tf:TextField;
		public var guild_foreign_count_tf:TextField;
		public var guild_foreign_left_time_tf:TextField;
		public var guild_info_data:Object;
		
		public function GuildForeignInfoListItem()
		{
			// constructor code
		}
		
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
				if (guild_info_data.guild_foreign_type == 1)
				{
					if((e as MouseEventEx).buttonIdx == 1)
					{
						var pos:Point = new Point;
						pos.x = root.mouseX;
						pos.y = root.mouseY;
						ExternalInterface.call("ASAllianceRightClick", pos.x, pos.y, guild_info_data.guild_id);
					}
				}
			}
		}
		
		public function updateItemData(data:Object):void
		{
			if (data != null)
			{
				guild_info_data = data;
				visible = true;
				
				guild_foreign_name_tf.text =  String(data.guild_name);
				guild_foreign_level_tf.text = String(data.guild_level);
				guild_foreign_count_tf.text = String(data.guild_member_count);
				guild_foreign_left_time_tf.text =  String(data.guild_left_time);
			}
			else
			{
				visible = false;
			}
		}
	}
}


























