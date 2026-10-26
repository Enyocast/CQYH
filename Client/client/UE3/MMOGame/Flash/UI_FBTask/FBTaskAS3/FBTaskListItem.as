package UI_FBTask.FBTaskAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.UILoader;
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	
	import UI_FBTask.FBTaskAS3.FBTaskListItemData;
	import UI_FBTask.FBTaskAS3.FBTaskListItemMainProgress;
	import UI_FBTask.FBTaskAS3.FBTaskListItemSubProgress;
	
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	
	public class FBTaskListItem extends ListItemTreeRenderer
	{
		public var MainProgressItemMc:FBTaskListItemMainProgress;
		public var SubProgressItemMc:FBTaskListItemSubProgress;
		
		public var ListItemData:FBTaskListItemData;
		
		override protected function configUI():void
		{
			super.configUI();
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(UpdateData);
		}

		function UpdateData(data:Object):void
		{
			ListItemData = data as FBTaskListItemData;
			if( !ListItemData ){
				visible = false;
				return;
			}
			visible = true;
			
			//
			MainProgressItemMc.visible = false;
			SubProgressItemMc.visible = false;
			switch( ListItemData.TaskType )
			{
				case 1:
				MainProgressItemMc.UpdateItem( ListItemData );
				MainProgressItemMc.visible = true;
				break;
				
				case 2:
				SubProgressItemMc.UpdateItem( ListItemData );
				SubProgressItemMc.visible = true;
				break;
			}
			
		}
	}

}