package ActionScript3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.TextInput;
	import flash.text.TextField;
	import flash.text.TextFieldType;
	import flash.events.FocusEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;

	public class MoneyInput extends UIComponent
	{
		//[Inspectable(type = "String",name = "Caption")]
		public var _label:String = "";
		public var _isReadOnly:Boolean = false;
		public var _showBgBorder:Boolean = false;
		public var _showInputBgBorder:Boolean = false;

		public var _moneyIconType:int = 4;
		public var _moneyIconTypeW:int = 0;

		public var money_icon:MoneyIcon;
		public var money_w_icon:MoneyIcon;

		public var money_w_input:TextField;
		public var money_input:TextField;
		public var caption_label:TextField;
		public var bg_border_mc:MovieClip;
		public var bg_input_border_mc:MovieClip;

		public static const C_MoneyCarry = 10000;


		override protected function configUI():void
		{
			super.configUI();
			caption_label.mouseEnabled = false;
			setMoney(0);
			invalidateData();

			money_w_input.addEventListener(FocusEvent.FOCUS_IN, handleTextFieldFocusInW, false, 0, true);
			money_w_input.addEventListener(FocusEvent.FOCUS_OUT, handleTextFieldFocusOutW, false, 0, true);

			money_input.addEventListener(FocusEvent.FOCUS_IN, handleTextFieldFocusIn, false, 0, true);
			money_input.addEventListener(FocusEvent.FOCUS_OUT, handleTextFieldFocusOut, false, 0, true);
		}

		protected function handleTextFieldFocusInW(e:FocusEvent):void
		{
			if(!this._isReadOnly)
			{
				money_w_input.addEventListener( Event.CHANGE, handleTextChange, false, 0, true );
				ExternalInterface.call( "ASFocusInTextInput" , true );
			}
		}

		protected function handleTextFieldFocusOutW(e:FocusEvent):void
		{
			if(!this._isReadOnly)
			{
				money_w_input.removeEventListener(Event.CHANGE, handleTextChange, false);
				ExternalInterface.call( "ASFocusInTextInput" , false );
			}
		}
		
		protected function handleTextFieldFocusIn(e:FocusEvent):void
		{
			if(!this._isReadOnly)
			{
				money_input.addEventListener( Event.CHANGE, handleTextChange, false, 0, true );
				ExternalInterface.call( "ASFocusInTextInput" , true );
			}
		}

		protected function handleTextFieldFocusOut(e:FocusEvent):void
		{
			if(!this._isReadOnly)
			{
				money_input.removeEventListener(Event.CHANGE, handleTextChange, false);
				ExternalInterface.call( "ASFocusInTextInput" , false );
			}
		}
		
		 protected function handleTextChange(evt:Event):void
		 {			
            dispatchEvent(new MoneyInput_Event(MoneyInput_Event.INPUT_CHANGE, this.getMoney()));
        }


		[Inspectable(defaultValue = "")]
		public function get label():String
		{
			return _label;
		}
		public function set label(value:String):void
		{
			if (_label == value)
			{
				return;
			}
			_label = value;
			invalidateData();
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
			caption_label.text = _label;

			if (_isReadOnly)
			{
				money_w_input.type = TextFieldType.DYNAMIC;
				money_input.type = TextFieldType.DYNAMIC;

				money_w_input.mouseEnabled = false;
				money_input.mouseEnabled = false;
			}
			else
			{
				money_w_input.type = TextFieldType.INPUT;
				money_input.type = TextFieldType.INPUT;

				money_w_input.mouseEnabled = true;
				money_input.mouseEnabled = true;
			}

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

			money_w_input.visible =  (money_w_input.type == TextFieldType.INPUT) || (w > 0);
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