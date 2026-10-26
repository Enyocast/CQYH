package MMO_UI.GameLoading.AS
{
	import flash.display.MovieClip;
	import flash.events.KeyboardEvent;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.ui.Keyboard;
	import flash.utils.Timer;
	
	import ActionScript3.MyProgressBarPanel;
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.UILoader;
	import flash.events.MouseEvent;

	public class LoadingProgressBar extends UIComponent
	{
		public var tF_title:TextField;
		public var castbar_mc:MovieClip;
        public var _bg0:MovieClip;
		public var _bg1:MovieClip;
		private const STATE_FRAME_LABLE:Array = ['casting','completed','interrupted'];

		private var _loadingTimer:Timer;
		private var _preEnterTimer:Timer;
		private var _preEnterProgress:Number;
		private var _preLeaveTimer:Timer;
		private var _preLeaveProgress:Number;
				
		private var _curProgress:Number;
		private var _curState:int = -1;
		
		private var _shine_mc:MovieClip;
		
		private var _bk_mc:MovieClip=null;
		public var loader_bg:MovieClip;
		

		override protected function configUI():void
		{
			super.configUI();
			UCSetLoadingProgressBar_reset();
			UCSetLoadingProgressBar_updateProgress(0);
			UCSetLoadingProgressBar_updateState(0);
			ExternalInterface.call("RegisterLoadingProgressBar",this);
			_shine_mc = castbar_mc['shine']['cast_shine_mc']['shine_mc'];
			_preEnterTimer= new Timer(30);
			_preEnterTimer.addEventListener(TimerEvent.TIMER,onPreEnterTimer);
			_preLeaveTimer= new Timer(30);
			_preLeaveTimer.addEventListener(TimerEvent.TIMER,onPreLeaveTimer);
			updatePos();
			UCSetLoadingProgressBar_updateTitle("");
			//UCSet_PreEnter();
			//testInterface();
			
		}
		

/*		private function testInterface():void
		{
			stage.addEventListener(KeyboardEvent.KEY_DOWN,onKeyPress);
			UCSetLoadingProgressBar_updateTitle("Loading...");
			UCSetLoadingProgressBar_updateProgress(0);
			UCSetLoadingProgressBar_updateState(0);
			_loadingTimer = new Timer(30);
			_loadingTimer.addEventListener(TimerEvent.TIMER,onTimer);
			_curProgress = 0;
			_loadingTimer.start();
		}

		private function onKeyPress(e:KeyboardEvent):void
		{
			if (e.keyCode == Keyboard.ESCAPE)
			{
				if (_loadingTimer.running && _curState == 0)
				{
					_loadingTimer.stop();
					UCSetLoadingProgressBar_updateState(2);
					UCSetLoadingProgressBar_updateTitle("Loading interrupted");
				}
			}
			else if (e.keyCode == Keyboard.SPACE)
			{
				if (! _loadingTimer.running && _curState == 2)
				{
					_loadingTimer.start();
					UCSetLoadingProgressBar_updateState(0);
					UCSetLoadingProgressBar_updateTitle("Loading...");
				}
			}
		}*/

/*		private function onTimer(e:TimerEvent):void
		{
			_curProgress +=  0.001;
			UCSetLoadingProgressBar_updateProgress(_curProgress);
			if ((_curProgress >= 1))
			{
				//_curProgress = 0;
				_loadingTimer.removeEventListener(TimerEvent.TIMER,onTimer);
				UCSetLoadingProgressBar_updateTitle("Loading Complete");
				UCSetLoadingProgressBar_updateState(1);
			}
		}*/

		private function onPreEnterTimer(e:TimerEvent):void
		{
			_preEnterProgress+=0.03*2.5;
			if(_preEnterProgress>=1.0)
			{
				_preEnterProgress = 1.0;
				_preEnterTimer.stop();
				ExternalInterface.call("ASPreEnterCompleted");
			}
			alpha = _preEnterProgress;
			ExternalInterface.call("ASCallBackSetAlpha",_preEnterProgress); 
		}
		
		private function onPreLeaveTimer(e:TimerEvent):void
		{
			_preLeaveProgress-=0.03*2.5;
			if(_preLeaveProgress<=0.0)
			{
				_preLeaveProgress = 0.0;
				_preLeaveTimer.stop();
				ExternalInterface.call("ASPreLeaveCompleted");
			}
			alpha = _preLeaveProgress;
			ExternalInterface.call("ASCallBackSetAlpha",_preLeaveProgress); 
		}		
		
		//;
		public function UCSetLoadingProgressBar_updateTitle(strTitle:String):void
		{
			if(strTitle=="")
			{
				loader_bg._loader.source="img://MMOUIImage.Loading.bg_1";
			}
			else
			{
				loader_bg._loader.source=strTitle;
			}
			//tF_title.text = strTitle;
		}

		public function UCSetLoadingProgressBar_updateProgress(curProgress:Number)
		{
			if(curProgress < 0.05 || curProgress > 0.98){
				if(_shine_mc != null){
					_shine_mc.gotoAndStop(2);
				}
			}else{
				if(_shine_mc != null){
					_shine_mc.gotoAndStop(1);
				}
			}
			castbar_mc.setDivide(curProgress,1);
		}

		public function UCSetLoadingProgressBar_updateState(state:int)
		{
			if ((_curState != state))
			{
				_curState = state;
				if (((state >= 0) && state < STATE_FRAME_LABLE.length))
				{
					castbar_mc.setState(STATE_FRAME_LABLE[state]);
				}
			}
		}
		
		public function UCSetLoadingProgressBar_reset():void
		{
			//tF_title.text = "欢迎试玩《传奇永恒》";
			//tF_title.x = ((width - tF_title.width) / 2);//already fix in fla file,no need change more.
			castbar_mc.setDivide(0,1);
			castbar_mc.hideShine();
			_curState = -1;
		}
		
		public function UCSet_PreEnter():void
		{
			this.x=this.y=0;
			_preEnterProgress=0.01;
			_preLeaveTimer.stop();
			_preEnterTimer.start();			
			alpha = _preEnterProgress;
            ExternalInterface.call("ASCallBackSetAlpha",_preEnterProgress); 
		}
		
		public function UCSet_AftEnter():void
		{
			this.x=this.y=0;
			_preEnterTimer.stop();
			_preLeaveTimer.stop();			
			alpha = 1.0;
            ExternalInterface.call("ASCallBackSetAlpha",1.0); 			
		}
		
		public function UCSet_PreLeave():void
		{
			this.x=this.y=0;
			_preLeaveProgress=1.0;
			_preEnterTimer.stop();
			_preLeaveTimer.start();			
			alpha = _preLeaveProgress;
            ExternalInterface.call("ASCallBackSetAlpha",_preLeaveProgress); 			
		}
		
		public function UCSet_Back(bk_mc:MovieClip)
		{
			_bk_mc = bk_mc;
		}
		
		public function updatePos():void
		{
			var screenWidth:int=root.stage.stageWidth;
			var screenHeight:int=root.stage.stageHeight;
			loader_bg.scaleX=screenWidth/1600;
			loader_bg.scaleY=screenHeight/900;
			_bg0.x=(screenWidth-1920)/2;
			_bg1.x=_bg0.x+1920;
			_bg0.y=_bg1.y=screenHeight-101;
			castbar_mc.y=_bg0.y+60;
			castbar_mc.x=_bg0.x+572;
			tF_title.y=_bg0.y+20;
			tF_title.x=_bg0.x+160;
		}

		public function UCSetX(screenWidth:int,offset:int)
		{
			//x = (((screenWidth - width) >> 1) + offset);
		}
		//
		public function UCSetY(screenHeight:int,offset:int)
		{
			//y = (((screenHeight - height) >> 1) + offset);
		}
	}
}