package ActionScript3.Master 
{
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	
	public class AlertPanel extends MyPanel
	{
		public var confirm_mc:Button;
		public var tF_name_master:TextField;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			(MyWindowsFrame_mc.getChildByName("divide") as MovieClip).y=186;
			confirm_mc.addEventListener(MouseEvent.CLICK, onConfirmPanel );
			SetWindowTitle("");
		}
		
		private function onConfirmPanel(evt:MouseEvent):void
		{
			ExternalInterface.call("ASClickCLosePanel");
		}
		
		public function UCSetWindowContent(wTitle:String , wContent:String):void
		{
			tF_name_master.text = wContent;
			SetWindowTitle(wTitle);
		}
	}
}
