package UI_FBEndAll.FBEndAllAS3
{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import flash.utils.getTimer;
	
	public class FBBattleComfirmPanel extends MyPanel
	{
		public var tF_timeCounter:TextField;
		//public var bt_playAgain:Button;
		//
		public var bt_backFBSummary:Button;
		public var bt_closeFBui:Button;
		//public var bt_backFBAward:Button;
		public var bt_leave:Button;
		
		//
		var bUIOpened:Boolean;
		static var MAX_LEAVE_TIME:uint = 120000;
		//public var timeLeft:Number = MAX_LEAVE_TIME;
		public var timerCountDown:Timer = new Timer(1000);
		
		public var BeginTime:uint;
		public var CurTime:uint;
		public var TotalTimeInMiniSec:uint = MAX_LEAVE_TIME;
		var IsInitTime:Boolean = false;
		
		override protected function configUI():void
		{
			super.configUI();
			//
			//bt_playAgain.label = "再次挑战副本";
			//bt_playAgain.addEventListener( "click", PlayAgain );
			//
			bt_leave.label = "离开副本";
			bt_leave.addEventListener( "click", LeaveFB );
			//
			bt_backFBSummary.label = "查看副本评价";
			bt_backFBSummary.addEventListener( "click", BackToSummary );
			bt_backFBSummary.visible = false;
			//bt_backFBAward.label = "查看副本抽奖";
			//bt_backFBAward.addEventListener( "click", BackToAward );
			//bt_backFBAward.visible = !bt_backFBSummary.visible;
			//
			//bt_closeFBui.label = "关闭抽奖界面";
			//bt_closeFBui.addEventListener( "click", CloseFBui );
			bt_closeFBui.label = "隐藏副本评价";
			bt_closeFBui.addEventListener( "click", HideFBui );
			bt_closeFBui.visible = true;
			//
			bUIOpened = true;
			IsInitTime = false;
			//
			ExternalInterface.call( "RegisterFBBattleComfirm", this );
		}
		//
		public function StartCloseCountDown( LeftTime:int )
		{
			TotalTimeInMiniSec = LeftTime;
			
			BeginTime = getTimer();
			CurTime = BeginTime;
			
			tF_timeCounter.text = (int)( (TotalTimeInMiniSec + 999 ) / 1000 ) + "秒";
			
			if( !IsInitTime ){
				IsInitTime = true;
				timerCountDown.addEventListener(TimerEvent.TIMER, timerHandle);
			}
			timerCountDown.start();
		}
		//
		function timerHandle()
		{
			CurTime = getTimer();
			var leftTime:int = (Number)( TotalTimeInMiniSec - CurTime + BeginTime + 999 ) / 1000;
			
			if (leftTime <= 0 )
			{
				leftTime = 0;
				StopAndHideFB();
				//LeaveFB();
			}
			
			tF_timeCounter.text = leftTime + "秒";
		}
		//
		function PlayAgain()
		{
			ExternalInterface.call( "WantPlayFbAgain" );
		}
		// leave this script
		function LeaveFB()
		{
			ExternalInterface.call( "LeaveFB" );
		}
		public function StopAndHideFB()
		{
			timerCountDown.stop();
			visible = false;
		}
		// back to the battle summary UI
		function BackToSummary()
		{
			//ToggleSummaryAndAward();
			ExternalInterface.call( "HideFBAward" );
			ExternalInterface.call( "ReviewFBSummary" );
			bUIOpened = true;
			//bt_closeFBui.visible = bUIOpened;
			bt_backFBSummary.visible = false;
		}
		function HideFBui()
		{
			ExternalInterface.call( "HideFBAward" );
			ExternalInterface.call( "HideFBSummary" );
			bUIOpened = false;
			bt_closeFBui.visible = bUIOpened;
			bt_backFBSummary.visible = true;
		}
		/*
		function BackToAward()
		{
			ToggleSummaryAndAward();
			ExternalInterface.call( "HideFBSummary" );
			ExternalInterface.call( "OpenFBAward" );
			bUIOpened = true;
		}
		function ToggleSummaryAndAward()
		{
			bt_backFBSummary.visible = !bt_backFBSummary.visible;
			bt_backFBAward.visible = !bt_backFBAward.visible;
			if( bt_backFBSummary.visible ){
				bt_closeFBui.label = "关闭抽奖界面";
			}
			//
			if( bt_backFBAward.visible ){
				bt_closeFBui.label = "关闭评分界面";
			}
		}
		function CloseFBui()
		{
			if( bt_backFBSummary.visible ){
				if( bUIOpened ){
					ExternalInterface.call( "HideFBAward" );
					bt_closeFBui.label = "打开抽奖界面";
				}
				else{
					ExternalInterface.call( "OpenFBAward" );
					bt_closeFBui.label = "关闭抽奖界面";
				}
			}
			//
			if( bt_backFBAward.visible ){
				if( bUIOpened ){
					ExternalInterface.call( "HideFBSummary" );
					bt_closeFBui.label = "打开评分界面";
				}
				else{
					ExternalInterface.call( "OpenFBSummary" );
					bt_closeFBui.label = "关闭评分界面";
				}
			}
			//
			bUIOpened = !bUIOpened;
		}
		*/
	}
}

