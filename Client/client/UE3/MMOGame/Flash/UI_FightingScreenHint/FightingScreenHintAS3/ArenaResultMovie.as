package UI_FightingScreenHint.FightingScreenHintAS3
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.Timer;
	import flash.utils.setInterval;
	import flash.utils.setTimeout;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	
	public class ArenaResultMovie extends UIComponent
	{
		private static const WIN_ANIMATION_DELAY_TIME:int = 2;
		public var result_movie_mc:MovieClip;
		
		protected var _countDownTimer:Timer = new Timer(1000);
		//second
		protected var _exitTimeLeft:int;
		protected var _movie_all:MovieClip;
		protected var _exitTimeText:TextField;
		
		public function ArenaResultMovie()
		{
			super();
		}
		
		public function set exitTimeLeft(value:int):void
		{
			_exitTimeLeft = value;
		}

		override protected function configUI():void
		{
			// TODO Auto Generated method stub
			super.configUI();
			_countDownTimer.addEventListener(TimerEvent.TIMER, onCountDown);
			this.visible = false;
		}
		
		protected function onCountDown(event:TimerEvent):void
		{
			if(_exitTimeLeft > 0){
				_exitTimeLeft--;
				_movie_all = result_movie_mc.getChildByName('movie_all') as MovieClip;
				if(_movie_all != null){
					_exitTimeText = _movie_all.getChildByName('txt_time_left') as TextField;
					if(_exitTimeText != null){
						_exitTimeText.text = _exitTimeLeft.toString();
					}
				}
			}
			
			if(_exitTimeLeft == 0){
				_countDownTimer.stop();
				ExternalInterface.call("ASOnExitCountDownTimeOver");
				result_movie_mc.visible = false;
			}
		}
		
		public function showResultMovie(isWin:Boolean):void
		{
			this.visible = true;
			if(isWin){
				_exitTimeLeft = WIN_ANIMATION_DELAY_TIME;
			}
			if(!_countDownTimer.running){
				_countDownTimer.start();
			}
			_movie_all = result_movie_mc.getChildByName('movie_all') as MovieClip;
			if(_movie_all){
				_movie_all.gotoAndStop(isWin?'win':'lose');
				_exitTimeText = _movie_all.getChildByName('txt_time_left') as TextField;
				if(_exitTimeText != null){
					_exitTimeText.text = _exitTimeLeft.toString();
				}
			}
			result_movie_mc.gotoAndPlay(1);
			result_movie_mc.visible = true;
		}
	}
}