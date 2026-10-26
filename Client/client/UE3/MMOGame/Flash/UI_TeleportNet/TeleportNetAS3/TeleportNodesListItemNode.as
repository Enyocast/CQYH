package UI_TeleportNet.TeleportNetAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import UI_TeleportNet.TeleportNetAS3.TeleportNodesData;
	import scaleform.clik.controls.UILoader;

	public class TeleportNodesListItemNode extends MovieClip
	{
		public var nodeName_tf:TextField;
		//public var nodeMnyType_mc:MovieClip;
		public var nodeMny_tf:TextField;
		public var nodePic_mc:UILoader;
		public var nodeItemData:TeleportNodesData;

		function updateData(data:Object):void
		{
			nodeItemData = data as TeleportNodesData;
			ReflashData();
		}
		
		//
		public function ReflashData():void
		{
			if( nodeItemData ){
				visible = true;
				//teleportNodesListItemNode.nodeMnyType_mc.gotoAndStop(nodeItemData.CostType);
				
				if( nodeItemData.ShowState == 0 ){
					//it is normal
					nodeName_tf.htmlText = nodeItemData.NodeName;
					nodeMny_tf.htmlText = nodeItemData.CostString;
					
					//nodePic_mc.gotoAndStop( nodeItemData.PicName );
					if( nodeItemData.PicName.length > 0 ){
						nodePic_mc.source = "img://MMO_UIImg.img_list_" + nodeItemData.PicName;
					}
				}
				else if( nodeItemData.ShowState == 1 ){
					//it is locked(current node)
					//it is normal
					nodeName_tf.htmlText = "<font color='#888888'>" + nodeItemData.NodeName + "</font>";
					nodeMny_tf.htmlText = nodeItemData.CostString;
					
					//nodePic_mc.gotoAndStop( nodeItemData.PicName );
					if( nodeItemData.PicName.length > 0 ){
						nodePic_mc.source = "img://MMO_UIImg.img_list_" + nodeItemData.PicName;
					}
				}
				else{
				}
				
			}
			else{
				visible = false;
			}
		}
	}
}