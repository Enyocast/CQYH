package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ButtonEvent;
	import flash.external.ExternalInterface;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	
	public class LoginQueuePanel extends MyPanel {
		
		public var txt_rank:TextField;
		public var txt_timer:TextField;
		public var btn_cancel:Button;
		public var timer:Timer;
		private var _timer:int;
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			MyWindowsFrame_mc.InfoDragButton_mc.visible = false;
			(MyWindowsFrame_mc.getChildByName("divide") as MovieClip).visible=false;
			btn_cancel.addEventListener(ButtonEvent.CLICK,cancelHandler);
			this.SetWindowTitle("登录排队");
			timer=new Timer(1000);
			timer.addEventListener(TimerEvent.TIMER,step);
			//UCUpdateData(1000,3601);
		}
		
		private function step():void
		{
			_timer--;
			if(_timer==0)
			{
			    clear();
				ExternalInterface.call("ASRequestLoginQueueEnd");//排队时间结束
			}
			txt_timer.text=timerConvert(_timer);
		}
		
		private function cancelHandler(evt:ButtonEvent):void
		{
			clear();
			ExternalInterface.call("ASRequestCancelLoginQueue");//取消
		}
		
		private function clear():void
		{
			_timer=0;
			timer.stop();
			txt_rank.text="";
			txt_timer.text="";
		}
		
		public function UCUpdateData(rank:int,dat:int):void
		{
			_timer=dat;
			txt_rank.text="第"+rank+"位";
			txt_timer.text=timerConvert(_timer);
			//timer.start();
		}
		
		public function UCUpdateTime(txt:String):void
		{
			txt_timer.text= txt;
		}
		
		//时间转换成秒分时
		private function timerConvert(sceond:int):String
		{
			//var h:int=Math.floor(sceond/3600);
			//var sec:int=sceond-(3600*h);
			//var m:int=0;
			//if(sec>0)
			//{
				//m=Math.floor(sec/60);
			//}
			//var s:int=sec-(60*m);
			//if(h>0)
			//{
				//return h+"小时"+m+"分钟"+s+"秒";
			//}
			//else
			//{
				//if(m>0)
				//{
					//return m+"分钟"+s+"秒";
				//}
				//else
				//{
					//return s+"秒";
				//}
			//}
			var s:String;
			
			var sec:int = sceond/60;
			
			if(sec > 30)
			{
				s = "大于30分钟";
			}
			else if(sec <= 30 && sec >25)
			{
				s = "小于30分钟";
			}
			else if(sec <= 25 && sec >20)
			{
				s = "小于25分钟";
			}
			else if(sec <= 20 && sec >15)
			{
				s = "小于20分钟";
			}
			else if(sec <= 15 && sec >10)
			{
				s = "小于15分钟";
			}
			else if(sec <= 10 && sec >5)
			{
				s = "小于10分钟";
			}
			else if(sec <= 5 )
			{
				s = "小于5分钟";
			}
			return s;
			
		}
	}
	
}
