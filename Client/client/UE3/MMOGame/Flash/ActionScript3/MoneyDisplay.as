package ActionScript3
{ 
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.TextInput;
	import flash.text.TextField;

	public class MoneyInput extends UIComponent
	{
		//[Inspectable(type = "String",name = "Caption")]
		public var _label:String = "";
		
		public var money_w_input:TextField;
		public var money_input:TextField;		
		public var caption_label:TextField;
		
		public static const C_MoneyCarry = 10000;
				
		
		override protected function configUI():void
		{
           	super.configUI();
			
			invalidateData();
        }
		
		[Inspectable(defaultValue="")]
        public function get label():String { return _label; }
        public function set label(value:String):void {
            if (_label == value) { return; }
            _label = value;
            invalidateData();
        }
		
		public override function invalidateData():void
		{			
			super.invalidateData();
			caption_label.text = _label;
		}
		
		public function setMoney(cnt:int):void
		{
			var w:int = cnt / C_MoneyCarry;			
			var m:int = cnt - w * C_MoneyCarry;
			
			money_w_input.text = w.toString();
			money_input.text = m.toString();
		}
		
		public function getMoney():int
		{
			var w:int = parseInt(money_w_input.text);
			var m:int = parseInt(money_input.text);
			
			return w * C_MoneyCarry + m;
		}
	}

}