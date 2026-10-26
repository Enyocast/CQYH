package UI_SpecialExpApply.AS3
{
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.TextInput_Advanced;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;
	
	public class SpecailExpApplyBox extends MyPanel
	{
		public var txt_input_hour:TextInput_Advanced;
		public var txt_cost_money:TextField;
		public var txt_my_money:TextField;
//		public var txt_announcement:TextField;
		public var btn_apply:Button;
		
		private var _expHourCount:int = 0;
		
		private static const MIN_EXP_HOUR:int = 1;
		private static const MAX_EXP_HOUR:int = 9999;
		
		public function SpecailExpApplyBox()
		{
			super();
		}
		
		override protected function configUI():void
		{
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			SetWindowTitle("历练");
			txt_input_hour.textField.restrict = ConfigConstants.RESTRICT_OF_MONEY_INPUT;
			txt_input_hour.addEventListener(Event.CHANGE, onInputChange);
			btn_apply.addEventListener(ButtonEvent.CLICK, onApplyExperience);
			onInputChange(null);
		}
		
		private function onInputChange(evt:Event):void
		{
			_expHourCount = int(txt_input_hour.text);
			_expHourCount = Math.max(MIN_EXP_HOUR, Math.min(_expHourCount, MAX_EXP_HOUR));
			txt_input_hour.text = _expHourCount.toString();
			ExternalInterface.call("ASApplyCntChanged", _expHourCount);
		}
		
		public function UCSetCurCost(curCostStr :String):void
		{
			txt_cost_money.htmlText = curCostStr;
		}
		
		public function UCSetCurMoney(curMoneyStr:String):void
		{
			txt_my_money.htmlText = curMoneyStr;
		}
		
		public function UCSetAnnouncement(hintStr:String):void
		{
			//txt_announcement.htmlText = hintStr;
		}
		
		public function UCGetCurApplyCnte():int
		{
			return _expHourCount;
		}
		
		public function onApplyExperience(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASTryToApply");
		}
		
	}
}