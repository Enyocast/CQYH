package ActionScript3.Widget
{
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;

	public class FacePanel extends UIComponent
	{
		public var clickfunc:Function;

		static var FaceNum:int = 20;//目前24个

		override protected function configUI():void
		{
			super.configUI();
			var i:int;
			for ( i = 0; i < FaceNum ; i++)
			{
				var facebutton:Button = this.getChildByName( "FaceButton"+i) as Button;
				if (facebutton)
				{
					facebutton.itemid = i;
					facebutton.addEventListener( MouseEvent.CLICK , ClickFace );
					var faceIcon:UILoader = facebutton.getChildByName("FaceIcon") as UILoader;
					if (faceIcon)
					{
						faceIcon.source = "img://MMO_UIFace." + i;
					}
				}
			}			
		}

		public static function GetFaceNum():int
		{
			return FaceNum;
		}

		function ClickFace( e:MouseEvent):void
		{

			if ( clickfunc != null )
			{
				if (e.target is Button)
				{
					clickfunc(( e.target as Button ).itemid);

				}
			}
			visible = false;
		}
	}
}