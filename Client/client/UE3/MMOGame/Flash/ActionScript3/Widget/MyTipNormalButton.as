package ActionScript3.Widget
{
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;

	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;

	//这里用直接寻址，间接寻址有点怪问题
	public class MyTipNormalButton extends Button
	{
		
		public var tabCaption:String;
		
		override protected function configUI():void 
		{
			super.configUI();
			
			//button的tips先停用
			this.addEventListener( MouseEvent.ROLL_OVER, ShowTips);
			this.addEventListener( MouseEvent.ROLL_OUT, HideTips);
			

		}
				
		function ShowTips(e:Event)
		{
			ExternalInterface.call("ASShowTips_Tab", this);			
		}
		
		function HideTips(e:Event)
		{
			ExternalInterface.call("ASHideTips_Tab", this);

			
		}
	}

}