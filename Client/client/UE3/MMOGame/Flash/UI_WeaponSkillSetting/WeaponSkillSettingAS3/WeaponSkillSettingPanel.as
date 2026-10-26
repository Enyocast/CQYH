package UI_WeaponSkillSetting.WeaponSkillSettingAS3
{
	//import scaleform.clik.core.UIComponent;
	import ActionScript3.MyPanel;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	//import scaleform.clik.controls.UILoader;
	
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	
	public class WeaponSkillSettingPanel extends MyPanel
	{
		public var CurWeaponSkillSlot:MyItemSlot;
		public var WeaponSkillNameTf:TextField;
		
		public var CurSkillLvTf:TextField;
		public var NextSkillLvTf:TextField;
		
		public var RequireConditionTf:TextField;
		public var CurConditionTf:TextField;
		public var MaxLevelTf:TextField;
		public var StaticTextContainerMc:MovieClip;
		public var WeaponSkillLevelUpSlotMc:MyItemSlot;
		public var WeaponSkillLevelUpCntTf:TextField;
		
		public var RequireMoneyConditionTf:TextField;
		public var RequireMoneyCurConditionTf:TextField;
		
		public var PanelHintTf:TextField;
		
		//public var ReplaceMoneyNeedTf:TextField;
		public var LevelUpBtn:Button;
		
		public var _SkillSlotType:int;
		//
		override protected function configUI():void
		{
			super.configUI();
			
			MaxLevelTf.visible = false;
			LevelUpBtn.addEventListener( MouseEvent.CLICK, OnLevelUpClick );
			
			ExternalInterface.call( "RegisterWeaponSkillSetting", this );
		}
		
		//
		public function get SkillSlotType():int
		{
			return _SkillSlotType;
		}
		public function set SkillSlotType( setValue:int )
		{
			_SkillSlotType = setValue;
		}
		
		//
		function OnLevelUpClick(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASLevleUpWeaponSkill", _SkillSlotType );
		}
	}
}