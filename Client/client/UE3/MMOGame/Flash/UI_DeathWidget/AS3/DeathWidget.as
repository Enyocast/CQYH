package UI_DeathWidget.AS3 {
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.utils.Timer;
	import flash.external.ExternalInterface;
	import flash.events.TimerEvent;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	
	public class DeathWidget extends MyPanel{

		//复活方式
		private static var revive_Free:Number = 3;
		
        public var btn_Revive_Coin:Button;
		public var tF_timeCounter:TextField;
		public var tF_Title3:TextField;
		public var tF_Title1:TextField;
		public var tipinfo:MovieClip;
		public var reviveCountDown:int = 10;
		public var reviveCountDownWaiting:int = 10;
		public var timerCountDown:Timer = new Timer(1000);
		public var timerCountDownWaiting:Timer = new Timer(1000);
		public var reqObject:Object = null;
		public var mapType:Number = 0;
		public var mapTypeName:String = "";
		public var _deathbg:MovieClip;
		public var _bg:MovieClip;
		public function DeathWidget() {
			// constructor code
		}
		
		override protected function configUI():void
		{
			ShowMode="Death";
			super.configUI();
			timerCountDown.addEventListener(TimerEvent.TIMER, timerHandle);
			timerCountDownWaiting.addEventListener(TimerEvent.TIMER,timerHandleWaiting);
			btn_Revive_Coin.addEventListener(MouseEvent.CLICK,clickReviveHandler);
			//ExternalInterface.call( "RegisterDeath", this);
			tipinfo.visible=false;
			stageChangeHandler(null);
		}
		
		private function clickReviveHandler(evt:MouseEvent):void
		{
			reviveCountDown = 0;
			timerCountDown.stop();
			reviveCountDownWaiting = 0;
			timerCountDownWaiting.stop();
			ExternalInterface.call("ASRelife",revive_Free,100001);
		}
		
		public function updateData(dat:Object):void
		{
			reqObject = dat;
			InitLoad();
		}
		
		public function InitLoad():void
		{
			ExternalInterface.call( "SetTextByID",tF_Title1,"MMOGame.reviveDialog.textTitle1");
			ExternalInterface.call( "SetTextByID",tipinfo.tF_Info,"MMOGame.reviveDialog.textTips2"+mapTypeName);
			if(reqObject.PlayerKilled && reqObject.WaitTime > 0)
			{
				timeWaitingStart();
			}
			else
			{
				timeCountStart();
			}
		}
				
		private function timeCountStart():void
		{
			setTimeCountTxtShow(true);
			ExternalInterface.call( "SetTextByID",tF_Title3,"MMOGame.reviveDialog.textTitle2"+mapTypeName);
			ExternalInterface.call("GetReviveCountDown",this,"reviveCountDown");
			tF_timeCounter.text = "" + reviveCountDown;
			timerCountDown.start();
		}
		
		private function timeWaitingStart():void
		{
			setRevive_FreeEnable(false);
			tF_Title3.text="秒后，可以免费复活";
			reviveCountDownWaiting = reqObject.WaitTime;
			tF_timeCounter.text="" + reviveCountDownWaiting;
			timerCountDownWaiting.start();

		}
		
		private function timerHandle():void
		{
			reviveCountDown = reviveCountDown - 1;
			tF_timeCounter.text = "" + reviveCountDown;
			if (reviveCountDown<=0)
			{
				reviveCountDown = 0;
				timerCountDown.stop();
				ExternalInterface.call("ASRelife",3,0);
			}			
		}
		
		private function timerHandleWaiting():void
		{
			reviveCountDownWaiting = reviveCountDownWaiting - 1;
			tF_timeCounter.text = "" + reviveCountDownWaiting;
			if (reviveCountDownWaiting <= 0)
			{
				setRevive_FreeEnable(true);
				reviveCountDownWaiting = 0;
				timerCountDownWaiting.stop();
				timeCountStart();
			}			
		}
		
		public function setRevive_FreeEnable(v:Boolean):void
		{
			btn_Revive_Coin.enabled = v;
		}

		
		public function ResetDeathType():void
		{
			ExternalInterface.call("GetCurrentMapType",this,"mapType");
			if (mapType == 2)
			{
				mapTypeName = "Dungeon";
			}
			else if (mapType == 3)
			{
				mapTypeName = "BattleField";
			}
			else if (mapType == 4)
			{
				mapTypeName = "Arena";
			}
			else if (mapType == 7)//E_est_Guild
			{
			}
			else
			{
				mapTypeName = "Static";
			}
			setTimeCountTxtShow(false);
		}

		public function setTimeCountTxtShow(v:Boolean):void
		{
			tF_timeCounter.visible = v
			tF_Title3.visible = v;
		}
		
		public function setRevive_CoinEnable(v:Boolean):void
		{
			btn_Revive_Coin.enabled = v;
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			this.cavasWidth=GameDispathcher.getInstance().StageWidth;
			this.cavasHeight=GameDispathcher.getInstance().StageHeight;
			btn_Revive_Coin.y=cavasHeight-btn_Revive_Coin.height-220;
			btn_Revive_Coin.x=(cavasWidth-btn_Revive_Coin.width)>>1;
			tF_timeCounter.y=btn_Revive_Coin.y-59;
			tF_timeCounter.x=btn_Revive_Coin.x-138;
			tF_Title3.y=btn_Revive_Coin.y-55;
			tF_Title3.x=tF_timeCounter.x+tF_timeCounter.width;
			tipinfo.y=btn_Revive_Coin.y-100;
			tipinfo.x=(cavasWidth-tipinfo.width)>>1;
			_deathbg.y=btn_Revive_Coin.y-75;
			_deathbg.x=tF_timeCounter.x+61;
			_bg.width=cavasWidth;
			_bg.height=cavasHeight;
			tF_Title1.x=(cavasWidth-760)>>1;

		}

	}
	
}
