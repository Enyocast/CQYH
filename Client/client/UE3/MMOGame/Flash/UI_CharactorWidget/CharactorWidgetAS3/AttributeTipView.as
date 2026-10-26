package UI_CharactorWidget.CharactorWidgetAS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.MyWindowsFrame;
	import flash.events.MouseEvent;
	
	
	public class AttributeTipView extends UIComponent {
		
		public var list:DetailProperty;
		public var MyWindowsFrame_mc:MyWindowsFrame;
		override protected function configUI():void
		{
			super.configUI();
			MyWindowsFrame_mc.tF_windowTitle.text="其他属性";
			MyWindowsFrame_mc.btn_close.addEventListener(MouseEvent.CLICK,closeHandler);
		}
		
		private function closeHandler(evt:MouseEvent):void
		{
			this.visible=false;
		}
	}
	
}
