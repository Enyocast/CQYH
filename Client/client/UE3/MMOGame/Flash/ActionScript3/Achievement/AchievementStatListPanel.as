//
// 成就系统个人成就列表
//
package ActionScript3.Achievement 
{
	import ActionScript3.MyPanel;

	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import flash.text.TextField;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	public class AchievementStatListPanel extends UIComponent 
	{
		public var achievement_stat_list_mc:AchievementStatList;
		
		
		// test
		/*
		public var achievement_stat_item_data:Array;
		*/
		
		public function AchievementStatListPanel() 
		{
			// constructor code
		}
		
		override protected function configUI():void 
		{			
			//trace(">>>>>>>>>>>>>>> AchievementStatListPanel::configUI");
			super.configUI();
			
			achievement_stat_list_mc.selectedIndex = 0;
			achievement_stat_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);
			
			// test
			/*
			achievement_stat_item_data = new Array();
			for (var i:int = 0; i < 10; i++)
			{
				var stat_data:Object = new Object;
				stat_data.stat_name = "成就统计"+i;
				stat_data.stat_value = 888;
				achievement_stat_item_data.push(stat_data);
			}
			updateList(achievement_stat_item_data);
			*/
		
			//trace("<<<<<<<<<<<<<<< AchievementStatListPanel::configUI");
		}
		
		public function updateList( data:Array ):void
		{
			achievement_stat_list_mc.dataProvider = new DataProvider(data);
			achievement_stat_list_mc.validateNow();
			achievement_stat_list_mc.invalidateData();
		}
		
		public function onListItemClick( event:ListEvent ):void
		{
			var itemRenderer:AchievementStatListItem = event.itemRenderer as AchievementStatListItem;
			if (itemRenderer != null)
			{
				itemRenderer.onListItemClick();
			}
		}
	}
}
