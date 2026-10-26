package ActionScript3.Master {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.UILoader;
	import flash.events.MouseEvent;
	import ActionScript3.Common.TimerManager;
	import flash.external.ExternalInterface;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import scaleform.clik.events.ComponentEvent;
	import flash.events.Event;
	
	public class MasterInfo extends MyPanel {
		
		public var tf_playerName:TextField;
		public var tf_level:TextField;
		public var tf_class:TextField;
		public var tf_timer:TextField;
		
		public var btn_ok:Button;
		public var btn_no:Button;
		
		public var head_icon:UILoader;
		
		public var Id:int;
		
		private var _timer:int;
		
		private var timer:Timer;
		
		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			this.SetWindowTitle("新徒推荐");
			timer=new Timer(1000);
			timer.addEventListener(TimerEvent.TIMER,step);
			(MyWindowsFrame_mc.getChildByName("divide") as MovieClip).visible=false;
			btn_ok.addEventListener(MouseEvent.CLICK,clickHandler);
			btn_no.addEventListener(MouseEvent.CLICK,closeHandler);
			this.addEventListener(ComponentEvent.HIDE,hideHandler);
			//UCUpdatePlayerInfo({RoleName:"deaa",Level:12});
			//UCUpdatePlayerName({RoleName:"deaa",ClassName:"战士"});
		}
		
		private function hideHandler(evt:Event):void
		{
			timer.stop();
			Id=0;
			tf_playerName.text="";
		    tf_level.text="";
			tf_class.text="";
			_timer=0;
			tf_timer.text="";
			head_icon.visible=false;
		}

		private function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASRectivedMaster" ,Id);
		}
		
		private function closeHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideStudentTwitter" , Id);
		}
		
		public function UCUpdatePlayerInfo(dat:Object):void
		{
			timer.stop();
			Id=dat.Id;
			tf_playerName.text=dat.RoleName;
		    tf_level.text=dat.Level.toString();
			tf_class.text=dat.ClassName;
			_timer=60;//dat.timer
			tf_timer.text=60+"秒";
			head_icon.source=dat.HeadIcon;
			head_icon.visible=true;
			if(_timer>0)
			{
				timer.start();
			}
		}
		
		public function UCUpdatePlayerName(dat:Object):void
		{
			tf_playerName.text=dat.RoleName;
			tf_class.text=dat.ClassName;
			head_icon.source=dat.HeadIcon;
			head_icon.visible=true;
		}
		
		private function step():void
		{
			_timer--;
			tf_timer.text=_timer+"秒";
			if(_timer<=0)
			{
				timer.stop();
				closeHandler(null);
			}
		}
	}
}
