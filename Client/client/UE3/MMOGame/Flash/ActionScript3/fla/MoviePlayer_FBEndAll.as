package ActionScript3.fla
{
	import flash.display.StageScaleMode;
	import flash.external.ExternalInterface;
	
	import UI_FBEndAll.FBEndAllAS3.FBSummaryPanel;
	import UI_FBEndAll.FBEndAllAS3.FBAwardPanel;
	import UI_FBEndAll.FBEndAllAS3.FBBattleComfirmPanel;
	
	import ActionScript3.fla.MoviePlayerBase;
	
	public class MoviePlayer_FBEndAll extends MoviePlayerBase
	{
		public var FBSummary_mc:FBSummaryPanel;
		public var FBAwards_mc:FBAwardPanel;
		public var FBBattleConfirmPanel_mc:FBBattleComfirmPanel;
		
		override protected function configUI():void
		{
			super.configUI();
			
			/*
			//test
			FBAwards_mc.visible = false;
			for( var i:int = 1; i <= 8; ++i ){
				FBSummary_mc.SetFBAchievement( i, "副本评价点"+i, "评价点描述"+i, i%4 );
			}
			*/
		}
	}
}