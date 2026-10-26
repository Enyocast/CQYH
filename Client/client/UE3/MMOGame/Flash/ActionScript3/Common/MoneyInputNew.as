package ActionScript3.Common {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.text.TextFieldType;
	
	import ActionScript3.MoneyIcon;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import scaleform.clik.core.UIComponent;

	public class MoneyInputNew extends UIComponent {
		
		public var _isReadOnly:Boolean = false;
		public var _showBgBorder:Boolean = false;
		public var _showInputBgBorder:Boolean = false;

		public var _moneyIconType:int = 4;
		public var _moneyIconTypeW:int = 0;

		public var money_icon:MoneyIcon;
		public var money_w_icon:MoneyIcon;

		public var money_w_input:TextInput_Advanced;
		public var money_input:TextInput_Advanced;
		public var bg_border_mc:MovieClip;
		public var bg_input_border_mc:MovieClip;

		public static const C_MoneyCarry = 10000;
		override protected function configUI():void
		{
			super.configUI();
			money_w_input.textField.restrict = ConfigConstants.RESTRICT_OF_MONEY_INPUT;	
			money_input.textField.restrict = ConfigConstants.RESTRICT_OF_MONEY_INPUT;	
			setMoney(0);
			invalidateData();
			
			money_w_input.addEventListener( Event.CHANGE, handleTextChange, false, 0, true );
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
			money_input.editable = money_w_input.editable = !_isReadOnly;
			invalidateData();
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

		[Inspectable(defaultValue = "")]
		public function get moneyIconTypeW():int
		{
			return _moneyIconTypeW;
		}
		public function set moneyIconTypeW(value:int):void
		{
			if (_moneyIconTypeW == value)
			{
				return;
			}
			_moneyIconTypeW = value;
			invalidateData();
		}

		public override function invalidateData():void
		{
			super.invalidateData();

			bg_border_mc.visible = _showBgBorder;
			bg_input_border_mc.visible = _showInputBgBorder;

			money_icon.moneyType = this._moneyIconType;
			money_w_icon.moneyType = this._moneyIconTypeW;
		}

		public function setMoney(cnt:int):void
		{
			var w:int = cnt / C_MoneyCarry;
			var m:int = cnt - w * C_MoneyCarry;

			money_w_input.text = w.toString();
			money_input.text = m.toString();

			money_w_input.visible =  (money_w_input.textField.type == TextFieldType.INPUT) || (w > 0);
			money_w_icon.visible = money_w_input.visible;
		}

		public function getMoney():int
		{
			var w:int = parseInt(money_w_input.text);
			var m:int = parseInt(money_input.text);

			return w * C_MoneyCarry + m;
		}
	}
	
}
