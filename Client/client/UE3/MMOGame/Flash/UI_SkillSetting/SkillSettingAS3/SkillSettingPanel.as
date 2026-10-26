package UI_SkillSetting.SkillSettingAS3
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import UI_SkillSetting.SkillSettingAS3.SkillListPanel;
	import UI_SkillSetting.SkillSettingAS3.SkillSettingBtn;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	public class SkillSettingPanel extends MyPanel
	{
		public var Skill0:SkillSettingBtn;
		public var Skill1:SkillSettingBtn;
		public var Skill2:SkillSettingBtn;
		public var Skill3:SkillSettingBtn;
		public var Skill4:SkillSettingBtn;
		public var Skill5:SkillSettingBtn;
		
		public var SkillListPanelMc:SkillListPanel;
		public var SkillListPanelArrowMc:MovieClip;
		
		public var RestAllSkillBtn:Button;
		public var OpenSkillTreeBtn:Button;
		public var CheckSkillBtn:Button;
		
		override protected  function configUI():void
		{
			super.configUI();
			//
			ExternalInterface.call( "RegisterSkillSetting", this );
			//
			SkillListPanelArrowMc.visible = false;
			SkillListPanelMc.visible = false;
			
			//
			RestAllSkillBtn.addEventListener( MouseEvent.CLICK, RestAllSkills );
			//RestAllSkillBtn.textField.text = "重置";
			OpenSkillTreeBtn.addEventListener( MouseEvent.CLICK, OpenSkillTree );
			//OpenSkillTreeBtn.label = "技能总览";
			CheckSkillBtn.addEventListener( MouseEvent.CLICK, CheckSkill );
			
			Skill0.SettingBtnType = 0;
			Skill1.SettingBtnType = 1;
			Skill2.SettingBtnType = 2;
			Skill3.SettingBtnType = 3;
			Skill4.SettingBtnType = 4;
			Skill5.SettingBtnType = 5;
			
			/*
			//test
			Skill0.SetSkill( true, false, "试验技能1", 1, "", 10003 );
			//
			Skill1.SetSkill( true, false, "试验技能2", 2, "", 10004 );
			Skill1.SetSkillRune( true, "符文技能2", 3, 1 );
			Skill1.ActiveAutoSetBtn( true );
			Skill1.ActiveFastMakeEquipRune( true );
			//
			Skill2.SetSkill( true, true, "试验技能3", 3, "", 10005 );
			//
			Skill3.SetSkill( false, true, "试验技能4", 4, "", 10006 );
			//
			Skill4.SetSkill( false, true, "试验技能5", 5, "", 10007 );
			//
			Skill5.SetSkill( false, true, "试验技能6", 6, "", 10008 );
			*/
		}
		
		//
		public function UCSetSkillList( skillListType:int, skillData:Array ):void
		{
			SkillListPanelMc.SetSkillType( skillListType );
			SkillListPanelMc.UpdateSkillScrollList( skillData );
		}
		
		//
		public function RestAllSkills( e:Event )
		{
			ExternalInterface.call( "ASRestAllSkills" );
		}
		
		//
		public function OpenSkillTree( e:Event )
		{
			ExternalInterface.call( "ASOnClickOpenSkillTree" );
		}
		
		//
		public function CheckSkill( e:Event )
		{
			ExternalInterface.call( "ASCheckSkill" );
		}

	}
}