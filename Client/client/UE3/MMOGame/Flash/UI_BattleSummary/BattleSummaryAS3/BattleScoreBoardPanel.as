package UI_BattleSummary.BattleSummaryAS3
{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.display.MovieClip;
	//import ActionScript3.MyPanel;
	import scaleform.clik.core.UIComponent
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import ActionScript3.NumUi;
	
	import flash.utils.getTimer;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	public class BattleScoreBoardPanel extends UIComponent
	{
		//my team score
		public var TeamScore_mc2:NumUi;
		//other team 1 score
		public var TeamScore_mc1:NumUi;
		//battle summary button
		public var BattleSummary_btn:Button;
		//battle time
		public var BattleTime_mc:MovieClip;
		const TimeFrame:Number = 500;//时间侦听间隔
		var TimerCountDown:Timer = new Timer(TimeFrame);
		var TotalTimeInMiniSec:uint = 0;
		//public var testTeamID:int;
		//public var testScore:int;
		
		public var BeginTime:uint;
		public var CurTime:uint;
		public var TotalSecond:uint;
		public var IsInitTime:Boolean = false;
		
		override protected function configUI():void
		{
			super.configUI();
			//
			ExternalInterface.call( "RegisterBattleScoreBoard", this );
			//
			BattleSummary_btn.addEventListener( "click", onClickBattleSummaryBtn );
			//
			BattleTime_mc.visible = false;
			IsInitTime = false;

			//UCBeginTime( 120 );
			//
			TeamScore_mc2.Init( 6, 17, false );
			TeamScore_mc1.Init( 6, 17, true );
			
			//test
			//UCSetScore( 2, 2 );
			//UCSetScore( 1, 4 );
		}
		//
		function onClickBattleSummaryBtn( e:Event ):void
		{
			ExternalInterface.call( "ToggleBattleSummary" );
			//var testMc = parent.getChildByName( "FightingScreenHint_mc" ) as FightingScreenHint;
			//testMc.TenSecCountDown_mc.visible = true;
			//testMc.TenSecCountDown_mc.gotoAndPlay( 2 );
			//testTeamID += 1;
			//testScore += 1;
			//trace( "team : ", testTeamID%2+1 );
			//UCSetScore( testTeamID%2+1, testScore );
		}
		//
		public function UCSetScore( teamIdx:int, score:int ):void
		{
			if( teamIdx == 2 ){
				TeamScore_mc2.SetNumber( score );
			}
			else{
				TeamScore_mc1.SetNumber( score );
			}
		}
		//=======================================================================================================
		public function UCBeginTime( allTimeInSecond:uint )
		{
			if( IsInitTime ){
				//正在倒计时
				TimerCountDown.removeEventListener(TimerEvent.TIMER, BattleTimeCountDownHandle);
				TimerCountDown.stop();
			}
			//
			IsInitTime = true;
			//
			TotalTimeInMiniSec = allTimeInSecond * 1000;
			TimerCountDown.addEventListener(TimerEvent.TIMER, BattleTimeCountDownHandle);
			BeginTime = getTimer();
			CurTime = BeginTime;
			//
			TimerCountDown.start();
			//
			var minute:uint = (uint)( allTimeInSecond / 60 );
			BattleTime_mc.minute_mc.text = ( minute < 10 ? "0"+minute : minute );
			
			var second:uint = (uint)( allTimeInSecond % 60 );
			BattleTime_mc.second_mc.text = ( second < 10 ? "0"+second : second );
			
			BattleTime_mc.visible = true;
		}
		//-------------------------------------------------------------------------------------------------------------
		public function UCForceStopBattleTime()
		{
			StopBattleTime();
			//BattleTime_mc.visible = false;
		}
		//-------------------------------------------------------------------------------------------------------------
		public function StopBattleTime()
		{
			if( IsInitTime ){
				TimerCountDown.stop();
				TimerCountDown.removeEventListener(TimerEvent.TIMER, BattleTimeCountDownHandle);
				//
				IsInitTime = false;
			}
			//
			TotalTimeInMiniSec = 0;
		}
		//--------------------------------------------------------------------------------------------------------------
		function BattleTimeCountDownHandle( e:TimerEvent )
		{
			CurTime = getTimer();
			//var DeltaTime:Number = (Number)( CurTime - BeginTime ) / 1000;
			var leftTime:int = (int)( TotalTimeInMiniSec - CurTime + BeginTime + 999 ) / 1000;
			//trace( "DeltaTime : ", DeltaTime, (uint)( DeltaTime / 60 ), (uint)( DeltaTime % 60 ) );
			
			if( leftTime <= 0 ){
				StopBattleTime();
				//
				ExternalInterface.call( "ASNotifyBattleTimesUp" );
				//
				leftTime = 0;
			}
			
			var minute:uint = (uint)( leftTime / 60 );
			BattleTime_mc.minute_mc.text = ( minute < 10 ? "0"+minute : minute );
			
			var second:uint = (uint)( leftTime % 60 );
			BattleTime_mc.second_mc.text = ( second < 10 ? "0"+second : second );
		}

	}
}