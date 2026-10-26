package UI_SkillTree.SkillTreeAS3
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.sampler.Sample;
	import flash.text.TextField;
	import flash.utils.Timer;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataBinding;
	import scaleform.clik.events.ButtonEvent;

	public class HeavenMainPanel extends UIComponent
	{
		private const FX_TYPE_TO_LABEL:Array = ['yellow','blue','green'];
		
		//public var txt_debugInfo:TextField;
		public var BtnConverter_mc:Button;
		//public var preTitleBtn_mc:Button;
		//public var nextTitleBtn_mc:Button;
		public var heavenTitle_tf:TextField;
		public var warn_max_levell_tf:TextField;
		public var HeavenLevel_tf:TextField;
		public var gotXP_tf:TextField;
		//public var soulHead_tf:TextField;
		//public var xiuLianHead_tf:TextField;
		
		public var curSoulall_tf:TextField;
		public var CurXiuLianAll:TextField;
		
		//public var heavenExp_tf:TextField;
		public var costSoul_tf:TextField;
		public var GotXiuLian_tf:TextField;

		public var needTime_tf:MovieClip;
		public var curLevel_tf:TextField;
		public var pluse_tf:TextField;
		public var reduction_tf:TextField;
		public var warn_not_enough_soul_tf:TextField;
		
		public var light_FX_mc:MovieClip;
		public var convert_times_mc:MovieClip;
		
		public var gasLog_mc:gasLog;
		public var btnOpenLog:Button;
		
		public var proExpBar_mc:MovieClip;
		
	//	public var viphintClip_tf:MovieClip;
	//	public var normalXiuLian_tf:MovieClip;
		public var soulPool_tf:MovieClip;
	//	public var XiuLianPool_tf:MovieClip;
	//	public var speedHint_tf:MovieClip;
		public var speedHintPic_mc:MovieClip;
		public var bottle_info_text_mc:MovieClip;
		public var hint_tf:TextField;
		public var xp_progress_tf:TextField;
		
//		public var allSoulClipMc:MovieClip;
//		public var allXiuLianClipMc:MovieClip;
//		public var needSoulClipMc:MovieClip;
//		public var getXiuLianlClipMc:MovieClip;
//		public var decSoulClipMc:MovieClip;
//		public var decXiuLianClipMc:MovieClip;
		public var convertOk_mc:MovieClip;
				
		public var circle_experience_bar:MovieClip;
		public var xp_bar_hint_area:MovieClip;
		
		public var heavenState1:HeavenStateUnit;
		public var curStateIndex:int;
		public var curStarNum:int;
		public var maxIndex:int;
		
		protected var _exp_bar_mask:MovieClip;
		protected var _XP_indicator_mc:MovieClip;
		protected var _soulBottleTf_mc:TextField;
		protected var _curFrame:int;
		protected var _targetFrame:int = -1;
		protected var _realTargetFrame:int = -1;
		protected var _isPlaying:Boolean = false;
		protected var _prevMaxValue:int = -1;;
		protected var _progressStr:String;
		
		public var arrHeavenTitle:Array;
		
		//time pass
		var needTimer:Timer = new Timer(1000,0);
		var nNeedTime:int = 0;
		
		protected var _needTimerExp:Timer = new Timer(500,1);
		var nAimWidth:int	 = 0;
		var nSpanWidth:Number = 1;
		var nTest:int = 0;
		
		private var _lineCount:int = 0;
		
		override protected function configUI():void
		{
			super.configUI();
			//txt_debugInfo.mouseEnabled = false;
			//var xp_bar:MovieClip = heavenState1.getChildByName('circle_experience_bar') as MovieClip;
			_exp_bar_mask = circle_experience_bar.getChildByName('mask_all_mc') as MovieClip;
			_XP_indicator_mc = circle_experience_bar.getChildByName('XP_indicator_mc') as MovieClip;
			_soulBottleTf_mc = bottle_info_text_mc.getChildByName('soulBottleTf_mc') as TextField;
			bottle_info_text_mc.visible = false;
			//to be delete
			heavenTitle_tf.visible = false;
			warn_max_levell_tf.visible = false;
			_curFrame = 1;
			_exp_bar_mask.gotoAndStop(_curFrame);
			_XP_indicator_mc.gotoAndStop(_curFrame);
			BtnConverter_mc.addEventListener(ButtonEvent.CLICK,ClickConverter);
			needTimer.addEventListener(TimerEvent.TIMER,timerHandleNeedTime);
			_needTimerExp.addEventListener(TimerEvent.TIMER,timerHandleNeedTimeExp);
			btnOpenLog.addEventListener(ButtonEvent.CLICK,ClickOpenGasLog);

			xp_bar_hint_area.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenExpBar);
			xp_bar_hint_area.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenExpBar);
		//	normalXiuLian_tf.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenHintCtrl0);
		//	normalXiuLian_tf.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenHintCtrl);
			
		//	viphintClip_tf.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenHintCtrl1);
		//	viphintClip_tf.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenHintCtrl);
			
			soulPool_tf.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenHintCtrl2);
			soulPool_tf.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenHintCtrl);
			
		//	XiuLianPool_tf.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenHintCtrl3);
		//	XiuLianPool_tf.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenHintCtrl);
			
		//	speedHint_tf.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenHintCtrl4);
		//	speedHint_tf.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenHintCtrl);
			
			needTime_tf.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenHintCtrl5);
			needTime_tf.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenHintCtrl);
			 maxIndex = 14;
			 curStateIndex = 0;
			 curStarNum = 0;
			 arrHeavenTitle = new Array();
			 arrHeavenTitle[0] = "_1";
			 arrHeavenTitle[1] = "_2";
			 arrHeavenTitle[2] = "_3";
			 arrHeavenTitle[3] = "_4"; 
			 needTimer.start();
			 gasLog_mc.visible = true;
			 convertOk_mc.visible = false;
			 light_FX_mc.visible = false;
			 CurXiuLianAll.visible= false;
			 convert_times_mc['convert_times_tf'].text = "0/0";
			 xp_progress_tf.text = "0/0";
			 hint_tf.text = "此处可放置装魂瓶";
			 //convert_times_mc.visible = false;
			//trace("--------------->instance check:　", viphintClip_tf, speedHint_tf, needTime_tf);
			// viphintClip_tf.gotoAndStop("normal");
			// speedHint_tf.gotoAndStop("_1");
			 needTime_tf.gotoAndStop("_time");
			 
			 //UCUpdateExpProBar(0,200);
			 /*viphintClip_tf.gotoAndStop("vip");
				speedHint_tf.gotoAndStop("_2");
				normalXiuLian_tf.gotoAndStop("vip");*/
		}
		
	//	private var _testIndex:int = 1;
		
		public function ClickConverter():void
		{
/*			nTest++;
			if(nTest > 6 ){
				UCUpdateExpProBar(100 * _testIndex *nTest,600 * _testIndex);
				nTest = 0;
				_testIndex++;
			}
			UCUpdateExpProBar(100 * _testIndex *nTest,600 * _testIndex);
			UCPlayMainAnimation(0);*/
			ExternalInterface.call( "ASClickConverter", this);
		}
		public function ClickOpenGasLog():void
		{
			//txt_debugInfo.text = "";
			 if(gasLog_mc.visible)
			 	gasLog_mc.visible = false;
			else
			{
				gasLog_mc.visible = true;
				ExternalInterface.call( "ASClickOpenHeavenLog", this);
			}
		}
		
		//更新当前总魂值
		public function UCUpdateSoulValue( soulValue:String)
		{
			curSoulall_tf.text = soulValue;
		}
		
		//更新当前总修炼值
		public function UCUpdateXiulianValue(soulValue:String)
		{
			CurXiuLianAll.text = soulValue;
		}
		
		protected function LOG(info:String):void
		{
			//txt_debugInfo.appendText("\n" + info);
		}

		//更新境界经验条
		public function UCUpdateExpProBar(curValue:int, maxValue:int)
		{
			_progressStr = curValue.toString() + "/" + maxValue.toString();
			//LOG("UCUpdateExpProBar: " + "|curValue: " + curValue + "|maxValue: " + maxValue);
			curValue = Math.min(curValue,maxValue);
			_targetFrame = 1 + 100 * curValue / maxValue;
			//LOG("|_prevMaxValue: " + _prevMaxValue + "|maxValue: " + maxValue);
			if(_prevMaxValue != -1 && maxValue != _prevMaxValue){
				_realTargetFrame = _targetFrame;
				_targetFrame = 101;
			}else{
				_realTargetFrame = -1;
			}
			//LOG("|_targetFrame: " + _targetFrame);
			if(_targetFrame > 1){
				if(_exp_bar_mask.currentFrame == _targetFrame){
					if(maxValue == _prevMaxValue){
						//LOG("doesn't change any more return");
						return;//doesn't change any more.
					}
					if(_targetFrame == 101 && _realTargetFrame == 1){
						_curFrame = 1;
						_exp_bar_mask.gotoAndStop(_curFrame);
						_XP_indicator_mc.gotoAndStop(_curFrame);
						_isPlaying = false;
						delayHideConvertOK();
						_prevMaxValue = maxValue;
						//LOG("stop 1 return");
						return;
					}
				}
				if(_curFrame == _exp_bar_mask.totalFrames){
					_curFrame = 1;
				}else{
					if(_isPlaying){
						_curFrame = _exp_bar_mask.currentFrame;
					}
				}
				if(!_isPlaying){
					_exp_bar_mask.addEventListener(Event.ENTER_FRAME, onCheckTargetFrame);
				}
				_isPlaying = true;
				//LOG("gotoAndPlay: " + _curFrame);
				_exp_bar_mask.gotoAndPlay(_curFrame);
				_XP_indicator_mc.gotoAndPlay(_curFrame);
			}else{
				if(_isPlaying){
					_targetFrame = 101;
					_realTargetFrame = 1;
					_prevMaxValue = maxValue;
					return;
				}
				_curFrame = 1;
				_exp_bar_mask.gotoAndStop(_curFrame);
				_XP_indicator_mc.gotoAndStop(_curFrame);
				_isPlaying = false;
				delayHideConvertOK();
				//LOG("stop 1 end");
			}
			
			_prevMaxValue = maxValue;
		}
		
		//更显当前境界属性
		public function UCUpdateStateAll(sLevel:String,sPluseValue:String,sReductionValue:String)
		{
			curLevel_tf.text = sLevel;
			pluse_tf.text = sPluseValue;
			reduction_tf.text = sReductionValue;
		}
		
		//显示升级到最高的警告
		public function UCShowMaxLevelWarnText(bVisible:Boolean):void
		{
			warn_max_levell_tf.visible = bVisible;
		}
		
		//更显当前境界等级 及字符串显示
		public function UCUpdateStateLevel(nHeavenLevel:int,sHeavenText:String)
		{
			curStateIndex = nHeavenLevel;
			//heavenTitle_tf.text = sHeavenText;
			UpdateHeavenState();
		}
		
		//更新当前境界星数及字符串显示
		public function UCUpdateStateLevelStarNum(nStarNum:int,sStarText:String)
		{
			curStarNum = nStarNum;
			HeavenLevel_tf.text = sStarText;
			UpdateHeavenState();
		}
		//播放动画类型
		public function UCPlayMainAnimation(nIndex:int)
		{
			 convertOk_mc.visible = true;
			 _needTimerExp.reset();
		}
		
		public function UCUpdateHeavenLog(data:Array)
		{
			gasLog_mc.UpdateHeavenLog(data);
		}
		
		//update convert times text;
		public function UCSetConvertTimes(value:String):void
		{
			convert_times_mc['convert_times_tf'].text = value;
		}
		
		public function UCSetSoulBottleHintText(sHint:String):void
		{
			hint_tf.text = sHint;
		}
		
		//soul bottle progress
		public function UCSetSoulBottleProgress(curValue:int, maxValue:int):void
		{
			if(curValue == 0 && maxValue == 0){
				UCSetSoulBottleHintText("此处可放置装魂瓶");
				bottle_info_text_mc.visible = false;
			}else{
				//locale
				UCSetSoulBottleHintText('您已放置装魂瓶');
				_soulBottleTf_mc.text = curValue.toString() + "/" + maxValue.toString() + "( " + (int(curValue * 100 / maxValue )).toString() + "% )";
				bottle_info_text_mc.visible = true;
			}
		}
		
		public function timerHandleNeedTime(evt:TimerEvent)
		{
			if(nNeedTime == 0)
				return;
			nNeedTime -= 1;
			var nHour:int =  nNeedTime/3600;
			var nMinute:int =  (nNeedTime%3600)/60;
			var nSecond:int =  nNeedTime%60;
			
			var timeText:TextField = needTime_tf.getChildByName("text") as TextField;
			if(timeText)
				timeText.text = GetStringFormat(nHour) + ":" + GetStringFormat(nMinute)+ ":" + GetStringFormat(nSecond);
		}
		public function timerHandleNeedTimeExp(evt:TimerEvent)
		{
			convertOk_mc.visible = false;
			_needTimerExp.reset();
		}
		
		protected function onCheckTargetFrame(e:Event):void
		{
			if(_exp_bar_mask.currentFrame == _targetFrame){
				//LOG("_exp_bar_mask.currentFrame == _targetFrame");
				if(_exp_bar_mask.currentFrame == _exp_bar_mask.totalFrames && _realTargetFrame != -1){
					_targetFrame =  _realTargetFrame;
					if(_targetFrame == 1){
						_exp_bar_mask.gotoAndStop(1);
						_XP_indicator_mc.gotoAndStop(1);
						_curFrame = 1;
						_exp_bar_mask.removeEventListener(Event.ENTER_FRAME, onCheckTargetFrame);
						_isPlaying = false;
						delayHideConvertOK();
						//LOG("gotoAndStop(1) as targetFrame == 1");
					}else{
						_exp_bar_mask.gotoAndPlay(1);
						_XP_indicator_mc.gotoAndPlay(1);
						//LOG("gotoAndPlay(1)");
					}
				}else{
					_exp_bar_mask.gotoAndStop(_targetFrame);
					_XP_indicator_mc.gotoAndStop(_targetFrame);
					_curFrame = _targetFrame;
					_exp_bar_mask.removeEventListener(Event.ENTER_FRAME, onCheckTargetFrame);
					_isPlaying = false;
					delayHideConvertOK();
					//LOG("gotoAndStop(_targetFrame)" + _targetFrame);
				}
			}else{
				if(_exp_bar_mask.currentFrame == _exp_bar_mask.totalFrames){
					_exp_bar_mask.gotoAndPlay(1);
					_XP_indicator_mc.gotoAndPlay(1);
					//LOG("gotoAndPlay(1) again" );
				}
			}
		}
		
		protected function delayHideConvertOK():void
		{
			if(_progressStr){
				xp_progress_tf.text = _progressStr;
			}
			if(convertOk_mc.visible){
				_needTimerExp.start();
			}
		}
		
		public function GetStringFormat(nTime:int):String
		{
			if(nTime > 9)
				return nTime.toString();
			return "0"+ nTime.toString();
		}
		
		function onRollOverHeavenExpBar( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenExpBar",this);
		}

		function onRollOutHeavenExpBar( e:Event )
		{
			trace("***onRollOutHeavenLevelSlot");
			ExternalInterface.call("ASHideTips_HeavenExpBar" );
		}
		
