package com.scaleform.fxplayer {
    
    import flash.display.MovieClip;
    import flash.events.MouseEvent;
    import flash.geom.Rectangle;
    import flash.text.TextField;
    import flash.external.ExternalInterface;

    public class Slider extends MovieClip {
        
        [Inspectable(defaultValue = "button")]
        public var controlType:String = "button";
        [Inspectable(defaultValue="-1")]
        public var controlIdx:int = -1;
        
        public var label:TextField;
        public var value:TextField;
        public var focus:MovieClip;
        public var grip:Button;
        public var bar:MovieClip;
               
        protected var _gripBounds:Rectangle;
        
        public function Slider() {
            var gw:Number = grip.width;
            var gh:Number = grip.height;                        
            _gripBounds = new Rectangle(Math.round(gw / 2), Math.round(gh / 2) + 1, bar.width - gw, 0);
            
            grip.addEventListener(MouseEvent.MOUSE_DOWN, handleMouseDown, false, 0, true);
            grip.addEventListener(MouseEvent.MOUSE_UP, handleMouseUp, false, 0, true);
        }
        
        public function get position():Number {
            return (grip.x - _gripBounds.x) / _gripBounds.width;
        }
        public function set position(v:Number):void {
            grip.x = _gripBounds.x + Math.min(Math.max(0, v), 1) * _gripBounds.width;
        }
        
        protected function handleMouseDown(e:MouseEvent):void {
            var gw:Number = grip.width;
            var gh:Number = grip.height;            
            grip.startDrag(false, _gripBounds);
            stage.addEventListener(MouseEvent.MOUSE_MOVE, handleGripDrag, false, 0, true);
            stage.addEventListener(MouseEvent.MOUSE_UP, handleGripOut, false, 0, true);
        }
        
        protected function handleMouseUp(e:MouseEvent):void {            
            grip.stopDrag();
            stage.removeEventListener(MouseEvent.MOUSE_MOVE, handleGripDrag);
            stage.removeEventListener(MouseEvent.MOUSE_UP, handleGripOut);            
        }
        
        protected function handleGripDrag(e:MouseEvent):void {
            if (controlIdx >= 0) {
                trace(position);
                ExternalInterface.call(controlType + "Change", controlIdx, position);
            }
        }
        
        protected function handleGripOut(e:MouseEvent):void {
            handleMouseUp(e);
        }
    }
    
}
