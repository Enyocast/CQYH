package UI_FBEndAll.FBEndAllAS3
{
	import scaleform.clik.core.UIComponent;
	import UI_FBEndAll.FBEndAllAS3.FBAchievement;
	
	import flash.external.ExternalInterface;
	
	public class FBAchievementsContainer extends UIComponent
	{
		public var fbAchievement1:FBAchievement;
		public var fbAchievement2:FBAchievement;
		public var fbAchievement3:FBAchievement;
		public var fbAchievement4:FBAchievement;
		public var fbAchievement5:FBAchievement;
		public var fbAchievement6:FBAchievement;
		public var fbAchievement7:FBAchievement;
		public var fbAchievement8:FBAchievement;
		
		override protected function configUI():void
		{
			super.configUI();
			
			mouseChildren = true;
		}
		//
		public function SetFBAchievement( idx:int, titleName:String, desc:String, achievementType:int ):void
		{
			var achievementMc:FBAchievement = getChildByName( "fbAchievement"+idx ) as FBAchievement;
			if( achievementMc == null ){
				ExternalInterface.call("ASTrace", "SetFBAchievement at"+idx+" asMc is not FOUND" );
				return;
			}
			
			if( achievementType < 0 ){
				achievementMc.visible = false;
			}
			else{
				achievementMc.visible = true;
				achievementMc.SetContentValue( titleName, desc, achievementType );
			}

		}
	}
}