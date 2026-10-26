package ActionScript3.Common
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.Event;
	
	import scaleform.clik.motion.Tween;

	public class DrawLine extends MovieClip
	{
		public var _mask:Shape;
		public var tween:Tween;
		public function DrawLine()
		{
		}
		
		public function update(param1:int,param2:int,param3:int,timer:int):void
		{
			clear();
			this._mask=new Shape();
			this._mask.x=param1;
			this._mask.y=param3;
			this._mask.graphics.lineStyle(1,0xffffff);
			this._mask.graphics.lineTo(param2,0);
			this._mask.width=0;
			this.addChild(_mask);
			tween=new Tween(timer,_mask,{width:param2},{paused:false,onComplete:CompleteTween,loop:false});
		}
		
		public function CompleteTween():void
		{
			this.dispatchEvent(new Event("drawLineComplete"));
		}
		
		public function clear():void
		{
			if(this.numChildren>0){
				this.removeChildAt(0);
			}
			if(tween){
				tween.reset();
				tween.paused=true;
				tween=null;
			}
		}
	}
}