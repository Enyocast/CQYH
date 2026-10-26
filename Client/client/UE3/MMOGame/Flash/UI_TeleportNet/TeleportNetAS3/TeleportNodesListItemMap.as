package UI_TeleportNet.TeleportNetAS3
{
	import flash.display.MovieClip;	
	import flash.text.TextField;
	import UI_TeleportNet.TeleportNetAS3.TeleportMapData;
	import flash.events.MouseEvent;
	
	public class TeleportNodesListItemMap extends MovieClip 
	{
		public var mapName_tf:TextField;
		//public var unfold_mc:MovieClip;
		
		public var mapItemData:TeleportMapData;
		
		public var _select:Boolean;
		public function TeleportNodesListItemMap():void
		{
			this.addEventListener(MouseEvent.CLICK,clickHandler);
		}
		
		private function clickHandler(e:MouseEvent):void
		{
			mapItemData.select=!mapItemData.select;
			this.selected=mapItemData.select;
		}
		
		public function updateData(data:Object):void
		{
			mapItemData = data as TeleportMapData;
			selected=mapItemData.select;
			if( mapItemData ){
				visible = true;
				mapName_tf.text = mapItemData.MapName;
			}
		}
		
		public function set selected(b:Boolean):void
		{
			_select=b;
			if(b){
				this.gotoAndStop( "selected_up" );
			}else{
				this.gotoAndStop( "up" );
			}
		}
		
		public function get selected():Boolean
		{
			return _select;
		}
	}
}

