//
// 家族查看列表节点
//
package ActionScript3.Guild
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import scaleform.clik.core.UIComponent;
	
	public class GuildViewListItem extends ListItemTreeRenderer 
	{	
		public var guild_view_list_item_name_tf:TextField;
		public var guild_view_list_item_id_tf:TextField;
		public var guild_view_list_item_level_tf:TextField;
		public var guild_view_list_item_member_count_tf:TextField;
		public var guild_view_list_item_leader_tf:TextField;
		public var guild_view_list_create_time_tf:TextField;
		public var mc_icon:UIComponent;

		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren=true;
			guild_view_list_item_name_tf.mouseEnabled=false;
			guild_view_list_item_id_tf.mouseEnabled=false;
			guild_view_list_item_level_tf.mouseEnabled=false;
			guild_view_list_item_member_count_tf.mouseEnabled=false;
			guild_view_list_item_leader_tf.mouseEnabled=false;
			guild_view_list_create_time_tf.mouseEnabled=false;
			mc_icon.visible=false;
			mc_icon.addEventListener(MouseEvent.ROLL_OVER,overHandler);
			mc_icon.addEventListener(MouseEvent.ROLL_OUT,outHandler);
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateItemData);
		}
		
		private function overHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASGetStringByID",this,"tipsHtml","MMOGame.Guild.GuildIconTips1");
		    ExternalInterface.call("ASShowTips_PlainText",this );
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_PlainText",this );
		}
		
		public function updateItemData(data:Object):void
		{
			if (data != null)
			{
				if(visible==false)
				{
					visible = true;
				}
				mc_icon.visible=false;
				if(data.icon && data.icon>0)
				{
					mc_icon.visible=true;
					mc_icon.gotoAndStop(data.icon);
				}
				guild_view_list_item_name_tf.htmlText = data.guild_name;
				guild_view_list_item_id_tf.text = data.guild_id;
				guild_view_list_item_level_tf.text = String(data.guild_level);
				guild_view_list_item_member_count_tf.text = String(data.guild_member_count);
				guild_view_list_item_leader_tf.text = data.guild_leader_name;
				guild_view_list_create_time_tf.text = data.guild_create_time;
			}
			else
			{
				visible = false;
			}	
		}
	}
}
























