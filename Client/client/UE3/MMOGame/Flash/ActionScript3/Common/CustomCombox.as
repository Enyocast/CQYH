package ActionScript3.Common {
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.TextInput;
	
	
	public class CustomCombox extends UIComponent {
		
	    public var txt_combox_mc:TextInput;
		public var dropdown_combox_mc:DropdownMenu;
		public function CustomCombox() {
			// constructor code
		}
		
		override protected function configUI():void 
        {
			super.configUI();
			dropdown_combox_mc.addEventListener(ListEvent.INDEX_CHANGE, OnTextInputChange);
		}
		
		
		private function OnTextInputChange(e:ListEvent)
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
			//trace("@@@@@@@@@@@@@@@@@@UpdateComboxData", data);
			dropdown_combox_mc.dataProvider = new DataProvider(data);
            dropdown_combox_mc.invalidateData();
            dropdown_combox_mc.selectedIndex = selIdx;
            dropdown_combox_mc.validateNow();
		}
		
		public function set TextInputMaxChar(value:uint):void
		{
			txt_combox_mc.maxChars = value;
		}
		
		public function get TextInputMaxChar():uint
		{
			return txt_combox_mc.maxChars;
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
