package ActionScript3.Option {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import UI_Minimap.MinimapAS3.SceneLinesDropDownListData;
	
	import scaleform.clik.controls.ListItemRenderer;
	
	
	public class LineItem extends ListItemRenderer {
		
		override protected function configUI():void
		{
			super.configUI();
			this.addEventListener(MouseEvent.CLICK,clickHandler);
		}
		override public function setData(data:Object):void
		{
			this.data = data;
			updateItemData(data);
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASChangeSceneLineByOptionMenu",  this.data.lineID );
		}
		
		public function updateItemData(data:Object):void
		{
			var node:SceneLinesDropDownListData=data as SceneLinesDropDownListData;
			if (node)
			{
				textField.text=node.label;

			}
		}

	}
	
}
