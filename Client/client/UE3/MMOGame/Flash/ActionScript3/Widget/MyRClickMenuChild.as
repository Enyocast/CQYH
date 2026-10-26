package ActionScript3.Widget
{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.managers.PopUpManager;
	import scaleform.clik.events.ComponentEvent;
	import flash.events.FocusEvent;
	import scaleform.clik.events.FocusHandlerEvent;
	import scaleform.clik.managers.FocusHandler;
	import ActionScript3.Widget.MyRClickMenu;
	
	public class MyRClickMenuChild extends MyRClickMenu //ActionScript.MyPanel
	{
		override protected  function configUI():void 
		{
			
			super.configUI();
			var i:int;
			for( i = 0 ; i< MaxLimit ; i++)
			{
				var itembutton:Button = this.getChildByName( "RClicklistItem"+i ) as Button;
				itembutton.itemid = i;
				itembutton.isHtmlLabel = true;
				itembutton.addEventListener( MouseEvent.CLICK , ClickItemButton );
			}
			//this.addEventListener(FocusHandlerEvent.FOCUS_OUT,outHandler);
		}
		
		private function ClickItemButton(e:MouseEvent):void
		{
			if( e.target is Button)
			{
				ExternalInterface.call("ASClickRightChildMenuItem", MenuLevel, (e.target as Button).itemid );
			}
			ResetChildMenuButton();
		}
	}
}