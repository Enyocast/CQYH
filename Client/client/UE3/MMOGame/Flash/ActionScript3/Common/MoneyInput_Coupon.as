package ActionScript3.Common {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	import ActionScript3.MoneyIcon;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;

	public class MoneyInput_Coupon extends UIComponent {
		public var _showBgBorder:Boolean = false;
		public var _showInputBgBorder:Boolean = false;
		public var _isReadOnly:Boolean = false;

		public var money_input:TextInput_Advanced;//in order to set text color in focus state or default state
		public var bg_border_mc:MovieClip;
		public var bg_input_border_mc:MovieClip;
		public var money_icon:MoneyIcon;
		public var _moneyIconType:int = 4;
		
		public static const C_MoneyCarry = 10000;
		override protected function configUI():void
		{
			super.configUI();
			money_input.textField.restrict = ConfigConstants.RESTRICT_OF_MONEY_INPUT;	
			setMoney(0);
			invalidateData();
			money_input.addEventListener( Event.CHANGE, handleTextChange, false, 0, true );
		}
		
		
		protected function handleTextChange(evt:Event):void
		{			
            dispatchEvent(new ParamEvent(ParamEvent.INPUT_CHANGE, this.getMoney()));
        }

		[Inspectable(defaultValue = "")]
		public function get isReadOnly():Boolean
		{
			return _isReadOnly;
		}
		public function set isReadOnly(value:Boolean):void
		{
			if (_isReadOnly == value)
			{
				return;
			}
			_isReadOnly = value;
			money_input.editable = !value;
		}
		
		[Inspectable(defaultValue = "")]
		public function get showBgBorder():Boolean
		{
			return _showBgBorder;
		}
		public function set showBgBorder(value:Boolean):void
		{
			if (_showBgBorder == value)
			{
				return;
			}
			_showBgBorder = value;
			invalidateData();
		}

		[Inspectable(defaultValue = "")]
		public function get showInputBgBorder():Boolean
		{
			return _showInputBgBorder;
		}
		public function set showInputBgBorder(value:Boolean):void
		{
			if (_showInputBgBorder == value)
			{
				return;
			}
			_showInputBgBorder = value;
			invalidateData();
		}

		[Inspectable(defaultValue = "")]
		public function get moneyIconType():int
		{
			return _moneyIconType;
		}
		public function set moneyIconType(value:int):void
		{
			if (_moneyIconType == value)
			{
				return;
			}
			_moneyIconType = value;
			invalidateData();
		}

		public override function invalidateData():void
		{
			super.invalidateData();

			//money_icon.moneyType = this._moneyIconType;
			bg_border_mc.visible = _showBgBorder;
			bg_input_border_mc.visible = _showInputBgBorder;
		}
		
		
		public function setMoney(cnt:int):void
		{
			money_input.text = cnt.toString();
		}

		public function getMoney():int
		{
			var m:int = parseInt(money_input.text);

			return m;
		}
	}
	
}
