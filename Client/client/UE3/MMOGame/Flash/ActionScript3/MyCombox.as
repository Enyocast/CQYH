package  ActionScript3
{
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.events.FocusHandlerEvent;
 	import flash.text.TextField;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;
	import flash.events.FocusEvent;
	import scaleform.gfx.FocusEventEx;
	import scaleform.gfx.FocusManager
	import scaleform.gfx.Extensions;
	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.events.FocusHandlerEvent;
	import scaleform.clik.events.ComponentEvent;
	import flash.external.ExternalInterface;
	import UI_ChatWidget.AS3.ChatTextField;
	
	public class MyCombox extends  UIComponent
	{
		public var txt_combox_mc:ChatTextField;
		public var dropdown_combox_mc:DropdownMenu;
		
		override protected function configUI():void 
        {
			super.configUI();
			dropdown_combox_mc.textField.visible = false; 
			dropdown_combox_mc.addEventListener(ListEvent.INDEX_CHANGE, OnTextInputChange);
		}

		override public function addEventListener(type:String, listener:Function, useCapture:Boolean = false, Priority:int = 0,
										 useWeakReference:Boolean = false):void
		{
			 dropdown_combox_mc.addEventListener(type, listener, useCapture, Priority, useWeakReference);
		}
		
		
		private function OnTextInputChange(e:Event)
		{
			var value:String = dropdown_combox_mc.dataProvider.requestItemAt(  dropdown_combox_mc.selectedIndex ) as String;
			dropdown_combox_mc.selectedIndex = -1;
			txt_combox_mc.text = value;
		}
		
		public function open():void
		{
			dropdown_combox_mc.open();
		}
		
		public function close():void
		{
			dropdown_combox_mc.close();
		}
		
		public function set dataProvider(data:IDataProvider):void
		{
			dropdown_combox_mc.dataProvider = data;
		}
		
		public function get dataProvider():IDataProvider
		{
			return dropdown_combox_mc.dataProvider as IDataProvider;
		}
		
		public function set selectedIndex(index:int):void
		{
			dropdown_combox_mc.selectedIndex = index;
		}
		
		public function get selectedIndex():int
		{
			return dropdown_combox_mc.selectedIndex;
		}
		
		public function UpdateComboxData( data:Array, selIdx:int = -1):void
		{
			dropdown_combox_mc.dataProvider = new DataProvider(data);
            dropdown_combox_mc.invalidateData();
            dropdown_combox_mc.selectedIndex = selIdx;
            dropdown_combox_mc.validateNow();
		}
		
		public function set TextInputMaxChar(value:uint):void
		{
			txt_combox_mc.textField.maxChars = value;
		}
		
		public function get TextInputMaxChar():uint
		{
			return txt_combox_mc.textField.maxChars;
		}
		
		public function set text(value:String):void
		{
			txt_combox_mc.text = value;
		}
		
		public function get text():String
		{
			return txt_combox_mc.text;
		}
	}
	
}
