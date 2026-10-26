package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.Event;
	
	public class FBEnterMsgPanel extends MyPanel
	{
		public var btn_Prepare:Button;
		public var btn_CancelPrepare:Button;
		
		override protected  function configUI():void 
		{
			super.configUI();
			//
			ExternalInterface.call( "RegisterFBEnterMsg", this );
			//
			btn_Prepare.addEventListener( "click",clickPrepareEnter );
			btn_CancelPrepare.addEventListener( "click",clickCancelPrepare );
		}
		//
		function clickPrepareEnter()
		{
			ExternalInterface.call("UCPrepareEnter");
		}
		//
		function clickCancelPrepare()
		{
			ExternalInterface.call("UCCancelPrepare");
		}
	}
}