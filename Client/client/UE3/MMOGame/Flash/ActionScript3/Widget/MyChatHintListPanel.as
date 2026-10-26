package ActionScript3.Widget {
	
	import ActionScript3.MyActivePanel;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.utils.getDefinitionByName;
	
	public class MyChatHintListPanel extends MyActivePanel
	{
		public var clickfunc:Function;
		var ListItemClass:Class;
		
		var ItemList:Array;
		
		//static var FaceNum:int = 12;//Ä¿Ç°12¸ö
		
		override protected  function configUI():void {
			super.configUI();
			
			ItemList = new Array;
			/*var i:int;
			for( i = 0 ; i < FaceNum ;i++)
			{
				var facebutton:Button = this.getChildByName( "FaceButton"+i) as Button;
				facebutton.itemid = i;
				facebutton.addEventListener( MouseEvent.CLICK , ClickFace );
			}*/
			
			ListItemClass = getDefinitionByName( "Btn_ChatLine" ) as Class;
			
		}
		
		public static function GetFaceNum():int
		{
			return FaceNum;
		}
		
		public function AddNewListItem()
		{
			var Item:Button = new ListItemClass;
			addChild( Item );
			ItemList.push( Item );
		}
		
		
		
		function ClickFace( e:Event )
		{
			
			if( clickfunc != null )
			{
				if( e.target is Button )
				{
					clickfunc(( e.target as Button ).itemid);
					
				}
				//clickfunc.call(0);
				
			}
			visible = false;
		}
	}
}