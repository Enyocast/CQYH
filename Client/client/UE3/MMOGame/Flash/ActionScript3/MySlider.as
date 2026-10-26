

/**********************************************************************
 Copyright (c) 2009 Scaleform Corporation. All Rights Reserved.

 Portions of the integration code is from Epic Games as identified by Perforce annotations.
 Copyright © 2010 Epic Games, Inc. All rights reserved.
 
 Licensees may use this file in accordance with the valid Scaleform
 License Agreement provided with the software. This file is provided 
 AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, 
 MERCHANTABILITY AND FITNESS FOR ANY PURPOSE.
**********************************************************************/

/*
*/
package ActionScript3
{

import flash.external.ExternalInterface; 

    import flash.display.DisplayObject;
    import flash.display.MovieClip;
    import flash.events.Event;
    import flash.events.MouseEvent;
    import flash.geom.Point;
    
    import scaleform.gfx.FocusManager;
    import scaleform.gfx.MouseEventEx;
    
    import scaleform.clik.constants.ConstrainMode;
    import scaleform.clik.constants.InvalidationType;
    import scaleform.clik.core.UIComponent;
    import scaleform.clik.events.InputEvent;
    import scaleform.clik.events.ComponentEvent;
    import scaleform.clik.events.SliderEvent;
    import scaleform.clik.constants.ControllerType;
    import scaleform.clik.ui.InputDetails;
    import scaleform.clik.constants.InputValue;
    import scaleform.clik.constants.NavigationCode;
    import scaleform.clik.utils.Constraints;

[InspectableList("disabled", "visible", "liveDragging", "minimum", "maximum", "value", "snapping", "snapInterval", "offsetLeft", "offsetRight", "enableInitCallback", "soundMap")]
class MySlider extends UIComponent {
	
// Constants:

       [Inspectable(defaultValue="true")]
        public var liveDragging:Boolean = true;
        /** The mouse state of the button.  Mouse states can be "default", "disabled". */
        public var state:String = "default";
        /** Left offset for the thumb. A positive value will push the thumb inward. */
        [Inspectable(defaultValue=0, verbose=1)]
        public var offsetLeft:Number = 0;
        /** Right offset for the thumb. A positive value will push the thumb inward. */
        [Inspectable(defaultValue=0, verbose=1)]
        public var offsetRight:Number = 0;
        
    // Private Properties:
        protected var _minimum:Number = 0;
        protected var _maximum:Number = 10;
        protected var _value:Number = 0;
        protected var _snapInterval:Number = 1;
        protected var _snapping:Boolean = false;
        protected var _dragOffset:Object;
        protected var _trackDragMouseIndex:Number;
        protected var _trackPressed:Boolean = false;
        protected var _thumbPressed:Boolean = false;
        
    // UI Elements:
        /** A reference to the thumb symbol in the Slider, used to display the slider {@code value}, and change the {@code value} via dragging. */
        public var thumb:Button;
        /** A reference to the track symbol in the Slider used to display the slider range, but also to jump to a specific value via clicking. */
        public var track:Button;
        
    // Initialization:
        public function MySlider() {
            super();
        }
        
        override protected function preInitialize():void {
            constraints = new Constraints(this, ConstrainMode.REFLOW);
        }
        
        override protected function initialize():void {
            super.initialize();
            tabChildren = false;
            mouseEnabled = mouseChildren = enabled;
        }
        
    // Public getter / setters:
        [Inspectable(defaultValue="true")]
        override public function get enabled():Boolean { return super.enabled; }
        override public function set enabled(value:Boolean):void {
            if (value == super.enabled) { return; }
            super.enabled = value;
            thumb.enabled = track.enabled = value;
            // setState(defaultState);
        }
        
        /**
         * Enable/disable focus management for the component. Setting the focusable property to 
         * {@code focusable=false} will remove support for tab key, direction key and mouse
         * button based focus changes.
         */
        [Inspectable(defaultValue="true")]
        override public function get focusable():Boolean { return _focusable; }
        override public function set focusable(value:Boolean):void { 
            super.focusable = value;
            tabChildren = false;
        }
        
        /**
         * The value of the slider between the {@code minimum} and {@code maximum}.
         * @see #maximum
         * @see #minimum
         */
        [Inspectable(defaultValue="0")]
        public function get value():Number { return _value; }
        public function set value(value:Number):void {
            _value = lockValue(value);
            dispatchEvent( new SliderEvent(SliderEvent.VALUE_CHANGE, false, true, _value) );
            draw();
        }
        
        /**
         * The maximum allowed value. The {@code value} property will always be less than or equal to the {@code maximum}. 
         */
        [Inspectable(defaultValue="10")]
        public function get maximum():Number { return _maximum; }
        public function set maximum(value:Number):void {
            _maximum = value;
        }
        
        /**
         * The minimum allowed value. The {@code value} property will always be greater than or equal to the {@code minimum}. 
         */
        [Inspectable(defaultValue="0")]
        public function get minimum():Number { return _minimum; }
        public function set minimum(value:Number):void {
            _minimum = value;
        }
        
        /**
         * The {@code value} of the {@code Slider}, to make it polymorphic with a {@link ScrollIndicator}.
         */
        public function get position():Number { return _value; }
        public function set position(value:Number):void { _value = value; }
        
        /**
         * Whether or not the {@code value} "snaps" to a rounded value. When {@code snapping} is {@code true}, the value can only be set to multiples of the {@code snapInterval}.
         * @see #snapInterval
         */
        [Inspectable(defaultValue="false")]
        public function get snapping():Boolean { return _snapping; }
        public function set snapping(value:Boolean):void {
            _snapping = value;
            invalidateSettings();
        }
        
        /**
         * The interval to snap to when {@code snapping} is {@code true}.
         * @see #snapping
         */
        [Inspectable(defaultValue="1")]
        public function get snapInterval():Number { return _snapInterval; }
        public function set snapInterval(value:Number):void {
            _snapInterval = value;
            invalidateSettings();
        }
        
    // Public Methods:
        /** 
         * Marks the settings of the Slider (max, mix, snapping, snap interval) as invalid. These settings will be updated on the next Stage.RENDER event. 
         */
        public function invalidateSettings():void {
            invalidate(InvalidationType.SETTINGS);
        }
        
        /** @exclude */
        override public function handleInput(event:InputEvent):void {
            if (event.isDefaultPrevented()) { return; }
            var details:InputDetails = event.details;
            var index = details.controllerIndex;
            
            var keyPress:Boolean = (details.value == InputValue.KEY_DOWN || details.value == InputValue.KEY_HOLD);
            switch (details.navEquivalent) {
                    case NavigationCode.RIGHT:
                    if (keyPress) { 
                        value += _snapInterval;
                        event.handled = true;
                    }
                    break;
                case NavigationCode.LEFT:
                    if (keyPress) {
                        value -= _snapInterval;
                        event.handled = true;
                    }
                    break;
                
                case NavigationCode.HOME:
                    if (!keyPress) {
                        value = minimum;
                        event.handled = true;
                    }
                    break;
                case NavigationCode.END:
                    if (!keyPress) {
                        value = maximum;
                        event.handled = true;
                    }
                    break;
                default:
                    break;
            }
        }
        
        /** @exclude */
        override public function toString():String { 
            return "[CLIK Slider " + name + "]";
        }
        
    // Protected Methods:
        override protected function configUI():void {
            addEventListener(InputEvent.INPUT, handleInput, false, 0, true);
            
            thumb.addEventListener(MouseEvent.MOUSE_DOWN, beginDrag, false, 0, true);
            track.addEventListener(MouseEvent.MOUSE_DOWN, trackPress, false, 0, true);
            
            tabEnabled = true;
            thumb.focusTarget = track.focusTarget = this;
            thumb.enabled = track.enabled = enabled;
            
            thumb.lockDragStateChange = true;
            constraints.addElement("track", track, Constraints.LEFT | Constraints.RIGHT);
        }
        
        override protected function draw():void {
            if (isInvalid(InvalidationType.STATE)) {
                gotoAndPlay(!enabled ? "disabled" : (_focused ? "focused" : "default"));
            }
            
            // Resize and update constraints
            if (isInvalid(InvalidationType.SIZE)) {
                setActualSize(_width, _height);
                constraints.update(_width, _height);
            }
            
            updateThumb();
        }
        
        override protected function changeFocus():void {
            super.changeFocus();
            invalidateState();
            
            // NFM: Moved here from within draw().
            if (enabled) {
                if (!_thumbPressed) {
                    thumb.displayFocus = (_focused != 0);
                }
                if (!_trackPressed) {
                    track.displayFocus = (_focused != 0);
                }
            }
        }
        
        protected function updateThumb():void {
            if (!enabled) { return; }
            var trackWidth:Number = (_width - offsetLeft - offsetRight);
            thumb.x = ((_value - _minimum) / (_maximum - _minimum) * trackWidth) - thumb.width / 2 + offsetLeft;
        }
        
        protected function beginDrag(e:MouseEvent):void {
            _thumbPressed = true;
            
            var lp:Point = globalToLocal( new Point(e.stageX, e.stageY) );
            _dragOffset = { x: (lp.x - thumb.x) - thumb.width / 2 };
            
            stage.addEventListener(MouseEvent.MOUSE_MOVE, doDrag, false, 0, true);
            stage.addEventListener(MouseEvent.MOUSE_UP, endDrag, false, 0, true);
        }
        
        protected function doDrag(e:MouseEvent):void {
            var lp:Point = globalToLocal( new Point(e.stageX, e.stageY) );
            var thumbPosition:Number = lp.x - _dragOffset.x;
            var trackWidth:Number = (_width - offsetLeft - offsetRight);
            var newValue:Number = lockValue( (thumbPosition - offsetLeft) / trackWidth * (_maximum - _minimum) + _minimum );
            
            if (value == newValue) { return; }
            _value = newValue;
            
            updateThumb();
            
            if (liveDragging) {
                dispatchEvent( new SliderEvent(SliderEvent.VALUE_CHANGE, false, true, _value) );
            }
        }
        
        protected function endDrag(e:MouseEvent):void {
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
        
        protected function trackPress(e:MouseEvent):void {
            _trackPressed = true;
            
            track.focused = _focused;
            
            var trackWidth:Number = (_width - offsetLeft - offsetRight);
            var newValue:Number = lockValue( (e.localX * scaleX - offsetLeft) / trackWidth * (_maximum - _minimum) + _minimum);
            
            if (value == newValue) { return; }
            value = newValue;
            
            if (!liveDragging) { 
                dispatchEvent( new SliderEvent(SliderEvent.VALUE_CHANGE, false, true, _value) );
            }
            
            // Pressing on the track moves the grip to the cursor and the thumb becomes draggable.
            _trackDragMouseIndex = 0 // e.mouseIdx; // @todo, NFM: This needs to use the multi-controller system.
            
            // thumb.onPress(trackDragMouseIndex);
            _dragOffset = {x:0};
        }
        
        // Ensure the value is in range and snap it to the snapInterval
        protected function lockValue( lvalue:Number ):Number {
            lvalue = Math.max(_minimum, Math.min(_maximum, lvalue));
            if (!snapping) { return lvalue; }
            var result:Number = Math.round(lvalue / snapInterval) * snapInterval;
            return result;
        }
        
        protected function scrollWheel(delta:Number):void {
            if (_focused) {
                value -= delta * _snapInterval;
                dispatchEvent( new Event(Event.CHANGE) ); 
            }
        }
}

}