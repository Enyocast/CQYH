/**************************************************************************

Filename    :   PopUpManager.as

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

﻿package scaleform.clik.managers {
    
    import flash.display.DisplayObject;
    import flash.display.DisplayObjectContainer;
    import flash.display.MovieClip;
    import flash.display.Shape;
    import flash.display.Sprite;
    import flash.display.Stage;
    import flash.events.Event;
    import flash.geom.Point;
    import scaleform.gfx.FocusManager;
    
    public class PopUpManager {
   		protected static var initialized:Boolean = false;
        public static function init(stage:Stage):void {
			if (initialized) { return; }
            PopUpManager._stage = stage;
			
			for(var i:int = 0; i < _canvas.length; ++i)			
			{
				_canvas[i] = new MovieClip();
				(_canvas[i] as MovieClip).mouseEnabled=false;
				(_canvas[i] as MovieClip).name="_canvas"+i;//当前
				_canvas[i].addEventListener(Event.REMOVED, handleRemovePopup, false, 0, true);
				_stage.addChild(_canvas[i]);
			}
            //_defaultPopupCanvas = new MovieClip();
            // Listen to children being removed from the _defaultPopupCanvas to track whether we need to actively keep
            // _defaultPopupCanvas on top of everything else.
            //_defaultPopupCanvas.addEventListener(Event.REMOVED, handleRemovePopup, false, 0, true);
            //_stage.addChild(_defaultPopupCanvas);
			initialized = true;
			
			var dragDropLayer:MovieClip = _canvas[C_DragDropIconLayer] as MovieClip;
			dragDropLayer.mouseEnabled = dragDropLayer.mouseChildren = false;
        }
        
    // Constants:
    
    // Protected Properties:
        protected static var _stage:Stage;
        //protected static var _defaultPopupCanvas:MovieClip;		
		public static const C_CanvasLayerCount = 6;
		public static const C_DragDropIconLayer = 5;
		public static const C_TopMostLayer = 4;
		
		protected static var _canvas:Array = new Array(C_CanvasLayerCount);
		
		protected static var _modalMc:Sprite;
		protected static var _modalBg:Sprite;
		protected static var _dragIcon:DisplayObject;
		
    // Public Methods:
        public static function show(mc:DisplayObject, x:Number = -1, y:Number = -1, scope:DisplayObjectContainer = null, priority:int = 2):void {
            if (!_stage || mc==null) { 
			   trace("PopUpManager has not been initialized _stage and mc",_stage,mc); 
			   return;
			}
			priority = Math.max(0, Math.min(priority, 4));//比较
			var oldX:int = x;
			var oldY:int = y;
			if(x == -1)
			{
				oldX = mc.x;// + parentX;
			}
			if(y == -1)
			{
				oldY = mc.y;// + parentY;
			}
            // Remove from existing parent
            if (mc.parent) { mc.parent.removeChild(mc); }
            
            // Reparent to popup canvas layer
           /// handleStageAddedEvent(null);
            //_defaultPopupCanvas.addChild(mc);
			_canvas[priority].addChild(mc);
            
            // Move to location by scope
            if (!scope) {
                scope = _stage;
            }
            var p:Point = new Point(oldX, oldY); // oscar
            p = scope.localToGlobal(p);
            mc.x = p.x;
            mc.y = p.y;
            //_stage.setChildIndex(_defaultPopupCanvas, _stage.numChildren - 1);
			//AdjustCanvasPriority();
			// _stage.removeEventListener(Event.ADDED, PopUpManager.handleStageAddedEvent, false);
           // _stage.addEventListener(Event.ADDED, PopUpManager.handleStageAddedEvent, false, 0, true);
        }
        
/*		public static function AdjustCanvasPriority():void
		{//遍历
		    trace("AdjustCanvasPriority===",_canvas.length,_stage.numChildren);
			for(var i:int = 0; i < _canvas.length; ++i)			
			{
				 trace("AdjustCanvasPriority+++++++",_canvas.length,_stage.numChildren,_canvas[i],_stage.getChildIndex(_canvas[i]),_stage.numChildren - (C_CanvasLayerCount - i));
				_stage.setChildIndex(_canvas[i], _stage.numChildren - (C_CanvasLayerCount - i));
			}
		}*/
        
		static public function addToDragCanvas(mc:DisplayObject):void
		{
			if (mc.parent) { mc.parent.removeChild(mc); }            
			PopUpManager._canvas[C_DragDropIconLayer].addChild(mc);
		}
		
		static public function removeDragCanvas(mc:DisplayObject):void
		{
			_dragIcon = mc;
			if (mc.parent) { mc.parent.removeChild(mc); }            
		}

        public static function showModal(mc:Sprite, mcX:Number = 0, mcY:Number = 0, bg:Sprite = null, controllerIdx:uint = 0, newFocus:Sprite = null):void {
            if (!_stage) { trace("PopUpManager has not been initialized. Automatic initialization has not occured or has failed; call PopUpManager.init() manually."); return; }
                       
			// Remove previous modal mc and bg if applicable
			// - Background is removed via event listener automatically
			if (_modalMc) { 
                //_defaultPopupCanvas.removeChild(_modalMc); 
				_canvas[C_TopMostLayer].removeChild(_modalMc);
            }
			
			// If mc is null, return (Useful to clear a modal mc)
			if (mc == null) {
                return;
            }
            
            // If bg is null, create an alpha 0 sprite the size of the stage and add it at 0, 0.
            if (bg == null) {
                bg = new Sprite();
                bg.graphics.lineStyle(0, 0xffffff, 0);
                bg.graphics.beginFill(0xffffff, 0);
                bg.graphics.drawRect(0, 0, _stage.stageWidth, _stage.stageHeight);
                bg.graphics.endFill();
            }
			
			// Track current modal mc and bg
			_modalMc = mc;
			_modalBg = bg;
			
            // Reparent to popup canvas layer
            _modalMc.x = mcX;
            _modalMc.y = mcY;
			
			_canvas[C_TopMostLayer].addChild(_modalBg);
			_canvas[C_TopMostLayer].addChild(_modalMc);
			
			//_defaultPopupCanvas.addChild(_modalBg);
            //_defaultPopupCanvas.addChild(_modalMc);
            FocusHandler.getInstance().setFocus(newFocus, controllerIdx, false);
            FocusManager.setModalClip(_modalMc, controllerIdx);
            
            // Get notified when the modal mc is removed for cleanup purposes
			_modalMc.addEventListener(Event.REMOVED_FROM_STAGE, handleRemoveModalMc, false, 0, true);			
           // _stage.addEventListener(Event.ADDED, PopUpManager.handleStageAddedEvent, false, 0, true);
        }
        
    // Protected Methods:
