
package ActionScript3.ItemSlot {

	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.events.MouseEvent;

	import scaleform.clik.events.ButtonEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	
	import flash.events.FocusEvent;
	import scaleform.gfx.FocusEventEx;
	import scaleform.gfx.FocusManager
	import scaleform.gfx.Extensions;
	import scaleform.clik.events.FocusHandlerEvent;
	import flashx.textLayout.conversion.ITextExporter;
	import flash.display.DisplayObject;
	import ActionScript3.ItemSlot.MyItemSlotComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;

	public class MyItemSlot_Character extends MyItemSlot
	{
		//人物面板里的格子，空的也会有tips
		override protected function RollOver(evt:MouseEvent):void
		{
			var targSlot:MyItemSlot = Extensions.getMouseTopMostEntity() as MyItemSlot;
			ExternalInterface.call("ASRollOverItemSlot", this, this.SlotType, this.containerID, this.slotID );
			playSound("menu_highlight_adv");
			return;

		}
	}
}