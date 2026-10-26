package UI_WorldMap.WorldMapAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;

	public class MapMarkListItem extends ListItemTreeRenderer
	{
		public var isDetailItem:Boolean;
		
		public var ListItemClass_mc:MapMarkListClassItem;
		//public var ListItemClassData:TeleportMapData;

		public var ListItemDetail_mc:MapMarkListDetailItem;
		//public var ListItemDetailData:TeleportNodesData;
		
		override protected function configUI():void
		{
			super.configUI();
			
			//this.addEventListener(MouseEvent.ROLL_OVER, onRollOverListItem);
			//this.addEventListener(MouseEvent.ROLL_OUT, onRollOutListItem);
			mouseChildren = true;
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateData);
		}

		function updateData(data:Object):void
		{
			if( !data || data.deepth >1 ){
				isDetailItem = false;
				visible = false;
				return;
			}
			
			visible = true;
			ListItemClass_mc.selected=this.selected;
			if( data.deepth == 0 ){
				
				ListItemClass_mc.visible = true;
				ListItemDetail_mc.visible = false;
				ListItemClass_mc.updateData( data );
				isDetailItem = false;
			}
			else if( data.deepth == 1 ){
				
				ListItemClass_mc.visible = false;
				ListItemDetail_mc.visible = true;
				ListItemDetail_mc.updateData( data );
				isDetailItem = true;
			}
		}
		

	}

}