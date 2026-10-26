package UI_GoldStore.AS
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.gfx.MouseEventEx;
	import ActionScript3.Slot.MySlot;
	import ActionScript3.MoneyInput;
	import scaleform.clik.core.UIComponent;
	
	public class GoldStore_Title extends UIComponent 
	{	
		public var hdr_1:Button;					
		public var hdr_2:Button;
		
		public var txt_label1:TextField;
		public var txt_label2:TextField;
		
		public function GoldStore_Title()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();

		}
		
		public function setLabel(label1:String, label2:String)
		{
			txt_label1.text = label1;
			txt_label2.text = label2;
		}
		
		
	}
	
}
