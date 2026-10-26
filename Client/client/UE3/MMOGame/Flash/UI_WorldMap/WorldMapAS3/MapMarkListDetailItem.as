package UI_WorldMap.WorldMapAS3
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	import ActionScript3.controls.StateUIComponent;
	
	import UI_WorldMap.WorldMapAS3.MapStaticMarkData;
	
	public class MapMarkListDetailItem extends StateUIComponent 
	{
		public var itemName_tf:TextField;
		//public var icon_mc:MovieClip;
		public var extName_tf:TextField;
		
		public var detailItemData:MapStaticMarkData;
		
		function updateData(data:Object):void
		{
			detailItemData = data as MapStaticMarkData;
			mouseChildren = false;
			doubleClickEnabled = true;
			if( detailItemData ){
				visible = true;
				var format:TextFormat=itemName_tf.getTextFormat();
				format.underline=true;
				itemName_tf.text = detailItemData.label;
				itemName_tf.setTextFormat(format);
				extName_tf.text = detailItemData.ExtName;
				//icon_mc.gotoAndStop( detailItemData.IconType );
			}
			else{
				visible = false;
			}
		}
	}
}

