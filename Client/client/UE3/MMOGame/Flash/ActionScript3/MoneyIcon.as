package ActionScript3
{ 
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;

	public class MoneyIcon extends UIComponent {
	
		public static const MoneyType_BindGoldW = 1;
		public static const MoneyType_GoldIcon = 2;
		
		public var _moneyType:Number = 1;
		
		[Inspectable(defaultValue="")]
        public function get moneyType():int { return _moneyType; }
        public function set moneyType(value:int):void {
            _moneyType = value;
			this.gotoAndStop(_moneyType);
        }
		
		override protected function configUI():void
		{
			super.configUI();   	
        }

	}

}