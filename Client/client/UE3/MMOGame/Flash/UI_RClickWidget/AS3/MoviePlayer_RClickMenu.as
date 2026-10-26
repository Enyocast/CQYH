package UI_RClickWidget.AS3 {
	
	import ActionScript3.fla.MoviePlayerBase;
	import ActionScript3.Widget.MyRClickMenu;
	import flash.external.ExternalInterface;
	
	public class MoviePlayer_RClickMenu extends MoviePlayerBase {
		
		//public var RClickMenuChild:MyRClickMenu;
		public var RClickMenu:MyRClickMenu;
		
		override protected  function configUI():void
		{			
			super.configUI();
			ExternalInterface.call( "RegisterRClickMenu" , RClickMenu );
		}
	}
	
}
