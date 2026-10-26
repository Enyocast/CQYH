package ActionScript3.SkillBar
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.utils.Dictionary;
	
	import ActionScript3.SkillBar.SkillSettingPanel.SkillSettingShortcutPanel;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	
	public class SkillSettingShortcutButtons extends UIComponent
	{
		public var btn_skill_shortcut_0:Button;
		public var btn_skill_shortcut_1:Button;
		public var btn_skill_shortcut_2:Button;
		public var btn_skill_shortcut_3:Button;
		public var btn_skill_shortcut_4:Button;
		public var btn_skill_shortcut_5:Button;
		
		private const NUMBER_OF_BUTTONS:uint = 6;
		private var _skillSettingPanelInstance:SkillSettingShortcutPanel;
		private var _buttonsMap:Dictionary = new Dictionary(true);
		private var _buttonIndex:int = -1;
		
		var PosAnzer:PosAnz;
		
		public function SkillSettingShortcutButtons()
		{
			super();
		}
		
		public function setPanelInstance(instance:SkillSettingShortcutPanel):void
		{
			_skillSettingPanelInstance = instance;
			_skillSettingPanelInstance.setButtonsPos(this.x, this.y);
		}
		
		//interface
		public function UCSetSkillShortcutButtonsVisible(bVisible:Boolean):void
		{
			visible = bVisible;
		}
		
		override protected function configUI():void
		{
			super.configUI();
			for(var i:int = 0; i < NUMBER_OF_BUTTONS; i++)
			{
				_buttonsMap[this['btn_skill_shortcut_' + i]] = i;
				(this['btn_skill_shortcut_' + i] as Button).addEventListener(MouseEvent.CLICK, onButtonClick);
			}
			visible = false;
			
			PosAnzer=new PosAnz;
			PosAnzer.InitObject(btn_skill_shortcut_0,btn_skill_shortcut_1,btn_skill_shortcut_2,btn_skill_shortcut_3,btn_skill_shortcut_4,btn_skill_shortcut_5);
		}
		
		public function UCSetCtrlType( type:int)
		{
			if(PosAnzer!=null){
				PosAnzer.SetCtrlType(type);
			}
		}
		
		private function onButtonClick(event:MouseEvent):void
		{
			var buttonClickIndex:int = _buttonsMap[event.currentTarget];
			var hasShowPanel:Boolean = _skillSettingPanelInstance.visible;
			if(hasShowPanel && buttonClickIndex == _buttonIndex){
				ExternalInterface.call('ASHideShortcutButtons');
				//test
				//this.visible = false;
			}else{
				ExternalInterface.call('ASShowPanel', buttonClickIndex);
				_buttonIndex = buttonClickIndex;
				//test
				// _skillSettingPanelInstance.TestBeingSettingSkill(buttonClickIndex);
			}
		}
	}
}