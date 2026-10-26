package ActionScript3.Widget
{
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	import scaleform.clik.core.UIComponent;

	import flash.external.ExternalInterface;

	//´¿Îı¾
	public class MyTipsText extends UIComponent
	{
		public var text:String;
		public var intData:int; 
		
		
		override protected function configUI():void 
		{
			super.configUI();
			
			//buttonµÄtipsÏÈͣÓÃ
			this.addEventListener( MouseEvent.ROLL_OVER, ShowTips);
			this.addEventListener( MouseEvent.ROLL_OUT, HideTips);
		}
		

		function ShowTips(e:Event)
		{
			ExternalInterface.call("ASShowTips_Text", this);
			//trace( "tips:"+text);
			//this["root"].ChangeTips();
		}
		
		function HideTips(e:Event)
		{
			ExternalInterface.call("ASHideTips_Text", this);
			//trace("hidetips");
			//this["root"].tooltips_mc.visible =false;
			
		}
	}

}