/*        protected static function handleStageAddedEvent(e:Event):void {
            // We make sure that the defaultPopupCanvas is always on top of everything else on the stage
            //_stage.setChildIndex(_defaultPopupCanvas, _stage.numChildren - 1);
			AdjustCanvasPriority();
        }*/
        
        protected static function handleRemovePopup(e:Event):void {
            removeAddedToStageListener();
        }
		
		protected static function handleRemoveModalMc(e:Event):void {
			if (_modalMc)
			{
				_modalMc.removeEventListener(Event.REMOVED_FROM_STAGE, handleRemoveModalMc, false);
			}
				// Remove modal background if applicable
			if(_modalBg)
			{
				//_defaultPopupCanvas.removeChild(_modalBg);
				_canvas[C_TopMostLayer].removeChild(_modalBg);
			}
            
			// Clear tracking variables
			_modalMc = null;
			_modalBg = null;
            
            removeAddedToStageListener();
		}
        
        protected static function removeAddedToStageListener():void {
            
			if (_canvas[C_TopMostLayer].numChildren == 0 && _modalMc == null) { 
               // _stage.removeEventListener(Event.ADDED, PopUpManager.handleStageAddedEvent, false);
            }
			
			//if (_defaultPopupCanvas.numChildren == 0 && _modalMc == null) { 
//                _stage.removeEventListener(Event.ADDED, PopUpManager.handleStageAddedEvent, false);
//            }
        }
    }
    
}