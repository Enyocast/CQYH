package ActionScript3.Common {
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.InputEvent;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import scaleform.clik.events.SliderEvent;
	import scaleform.clik.controls.Slider;
	
	
	public class CustomSlider extends Slider {
		

		public var nextBtn:Button;
        public var prevBtn:Button;
		public function CustomSlider() {
			super();
		}
		
		override protected function configUI():void {
            super.configUI();
            nextBtn.addEventListener(ButtonEvent.CLICK, onNext, false, 0, true);
            prevBtn.addEventListener(ButtonEvent.CLICK, onPrev, false, 0, true);

            prevBtn.enabled = nextBtn.enabled = enabled;
            prevBtn.autoRepeat = nextBtn.autoRepeat = true;
            prevBtn.focusable = nextBtn.focusable = false;
            prevBtn.focusTarget = nextBtn.focusTarget = this;
            prevBtn.tabEnabled = nextBtn.tabEnabled = false;
            prevBtn.mouseEnabled = nextBtn.mouseEnabled = true;
        }    
        protected function onNext( event:ButtonEvent ):void {
            value = _value + 1;
        }
        
        protected function onPrev( event:ButtonEvent ):void {
            value = _value - 1;
        }
		
		override protected function updateThumb():void {
            if (!enabled) { return; }
			var trackWidth:Number = (_height - offsetLeft - offsetRight);
			thumb.y = ((_value - _minimum) / (_maximum - _minimum) * trackWidth) - thumb.height / 2 + offsetLeft;
			
        }
		override protected function beginDrag(e:MouseEvent):void {
			_thumbPressed = true;
			
			var lp:Point = globalToLocal( new Point(e.stageX, e.stageY) );
			_dragOffset = { y: (lp.y - thumb.y) - thumb.height / 2 };
			
			stage.addEventListener(MouseEvent.MOUSE_MOVE, doDrag, false, 0, true);
			stage.addEventListener(MouseEvent.MOUSE_UP, endDrag, false, 0, true);
        }
		
		override protected function doDrag(e:MouseEvent):void {
			var lp:Point = globalToLocal( new Point(e.stageX, e.stageY) );
			var thumbPosition:Number = lp.y - _dragOffset.y;
			var trackWidth:Number = (_height- offsetLeft - offsetRight);
			var newValue:Number = lockValue( (thumbPosition - offsetLeft) / trackWidth * (_maximum - _minimum) + _minimum );
			
			if (value == newValue) { return; }
			_value = newValue;
			
			updateThumb();
			
			if (liveDragging) {
				dispatchEvent( new SliderEvent(SliderEvent.VALUE_CHANGE, false, true, _value) );
			}
        }
        
       override protected function endDrag(e:MouseEvent):void {
            stage.removeEventListener(MouseEvent.MOUSE_MOVE, doDrag, false);
            stage.removeEventListener(MouseEvent.MOUSE_UP, endDrag, false);
            
            if (!liveDragging) { 
                dispatchEvent( new SliderEvent(SliderEvent.VALUE_CHANGE, false, true, _value) ); 
            }
            
            // If the thumb became draggable on a track press,
            // manually generate the thumb events.
            /* 
            if (trackDragMouseIndex != undefined) {
                if (!thumb.hitTest(_root._xmouse, _root._ymouse)) {
                    thumb.onReleaseOutside(trackDragMouseIndex);
                } else {
                    thumb.onRelease(trackDragMouseIndex);
                }
            }
            */
            
            _trackDragMouseIndex = undefined;
            _thumbPressed = false;
            _trackPressed = false;
        }
		 override protected function trackPress(e:MouseEvent):void {
			 _trackPressed = true;
			 
			 track.focused = _focused;
			 
			 var trackWidth:Number = (_height - offsetLeft - offsetRight);
			 var newValue:Number = lockValue( (e.localY * scaleY - offsetLeft) / trackWidth * (_maximum - _minimum) + _minimum);
			 
			 if (value == newValue) { return; }
			 value = newValue;
			 
			 if (!liveDragging) { 
				 dispatchEvent( new SliderEvent(SliderEvent.VALUE_CHANGE, false, true, _value) );
			 }
			 
			 // Pressing on the track moves the grip to the cursor and the thumb becomes draggable.
			 _trackDragMouseIndex = 0 // e.mouseIdx; // @todo, NFM: This needs to use the multi-controller system.
			 
			 // thumb.onPress(trackDragMouseIndex);
			 _dragOffset = {y:0};
        }

        

	}
	
}
