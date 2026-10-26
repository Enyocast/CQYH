package UI_DynamicUIWidget.AS3 {
	import ActionScript3.MyPanel;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.display.MovieClip;
	import ActionScript3.Common.Events.ParamEvent;
	import flash.external.ExternalInterface;
	import flashx.textLayout.formats.TextAlign;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	
	public class NewEventPanel extends MyPanel {

        public var delay_time:int = 2;
		var limit_timer:Timer;
		public var content_mc:MovieClip;
		public var exmark:MovieClip;
		public var _bg:MovieClip;
		override protected  function configUI():void 
		{			
		    ShowMode="BCB";
			super.configUI();
			this.mouseChildren=false;
			this.enabled=false;
			clear();
			stageChangeHandler(null);
			limit_timer = null;			
			//UCShowNewEvent(1,"测试点点滴滴");
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=(cavasWidth-this.width>>1);
		}
		
		public function UCShowNewEvent(tips_type:int,dat:String):void
		{
			//trace("UCShowNewEvent============",dat,content_mc);
			if(dat && dat!="")
			{
				content_mc.content_mc.gotoAndStop("taskend");
				var txt:TextField=content_mc.content_mc.textField;
				txt.text="紧急事件["+dat+"]完成";
				txt.autoSize =TextFieldAutoSize.LEFT;
				var hy:int=60+txt.textWidth;
				_bg.width=hy+80;
				content_mc.x=_bg.width-txt.textWidth>>1;
				exmark.x=content_mc.x-80;
			}
			else
			{
				switch (tips_type)
				{
					case 0 :
					content_mc.content_mc.gotoAndStop("event");
					break;
					case 1 :
					content_mc.content_mc.gotoAndStop("help");
					break;
				    case 2 :
					content_mc.content_mc.gotoAndStop("danger");
					break;
				}
				content_mc.x=103;
				exmark.x=content_mc.x-80;
				_bg.width=262;
			}
			onStart();
		}
		
		private function onStart():void
		{
			this.visible = true;
			this.gotoAndPlay(1);
			_bg.gotoAndPlay(1);
			exmark.gotoAndPlay(1);
			content_mc.gotoAndPlay(1);
		}
		
		public function onPause():void
		{
			this.gotoAndStop(16);
			_bg.gotoAndStop(16);
			exmark.gotoAndStop(16);
			content_mc.gotoAndStop(16);
			if (limit_timer == null)
			{
				limit_timer = new Timer(1000);
			}
			limit_timer.start();
			limit_timer.addEventListener(TimerEvent.TIMER, onTimer);
		}
		
		private function onTimer(e:TimerEvent):void
		{
			if (delay_time > 0)
			{
				delay_time -= 1;
			}
			else
			{
				if (limit_timer != null)
				{
					limit_timer.stop();
					limit_timer.removeEventListener(TimerEvent.TIMER, onTimer);
					limit_timer = null;
				}
				exmark.gotoAndPlay(16);
				this.gotoAndPlay(16);
				_bg.gotoAndPlay(16);
				content_mc.gotoAndPlay(16);
			}
		}
		
		private function clear():void
		{
			this.visible = false;
			this.gotoAndStop(1);
			_bg.gotoAndStop(1);
			exmark.gotoAndStop(1);
			content_mc.gotoAndStop(1);
		}
		
		public function onEnd():void
		{
			clear();
			//UCShowNewEvent(0,"");
			ExternalInterface.call("ASOnPanelClose",this.name);
		}

	}
	
}
