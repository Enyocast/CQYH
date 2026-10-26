package ActionScript3.Common {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import ActionScript3.MyScrollPanel;
	import flash.text.TextField;
	
	
	public class CustomScrollBar extends ScrollBar {

        public var btn_arrow:Button;
		public function CustomScrollBar():void {


	    }
		
		override protected function configUI():void 
		{						
            super.configUI();
			btn_arrow.mouseChildren=false;
			btn_arrow.mouseEnabled=false;
			
		 }
		 		
	    override public function set position(value:Number):void 
		{
            value = Math.round(value);
            //if (value == position) { return; }
			//super.position = value;
			
            value = Math.max(_minPosition, Math.min(_maxPosition, value));
            if (value == _position) { return; }
            _position = value;
            dispatchEvent(new Event(Event.SCROLL));
			updateThumbPosition();
            //invalidateData();
			
            updateScrollTarget();
			
			//trace( _position + "/" + _maxPosition );
        }
		
		override protected function handleTargetScroll(event:Event):void {
            if (_isDragging) { return; } 
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
		
		// Public Methods:
		/** @exclude */
		override public function get availableHeight():Number {
			return track.height - thumb.height-upArrow.height-downArrow.height + offsetBottom + offsetTop;
		}
		
	    override protected function drawLayout():void {
            // NFM: Reset the y position of the thumb so that the _height is valid when the constraints are updated.
            thumb.y = track.y - offsetTop+upArrow.height;
			btn_arrow.y=thumb.y+((thumb.height-btn_arrow.height-8)>>1);
            if (isHorizontal) {
				constraints.update(_width, _height);
            } else {
                constraints.update(_width, _height);
            }
            if (isHorizontal && actualWidth != width) {
                var yScaleFix:Number = width / actualWidth;
                scaleY = yScaleFix;

            }
        }
		
		 override protected function updateThumb():void {
            var per:Number = Math.max(1, _maxPosition - _minPosition + _pageSize);
            var trackHeight:Number = track.height + offsetTop + offsetBottom-upArrow.height; // Uses the track as the height indicator, since ScrollIndicator can use just gfx as a track.
            thumb.height = Math.max(_minThumbSize, Math.min(trackHeight, _pageSize / per * trackHeight));
            if (thumb is UIComponent) { (thumb as UIComponent).validateNow(); }
            updateThumbPosition();
        }
        
        override protected function updateThumbPosition():void {
            var percent:Number = (_position - _minPosition) / (_maxPosition - _minPosition);
            var top:Number = track.y - offsetTop+upArrow.height;
            var yPos:Number = Math.round(percent * availableHeight + top);
            
            thumb.y = Math.max(top, Math.min(track.y + track.height - thumb.height + offsetBottom-downArrow.height, yPos));
			var thumbVisible = !(isNaN(percent) || isNaN(_pageSize) || _maxPosition <= 0 || _maxPosition == Infinity);
			if(thumbVisible!= thumb.visible){
				thumb.visible = thumbVisible;
			}
            //thumb.visible = !(isNaN(percent) || isNaN(_pageSize) || _maxPosition <= 0 || _maxPosition == Infinity);
			btn_arrow.y=thumb.y+((thumb.height-8)>>1);
			//btn_arrow.visible=thumb.visible;
			if(thumbVisible!= btn_arrow.visible){
				btn_arrow.visible = thumbVisible;
			}
			
            var showThumb:Boolean = thumb.visible && enabled;
            if (upArrow) {
				var upArrowEnabled = showThumb && (_position > _minPosition);
				if(upArrowEnabled!=upArrow.enabled){
	                upArrow.enabled = upArrowEnabled;
    	            upArrow.validateNow();
				}
            }
            if (downArrow) {
				var downArrowEnabled = showThumb && (_position < _maxPosition);
				if(downArrowEnabled!=downArrow.enabled){
                	downArrow.enabled = downArrowEnabled;
                	downArrow.validateNow();
				}
            }
			if(showThumb!=track.enabled){
	            track.enabled = track.mouseEnabled = showThumb;
			}
        }
	}
	
}
