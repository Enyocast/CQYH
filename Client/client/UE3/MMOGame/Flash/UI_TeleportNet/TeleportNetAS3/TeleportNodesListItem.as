package UI_TeleportNet.TeleportNetAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;

	public class TeleportNodesListItem extends ListItemTreeRenderer
	{
		public var teleportItemType:int=-1;
		//public var mapName_tf:TextField;
		public var teleportMap_mc:TeleportNodesListItemMap;
		public var mapItemData:TeleportMapData;
		
		//public var nodeName_tf:TextField;
		//public var nodeMnyType_mc:MovieClip;
		//public var nodeMny_tf:TextField;
		public var teleportNode_mc:TeleportNodesListItemNode;
		public var nodeItemData:TeleportNodesData;
		
		public var teleportNodeEmpty_mc:MovieClip;
		
		override protected function configUI():void
		{
			super.configUI();
			
			//this.addEventListener(MouseEvent.ROLL_OVER, onRollOverListItem);
			//this.addEventListener(MouseEvent.ROLL_OUT, onRollOutListItem);
			//this.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDownListItem);
			//this.addEventListener(MouseEvent.MOUSE_UP, onMouseUpListItem);
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateData);
		}

		function updateData(data:Object):void
		{
			if( !data || data.deepth >1 ){
				teleportItemType = -1;
				visible = false;
				return;
			}
			
			visible = true;
			if( data.deepth == 0 ){
				mapItemData = data as TeleportMapData;
				//trace("mapItemData : " + mapItemData);
				teleportNodeEmpty_mc.visible = false;
				teleportNode_mc.visible = false;
				teleportMap_mc.visible = true;
				
				teleportMap_mc.updateData( data );
				teleportItemType = 0;
			}
			else if( data.deepth == 1 ){
				nodeItemData = data as TeleportNodesData;
				if( nodeItemData ){
					//trace("nodeItemData : " + nodeItemData);
					teleportNodeEmpty_mc.visible = false;
					teleportNode_mc.visible = true;
					teleportMap_mc.visible = false;
				
					teleportNode_mc.updateData( data );
					teleportItemType = 1;
				}
				else{
					teleportNodeEmpty_mc.visible = true;
					teleportNode_mc.visible = false;
					teleportMap_mc.visible = false;
					
					teleportNodeEmpty_mc.gotoAndStop("down");
					teleportItemType = 2;
				}
			}
		}
		
		

	}

}