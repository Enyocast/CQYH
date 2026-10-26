
package ActionScript3.Slot
{

//	import scaleform.clik.core.UIComponent;
//	import scaleform.clik.controls.Button;
//	import ActionScript3.Slot.MySlotData;
//	import ActionScript3.Slot.MySlotRender;
//	import ActionScript3.Slot.MySlotContral;

	import ActionScript3.Slot.ItemSlotRender;
	import flash.utils.getDefinitionByName;

	import flash.events.Event;
	import flash.events.MouseEvent;
	
	import flash.utils.Timer;
	import flash.utils.getTimer;
	import flash.events.TimerEvent;

	public class CoolDown
	{
		public var cdTimer:Timer;
		 
		public var cdTotalMS:int = 0;
		public var cdPassedMS:int = 0;		
		
		public var startMS:int = 0;
		public var currentMS:int = 0;		
		
		public var bCDing:Boolean = false;		
		public var callBackRenderCD:Function = null;
				
		public function Init():void
		{
			cdTimer = new Timer(33);
		}
		public function UnInit():void
		{
			cdTimer = null;
			callBackRenderCD = null;
		}
		
		public function startCD(passedMS:int, totalMS:int, renderCD:Function )
		{
			//trace("startCD1");
			cdTotalMS = totalMS;
			cdPassedMS= passedMS;
			currentMS = getTimer();
			startMS = currentMS;
			callBackRenderCD = renderCD;
			if( cdTimer==null )
			{
				cdTimer = new Timer(33);
			}

			if( cdTimer && bCDing==false)
			{
				cdTimer.addEventListener( TimerEvent.TIMER , OnTimer );
				cdTimer.start();
				bCDing = true;
				//trace("startCD1.5");
			}
			callBackRenderCD();
			//trace("startCD2");
		}
		
		public function stopCD(renderCD:Function)
		{
			//trace("stopCD1");
		 	cdTotalMS 	= 0;
		  	cdPassedMS 	= 0;		
		  	startMS 	= 0;
		  	currentMS 	= 0;
			callBackRenderCD = renderCD;
			
			if( cdTimer && bCDing )
			{
				cdTimer.stop();
				cdTimer.removeEventListener( TimerEvent.TIMER , OnTimer );
			}
			
			bCDing = false;
			callBackRenderCD();
			//trace("stopCD2");
		}
		
		public function isCDing():Boolean
		{
			return bCDing;
		}
		
		public function getCountDownSec():int
		{
			var deltaMS = currentMS-startMS;
			if(deltaMS<0)deltaMS=0;
			
			var res = (cdTotalMS - cdPassedMS - deltaMS )/1000 ;
			if(res<0)res=0;
			return res;
		}
		
		public function getProcess(denominator:int):int
		{
			var deltaMS = currentMS-startMS;
			if(deltaMS<0)deltaMS=0;
			
			var res = (cdPassedMS + deltaMS)*denominator/cdTotalMS;
			if(res>denominator)res=denominator;

			return res;
		}
		
		function renderCD()
		{
			if(callBackRenderCD!=null)
			{
				callBackRenderCD();
			}				
		}
		
		function OnTimer( e:Event )
		{		
			currentMS = getTimer();
			renderCD();
			
		}
		








	}
}