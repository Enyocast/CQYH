//
// 家族查看列表节点
//
package ActionScript3.Guild
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	
	public class GuildBuildingListItem extends ListItemTreeRenderer 
	{	
		public var guild_building_list_item_name_tf:TextField;
		public var guild_building_list_item_icon_mc:MovieClip;
		public var _over:MovieClip;
		override protected function configUI():void
		{
			super.configUI();
			_over.mouseChildren=false;
			_over.mouseEnabled=false;
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateItemData);
		}
		
		public function updateItemData(data:Object):void
		{
			if (data != null)
			{
				visible = true;
				
				guild_building_list_item_name_tf.text = data.guild_building_name;
				guild_building_list_item_icon_mc.source = data.guild_building_icon;
			}
			else
			{
				visible = false;
			}	
		}
	}
}
























