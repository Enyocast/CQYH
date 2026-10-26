package UI_FBEndAll.FBEndAllAS3
{
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import flash.display.MovieClip;
	
	//import ActionScript3.ItemSlot.IconSlot;
	import scaleform.clik.controls.Button;
	import ActionScript3.LinkShowButton;
	
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.events.TimerEvent;
	
	import flash.utils.Timer;
	import flash.external.ExternalInterface;
	
	
	public class FBAwardPanel extends MyPanel
	{
		//
		public var myPortrait_mc:Button;
		//
		public var FBGetAwardBtn1:LinkShowButton;
		public var FBGetAwardBtn2:LinkShowButton;
		public var FBGetAwardBtn3:LinkShowButton;
		
		public var AwardsBox1:MovieClip;
		public var AwardsBox2:MovieClip;
		public var AwardsBox3:MovieClip;
		
		//
		public var awardItemAni1_mc:MovieClip;
		public var awardItemAni2_mc:MovieClip;
		public var awardItemAni3_mc:MovieClip;
		
		//
		public var AwardHintTf1:TextField;
		public var AwardHintTf2:TextField;
		public var AwardHintTf3:TextField;
		
		//
		public var memberInfoMc:MovieClip;
		//public var tf_leftTime:TextField;
		static var PLAY_TIME_MAX:Number = 10000;//10秒
		public var PlayTimeLeft:Number = PLAY_TIME_MAX;
		public var timerCountDown:Timer = new Timer(500);
		
		override protected function configUI():void
		{
			super.configUI();
			
			//ShowMode = "TC";
			
			//add component events
			timerCountDown.addEventListener(TimerEvent.TIMER, OverTimerHandle);
			//
			FBGetAwardBtn1.addEventListener( MouseEvent.CLICK, function _ChangeDifficulty(e:Event){ clickAward(e,0);} );
			FBGetAwardBtn2.addEventListener( MouseEvent.CLICK, function _ChangeDifficulty(e:Event){ clickAward(e,1);} );
			FBGetAwardBtn3.addEventListener( MouseEvent.CLICK, function _ChangeDifficulty(e:Event){ clickAward(e,2);} );
			
			FBGetAwardBtn1.ShowMovieClip = AwardsBox1;
			FBGetAwardBtn2.ShowMovieClip = AwardsBox2;
			FBGetAwardBtn3.ShowMovieClip = AwardsBox3;
			
			/*
			var awardItemSlot:IconSlot;
			awardItemSlot = awardItemAni1_mc.getChildByName( "AnimSlotShow_mc" ) as IconSlot;
			awardItemSlot.SetData( 1, 1, "", "奖品" );
			
			awardItemSlot = awardItemAni2_mc.getChildByName( "AnimSlotShow_mc" ) as IconSlot;
			awardItemSlot.SetData( 1, 1, "", "奖品" );
			
			awardItemSlot = awardItemAni3_mc.getChildByName( "AnimSlotShow_mc" ) as IconSlot;
			awardItemSlot.SetData( 1, 1, "", "奖品" );
			*/
			
			//
			//closeBtn_mc.label = "退出界面";
			//closeBtn_mc.addEventListener( "click", NextToFBExit );
			//
			//backFBSummaryBtn_mc.label = "查看评分";
			//backFBSummaryBtn_mc.addEventListener( "click", BackToClick );
			//
			ExternalInterface.call( "RegisterFBAward", this );
		}
		//
		function clickAward( e:Event, idx:int )
		{
			ExternalInterface.call( "GetFBAward", idx );
			/*
			//test
			var awardItem:MovieClip;
			switch( idx )
			{
				case 0:
				awardItem = awardItemAni1_mc as MovieClip;
				bt_myAwards1.enabled = false;
				break;
				
				case 1:
				awardItem = awardItemAni2_mc as MovieClip;
				bt_myAwards2.enabled = false;
				break;
				
				case 2:
				awardItem = awardItemAni3_mc as MovieClip;
				bt_myAwards3.enabled = false;
				break;
			}
			//
			if( awardItem != null ){
				awardItem.visible = true;
				awardItem.gotoAndPlay(1);
				var awardItemSlot:IconSlot = awardItem.getChildByName( "AnimSlotShow_mc" ) as IconSlot;
				awardItemSlot.SetData( 1, 1, "0.TGA", "奖品"+idx );
			}
			*/
		}
		//play countdown
		public function StartPlayCountDown( time:int )
		{
			//
			PlayTimeLeft = time;
			timerCountDown.start();
			//
			//tf_leftTime.text = PlayTimeLeft + "秒";
		}
		function OverTimerHandle( e:Event )
		{
			PlayTimeLeft = PlayTimeLeft - 500;
			if( PlayTimeLeft <= 0 )
			{
				PlayTimeLeft = 0;
				timerCountDown.stop();
				PlayTimeUp();
			}
			//
			//tf_leftTime.text = PlayTimeLeft + "秒";
			//ExternalInterface.call( "ASTrace", visible );
		}
		public function PlayTimeUp()
		{
			ExternalInterface.call( "FBAwardPlayTimeOver" );
		}
		//btn
		public function NextToFBExit()
		{
			ExternalInterface.call( "OpenFBBattleComfirm" );
			visible = false;
		}
		public function BackToClick()
		{
			ExternalInterface.call( "OpenFBSummary" );
			visible = false;
		}
	}
}