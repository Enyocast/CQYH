package UI_Minimap.MinimapAS3 {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.ListItemRenderer;
		
	public class MapListItem extends ListItemRenderer {
		
		public var mc_line:MovieClip;
		override protected function configUI():void
		{
			super.configUI();
		}
		
		private function overHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_MapLineInfo",this.data.lineState);
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_MapLineInfo");
		}
		
		override public function setData(data:Object):void
		{
			this.data = data;
			updateItemData(data);
		}
		
		public function updateItemData(data:Object):void
		{
			var node:SceneLinesDropDownListData=data as SceneLinesDropDownListData;
			if (node)
			{
				textField.text=node.label;
				if(node.lineState>0){
					 mc_line.visible = true;
					 mc_line.gotoAndStop(node.lineState);
					 this.removeEventListener(MouseEvent.MOUSE_OVER,overHandler);
			         this.removeEventListener(MouseEvent.MOUSE_OUT,outHandler);
				     this.addEventListener(MouseEvent.MOUSE_OVER,overHandler);
			         this.addEventListener(MouseEvent.MOUSE_OUT,outHandler);
				}
			}
			else
			{
				this.removeEventListener(MouseEvent.MOUSE_OVER,overHandler);
			    this.removeEventListener(MouseEvent.MOUSE_OUT,outHandler);
				mc_line.visible = false;
			}
		}

	}
	
}
