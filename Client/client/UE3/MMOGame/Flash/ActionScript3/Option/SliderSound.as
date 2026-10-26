package ActionScript3.Option
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	import flashx.textLayout.operations.MoveChildrenOperation;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.Slider;
	import scaleform.clik.events.SliderEvent;

	public class SliderSound extends Slider
	{
		public var progres:MovieClip;
		public var _img:MovieClip;
		
		protected var _valueTextField:TextField;
		
		protected var _defaultValue:Number;
		
		[Inspectable(type = "String")]
		public function get valueTextField():Object
		{
			return _valueTextField;
		}
		public function set valueTextField(value:Object):void
		{
			if (value is String) {
				if (value.toString() == "" || parent == null) { return; }
				value = parent.getChildByName(value.toString());
				if (value == null) { return; }
				_valueTextField = value as TextField;
			}			
		}

		/**
		 * Enable/disable
		 */
		override public function set enabled(value:Boolean):void
		{
			if (value == super.enabled)
				return;
			super.enabled = value;
			progres.enabled = value;
		}
		
		override protected function configUI():void
		{
			super.configUI();
			_defaultValue = value;
			if(_valueTextField){
				_valueTextField.text = value.toString();
			}
			this.addEventListener(SliderEvent.VALUE_CHANGE, OnUpdateValueTextFiled);
		}
		
		private function OnUpdateValueTextFiled(evt:SliderEvent):void
		{
			if(_valueTextField){
				_valueTextField.text = value.toString();
			}
		}
		/**
		 * The value of the slider between the {@code minimum} and {@code maximum}.
		 */
		override public function set value(_value:Number):void
		{
			if (_value == this.value)
				return;
			progres.width = this._img.width * (_value-this.minimum) / (this.maximum-this.minimum);
			super.value = _value;
		}
		
		override protected function doDrag(e:MouseEvent):void
		{
			super.doDrag(e);
			progres.width = this._img.width * (super.value-this.minimum) / (this.maximum-this.minimum);
		}
		
		public function defaultValue():void
		{
			if(!isNaN(_defaultValue)){
				this.value = _defaultValue;
			}
		}
	}
}
