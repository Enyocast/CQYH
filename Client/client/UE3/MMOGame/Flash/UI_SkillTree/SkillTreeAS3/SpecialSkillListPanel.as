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
	
	import UI_SkillTree.SkillTreeAS3.SpecialSkillListItem;
	import UI_SkillTree.SkillTreeAS3.SpecialSkillListItemData;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	
	//test
	//import UI_SkillTree.SkillTreeAS3.ActiveSkillListItemSingleData;
	
	public class SpecialSkillListPanel extends UIComponent
	{
		public var AllSpecialSkillsScrollList:ScrollingList;
		
		override protected function configUI():void
		{
			super.configUI();
		
			UpdateSpecialSkillList( null );
			//TestData();
		}
		//
		public function UpdateSpecialSkillList( data:Array ):void
		{
			AllSpecialSkillsScrollList.dataProvider = new DataProvider(data);
			AllSpecialSkillsScrollList.validateNow();
			AllSpecialSkillsScrollList.invalidateData();
		}
		//==========================================================================================================
		public function TestData()
		{
			var itemsData:Array = new Array();
			var itemIdx:int = 0;
			for (var i:int = 1; i <= 4; i++)
			{
				var listItem:SpecialSkillListItemData = new SpecialSkillListItemData ;
				listItem.ShowMask = 0x1 | 0x2 | 0x4 | 0x8;
				//1
				listItem.SingleData1 = new SpecialSkillListItemSingleData ;
				listItem.SingleData1.ItemIdx = 0;
				listItem.SingleData1.TipsType = 8;
				listItem.SingleData1.CanDrag = false;
				listItem.SingleData1.IsDisabled = ( i <= 2 );
				
				listItem.SingleData1.SkillName = "测试技能"+itemIdx
				listItem.SingleData1.SkillRequire = listItem.SingleData1.IsDisabled ? "未学会" : "已学会";
				
				listItem.SingleData1.SkillID = itemIdx + 1000;
				listItem.SingleData1.SkillIconName = (itemIdx + i)%2 + ".tga";
				++itemIdx;
				//2
				listItem.SingleData2 = new SpecialSkillListItemSingleData ;
				listItem.SingleData2.ItemIdx = 1;
				listItem.SingleData2.TipsType = 8;
				listItem.SingleData2.CanDrag = false;
				listItem.SingleData2.IsDisabled = ( i <= 2 );
				
				listItem.SingleData2.SkillName = "测试技能"+itemIdx
				listItem.SingleData2.SkillRequire = listItem.SingleData1.IsDisabled ? "未学会" : "已学会";
				
				listItem.SingleData2.SkillID = itemIdx + 1000;
				listItem.SingleData2.SkillIconName = (itemIdx + i)%2 + ".tga";
				++itemIdx;
				//3
				listItem.SingleData3 = new SpecialSkillListItemSingleData ;
				listItem.SingleData3.ItemIdx = 2;
				listItem.SingleData3.TipsType = 8;
				listItem.SingleData3.CanDrag = true;
				listItem.SingleData3.IsDisabled = ( i <= 2 );
				
				listItem.SingleData3.SkillName = "测试技能"+itemIdx
				listItem.SingleData3.SkillRequire = listItem.SingleData1.IsDisabled ? "未学会" : "已学会";
				
				listItem.SingleData3.SkillID = itemIdx + 1000;
				listItem.SingleData3.SkillIconName = (itemIdx + i)%2 + ".tga";
				++itemIdx;
				//4
				listItem.SingleData4 = new SpecialSkillListItemSingleData ;
				listItem.SingleData4.ItemIdx = 3;
				listItem.SingleData4.TipsType = 8;
				listItem.SingleData4.CanDrag = true;
				listItem.SingleData4.IsDisabled = ( i <= 2 );
				
				listItem.SingleData4.SkillName = "测试技能"+itemIdx
				listItem.SingleData4.SkillRequire = listItem.SingleData1.IsDisabled ? "未学会" : "已学会";
				
				listItem.SingleData4.SkillID = itemIdx + 1000;
				listItem.SingleData4.SkillIconName = (itemIdx + i)%2 + ".tga";
				++itemIdx;
				
				itemsData.push( listItem );
			}
			
			//
			var lastListItem:SpecialSkillListItemData = new SpecialSkillListItemData ;
			lastListItem.ShowMask = 0x8;
			lastListItem.SingleData4 = new SpecialSkillListItemSingleData ;
			lastListItem.SingleData4.ItemIdx = 0;
			lastListItem.SingleData4.TipsType = 8;
			lastListItem.SingleData4.CanDrag = false;
			lastListItem.SingleData4.IsDisabled = false;
			
			lastListItem.SingleData4.SkillName = "测试技能多"+itemIdx;
			lastListItem.SingleData4.SkillRequire = "未学会"+itemIdx;
			
			lastListItem.SingleData4.SkillID = 233232;
			lastListItem.SingleData4.SkillIconName = itemIdx%2 + ".tga";

			//
			itemsData.push( lastListItem );
			
			UpdateSpecialSkillList( itemsData );
		}
	}
}