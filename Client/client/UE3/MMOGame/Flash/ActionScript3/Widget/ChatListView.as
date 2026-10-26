package ActionScript3.Widget{
	
	import flash.events.Event;
	
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.core.UIComponent;
	import flash.utils.setTimeout;
	import flash.utils.clearTimeout;
	import flash.events.MouseEvent;
	//import ActionScript3.Common.TimerManager;

	public class ChatListView extends UIComponent 
	{
		public var MaskView_mc:ScrollingView;
		public var DisplayPanel_mc:ChatRoller;
		public var ChatScrollBar_mc:ScrollBar;
		
		public var ISScroll:Boolean=true;//是否自动滚屏 
		//public const Delay:int=10000;//延迟时间(毫秒)
		//public var setTimer:uint;
		//private var timer:int;
		override protected function configUI():void
		{
			super.configUI();
			this.focusable = false;
			MaskView_mc.focusable = false;
			DisplayPanel_mc.focusable = false;
			//this.addEventListener(MouseEvent.ROLL_OVER,handler);//监听滚动条
/*			ChatScrollBar_mc.addEventListener(MouseEvent.MOUSE_WHEEL,handler);
			ChatScrollBar_mc.addEventListener(MouseEvent.MOUSE_DOWN,handler);*/
			ChatScrollBar_mc.focusable = false;
			UpdateView();
		}
		
		private function handler(evt:Event):void
		{
			//trace(timer+"MouseEvent.MOUSE_WHEEL=============="+ISScroll);
			//timer=0;
			ISScroll=false;//
			//clearTimeout(setTimer);
			//setTimer=setTimeout(step,Delay);
		}
		private function step():void
		{
/*		    trace(timer+"TimerOut=============="+ISScroll);
			timer=0;*/
			//clearTimeout(setTimer);
			ISScroll=true;//
			ScrollHandler();
		}
		
		public function SetLogicSize(w:Number,h:Number):void
		{
			MaskView_mc.setActualSize(w,h);
			ChatScrollBar_mc.height = h;

			invalidateSize();
		}
		public function UpdateView():void
		{
			ScrollHandler();//开始滚屏
		}
		
		private function ScrollHandler():void
		{
			if(ISScroll==true || (DisplayPanel_mc.height - MaskView_mc.height)==ChatScrollBar_mc.position)
			{
				DisplayPanel_mc.UpdateView();
				MaskView_mc.updateScrollBar();
			    ChatScrollBar_mc.position =   Math.max(0,(DisplayPanel_mc.height - MaskView_mc.height));
			}
		}
		
		public function ClearChatMsg():void
		{
			DisplayPanel_mc.ClearItem();
		}
		
		public function AddChatMsg(chatMsg:Array):void
		{
			for(var i=0;i<chatMsg.length;i++)
			{
				DisplayPanel_mc.AddItem(chatMsg[i]);
			}
			UpdateView();
		}
	}
}