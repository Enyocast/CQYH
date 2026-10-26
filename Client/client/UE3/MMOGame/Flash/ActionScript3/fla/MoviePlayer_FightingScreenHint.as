package ActionScript3.fla
{
	import UI_FightingScreenHint.FightingScreenHintAS3.FightingScreenHintPanel;
	import UI_FightingScreenHint.FightingScreenHintAS3.ScreenPopUpBoxMsg;
	
	//import flash.utils.getTimer;
	
	public class MoviePlayer_FightingScreenHint extends MoviePlayerBase
	{
		public var FightingScreenHint_mc:FightingScreenHintPanel;
		public var ScreenPopUpBoxMsgAOGMc:ScreenPopUpBoxMsg;
		
		override protected function configUI():void
		{
			super.configUI();
			
			ScreenPopUpBoxMsgAOGMc.visible = false;
			//ScreenPopUpBoxMsgAOGMc.UCSetMsgInfo( 1, "获得技能", "牛逼技能", "0.TGA", "");
			//ScreenPopUpBoxMsgAOGMc.UCSetMsgInfo( 2, "您已获得了", "主动技能槽解锁", "", "1键");
			//ScreenPopUpBoxMsgAOGMc.UCSetMsgInfo( 3, "多重箭", "等级升到2级", "0.TGA", "");
			//ScreenPopUpBoxMsgAOGMc.UCSetMsgInfo( 6, "通关", "XXX副本难度", "", "" );
			//trace( "----------------Begin Time:", getTimer() );
		}				
	}
}