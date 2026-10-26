
package ActionScript3.Achievement
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	
	public class AchievementStatListItem extends ListItemTreeRenderer 
	{
		public var achievement_stat_name_tf:TextField;
		public var achievement_stat_value_tf:TextField;
		
		public function AchievementStatListItem()
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
				
				achievement_stat_name_tf.text = data.stat_name;
				achievement_stat_value_tf.text = data.stat_value.toString();
			}
			else
			{
				visible = false;
			}	
		}
	}

}

