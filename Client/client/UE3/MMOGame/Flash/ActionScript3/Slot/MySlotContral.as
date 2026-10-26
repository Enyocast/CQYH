
package ActionScript3.Slot
{

	import flash.display.MovieClip;
	import flash.display.DisplayObject;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import ActionScript3.Slot.MySlot;
	import flash.external.ExternalInterface;
	import scaleform.gfx.Extensions;

	public class MySlotContral
	{
		protected var _mouseDown:Boolean = false;
		protected var _mouseDrag:Boolean = false;
		
		protected var _PressX:Number;
		protected var _PressY:Number;

		public var parentSlot:MySlot = null;

		public function SetState( frameName:String ):void
		{
			if (parentSlot!=null)
			{
				parentSlot.SetState(frameName);
			}
		}

		public function Init( slot:MySlot ):void
		{
			parentSlot = slot;
			if (parentSlot!=null)
			{
				parentSlot.addEventListener(MouseEvent.ROLL_OVER, handleMouseRollOver, false, 0, true);
				parentSlot.addEventListener(MouseEvent.ROLL_OUT, handleMouseRollOut, false, 0, true);
				parentSlot.addEventListener(MouseEvent.MOUSE_DOWN, handleMousePress, false, 0, true);
				parentSlot.addEventListener(MouseEvent.MOUSE_MOVE,handleMouseMove, false, 0, true);
				parentSlot.addEventListener(MouseEvent.MOUSE_UP, handleMouseRelease, false, 0, true);
				parentSlot.addEventListener(MouseEvent.CLICK,handleMouseClick, false, 0, true);
				parentSlot.addEventListener(MouseEvent.DOUBLE_CLICK,handleMouseDbClick, false, 0, true);
			}
		}

		public function UnInit():void
		{
			if (parentSlot!=null)
			{
				parentSlot.removeEventListener(MouseEvent.ROLL_OVER, handleMouseRollOver );
				parentSlot.removeEventListener(MouseEvent.ROLL_OUT, handleMouseRollOut);
				parentSlot.removeEventListener(MouseEvent.MOUSE_DOWN, handleMousePress);
				parentSlot.removeEventListener(MouseEvent.MOUSE_MOVE,handleMouseMove);
				parentSlot.removeEventListener(MouseEvent.MOUSE_UP, handleMouseRelease  );
				parentSlot.removeEventListener(MouseEvent.CLICK,handleMouseClick);
				parentSlot.removeEventListener(MouseEvent.DOUBLE_CLICK, handleMouseDbClick);
				
				if (_mouseDrag==true )
				{
					_mouseDrag=false;
					parentSlot.stage.removeEventListener(MouseEvent.MOUSE_UP, handleReleaseDrag, false);
				}				
			}
		}

		protected function isLeftMouseBtn(event:MouseEvent):Boolean
		{
			var sfEvent:MouseEventEx = event as MouseEventEx;
			var btnIdx:uint = (sfEvent == null) ? 0:sfEvent.buttonIdx;
			if(btnIdx == 0)	return true;
			else			return false;
		}
		
		protected function isRightMouseBtn(event:MouseEvent):Boolean
		{
			var sfEvent:MouseEventEx = event as MouseEventEx;
			var btnIdx:uint = (sfEvent == null) ? 0:sfEvent.buttonIdx;
			if(btnIdx == 1)	return true;
			else			return false;
		}		
		
		protected function startDrag():void
		{
			if(parentSlot==null)return;
			_mouseDrag = true;
			if(parentSlot.CanSlotDrag()){
				ExternalInterface.call("ASSlot_StartDrag", parentSlot);
			}
			parentSlot.stage.addEventListener(MouseEvent.MOUSE_UP, handleReleaseDrag, false, 0, true);
		}
		
		protected function releaseDrag(slot:DisplayObject):void
		{
			ExternalInterface.call("ASTrace","---------------------parentSlot="+parentSlot );
			if(parentSlot==null)return;
			
			ExternalInterface.call("ASTrace","---------------------parentSlot.SlotType="+parentSlot.SlotType+"   _mouseDrag="+_mouseDrag );
				
			if(_mouseDrag == true){
				_mouseDown = false;
				_mouseDrag = false;
				if(parentSlot.CanSlotDrag()){
					ExternalInterface.call("ASSlot_ReleaseDrag", parentSlot,slot);
				}
				parentSlot.stage.removeEventListener(MouseEvent.MOUSE_UP, handleReleaseDrag);
			}
		}		
		
		// Mouse-only input
		protected function handleMousePress(event:MouseEvent):void
		{
			if (parentSlot && parentSlot.enabled==false)
			{
				return;
			}
			
			SetState("down");
			
			if ( isLeftMouseBtn(event) )
			{
				_mouseDown = true;
				_mouseDrag = false;
				_PressX=event.stageX;
				_PressY=event.stageY;
				ExternalInterface.call("ASHideTips");
				//ExternalInterface.call("ASSlot_MouseLeftPress", parentSlot );
			}
		}
		
		protected function handleMouseMove(event:MouseEvent):void
		{
			if (parentSlot && parentSlot.enabled==false)
			{
				return;
			}
			if (_mouseDown==true && _mouseDrag==false)
			{
				if( (_PressX-event.stageX)*(_PressX-event.stageX) + (_PressY-event.stageY)*(_PressY-event.stageY) <  25 )
				{
					startDrag();
				}
			}
		}
		
		protected function handleMouseRollOut(event:MouseEvent):void
		{
			
			if (parentSlot && parentSlot.enabled==false)
			{
				return;
			}
			if(_mouseDrag==false)
			{
				ExternalInterface.call("ASHideTips");
			}
			SetState("up");
			
			ExternalInterface.call("ASDragOut", parentSlot, parentSlot.SlotType, parentSlot.containerID, parentSlot.slotID);
			
			if (_mouseDown==true && _mouseDrag==false)
			{
				startDrag();
			}
		}
		
		

		protected function handleMouseRelease(event:MouseEvent):void
		{
			if (parentSlot && parentSlot.enabled==false)
			{
				return;
			}
			
			//非拖动
			if ( isLeftMouseBtn(event) ){
				if(_mouseDrag == false){
					_mouseDown = false;
					_mouseDrag = false;
				}
				SetState("over");
			}
		}

		protected function handleReleaseDrag(event:MouseEvent):void
		{
			if (parentSlot && parentSlot.enabled==false)
			{
				return;
			}
			//拖动状态
			if ( isLeftMouseBtn(event) ){
				var targObject:DisplayObject = Extensions.getMouseTopMostEntity();
				var targSlot:MySlot		= 	 targObject as MySlot;
				ExternalInterface.call("ASTrace","---------------------targObject="+targObject+"  targSlot="+targSlot );
				//releaseDrag( targObject );//event.target as MySlot  );
				ExternalInterface.call("ASTrace","---------------------parentSlot.SlotType="+parentSlot.SlotType+"   _mouseDrag="+_mouseDrag );
				if(_mouseDrag == true){
					_mouseDown = false;
					_mouseDrag = false;
					if(parentSlot.CanSlotDrag()){
						ExternalInterface.call("ASTrace","---------------------ASSlot_ReleaseDrag");
						ExternalInterface.call("ASSlot_ReleaseDrag", parentSlot,targObject);
					}
					parentSlot.stage.removeEventListener(MouseEvent.MOUSE_UP, handleReleaseDrag);
				}
				ExternalInterface.call("ASTrace","---------------------handleReleaseDrag" );
			}
		}

		protected function handleMouseRollOver(event:MouseEvent):void
		{
			if (parentSlot && parentSlot.enabled==false)
			{
				return;
			}
			if(_mouseDrag == false && parentSlot.HaveData){
				ExternalInterface.call("ASRollOverItemSlot", parentSlot, parentSlot.SlotType, parentSlot.containerID, parentSlot.slotID );
			}
			else
			{
				ExternalInterface.call("ASDragOver", parentSlot, parentSlot.SlotType, parentSlot.containerID, parentSlot.slotID);
			}
			
			SetState("over");
		}

		protected function handleMouseClick(event:MouseEvent):void
		{
			if (parentSlot && parentSlot.enabled==false)
			{
				return;
			}
			
			if ( isLeftMouseBtn(event) )
			{
				ExternalInterface.call("ASSlot_MouseLeftClick", parentSlot);
				ExternalInterface.call("ASHideTips");				
			}
			else if( isRightMouseBtn(event) )
			{
				ExternalInterface.call("ASSlot_MouseRightClick", parentSlot );
				ExternalInterface.call("ASHideTips");								
			}
			
		}

		protected function handleMouseDbClick(event:MouseEvent):void
		{
			if (parentSlot && parentSlot.enabled==false)
			{
				return;
			}
			
			if ( isLeftMouseBtn(event) )
			{
				ExternalInterface.call("ASSlot_MouseLeftDbClick", parentSlot );
				ExternalInterface.call("ASHideTips");				
			}
			else if( isRightMouseBtn(event) )
			{
				ExternalInterface.call("ASSlot_MouseRightDbClick", parentSlot );
				ExternalInterface.call("ASHideTips");								
			}

		}

	}
}