//
// 家族查看列表节点
//
package ActionScript3.Guild
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	
	public class GuildWelfareListItem extends ListItemTreeRenderer 
	{	
		public var guild_welfare_list_item_name_tf:TextField;
		public var guild_welfare_list_item_level_tf:TextField;
		
		public function GuildWelfareListItem()
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
				
				guild_welfare_list_item_level_tf.text = String(data.guild_welfare_level);
				
				if (data.guild_welfare_level > 0)
				{
					guild_welfare_list_item_name_tf.htmlText = "<font color='#FFFFFF'>" + String(data.guild_welfare_name) + "</font>";
				}
				else
				{
					guild_welfare_list_item_name_tf.htmlText = "<font color='#666666'>" + String(data.guild_welfare_name) + "</font>";
				}
			}
			else
			{
				visible = false;
			}	
		}
	}
}
























