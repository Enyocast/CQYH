package ActionScript3.Widget
{


	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import ActionScript3.MyTipButton;
	import flash.display.MovieClip;
	import flash.events.Event;

	import ActionScript3.MyCloseButton;
	import ActionScript3.MyPanel;

	public class UWindow extends UIComponent
	{
		public var tab0:MyTipButton;
		public var tab1:MyTipButton;
		public var tab2:MyTipButton;
		public var tab3:MyTipButton;
		public var btnClose:MyCloseButton;
		public var MWTitleIcon:MovieClip;
		public var MWTitleText:MovieClip;
		public var bg_mc:MovieClip;
		public var up:MovieClip;
		public var bg1:MovieClip;
		public var down:MovieClip;
		public var right:MovieClip;
		public var TabFunction:Function = null;// 使用通用框时，赋值此函数来响应tab按键

		public static var TabNum:int = 4;

		override protected function configUI():void
		{
			super.configUI();



			var i:int;
			for (i = 0; i < TabNum; i++)
			{
				var tab = this.getChildByName( "tab"+i );
				if (tab)
				{
					tab.itemid = i;
					tab.addEventListener( MouseEvent.CLICK, ClickTab );

				}
			}

		}

		function ClickTab( e:Event)
		{
			if (e.target is Button && TabFunction != null)
			{
				TabFunction( (e.target as Button).itemid );
			}
		}




		public function Resize( w:int , h:int ,x_edge:int = 40 )
		{
			//trace(w);
			//trace(bg_mc.width);

			var dw:int = w - bg_mc.width;
			var dh:int = h - bg_mc.height;
			bg_mc.width = w;
			bg_mc.height = h;
			bg1.width = w;
			bg1.height = h;
			btnClose['x'] +=  dw;
			up.x = up.x + (dw - x_edge) / 2;
			down.x = down.x + (dw - x_edge) / 2;
			down.y = down.y + dh;
			//right.x = right.x + dw;
			//right.y = right.y + dh;
			trace("UWindowSizeSetted");

		}
		//MWindow Resize
		/*var w:Number = 710;
		var h:Number = 505;
		
		var x_edge:Number = 40;
		
		
		
		
		
		
		
		
		MWindow.up._x = MWindow.up._x + (dw - x_edge) / 2;
		
		MWindow.down._x = MWindow.down._x + (dw - x_edge) / 2;
		MWindow.down._y = MWindow.down._y + dh;
		
		MWindow.right._x = MWindow.right._x + dw;
		MWindow.right._y = MWindow.right._y + dh;
		*/

	}

}