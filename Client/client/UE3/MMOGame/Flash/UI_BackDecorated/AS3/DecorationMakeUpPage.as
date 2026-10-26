package UI_BackDecorated.AS3
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	
	public class DecorationMakeUpPage extends UIComponent
	{
		public var materials_slot_mc:MyItemSlot;
		public var decoration_slot_mc:MyItemSlot;
		
		public var txt_slot_count:TextField;
		public var txt_cost_money:TextField;
		public var btn_smelting:Button;
		
		public var makeup_FX_mc:MovieClip;
		private var _canMakeUp:Boolean = false;
		private var _isPlaying:Boolean = false;
		
		public function DecorationMakeUpPage()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			btn_smelting.addEventListener(ButtonEvent.CLICK, onDecorationMakeUp);
			
			makeup_FX_mc.mouseChildren = makeup_FX_mc.mouseEnabled = makeup_FX_mc.visible = false;
			makeup_FX_mc.addFrameScript(makeup_FX_mc.totalFrames - 1,  onAnimationPlayEnd);
		}
		
		private function onDecorationMakeUp(evt:ButtonEvent):void
		{
			if(!_isPlaying)
			{
				ExternalInterface.call("ASOnConfirmMakeUp");
				if(_canMakeUp)
				{
					playMakeUpFXAniamtion();
				}
			}
		}
		
		public function playMakeUpFXAniamtion():void
		{
			_isPlaying = true;
			makeup_FX_mc.visible = true;
			makeup_FX_mc.gotoAndPlay(1);
		}
		
		private function onAnimationPlayEnd():void
		{
			_isPlaying = false;
			makeup_FX_mc.visible = false;
		}
		
		public function UCSetMakeUpConsumptionInfo(iconName:String, itemID:int, colorIdx:int, curConsumptionCnt:int, needConsumptionCnt:int):void
		{
			//materials_slot_mc.SetData(0, iconName, itemID, "", colorIdx, -1, -1);
			_canMakeUp = curConsumptionCnt >= needConsumptionCnt;
			var curCntColor:String = _canMakeUp ? "'#84ec60'" : "'#ff0000'";
			materials_slot_mc.valueAmount.htmlText = "<font color=" + curCntColor + ">"+ needConsumptionCnt.toString() +  "/" + curConsumptionCnt.toString() + "</font>";
		}
		
		public function UCSetMakeUpResultItem(iconName:String, itemID:int, colorIdx:int):void
		{
			decoration_slot_mc.SetData(0, iconName, itemID, "", colorIdx, -1, -1);
		}
		
		public function UCSetMakeUpMoney(moneyStr:String):void
		{
			txt_cost_money.htmlText = moneyStr;
		}
	}
}