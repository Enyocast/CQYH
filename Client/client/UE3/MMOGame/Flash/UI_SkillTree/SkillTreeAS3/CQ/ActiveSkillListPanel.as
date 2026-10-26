package UI_SkillTree.SkillTreeAS3.CQ
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	
	public class ActiveSkillListPanel extends UIComponent
	{
		public var ShowLearnedActiveSkillsChkBtn:RadioButton;
		public var ShowAllActiveSkillsChkBtn:RadioButton;
		public var skill_list_mc:ScrollingList;
		
		protected var _listData:DataProvider = new DataProvider();
		protected var _skillListData:Array;
		
		public function ActiveSkillListPanel()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			ShowLearnedActiveSkillsChkBtn.addEventListener(Event.SELECT, onShowLearnedActiveSkills);
			ShowAllActiveSkillsChkBtn.addEventListener(Event.SELECT, onShowAllActiveSkills);
			ShowLearnedActiveSkillsChkBtn.selected = true;
			ShowLearnedActiveSkillsChkBtn.visible = ShowAllActiveSkillsChkBtn.visible = false;
		}
		
		//==========================================================================================================
		public function onShowLearnedActiveSkills(e:Event)
		{
			ExternalInterface.call( "ASShowLearnedActiveSkills" );
		}
		//==========================================================================================================
		public function onShowAllActiveSkills(e:Event)
		{

			ExternalInterface.call( "ASShowAllActiveSkills" );
		}
		
		//----------------------------------------------------------------------------------------
		public function UCSetActiveSkillList( skillsData:Array ):void
		{
			_listData.cleanUp();
			_listData.setSource(skillsData);
			skill_list_mc.invalidateData();
			skill_list_mc.dataProvider = _listData;
			skill_list_mc.validateNow();
		}
		
	}
}