package UI_Hurt.HurtAS3  {
	
	import flash.display.MovieClip;
	import ActionScript3.fla.MoviePlayerBase;
	
	
	public class MoviePlayer_PopUpHurt extends MoviePlayerBase {
		
		public var hurtView:HurtPopUp;
		//public var hurt_tips:HurtTips;
		override protected function configUI():void
		{
			super.configUI();
			
			//hurt_tips.visible = false;
		}				
	}
	
}
