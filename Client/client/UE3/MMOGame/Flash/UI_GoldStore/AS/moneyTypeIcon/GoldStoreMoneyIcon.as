package UI_GoldStore.AS.moneyTypeIcon
{
	import scaleform.clik.core.UIComponent;
	import UI_GoldStore.AS.GoldStoreUltils;
	
	public class GoldStoreMoneyIcon extends UIComponent
	{
		protected var _couponValue:Number = 0;
		protected var _curType:int = 0;
		protected var _referNumberTextField:Object;
		protected var _formatMoneyValue:Boolean = true;
		
		public function GoldStoreMoneyIcon()
		{
			super();
			GoldStoreMoneyIconPool.getInstance().addToMoneyIconPool(this);
		}
		
		[Inspectable(type = "Boolean", defaultValue="true")]
		public function get formatMoneyValue():Boolean
		{
			return _formatMoneyValue;
		}

		public function set formatMoneyValue(value:Boolean):void
		{
			_formatMoneyValue = value;
		}

		public function set couponValue(value:Number):void
		{
			_couponValue = value;
			updateMoneyValueByType();
		}

		[Inspectable(type = "String")]
		public function get referNumberTextField():Object
		{
			return _referNumberTextField;
		}
		public function set referNumberTextField(value:Object):void
		{
			if (value is String) 
			{
				if (value.toString() == "" || parent == null) 
				{ 
					return; 
				}
				value = parent.getChildByName(value.toString());
				if (value == null) 
				{ 
					return; 
				}
				_referNumberTextField = value;
			}			
		}
		
		public function onMoneyTypeChanged(type:int):void
		{
			if(_curType != type)
			{
				_curType = type;
				this.gotoAndStop(type);
				updateMoneyValueByType();
			}
		}
		
		private function updateMoneyValueByType():void
		{
			if(_referNumberTextField == null)
			{
				return;
			}
			if(_curType == GoldStoreUltils.MONEY_TYPE_GOLD)
			{
				_referNumberTextField.text = GoldStoreUltils.couponToGold(_couponValue, _formatMoneyValue);
			}
			else if(_curType == GoldStoreUltils.MONEY_TYPE_RMB)
			{
				_referNumberTextField.text = GoldStoreUltils.couponToCash(_couponValue, _formatMoneyValue);
			}
		}
	}
}