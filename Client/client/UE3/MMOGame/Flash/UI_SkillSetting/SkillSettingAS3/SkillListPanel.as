package UI_SkillSetting.SkillSettingAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	//import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	import UI_SkillSetting.SkillSettingAS3.SkillListItem;
	import UI_SkillSetting.SkillSettingAS3.SkillListItemData;
	import scaleform.clik.controls.Button;
	
	public class SkillListPanel extends UIComponent
	{
		public var SkillListCloseBtn:Button;
		//技能类型
		public var SkillType:int;
		public var SkillListTypeMc:MovieClip;
		//技能列表
		public var SkillScrollListMc:ScrollingList;
		
		override protected function configUI():void
		{
			super.configUI();
			
			SkillListCloseBtn.addEventListener(MouseEvent.CLICK, onClickToClose);
			SkillScrollListMc.addEventListener(ListEvent.ITEM_CLICK, onClickSkill);
			
			UpdateSkillScrollList( null );
		}
		//
		public function SetSkillType( type:int )
		{
			SkillType = type;
			SkillListTypeMc.gotoAndStop( "Slot"+ SkillType );
		}
		//
		public function UpdateSkillScrollList( data:Array ):void
		{
			SkillScrollListMc.selectedIndex = -1;
			SkillScrollListMc.dataProvider = new DataProvider(data);
			SkillScrollListMc.validateNow();
			SkillScrollListMc.invalidateData();
		}
		//
		public function onClickSkill(e:ListEvent)
		{
			var targetList:ScrollingList = e.target as ScrollingList;
			if( targetList == null ){
				ExternalInterface.call( "ASTrace", "onClickSkill ScrollingList not found" );
				return;
			}
			
			var listDataProvider:DataProvider = targetList.dataProvider as DataProvider;
			if( listDataProvider == null ){
				ExternalInterface.call( "ASTrace", "onClickSkill DataProvider not found" );
				return;
			}
			
			//listDataProvider.handleListItemClick( e );
			
			var itemData:SkillListItemData = listDataProvider.requestItemAt(e.index) as SkillListItemData;
			ExternalInterface.call( "ASSetSkill", SkillType, itemData.SkillID );
			
			//test
			//visible = false;
		}
		//
		public function onClickToClose( evt:Event )
		{
			//if( (evt as MouseEventEx).buttonIdx == 1){
				ExternalInterface.call( "ASCloseSkillList" );
			//}
		}
	}
}