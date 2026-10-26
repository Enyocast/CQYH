package UI_SkillTree.SkillTreeAS3.CQ
{
	import flash.external.ExternalInterface;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import UI_SkillTree.SkillTreeAS3.ActiveSkillListItemSingleData;
	import SkillTreeAS3.CQ.ActiveSkillListPanel;
	
	public class SkillSettingPanel extends MyPanel
	{
		public var ActiveSkillListPanelMc:ActiveSkillListPanel;
		
		public function SkillSettingPanel()
		{
			super();
		}
		
		override public function UCGetWidth():int
		{
			if(MyWindowsFrame_mc){
				return MyWindowsFrame_mc.width;
			}
			return super.UCGetWidth();
		}
		
		override protected function configUI():void
		{
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			//ExternalInterface.call( "RegisterSkillSetting", this);

			//UCSetActiveSkillList(getTestData());
		}
		
		//----------------------------------------------------------------------------------------
		public function UCSetActiveSkillList( skillsData:Array ):void
		{
			ActiveSkillListPanelMc.UCSetActiveSkillList(skillsData);
		}
		
		private function getTestData():Array
		{
			var DataCnt:int = 11;
			var singleItemData:ActiveSkillListItemSingleData;
			var listData:Array = [];
			for (var i:int = 0; i < 8; ++i)
			{
				singleItemData = new ActiveSkillListItemSingleData();
				
				singleItemData.ItemIdx = i;
				singleItemData.SkillName = "测试技能" + i;
				singleItemData.SkillLv = i % 10 + 1;
				singleItemData.SkillExp = String(1000 * i) + "/" + String(1000 * (i + 2));
				singleItemData.SkillRequireLv = (i % 3 + 1) * 5;
				singleItemData.IsDisabled = true;//( i >= DataCnt  - 3);
				
			//	singleItemData.RuneSkillID = (itemIdx % 7);
			//	singleItemData.SkillInscriptionType = (singleItemData.RuneSkillID).toString();
				singleItemData.SkillID = i + 1000;
				singleItemData.SkillIconName = i.toString() +  ".tga";
				singleItemData.SlotType = 3;
				listData.push(singleItemData);
			}
			return listData;
		}
	}
}