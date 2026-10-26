package ActionScript3 {
	import flash.events.MouseEvent;
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	import scaleform.clik.managers.FocusHandler;
	import scaleform.clik.core.CLIK;

	public class MyCloseButton extends Button
	{
		public var _TargetPanel:Object;
		override protected function configUI():void 
		{
			super.configUI();
			this.addEventListener(MouseEvent.CLICK,OnClose);
		}
		
		public function set CloseTargetPanel( tar:Object )
		{
			_TargetPanel = tar;
		}
		
		protected function OnClose(event:MouseEvent):void 
		{
			if( _TargetPanel )
			{
				ExternalInterface.call( "ASOnPanelClose" , _TargetPanel.PanelName );
			    if(FocusHandler.getInstance().getFocus(0)!=null)
			    {
				    FocusHandler.getInstance().setFocus(null);
			    }
			}
		}
		
		public function RemoveAddedEventListener()
		{
			this.removeEventListener( MouseEvent.CLICK, OnClose );
		}
	}

}