package ActionScript3
{
	
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
		
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Label;
	import scaleform.clik.controls.Button;

	public class MyHpBar extends UIComponent
	{
		var delaytime:Number ;
		var StartPos:Number = 0;
		var bStartTail:Boolean ;
		var orignvalue:Number = 18;
		
		var mpmask_lag:MovieClip;
		var mpmask:MovieClip;
		var shineEdge:MovieClip;
		
		override protected function configUI():void {
			super.configUI();

			this.addEventListener( Event.ENTER_FRAME,UpdateFrame );
			
		}
		
		function UpdateFrame()
		{
			var frametime =  this["root"].frametime;//newtime-prev ;
	
	
			if(bStartTail)
			{
				//trace("aad:"+delaytime);
				//trace("aaf:"+frametime);
				delaytime -= frametime;
				if( delaytime >0 )
					return;
				mpmask_lag.x -= frametime*0.4;
				//trace("aa:"+hpmask_lag._x);
			
				if( mpmask_lag.x < mpmask.x)
				{	
					bStartTail = false;
				}
				
				//trace(nframe);
			
				//cooldown_mc.gotoAndStop(nframe);
				//coolDown.gotoAndStop(nframe);
			
			}
		}
		
		function MPTail( newPercent:Number ,startTail:Boolean )
		{
			
			if( startTail )//¿ªʼÍÏβ
			{
				//trace("aad:"+startTail);
				mpmask_lag.x = mpmask.x;
				bStartTail = true;
				delaytime = 100;
			}	
			if( newPercent>0.99 )
				shineEdge.visible = false;
			else
				shineEdge.visible = true;
			mpmask.x = -mpmask.width *(1- newPercent ) + orignvalue;
			shineEdge.x = mpmask.x + mpmask.width;
			if(!startTail)
				mpmask_lag.x = mpmask.x;
		}
	}

}