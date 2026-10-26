package ActionScript3.Option
{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;
	
	public class OptionQuit extends MyPanel
	{
		public var quit_immed:Button;
		public var quit_cancel:Button;
		public var quit_text:TextField;
		public var quit_tk:Timer = new Timer(1000);
		public var quit_str_head:String;
		public var quit_tk_len:int;
		public var quit_str_tail:String
        public var _bg:MovieClip;
		
		override protected  function configUI():void
		{
			super.configUI();
			//MyWindowsFrame_mc.btn_close.visible=false;
			MyWindowsFrame_mc.tF_windowTitle.text="退出游戏";
			MyWindowsFrame_mc.InfoDragButton_mc.visible=false;
			//visible = false;
			
			//ExternalInterface.call( "ASRegisterOptionQuit", this);

			quit_immed.addEventListener("click",OnQuitImmed);
			quit_cancel.addEventListener("click",OnQuitCancel);
			quit_tk.addEventListener(TimerEvent.TIMER, OnTimeHandle);
			quit_tk.stop();
			stageChangeHandler(null);
			//UCInitQuitTimer("将在", 10, "秒后关闭...");
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			this.cavasWidth=GameDispathcher.getInstance().StageWidth;
			this.cavasHeight=GameDispathcher.getInstance().StageHeight;
			MyWindowsFrame_mc.x=cavasWidth-348>>1;
			MyWindowsFrame_mc.y=cavasHeight-216>>1;
			quit_text.x=MyWindowsFrame_mc.x+31;
			quit_text.y=MyWindowsFrame_mc.y+86;
			quit_immed.x=MyWindowsFrame_mc.x+61;
			quit_immed.y=quit_cancel.y=MyWindowsFrame_mc.y+153;
			quit_cancel.x=quit_immed.x+126;
		}
		public function OnQuitImmed()
		{
			ExternalInterface.call("ASOptionQuitImmed");
		}
		public function OnQuitCancel()
		{
			ExternalInterface.call("ASOnPanelClose", PanelName);
			//visible = false;
		}
		public function OnTimeHandle()
		{
			//不可见即是停止计时
			if(visible==false)
			{
				quit_tk.stop();
			}
			
			if (quit_tk_len <= 0)
			{
				quit_tk.stop();
				OnQuitImmed();
			}
			else
				DoTimeStep();
		}
		public function DoTimeStep()
		{
			quit_text.text = quit_str_head + quit_tk_len + quit_str_tail;
			quit_tk_len--;
		}
		public function UCInitQuitTimer(str_head:String, tk_len:int, str_tail:String)
		{
			quit_str_head = str_head;
			quit_tk_len = tk_len;
			quit_str_tail = str_tail;
			if (quit_tk_len > 0)
				quit_tk.start();
			DoTimeStep();
		}
	}
}