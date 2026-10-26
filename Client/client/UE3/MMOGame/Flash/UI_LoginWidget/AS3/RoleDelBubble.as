package UI_LoginWidget.AS3 {
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	
	public class RoleDelBubble extends MovieClip {

		public var timek:TextField;
		public var tk_tool:Timer = new Timer(1000);
		public var tk_value:int;
		public var role_id:int;
		
		public function RoleDelBubble()
		{
			this.mouseChildren=false;
			this.mouseEnabled=false;
			tk_tool.addEventListener(TimerEvent.TIMER, OnTimeHandle);
			tk_tool.stop();
		}
		public function SetOverTime(n:int, id:int):void
		{
			tk_tool.stop();
			tk_value = n;
			if (tk_value > 0)
			{
				visible = true;
				DoTimeStep();
				tk_tool.start();
			}
			else
				visible = false;
		}
		public function OnTimeHandle():void
		{
			if (!visible)
				tk_tool.stop();
			
			if (tk_value <= 0)
			{
				tk_tool.stop();
				OnTimeEnd();
			}
			else
				DoTimeStep();
		}
		public function DoTimeStep():void
		{
			var h:int = tk_value / 3600;
			var m:int = (tk_value % 3600) / 60;
			var s:int = tk_value % 60;
			var str:String = "";
			timek.text = "";
			if (h > 0)
				str += h + "小时";
			if (m > 0)
				str += m + "分";
			if (s > 0)
				str += s + "秒";
			timek.text = str;
			tk_value--;
		}
		public function OnTimeEnd():void
		{
			visible = false;
			ExternalInterface.call("ASOnTimeEnd", role_id);
		}

	}
	
}
