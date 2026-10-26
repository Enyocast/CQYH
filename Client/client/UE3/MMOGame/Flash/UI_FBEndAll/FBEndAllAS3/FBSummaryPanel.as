package UI_FBEndAll.FBEndAllAS3
{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import UI_FBEndAll.FBEndAllAS3.FBAchievementsContainer;
	//import UI_FBEndAll.FBEndAllAS3.FBAchievement;
	
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import flash.external.ExternalInterface;
	
	
	public class FBSummaryPanel extends MyPanel
	{
		//
		public var closeTimeLeft:Number = 5000;
		public var timerCountDown:Timer = new Timer(500);
		static var BAR_TIME_MAX:Number = 1000;
		public var barTimeLeft:Number = BAR_TIME_MAX;
		public var barTimerCountDown:Timer = new Timer(33);
		//
		public var iCurExp:int 			= 100;
		static var SUM_RANK:int 		= 0;//总评分
		static var TIME_RANK:int 		= 1;//通关时间评分
		static var SKILL_RANK:int 		= 2;//技能评分
		static var ACHIVEMENT_RANK:int 	= 3;//成就评分
		
		public var bt_skip:Button;
		//总评分
		public var sumRank_mc:MovieClip;
		//通关时间
		public var titleTime_mc:MovieClip;//评分
		public var detailScore0_mc:MovieClip;
		//击杀技巧
		public var titleKill_mc:MovieClip;//评分
		public var detailScore1_mc:MovieClip;
		public var detailScore2_mc:MovieClip;
		public var detailScore3_mc:MovieClip;
		//成就
		public var titleAchivement_mc:MovieClip;//评分
		public var achivementDetail_mc:FBAchievementsContainer;
		//综合评分
		public var scoreABCS_mc:MovieClip;
		//评分经验
		public var GradedExp_mc:MovieClip;
		//额外加成
		public var extraScore0_mc:MovieClip;
		public var extraScore1_mc:MovieClip;
		public var extraScore2_mc:MovieClip;
		public var extraScore3_mc:MovieClip;
		public var extraScore4_mc:MovieClip;
		//经验总加成
		public var expGet_mc:MovieClip;
		//玩家头像
		public var tf_PlayerName:TextField;
		//玩家等级
		public var tf_PlayerLevel:TextField;
		//经验条
		public var ExpBarTitle_mc:MovieClip;
		public var ExpBar_mc:MovieClip;
		public var ExpBarRealWidth:int;
		
		override protected function configUI():void
		{
			super.configUI();
			//
			//ShowMode = "TC";
			//
			scoreABCS_mc.score_mc.visible = false;
			scoreABCS_mc.scoreSS_mc.visible = false;
			scoreABCS_mc.scoreSSS_mc.visible = false;
			
			ExpBarTitle_mc.visible = false;
			ExpBar_mc.visible = false;
			ExpBarRealWidth = ExpBar_mc.width - 2 * 7;//减去两头空挡
			//add component events
			timerCountDown.addEventListener(TimerEvent.TIMER, CloseTimerHandle);
			barTimerCountDown.addEventListener(TimerEvent.TIMER, BarTimerHandle);
			//bt_skip.addEventListener( "click", Skip );
			SetCurExpPercent(100);
			//
			ExternalInterface.call( "RegisterFBSummary", this );
		}
		//设置评级
		public function SetFBRank( type:int, rank:int )
		{
			var rankDisply_mc:MovieClip;
			var parent_mc:MovieClip;

			if( type != SUM_RANK ){
				switch( type )
				{
					case TIME_RANK:
					parent_mc = titleTime_mc.getChildByName("Score_Anim_mc") as MovieClip;
					break;
					case SKILL_RANK:
					parent_mc = titleKill_mc.getChildByName("Score_Anim_mc") as MovieClip;
					break;
					case ACHIVEMENT_RANK:
					parent_mc = titleAchivement_mc.getChildByName("Score_Anim_mc") as MovieClip;
					break;
				}
				rankDisply_mc = parent_mc.getChildByName("score_mc") as MovieClip;
				rankDisply_mc.gotoAndStop( rank );
				//parent_mc.gotoAndPlay( 1 );
			}
			else{
				switch( rank )
				{
					case 1://c
					case 2://b
					case 3://a
					case 4://s
					scoreABCS_mc.score_mc.visible = true;
					scoreABCS_mc.scoreSS_mc.visible = false;
					scoreABCS_mc.scoreSSS_mc.visible = false;
					scoreABCS_mc.score_mc.score_mc.gotoAndStop( rank );
					break;
					case 5://ss
					scoreABCS_mc.score_mc.visible = false;
					scoreABCS_mc.scoreSS_mc.visible = true;
					scoreABCS_mc.scoreSSS_mc.visible = false;
					scoreABCS_mc.scoreSS_mc.score_mc.gotoAndStop(4);
					scoreABCS_mc.scoreSS_mc.score1_mc.gotoAndStop(4);
					break;
					case 6://sss
					scoreABCS_mc.score_mc.visible = false;
					scoreABCS_mc.scoreSS_mc.visible = false;
					scoreABCS_mc.scoreSSS_mc.visible = true;
					scoreABCS_mc.scoreSSS_mc.score_mc.gotoAndStop(4);
					break;
					default:
					scoreABCS_mc.score_mc.visible = false;
					scoreABCS_mc.scoreSS_mc.visible = false;
					scoreABCS_mc.scoreSSS_mc.visible = false;
					break;
				}
				//rankDisply_mc = scoreABCS_mc.getChildByName("score_mc") as MovieClip;
				//rankDisply_mc.gotoAndPlay(1);
			}
		}
		//close countdown
		public function StartCloseCountDown( time:int )
		{
			closeTimeLeft = time;
			timerCountDown.start();
		}
		function CloseTimerHandle( e:Event )
		{
			closeTimeLeft = closeTimeLeft - 500;
			if (closeTimeLeft <= 0 )
			{
				closeTimeLeft = 0;
				timerCountDown.stop();
				TimeUp();
			}
			//ExternalInterface.call( "ASTrace", visible );
		}
		public function TimeUp()
		{
			visible = false;
			ExternalInterface.call( "NextToPlayFBAward" );
		}
		//bt_skip click funtion
		public function Skip()
		{
			visible = false;
			ExternalInterface.call( "OpenFBAward" );
		}
		//start exp bar animation
		public function StartShowExpBar()
		{
			ExpBarTitle_mc.visible = true;
			ExpBar_mc.visible = true;
			//
			if (barTimeLeft > 0 )
			{
				barTimerCountDown.stop();
			}
			barTimeLeft = BAR_TIME_MAX;
			ExpBar_mc.maskMc.width = 0;
			//( ExpBar_mc.getChildByName( "mask" ) as MovieClip ).SetDivide( 0, BAR_TIME_MAX );
			barTimerCountDown.start();
		}
		function BarTimerHandle( e:Event )
		{
			barTimeLeft = barTimeLeft - 33;
			if (barTimeLeft <= 0 )
			{
				barTimeLeft = 0;
				barTimerCountDown.stop();
			}
			ExpBar_mc.maskMc.width = (BAR_TIME_MAX - barTimeLeft) * iCurExp / BAR_TIME_MAX;
			//( ExpBar_mc.getChildByName( "mask" ) as MovieClip ).SetDivide( BAR_TIME_MAX - barTimeLeft, BAR_TIME_MAX );
		}
		//set experience bar width
		public function SetCurExpPercent( iPercent:int )
		{
			iCurExp = ExpBarRealWidth * iPercent / 100;
		}
		//-------------------------------------------------------------------------------------------------------------------
		public function SetFBAchievement( idx:int, titleName:String, desc:String, achievementType:int ):void
		{
			if( achivementDetail_mc == null ){
				return;
			}
			achivementDetail_mc.SetFBAchievement( idx, titleName, desc, achievementType );
		}
		//-------------------------------------------------------------------------------------------------------------------
		/*//播放评分细项的特效
		public function DisplayScoreShowEft( mc:MovieClip )
		{
			( mc.getChildByName( "hintGlow_mc") as MovieClip ).gotoAndPlay(1);
		}
		*/
	}
}