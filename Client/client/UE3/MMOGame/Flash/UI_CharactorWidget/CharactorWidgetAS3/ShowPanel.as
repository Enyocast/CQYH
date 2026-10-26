package UI_CharactorWidget.CharactorWidgetAS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import ActionScript3.ItemSlot.MyItemSlotComponentQuality;
	import ActionScript3.ItemSlot.MyItemSlotComponentIcon;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.Widget.MyTipsText;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.CheckBox;
	import flash.events.Event;

	
	public class ShowPanel extends UIComponent {
		
		public var btn_detail:Button;
		public var Class_txt:TextField;
		public var Level_txt:TextField;
		public var BattlePoint_txt:TextField;
		public var BattlePointTipsText:MyTipsText;
		public var charactorBg:MovieClip;
		public var EquipSlotEnhanceInfoMc:MovieClip;
		public var attributeView:AttributeTipView;
		public var AttributePanel:MovieClip;
        public var chk_head:CheckBox;
		public function ShowPanel()
		{
			
		}
        override protected function configUI():void
		{
			super.configUI();
			charactorBg.gotoAndStop(1);
			attributeView.visible=false;
			chk_head.addEventListener(MouseEvent.CLICK,selectHandler);
		}
		
		private function selectHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASRequestCheckHead",chk_head.selected);
		}
		
		public function UpdateCheckBoxSelect(bool:Boolean):void
		{
			chk_head.selected=bool;
		}
		
		public function UpdateBaseInfo(classText:String,levelText:String,frame:int):void
		{
			Class_txt.text = classText;
			Level_txt.text = levelText;
			charactorBg.gotoAndStop( frame );
		}
		
		public function SetPanelText( battlePointTips:String ):void
		{
            BattlePointTipsText.text = battlePointTips;
		}
		
		public function UpdateBattlePoint( battlePoint:String ):void
		{
			BattlePoint_txt.text = battlePoint;
		}
	}
	
}
