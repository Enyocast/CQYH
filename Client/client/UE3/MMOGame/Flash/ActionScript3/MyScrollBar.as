package ActionScript3
{
	import scaleform.clik.controls.ScrollBar;
	import ActionScript3.MyScrollPanel;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	
	public class MyScrollBar extends ScrollBar
	{
        override protected function handleTargetScroll(event:Event):void {
            if (_isDragging) { return; } // Don't listen for scroll events while the thumb is dragging.
            var target:TextField = _scrollTarget as TextField;
            if (target != null) {
                setScrollProperties(target.bottomScrollV - target.scrollV, 1, target.maxScrollV);
                position = target.scrollV;
            }
			else 
			{
				var MySP:MyScrollPanel = _scrollTarget as MyScrollPanel;
				if (MySP != null) 
				{
					
					setScrollProperties(MySP.bottomScrollV - MySP.scrollV, 1, MySP.maxScrollV);
					position = MySP.scrollV;
				}
			}
			
        }
		
		 override protected function configUI():void 
		 {						
		 	
            super.configUI();
			
			if(_scrollTarget)
			{
				
				var mySP:MyScrollPanel = _scrollTarget as MyScrollPanel;
				
				if(mySP)
				{
					mySP.addEventListener(MouseEvent.MOUSE_WHEEL, scrollPanelhandleMouseWheel , false, 0, true);
				}				
			}
			
		 }
		
        override public function set position(value:Number):void {
            value = Math.round(value);
            //if (value == position) { return; }
			//super.position = value;
			
            value = Math.max(_minPosition, Math.min(_maxPosition, value));
            if (value == _position) { return; }
            _position = value;
            dispatchEvent(new Event(Event.SCROLL));
            //invalidateData();
			updateThumbPosition();
            updateScrollTarget();
			
			//trace( _position + "/" + _maxPosition );
        }
		
		
		function scrollPanelhandleMouseWheel( e:MouseEvent )
		{
			handleMouseWheel(e);
		}
	}
}