package UI_SkillTree.SkillTreeAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	import UI_SkillSetting.SkillSettingAS3.SkillListItem;
	import UI_SkillSetting.SkillSettingAS3.SkillListItemData;
	import scaleform.clik.controls.Button;
	
	
	public class ActiveDetailSkillsListPanel extends UIComponent
	{
		public var SkillsScrollListMc:ScrollingList;
		public var DetailSkillPanelClostBtn:Button;
		
		override protected function configUI():void
		{
			super.configUI();
			
			//AllActiveSkillsScrollList.addEventListener(ListEvent.ITEM_CLICK, onClickSkill);
			
			DetailSkillPanelClostBtn.addEventListener(MouseEvent.CLICK, onClickCloseBtn);
			
			UpdateSkillScrollList( null );
		}
		//
		public function UpdateSkillScrollList( data:Array ):void
		{
			SkillsScrollListMc.dataProvider = new DataProvider(data);
			SkillsScrollListMc.validateNow();
			SkillsScrollListMc.invalidateData();
		}
		//
		public function onClickCloseBtn(e:MouseEvent)
		{
			//this.visible = false;
			ExternalInterface.call("ASHideActiveDetailSkillsListPanel" );
		}
		
	}
}