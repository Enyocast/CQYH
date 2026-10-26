
package ActionScript3.Mall
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.TextEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;

	public class  MallFriendListItem extends ListItemTreeRenderer
	{
		public var name_tf:TextField;
		public var job_mc:TextField;
		public var level_mc:TextField;
		
		public var friendData:MallFriendListItemData;
		
		override protected function configUI():void
		{
			trace("------MallFriendListItem  configUI:");
			super.configUI();
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack( updateData );
			visible = false;
		}
		
		function updateData(data:Object):void
		{
			friendData = data as MallFriendListItemData;
			
			if(friendData)
			{
				visible = true;
				name_tf.text = friendData.RoleName;
				job_mc.text = friendData.RoleJob;
				level_mc.text = friendData.RoleLevel;
			}
			else
				visible = false;
		}
	}
}