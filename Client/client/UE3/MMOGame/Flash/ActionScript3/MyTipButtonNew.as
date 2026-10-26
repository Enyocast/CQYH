
package ActionScript3
{
	import flash.events.Event;
	import flash.external.ExternalInterface;
	
	import scaleform.clik.controls.RadioButton;
	public class MyTipButtonNew extends RadioButton
	{
		public var icon_mc:MyUILoaderContainer;
		
		override protected function configUI():void 
		{
			super.configUI();
			
			//this.addEventListener( MouseEvent.ROLL_OVER, ShowTips);
			//this.addEventListener( MouseEvent.ROLL_OUT, HideTips);
			
			//ExternalInterface.call( "ASTrace", "MyTipButtonNew-----------------------------------------------------------------------------1.0" );
			//icon_mc.source = "img://MMO_UIIcon.testIcon.Tab_Role";
			//ExternalInterface.call( "ASTrace", "MyTipButtonNew-----------------------------------------------------------------------------1.1" );
		}
		
/*		function ShowTips(e:Event)
		{
			ExternalInterface.call("ASShowTips_Tab", this);
		}
		
		function HideTips(e:Event)
		{
			ExternalInterface.call("ASHideTips_Tab", this);
		}*/
		
		public function loadPic(str:String)
		{
			icon_mc.loader_mc.source = str;
		}
		
	}
}


