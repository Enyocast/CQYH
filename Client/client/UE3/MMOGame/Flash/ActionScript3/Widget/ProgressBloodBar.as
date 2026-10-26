package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import ActionScript3.Common.Events.ParamEvent;
	
	public class ProgressBloodBar extends MyPanel
	{
		public var tF_title:TextField;
		public var tf_num:TextField;
		public var HPBar_mc:MovieClip;
		
		var HPMax:int = 100;
		
		var curValue_bar:Number = 0;
		var maxValue_bar:Number = 1;
		var aimValue_bar:Number = 0;
		var spanAdd:Number = 1;
		
		var timerCountDown:Timer = new Timer(33);

		override protected function configUI():void
		{
			ShowMode="BCB";
			super.configUI();
			timerCountDown.addEventListener(TimerEvent.TIMER, timeUpHandle);
			HPMax = HPBar_mc.hpMask.width;
			stageChangeHandler(null);
			this.mouseChildren = false;
			this.enabled=false;
			//SetInitBlood("testqqq",200, 200);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.y=cavasHeight-217;
			this.x=(cavasWidth - 388)>>1;
		}
		
		public function SetInitBlood(stitle:String,nCurValue:int,nMaxValue:int,lev:int,quality:int=0):void
		{
			curValue_bar = 0;
			maxValue_bar = 1;
			aimValue_bar = 0;
			spanAdd = 1;
			if(nCurValue <= 0)
				return;
            tf_num.text=lev+"";
			tf_num.visible = false;
			if(quality==8)
			{
				tF_title.textColor=0xFF4800;
			}
			else
			{
				tF_title.textColor=0xFFA200;
			}
		    tF_title.text = stitle;
			aimValue_bar = nCurValue;
			maxValue_bar = nMaxValue;
			
			spanAdd = (aimValue_bar)/20.0;
			timerCountDown.start();
		}
		
		public function UpdateBlood(nCurValue:Number)
		{
			aimValue_bar = nCurValue;
			spanAdd = (aimValue_bar - curValue_bar)/15.0;
		}
		
		function timeUpHandle()
		{
			if(curValue_bar == aimValue_bar)
				return;
			if(Math.abs(aimValue_bar - curValue_bar) > 1)
			{
				curValue_bar += spanAdd;
				updateBarPos();
			}
			else
			{
				spanAdd = 1;
				curValue_bar = aimValue_bar;
				updateBarPos();
			}
			
			if(curValue_bar==0)
			{
				timerCountDown.stop();
				//visible = false;				
			}
		}
		
		function updateBarPos():void
		{
			var newPercent:Number = (curValue_bar/maxValue_bar);
			HPBar_mc.hpMask.width = HPMax * newPercent;
			( HPBar_mc.hpMask as MovieClip ).scaleX = newPercent;
			HPBar_mc.shine.x = HPBar_mc.hpMask.x + HPBar_mc.hpMask.width-7;//闪光的位置不大对
		}
		
	}
}