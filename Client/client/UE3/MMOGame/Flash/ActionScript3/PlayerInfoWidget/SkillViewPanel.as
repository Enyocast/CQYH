package ActionScript3.PlayerInfoWidget
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.Common.CustomScrollBar;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	//test
	//import UI_SkillTree.SkillTreeAS3.SkillViewData;
	
	public class SkillViewPanel extends UIComponent
	{
		public var scrollingView_mc:ScrollingView;
		public var skillsListView_mc:SkillViewList;
		public var scroll_bar_mc:CustomScrollBar;
		
		public var ShowLearnedActiveSkillsChkBtn:Button;
		public var ShowAllActiveSkillsChkBtn:Button;
		
		override protected function configUI():void
		{
			super.configUI();
			
			if(ShowLearnedActiveSkillsChkBtn)
				ShowLearnedActiveSkillsChkBtn.addEventListener(MouseEvent.CLICK, onShowLearnedActiveSkills);
			if(ShowAllActiveSkillsChkBtn)
				ShowAllActiveSkillsChkBtn.addEventListener(MouseEvent.CLICK, onShowAllActiveSkills);
		
			UpdateMainSkillList( null );
			
			//TestData();
		}
		//
		public function UpdateMainSkillList( data:Array ):void
		{
			trace("UpdateMainSkillList",skillsListView_mc);
			skillsListView_mc.updateData(data);
			updateScrollingView();
		}
		
		private function updateScrollingView():void
		{
			if(skillsListView_mc.resetPosition()){
				scrollingView_mc.displayMc = skillsListView_mc;
				scrollingView_mc.scrollBar = scroll_bar_mc;
			}
		}
		//
		public function UpdateDetailSkillList( data:Array ):void
		{
			//DetailActiveSkillListPanelMc.UpdateSkillScrollList( data );
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
			
			//var itemData:SkillListItemData = listDataProvider.requestItemAt(e.index) as SkillListItemData;

		}
		public function onScrolling( e:Event )
		{
			ExternalInterface.call( "ASOnScroolingActiveSkillList" );
		}
		//==========================================================================================================
		public function onShowLearnedActiveSkills(e:Event)
		{
			ExternalInterface.call( "ASShowLearnedActiveSkills" );
			//TestData(8);
		}
		//==========================================================================================================
		public function onShowAllActiveSkills(e:Event)
		{
			ExternalInterface.call( "ASShowAllActiveSkills" );
			//TestData(16);
		}
			
		//==========================================================================================================
		public function TestData(groupLen:int = 6)
		{
			var itemsData:Array = new Array();
			var titleIdx:int = 0;
			for (var j:int = 0; j < groupLen; ++j)
			{
				//var listItemTitle:ActiveSkillListItemData = new ActiveSkillListItemData ;
				//
				//listItemTitle.DataCnt = DataCnt;
				//listItemTitle.TitleType = j;
				//listItemTitle.TitleString = "键位"+j;
				//itemsData.push( listItemTitle );
				
				var DataCnt:int = 1 + 9 * Math.random();
				var itemIdx:int = 0;
				var listItem:SkillViewItemData = new SkillViewItemData();
				listItem.DataCnt = DataCnt;
				listItem.TitleType = j;
				listItem.TitleString = j.toString();
				//var totalRow:int = 1 + (j + 2) / 3;
				trace("========================DataCnt:", DataCnt);
				listItem.SingleItemsData = new Array();
				var singleItemData:SkillViewSingleItemData;
				for (var i:int = 1; i <= DataCnt; ++i)
				{
					//1
					itemIdx = i - 1;
					singleItemData = new SkillViewSingleItemData();
						
						singleItemData.ItemIdx = itemIdx;
						singleItemData.IsNew = ( itemIdx %4 == 0 );
						singleItemData.IsCurrent = ( itemIdx % 5 == 0 );
						singleItemData.IsMaxLv = ( itemIdx == 3 || itemIdx == 9 );
						singleItemData.CanLvUp = !singleItemData.IsMaxLv;
						singleItemData.SkillName = "测试技能"+itemIdx;
						singleItemData.SkillLv = itemIdx % 10 + 1;
						singleItemData.SkillRequireLv = itemIdx % 20 + 1;
						singleItemData.IsDisabled = ( itemIdx == 2);

						singleItemData.RuneSkillID = (itemIdx % 5);
						singleItemData.SkillInscriptionType = (singleItemData.RuneSkillID).toString();
						singleItemData.SkillID = itemIdx + 1000;
						singleItemData.SkillIconName = "11.png";
						listItem.SingleItemsData.push(singleItemData);
/*						++itemIdx;
					//2
					if( i != totalRow || j%3 != 1 ){
						listItem.DataCnt = 2;
						listItem.SingleData2 = new SkillViewData ;
						listItem.SingleData2.ItemIdx = 1;
						listItem.SingleData2.IsNew = ( itemIdx %4 == 0 );
						listItem.SingleData2.IsCurrent = ( itemIdx % 5 == 0 );
						listItem.SingleData2.IsMaxLv = ( itemIdx == 3 || itemIdx == 9 );

						listItem.SingleData2.SkillName = "测试技能"+itemIdx;
						listItem.SingleData2.SkillLv = itemIdx % 10 + 1;
						listItem.SingleData2.SkillRequireLv = itemIdx % 20 + 1;
						listItem.SingleData2.IsDisabled = false;

						listItem.SingleData2.SkillSlotType = (itemIdx % 6);
						listItem.SingleData2.SkillID = itemIdx + 1000;
						listItem.SingleData2.SkillIconName = ( i % 2 > 0 ? "0.tga" : "1.tga" );
						++itemIdx;
					}
					//3
					if( i != totalRow || ( j%3 != 2 && j%3 != 1 ) ){
						listItem.DataCnt = 3;
						listItem.SingleData3 = new SkillViewData ;
						listItem.SingleData3.ItemIdx = 2;
						listItem.SingleData3.IsNew = ( itemIdx %4 == 0 );
						listItem.SingleData3.IsCurrent = ( itemIdx % 5 == 0 );
						listItem.SingleData3.IsMaxLv = ( itemIdx == 3 || itemIdx == 9 );

						listItem.SingleData3.SkillName = "测试技能"+itemIdx;
						listItem.SingleData3.SkillLv = itemIdx % 10 + 1;
						listItem.SingleData3.SkillRequireLv = itemIdx % 20 + 1;
						listItem.SingleData3.IsDisabled = false;

						listItem.SingleData3.SkillSlotType = (itemIdx % 6);
						listItem.SingleData3.SkillID = itemIdx + 1000;
						listItem.SingleData3.SkillIconName = ( i % 2 > 0 ? "0.tga" : "1.tga" );
						++itemIdx;
					}*/
				}//end of for i
				itemsData.push( listItem );
			}//end of for j
			
			
			UpdateMainSkillList( itemsData );
		}
	}
}