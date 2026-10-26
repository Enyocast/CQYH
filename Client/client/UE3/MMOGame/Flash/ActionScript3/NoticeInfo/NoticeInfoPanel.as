package ActionScript3.NoticeInfo
{
	import ActionScript3.MyActivePanel;
	import scaleform.clik.controls.Button;
	//import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.display.MovieClip;
	import flash.text.TextField;

	import scaleform.clik.motion.Tween;
	import ActionScript3.MyPanel;
	import fl.motion.easing.Linear;
	import flash.external.ExternalInterface;
	import scaleform.clik.events.ButtonEvent;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import scaleform.clik.managers.PopUpManager;
	import scaleform.clik.core.UIComponent;

	public class NoticeInfoPanel extends MyPanel
	{
		public var MarqueeNotice:MovieClip;
		var MarqueeNoticeArray:Array;
		var MarqueeTextField:TextField;

		public var RollingNotice0:MovieClip;
		public var RollingNotice1:MovieClip;
		var RollingNoticeTextField0:TextField;
		var RollingNoticeTextField1:TextField;
		var RollingTween0;
		var RollingTween1;

		var NewRolling:int = 0;
		var RollingOriY0:int;
		var RollingOriY1:int;

		//public var TestBtn:Button;
		public var marquee_bg:MovieClip;

		const NoticeZoneWidth:int = 610;
/*		static var count:int = 0;
		function OnTest()
		{

			//AddRollingNoticeInfo( "翻动公告翻动公告翻动公告翻动公告翻动公告"+count , "#0000ff" );
			//AddMarqueeNoticeInfo("公告很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长",5000,3,"#ff00ff");
			count++;
		}*/

		override protected function configUI():void
		{
			super.configUI();
            this.mouseChildren=false;
			this.mouseEnabled=false;
			this.enabled=false;
			if (MarqueeNotice)
			{
				MarqueeTextField = MarqueeNotice.getChildByName("textField_Notice") as TextField;
				MarqueeNotice.visible = false;
			}
			
			if(marquee_bg)
			{
				marquee_bg.visible = false;
			}

			if (RollingNotice0)
			{
				RollingNotice0.visible = false;
				RollingNoticeTextField0 = RollingNotice0.getChildByName("textField_Notice") as TextField;
				RollingOriY0 = RollingNotice0.y;
			}
			if (RollingNotice1)
			{
				RollingNotice1.visible = false;
				RollingNoticeTextField1 = RollingNotice1.getChildByName("textField_Notice") as TextField;
				RollingOriY1 = RollingNotice1.y;
			}

			MarqueeNoticeArray = new Array  ;

			RollingTween0 = new Tween(8000,RollingNoticeTextField0,{alpha:0},{paused:true,ease:Linear.easeNone,onComplete:CompleteRolling0,loop:false});
			RollingTween1 = new Tween(8000,RollingNoticeTextField1,{alpha:0},{paused:true,ease:Linear.easeNone,onComplete:CompleteRolling1,loop:false});


			stageChangeHandler(null);
			
			//AddMarqueeNoticeInfo("公告2",50,1,"#00ffff");
			//AddMarqueeNoticeInfo("公告很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长",50,1000000,"#ff00ff");
			//AddRollingNoticeInfo( "翻动公告翻动公告翻动公告翻动公告翻动公告" , "#FFF468" );

		}

		public function AddMarqueeNoticeInfo( notice:String , movieSpeed:int , repeatTimes:int , color:String ):void
		{
			var isCurrentPlaying:Boolean = ( MarqueeNoticeArray.length > 0 );
			MarqueeNoticeArray.push( { Notice:notice , MovieSpeed:movieSpeed , RepeatTimes:repeatTimes , Color:color } );
			if (!isCurrentPlaying)
			{
				StartNewTween();
			}

		}

		public function AddRollingNoticeInfo( notice:String , color:String ):void
		{
			if ( NewRolling == 0 )
			{
				AddRollingNotice( 1 , notice , color );
			}
			else if ( NewRolling == 1 )
			{
				AddRollingNotice( 0 , notice , color );
			}


		}

		private function AddRollingNotice( idx:int , notice:String , color:String ):void
		{

			if ( idx == 0 )
			{
				if (RollingNoticeTextField0)
				{
					RollingNoticeTextField0.htmlText = "<font color='" + color + "'>" + notice + "</font>";
				}

				if ( RollingNotice0 && RollingNoticeTextField0 )
				{
					RollingNotice0.visible = true;
					RollingNoticeTextField0.alpha = 1;

					RollingTween0.paused = false;
					RollingTween0.reset();

					RollingNotice0.y = RollingOriY0;
					RollingNotice1.y = RollingOriY1;
				}

				NewRolling = 0;

			}
			else if ( idx == 1 )
			{
				if (RollingNoticeTextField1)
				{
					RollingNoticeTextField1.htmlText = "<font color='" + color + "'>" + notice + "</font>";
				}

				if (RollingNotice1&&RollingNoticeTextField1)
				{
					RollingNotice1.visible = true;
					RollingNoticeTextField1.alpha = 1;

					RollingTween1.paused = false;
					RollingTween1.reset();
					RollingNotice1.y = RollingOriY0;
					RollingNotice0.y = RollingOriY1;
				}

				NewRolling = 1;
			}
		}

		private function CompleteRolling0():void
		{
			RollingNotice0.visible = false;
		}

		private function CompleteRolling1():void
		{
			RollingNotice1.visible = false;
		}

		private function CompleteTween():void
		{
			if (MarqueeNoticeArray.length == 0)
			{
				return;
			}

			MarqueeNoticeArray[0].RepeatTimes--;

			if (MarqueeNoticeArray[0].RepeatTimes <= 0)
			{
				MarqueeNoticeArray.shift();
				if (MarqueeNoticeArray.length != 0)
				{
					StartNewTween();
				}
				else
				{
					//end
					MarqueeNotice.visible = false;
					if( marquee_bg )
					marquee_bg.visible = false;
				}
			}
			else
			{
				StartNewTween();
			}


		}

		private function StartNewTween():void
		{
			MarqueeNotice.visible = true;
			if( marquee_bg )
				marquee_bg.visible = true;
			
			MarqueeTextField.htmlText ="";
			MarqueeTextField.htmlText = "<font color='" + MarqueeNoticeArray[0].Color + "'>" + MarqueeNoticeArray[0].Notice + "</font>";
			MarqueeTextField.x = -MarqueeTextField.textWidth / 2;

			MarqueeTextField.width = MarqueeTextField.textWidth;
			MarqueeNotice.x = ( MarqueeTextField.width + NoticeZoneWidth ) / 2;
			var speed:Number = ( MarqueeNoticeArray[0].MovieSpeed > 0 ? MarqueeNoticeArray[0].MovieSpeed : 50 )
			var moveTimeTotal:int = ( 2 * MarqueeNotice.x ) * 1000 / speed + 1000;

			var buttonTween:Tween = new Tween(moveTimeTotal, MarqueeNotice,{x: -MarqueeNotice.x },{paused:false,ease:Linear.easeNone,onComplete:CompleteTween,loop:false});

		}
		
        override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=(cavasWidth-610>>1)+305;
		}

	}
}