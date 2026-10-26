package ActionScript3 {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;

	//import ActionScript3.MyPanel;

	import flash.external.ExternalInterface;

	public class MyHelperButton extends Button
	{
		public var _TargetPanel:Object;
		
		override protected function configUI():void 
		{
			super.configUI();
			this.addEventListener( MouseEvent.CLICK , OnHelp )
		}
		
		public function set HelperTargetPanel( tar:Object )
		{
			_TargetPanel = tar;
		}
		
		public function RemoveAddedEventListener()
		{
			this.removeEventListener( MouseEvent.CLICK, OnHelp );
		}

		private function OnHelp( e:MouseEvent ):void
		{
			if( _TargetPanel ) //&& _TargetPanel is ActionScript3.MyPanel )
			{
				ExternalInterface.call( "ASOnPanelHelp" , _TargetPanel.PanelName );
			}
		}

	}

}