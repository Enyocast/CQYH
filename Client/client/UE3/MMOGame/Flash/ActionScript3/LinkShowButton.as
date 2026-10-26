package ActionScript3
{
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	
	import flash.events.MouseEvent;
	import flash.events.Event;
	
	public class LinkShowButton extends Button
	{
		var _ShowMovieClip:MovieClip;
		
		override protected function configUI():void 
		{
			super.configUI();

			//addEventListener( MouseEvent.MOUSE_OVER, MouseRollOverShow, false, 0, true);
			//addEventListener( MouseEvent.MOUSE_OUT, MouseRollOutShow, false, 0, true);
			//addEventListener( MouseEvent.MOUSE_DOWN, MouseDownShow, false, 0, true);
			//addEventListener( MouseEvent.MOUSE_UP, MouseUpShow, false, 0, true);
		}
		
		//
		override protected function setState(state:String):void
		{
			super.setState( state );
			//
			//trace(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>LinkShowButton State:", state, " _ShowMovieClip:", _ShowMovieClip);
			if( _ShowMovieClip )
			{
				_ShowMovieClip.gotoAndPlay(state);
			}
        }
		//====================================================================================================
		public function get ShowMovieClip():MovieClip
		{
			return _ShowMovieClip;
		}
		
		//
		public function set ShowMovieClip( mc:MovieClip )
		{
			_ShowMovieClip = mc;
		}
		//====================================================================================================
		public function get ShowState():Boolean
		{
			if( _ShowMovieClip != null ){
				return _ShowMovieClip.visible;
			}
			return visible;
		}
		
		//
		public function set ShowState( isVisible:Boolean )
		{
			visible = isVisible;
			
			if( _ShowMovieClip != null ){
				_ShowMovieClip.visible = visible;
			}
		}
		//====================================================================================================
		function MouseRollOverShow( evt:Event )
		{
			if( _ShowMovieClip == null )
			{
				return;
			}
		}
		
		//====================================================================================================
		function MouseRollOutShow( evt:Event )
		{
			if( _ShowMovieClip == null )
			{
				return;
			}
		}
		
		//====================================================================================================
		function MouseDownShow( evt:Event )
		{
			if( _ShowMovieClip == null )
			{
				return;
			}
		}
		
		//====================================================================================================
		function MouseUpShow( evt:Event )
		{
			if( _ShowMovieClip == null )
			{
				return;
			}
		}
	}
}