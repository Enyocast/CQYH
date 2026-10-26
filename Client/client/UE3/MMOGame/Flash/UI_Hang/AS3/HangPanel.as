package UI_Hang.AS3 {
	
	import ActionScript3.MyPanel;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.RadioButton;
	import flash.display.MovieClip;
	import scaleform.clik.events.ComponentEvent;
	import flash.events.Event;
	
	
	public class HangPanel extends MyPanel {
		
		public var tabAssist:AssistTab;
		public var tabGame:GameTab;
		public var tabInput:InputTab;
		public var tab_hang:RadioButton;
		public var tab_game:RadioButton;
		public var tab_input:RadioButton;
		override protected  function configUI():void 
		{
			ShowMode="BC";
			super.configUI();
			this.SetWindowTitle("游戏设置");
			tab_hang.addEventListener(MouseEvent.CLICK,clickHangHandler);
			clickHangHandler(null);
			tab_game.addEventListener(MouseEvent.CLICK,clickGameHandler);
			tab_input.addEventListener(MouseEvent.CLICK,clickInputHandler);
			tab_hang.selected=true;
			this.addEventListener(ComponentEvent.HIDE,hideViewHandler);
		}
		
		private function hideViewHandler(evt:Event):void
		{
			tabAssist.config0.hide();
			tabAssist.config1.hide();
			tabAssist.config2.hide();
			tabInput.config0.clear(0);
		}
		
		private function clickHangHandler(evt:MouseEvent):void
		{
			tabAssist.visible=true;
			tabGame.visible=false;
			tabInput.visible=false;
		}
		
		private function clickGameHandler(evt:MouseEvent):void
		{
			tabAssist.visible=false;
			tabGame.visible=true;
			tabInput.visible=false;
		}
		
		private function clickInputHandler(evt:MouseEvent):void
		{
			tabAssist.visible=false;
			tabGame.visible=false;
			tabInput.visible=true;
		}
		//设置外挂道具配置
		public function SetHangItemConfig(dat:Array):void
		{
			tabAssist.config1.setItemData(dat);
		}
		//设置外挂道具下拉菜单选项
		public function SetHangMenuData(dat:Array):void
		{
			tabAssist.config1.setMenuData(dat);
		}
		
		//设置保护配置属性
		public function SetProtectData(dat:Array):void
		{
			tabAssist.config2.SetProtectData(dat);
		}
		//设置保护配置下拉菜单道具列表
		public function setProtectItemData(dat:Array):void
		{
			tabAssist.config2.setItemData(dat);
		}
		
		//设置游戏显示数据
		public function SetConfigGameData(dat:Object):void
		{
			tabGame.config0.setConfigData(dat as ConfigGameData);
			tabGame.config1.setConfigData(dat as ConfigGameData);
			tabGame.config2.setConfigData(dat as ConfigGameData);
		    tabInput.config0.setConfigData(dat as ConfigGameData);
			tabInput.config1.setConfigData(dat as ConfigGameData);
		}
		
		//设置技能配置数据
		public function SetConfigSkillData(dat:Object):void
		{
			tabAssist.config0.setData(dat as SkillConfigData);
		}
		
		//设置帮助数据
		public function SetConfigHelpData(dat:Object):void
		{
			tabAssist.config3.setData(dat as String);
		}
		
		public function UCShowWarning(warning:String):void
		{
			tabInput.config0.ShowWarning(warning);
			tabInput.config1.ShowWarning(warning);
		}
		
		public function UCSetCtrlType(ctrlType:int)
		{
			tabInput.config1.SetCtrlType(ctrlType);
		}
		
		public function UCSetMaxHMP(maxHp:int,maxMp:int):void
		{
			tabAssist.config2.SetMaxHMP(maxHp,maxMp);
		}
		
	}
	
}
