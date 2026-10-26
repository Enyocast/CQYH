package UI_SplitCompound.SplitCompoundAS3
{
	//import scaleform.clik.core.UIComponent;
	import ActionScript3.MyPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	//import ActionScript3.MyWindowsFrame;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	
	public class DecomposePanel extends MyPanel
	{
		public var RetMat_0:MyItemSlot;
		public var RetMat_1:MyItemSlot;
		public var RetMat_2:MyItemSlot;
		public var timerCountDown:Timer = new Timer(5000);
		
		override protected function configUI():void
		{
			super.configUI();
			SetWindowTitle("分解结果");
			if(this.MyWindowsFrame_mc.getChildByName("divide")!=null){
				(this.MyWindowsFrame_mc.getChildByName("divide")).visible=false;
			}
			timerCountDown.addEventListener(TimerEvent.TIMER, timerHandle);
		}
		
		private function timerHandle(evt:TimerEvent):void
		{
			timerCountDown.stop();
			ExternalInterface.call( "ASOnPanelClose" , this.name );
		}
		
		public function ResetTimer():void
		{
			timerCountDown.stop();
			timerCountDown.start();
		}
	}
}