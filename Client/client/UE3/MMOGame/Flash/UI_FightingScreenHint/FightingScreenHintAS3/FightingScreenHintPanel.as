package UI_FightingScreenHint.FightingScreenHintAS3
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.utils.clearTimeout;
	import flash.utils.setTimeout;
	
	import scaleform.clik.core.UIComponent;
	
	public class FightingScreenHintPanel extends UIComponent
	{
		private static const FIGHTING_COUNT_DOWN_TIME:int = 9;
		
		public var TenSecCountDown_mc:MovieClip;
		public var arena_result_movie:ArenaResultMovie;
		//public var FightingScreenMask_mc:MovieClip;
		
		
		private var isDebugTest:Boolean = false;
		
		override protected function configUI():void
		{
			super.configUI();
			TenSecCountDown_mc.visible = false;
			
			if(isDebugTest){
				//UCSetExitTimeLeft(5);
				//UCShowBattleResultMovie(false);
				//UCShowBattleWinMovie();
				UCShowBattleLoseMovie(5);
			//	PlayTenSecCountDown(5);
			}
			
		}
		//
		public function TenSecCountDownEnd()
		{
			TenSecCountDown_mc.stop();
			TenSecCountDown_mc.visible = false;
			
			ExternalInterface.call( "ASBeforeFightTenSecCountDownEnd");
		}
		//
		public function PlayTenSecCountDown($timeSec:int = FIGHTING_COUNT_DOWN_TIME)
		{
			if($timeSec > FIGHTING_COUNT_DOWN_TIME)
			{
				var delay:int = $timeSec - FIGHTING_COUNT_DOWN_TIME;
				var delayTimeOut:int = setTimeout(function(){
					clearTimeout(delayTimeOut);
					playCountDownAnimation(FIGHTING_COUNT_DOWN_TIME);
				}, delay * 1000);
			}else{
				playCountDownAnimation($timeSec);
			}
			
			function playCountDownAnimation($timeSec):void
			{
				if($timeSec >= 0 && $timeSec <= FIGHTING_COUNT_DOWN_TIME){
					TenSecCountDown_mc.visible = true;
					TenSecCountDown_mc.gotoAndPlay( 2 + 30 * (FIGHTING_COUNT_DOWN_TIME - $timeSec));
				}
			}
		}
		
		
		//===================================================================================================================
		public function UCShowBattleWinMovie():void
		{
			arena_result_movie.showResultMovie( true );
		}
		//===================================================================================================================
		public function UCShowBattleLoseMovie($exitTime:int):void
		{
			arena_result_movie.exitTimeLeft = $exitTime;
			arena_result_movie.showResultMovie( false );
		}
		//===================================================================================================================
		public function UCSetExitTimeLeft($exitTime:int):void
		{
			arena_result_movie.exitTimeLeft = $exitTime;
		}
		//===================================================================================================================
		public function UCShowBattleResultMovie(isWin:Boolean):void
		{
			arena_result_movie.showResultMovie(isWin);
		}
	}
}