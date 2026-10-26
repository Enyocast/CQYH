package UI_TradeP2P.TradeP2PAS3
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;

	public class ItemSlotContainer extends Button
	{
		public var slot_mc:MyItemSlot;
		public var mask_mc:MovieClip;
		//var eventObj:Object;
		
		override protected function configUI():void
		{
			super.configUI();
			//
			//eventObj = new Object;
			//eventObj.type = "xxxx";
			//eventObj.target = slot_mc;
			mask_mc.visible = false;
			
			mouseChildren = true;
			
			addEventListener( ButtonEvent.PRESS, OnMouseDownSlotContainer );
			addEventListener( ButtonEvent.RELEASE_OUTSIDE, OnDragRelease );
			addEventListener( ButtonEvent.CLICK, OnDragInSlotContainer );
			addEventListener( ButtonEvent.DRAG_OVER, DragOver );
			addEventListener( ButtonEvent.DRAG_OUT, DragOut );
			
			addEventListener( MouseEvent.ROLL_OVER, RollOver ); //mouse in
			addEventListener( MouseEvent.ROLL_OUT, RollOut );	//mouse out
			//addEventListener( MouseEvent.CLICK , MouseRightClickSlotContainer );
			addEventListener( MouseEvent.CLICK , MouseRightClickSlotContainer );
			
			trace("ItemSlotContainer initilized ItemSlot " + (slot_mc is MyItemSlot) );
		}
		//
		public function get containerID():int
		{
			return slot_mc.containerID;
		}
		public function get slotID():int
		{
			return slot_mc.slotID;
		}
		public function get panelType():int
		{
			return slot_mc.SlotType;
		}
		//
		public function set containerID( id:int )
		{
			slot_mc.containerID = id;
		}
		public function set slotID( id:int )
		{
			slot_mc.slotID = id;
		}
		public function set panelType( typeID:int )
		{
			slot_mc.SlotType = typeID;
		}
		
		//
		function MouseRightClickSlotContainer( e:MouseEvent )
		{
			//slot_mc.dispatchEvent( e );
			slot_mc.MouseRightClick( e );
		}
		//
		function OnMouseDownSlotContainer( e:ButtonEvent  )
		{
			//slot_mc.dispatchEvent( e );
			slot_mc.OnMouseDown( e );
		}
		//
		function OnDragInSlotContainer( e:ButtonEvent  )
		{
			//slot_mc.dispatchEvent( e );
			slot_mc.OnDragInSlot( e );
		}
		//
		function DragOver( e:ButtonEvent  )
		{
			//slot_mc.dispatchEvent( e );
			slot_mc.DragOver( e );
		}
		//
		function DragOut( e:ButtonEvent  )
		{
			//slot_mc.dispatchEvent( e );
			slot_mc.DragOut( e );
		}
		//
		function OnDragRelease( e:ButtonEvent  )
		{
			//slot_mc.dispatchEvent( e );
			slot_mc.OnDragRelease( e );
		}
		//
		public function RollOver( e:MouseEvent  )
		{
			mask_mc.visible = true;
			
			//slot_mc.dispatchEvent( e );
			//slot_mc.RollOver( e );
		}
		//
		public function RollOut( e:MouseEvent  )
		{
			mask_mc.visible = false;
			
			//slot_mc.dispatchEvent( e );
			//slot_mc.RollOut( e );
		}		
		//
	}
}