package UI_PVP_Bonus.AS3
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
	
	public class BattleTips extends UIComponent
	{
		public var txt_time_left:TextField;
		public var txt_record:TextField;
		public var txt_progress:TextField;
		public var fighting_btn:Button;
		public var result_movie_mc:MovieClip;
		
		protected var _countDownTimer:Timer = new Timer(1000);
		//second
		protected var _battleTimeLeft:int;
		protected var _fightTimeLeft:int;
		protected var _exitTimeLeft:int;
		
		protected var _progressText:String;
		
		protected var _movie_all:MovieClip;
		protected var _exitTimeText:TextField;
		
		private var isDebugTest:Boolean = false;
		public function BattleTips()
		{
			super();
		}
		
		override protected function configUI():void
		{
			// TODO Auto Generated method stub
			super.configUI();
			_countDownTimer.addEventListener(TimerEvent.TIMER, onCountDown);
			fighting_btn.addEventListener(MouseEvent.CLICK, onFightingButtonClick);
			result_movie_mc.visible = false;
			this.visible = false;
			
			ExternalInterface.call( "RegisterArenaState", this );
			
			if( isDebugTest )
			{
				visible = true;
				UCSetBattleTimeLeftText(300);
				UCSetTipsRecordText("您目前战绩  一连胜");
				UCSetProgressText("");
				UCSetFightButton('寻找对手', true);
			}
		}
		
		protected function onFightingButtonClick(event:MouseEvent):void
		{
			ExternalInterface.call("ASOnFightingButtonClick");
			//test
			if( isDebugTest )
			{
				UCSetTipsRecordText("您目前战绩  六连胜");
				UCSetProgressText("正在比赛",  65);
				UCSetFightButton('', false);
				
				/*
				updateProgressText('正在寻找对手...');
				fighting_btn.visible = false;
				setTimeout(function(){
						   updateProgressText("正在比赛中", 119);
						   setTimeout(function(){
									  showResultMovie(false);
									  },3000);
									  },
									  2000);
									  */
			}

		}
		
		protected function onCountDown(event:TimerEvent):void
		{
			if(_battleTimeLeft == 0 && _fightTimeLeft == 0 && _exitTimeLeft == 0){
				_countDownTimer.stop();
			}
			if(_battleTimeLeft > 0){
				_battleTimeLeft--;
				txt_time_left.text = formatTimeString(_battleTimeLeft);
			}
			if(_fightTimeLeft > 0){
				_fightTimeLeft--;
				txt_progress.text = _progressText + "  " + formatTimeString(_fightTimeLeft);
			}
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
		}
		
		protected function formatTimeString(timeSec:int):String
		{
			if(timeSec >= 0){
				var h:int = timeSec / 3600;
				var left:int = timeSec % 3600;
				var m:int = left / 60;
				var s:int = left % 60
			}
			var result:String = "";
			if(h > 0){
				result += ((100 + h).toString()).substring(1) + ":";
			}
			result += ((100 + m).toString()).substring(1) + ":";
			result += ((100 + s).toString()).substring(1);
			return result;
		}
		
		public function updateFightingButton(lableStr:String = "", $visible:Boolean = false):void
		{
			fighting_btn.label = lableStr;
			fighting_btn.visible = $visible;
		}
		
		public function showResultMovie(isWin:Boolean):void
		{
			if(!isWin){
				if(!_countDownTimer.running){
					_countDownTimer.start();
				}
				//todo set by UC
				_exitTimeLeft = 5;
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
		
		public function updateTimeLeftText($leftTime:int):void
		{
			//txt_time_left.text = $leftSecText;
			_battleTimeLeft = $leftTime;
			txt_time_left.text = formatTimeString(_battleTimeLeft);
			if(_battleTimeLeft > 0 && !_countDownTimer.running){
				_countDownTimer.start();
			}
		}
		
		public function updateRecordText($recordText:String):void
		{
			txt_record.htmlText = $recordText;
		}
		
		public function updateProgressText($progressText:String, $fightTimeLeft:int = -1):void
		{
			_progressText	 = $progressText;
			_fightTimeLeft = $fightTimeLeft;
			if(_fightTimeLeft > 0){
				if(!_countDownTimer.running){
					_countDownTimer.start();
				}
			}else{
				txt_progress.text = $progressText;
			}
		}
		
		//===================================================================================================================
		public function UCSetBattleTimeLeftText($leftTime:int):void
		{
			updateTimeLeftText($leftTime);
		}
		
		//===================================================================================================================
		public function UCSetTipsRecordText($recordText:String):void
		{
			updateRecordText($recordText);
		}
		
		//===================================================================================================================
		public function UCSetProgressText($progressText:String, fightTimeLeft:int = -1):void
		{
			updateProgressText($progressText, fightTimeLeft);
		}
		
		//===================================================================================================================
		public function UCSetFightButton(lableStr:String = "", $visible:Boolean = false):void
		{
			updateFightingButton(lableStr, $visible);
		}
		
		//===================================================================================================================
		public function UCShowBattleResultMovie(isWin:Boolean):void
		{
			showResultMovie(isWin);
		}
	}
}