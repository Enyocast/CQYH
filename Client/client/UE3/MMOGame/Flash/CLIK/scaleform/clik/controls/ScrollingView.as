/**
 * An abstract class used to display a list of data, and set a selectedIndex (or indices). This class only manages data, and instantiating itemRenderers, but the sub-class must request the renderers and arrange them. It is sub-classed by the ScrollingList and TileList components.
 */

/**************************************************************************

Filename    :   CoreList.as

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
 
package scaleform.clik.controls {
    
    import flash.display.DisplayObject;
    import flash.display.Sprite;
    import flash.events.Event;
    import flash.events.MouseEvent;
    import flash.geom.Rectangle;
    import flash.utils.getDefinitionByName;
    import scaleform.gfx.MouseEventEx;
    
    import scaleform.clik.constants.InvalidationType;
    import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ScrollBar;
    import scaleform.clik.data.DataProvider;
    import scaleform.clik.events.InputEvent;
    import scaleform.clik.events.ListEvent;
    import scaleform.clik.events.ButtonEvent;
    import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.interfaces.IScrollBar;
    import scaleform.clik.interfaces.IListItemRenderer;
        
    public class ScrollingView extends UIComponent {
        
		// UI Elements:
		protected var _scrollBar:IScrollBar;
		protected var _displayMc:Object;
		protected var _isHorizontal:Boolean = false;
		protected var _scrollPageSize:Number = 1;


    // Initialization:
        public function ScrollingView() {
            super();
        }
        
        
        
		[Inspectable(type = "String")]
		public function get displayMc():Object
		{
			return _displayMc;
		}
		public function set displayMc(value:Object):void
		{
            if (value is String) {
                if (value.toString() == "" || parent == null) { return; }
                value = parent.getChildByName(value.toString());
                if (value == null) { return; }
            }			
			_displayMc = value;
			_displayMc.addEventListener(MouseEvent.MOUSE_WHEEL, handleMouseWheel, false, 0, true);
			updateScrollBar();
		}
		
		
		[Inspectable(type = "String")]
		public function get scrollBar():Object
		{
			return _scrollBar;
		}
		public function set scrollBar(value:Object):void
		{
            if (value is String) {
                if (value.toString() == "" || parent == null) { return; }
                value = parent.getChildByName(value.toString());
                if (value == null) { return; }
            }
			
			_scrollBar 	= value as IScrollBar;
			if(_scrollBar){
				_scrollBar.addEventListener(Event.SCROLL, handleScroll, false, 0, true);
				_scrollBar.addEventListener(Event.CHANGE, handleScroll, false, 0, true);
				_scrollBar.focusTarget = this;
				_scrollBar.tabEnabled = false;				
				_scrollBar.position   = 0;
				updateScrollBar();
			}
		}
		
		protected function handleScroll(event:Event):void
		{
			if(_displayMc==null)return;
			
			if(_isHorizontal)
			{
				_displayMc.x = x - _scrollBar.position;
			}
			else{
				_displayMc.y = y - _scrollBar.position;
			}
		}		
		
		public function updateScrollBar():void
		{
			if (_scrollBar == null || _displayMc == null)return;

			if (_scrollBar is ScrollIndicator)
			{
				var scrollIndicator:ScrollIndicator = _scrollBar as ScrollIndicator;
				if(_isHorizontal)
				{
					_scrollPageSize = _displayMc.width-width;
					_displayMc.y = y;
				}
				else
				{
					_scrollPageSize = _displayMc.height-height;
					_displayMc.x = x;					
				}
				
				_isHorizontal = scrollIndicator.isHorizontal;
				scrollIndicator.setScrollProperties(_scrollPageSize, 0, _scrollPageSize,20);
			}
			_scrollBar.validateNow();
		}

        override protected function configUI():void {
            super.configUI();
            
        }        
        
        protected function handleMouseWheel(event:MouseEvent):void {
			if(_scrollBar){
				_scrollBar.position -= (event.delta > 0 ? 1 : -1) * 20;// _pageScrollSize;
			}
        }
        

    }
}