/*		function onRollOverHeavenHintCtrl0( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenHintCtrl",this,0);
		}
		
		function onRollOverHeavenHintCtrl1( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenHintCtrl",this,1);
		}*/
		
		function onRollOverHeavenHintCtrl2( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenHintCtrl",this,2);
		}
		
		function onRollOverHeavenHintCtrl3( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenHintCtrl",this,3);
		}
		function onRollOverHeavenHintCtrl4( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenHintCtrl",this,4);
		}
		function onRollOverHeavenHintCtrl5( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenHintCtrl",this,5);
		}
		function onRollOutHeavenHintCtrl( e:Event )
		{
			trace("***onRollOutHeavenLevelSlot");
			ExternalInterface.call("ASHideTips_HeavenHintCtrl" );
		}
		
		
		public function UCUpdateNextConverInfo(nextData:HeavenNextConvertData)
		{
			nNeedTime = nextData.nNeedTime;
			
			costSoul_tf.text = nextData.nCostSoulValue;
			GotXiuLian_tf.text = nextData.nGetXiuLian;
			gotXP_tf.text = nextData.nGetHeavenExp;
			if(nextData.bSoulNotEnough)
			{
				nNeedTime = 0;
				warn_not_enough_soul_tf.visible = true;
			}
			else{
				warn_not_enough_soul_tf.visible = false;
			}
			if(nNeedTime <= 0)
			{
				nNeedTime = 0;
				if(timeText)
				{
					var timeText:TextField = needTime_tf.getChildByName("text") as TextField;
					timeText.text = GetStringFormat(0) + ":" + GetStringFormat(0)+ ":" + GetStringFormat(0)
					
				}
			}
			if(nextData.bVIPSpeedup)
			{
			//	viphintClip_tf.gotoAndStop("vip");
			//	speedHint_tf.gotoAndStop("_2");
				//normalXiuLian_tf.gotoAndStop("vip");
			}
			else
			{
			//	viphintClip_tf.gotoAndStop("normal");
			//	speedHint_tf.gotoAndStop("_1");
				//normalXiuLian_tf.gotoAndStop("normal");
			}
		}
		
		public function UpdateHeavenState():void
		{
			var data1 : HeavenStateData;
			data1 = new HeavenStateData()
			
			data1.nStateIndex = curStateIndex;
			data1.IsNowState = true;
			data1.nStarNum = curStarNum;
			heavenState1.UpdateData(data1);
			setStateLevelFX();
		}
		
		protected function setStateLevelFX():void
		{
			//hard code for level fx;
			var fxType:int = -1;
			if((curStateIndex >= 0 && curStateIndex < 3) || (curStateIndex >= 9 && curStateIndex < 14) ){
				fxType = 0;
			}else if(curStateIndex >= 3 && curStateIndex < 6){
				fxType =  1;
			}else if(curStateIndex >= 6 && curStateIndex < 9){
				fxType =  2;
			}
			if(fxType >=0 && fxType < FX_TYPE_TO_LABEL.length){
				//light_FX_mc.visible = true;
				light_FX_mc.gotoAndStop(FX_TYPE_TO_LABEL[fxType]);
			}
		}
	}
}
