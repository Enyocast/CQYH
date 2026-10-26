package ActionScript3.Common {
	import flash.display.DisplayObject;
	import flash.events.MouseEvent;
	import flash.filters.GlowFilter;
	import flash.filters.BitmapFilterQuality;
	
	public class FalshEffect extends Object {

        public var _display:DisplayObject;
		public var _glowW:int;
		public var _glowDirect:int;
		public var _glowRate:int;
		public var _glowColor:uint;
		public var _glowArr:Array;
		public var _glow:GlowFilter;
		public function FalshEffect() 
		{
			// constructor code
		}
		
		public function beginGlow(display:DisplayObject,loop:Boolean,color:uint):void
		{
			if(display==null)
			{
				return;
			}
			_display=display;
			this._display.removeEventListener(MouseEvent.ROLL_OVER,rolloverHandler);
			if(loop==true)
			{
				this._display.addEventListener(MouseEvent.ROLL_OVER,rolloverHandler);
			}
			if(_glow==null)
			{
				_glow=new GlowFilter();
				_glow.color=color;
				_glow.blurX=0;
				_glow.blurY=0;
				_glow.quality=BitmapFilterQuality.LOW;
				this._glowArr=[_glow];
			}
			this._display.filters=this._glowArr;
			this._glowColor=color;
			this._glowRate=1000/5;
			this._glowW=12;
			TimerManager.getInstance().remove(step);
			TimerManager.getInstance().add(this._glowRate,step);
		}
		
		private function step():void
		{
			_glow.blurX=_glow.blurX+this._glowDirect;
		    _glow.blurY=_glow.blurY+this._glowDirect;
			this._display.filters=this._glowArr;
			if(this._glow.blurX>=this._glowW)
			{
				_glowDirect-=2;
			}
			else if(this._glow.blurX<=2)
			{
				_glowDirect=2;
			}
	     }
		 
		 private function rolloverHandler(evt:MouseEvent):void
		 {
			 TimerManager.getInstance().remove(step);
			 this._display.addEventListener(MouseEvent.ROLL_OUT,rolloutHandler);
		 }
		 
		 private function rolloutHandler(evt:MouseEvent):void
		 {
			 TimerManager.getInstance().add(this._glowRate,step);
			 this._display.removeEventListener(MouseEvent.ROLL_OUT,rolloutHandler);
		 }
		 
		 public function endGlow():void
		 {
			 TimerManager.getInstance().remove(step);
			 this._display.removeEventListener(MouseEvent.ROLL_OVER,rolloverHandler);
			 _display.filters=null;
			 _display=null;
			 this._glow=null;
			 this._glowArr=null;
			 this._glowColor=0;
			 this._glowDirect=2;
			 this._glowW=0;
			 this._glowRate=0;
		 }
		 
		 public function get isGlowing():Boolean
		 {
			 if(this._display!=null &&this._display.filters!=null)
			 {
				 return true;
			 }
			 return false;
		 }

	}
	
}
