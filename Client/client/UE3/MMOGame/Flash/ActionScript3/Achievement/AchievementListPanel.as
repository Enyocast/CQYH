//
// 成就系统个人成就列表
//
package ActionScript3.Achievement
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollBar;
	import ActionScript3.MyScrollPanel;
	import ActionScript3.MyTipButton;
	import ActionScript3.Common.CustomScrollBar;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.events.SliderEvent;

	public class AchievementListPanel extends UIComponent
	{
		public var achievement_progress_left_mc:AchievementProgressBar;
		public var achievement_list_mask_mc:MovieClip;
		public var achievement_list_mc:AchievementList;
		public var achievement_list_scrollbar_mc:CustomScrollBar;
		
		public var achievement_right_panel_mc:AchievementRightPanel;
		
		private var _isSynchronizing:Boolean = false;
		
		public function AchievementListPanel()
		{
			// constructor code
		}
		
		public function LOG(info:String):void
		{
			(parent as AchievementPanel).LOG(info);
		}

		override protected function configUI():void
		{
			super.configUI();
			achievement_list_mc.setScrollBar(achievement_list_scrollbar_mc, 380);
			achievement_list_mc.addEventListener(SliderEvent.VALUE_CHANGE, onListScrollChange);
			achievement_right_panel_mc.achievement_comp_list_mc.addEventListener(SliderEvent.VALUE_CHANGE, onCompareListScrollChange);
		}
		
		function onWheelScroll(e:MouseEvent)
		{
			if (achievement_right_panel_mc.visible)
			{
				achievement_right_panel_mc.achievement_comp_list_mc.position -= e.delta;
			}
			
			if(achievement_list_scrollbar_mc.enabled)
			{
				achievement_list_scrollbar_mc.position -= e.delta;
			}
		}
		
		private function onListScrollChange(evt:SliderEvent):void
		{
			if(_isSynchronizing){
				return;
			}
			_isSynchronizing = true;
			var percent:Number = evt.value / 100;
			if(percent == 0.01)
			{
				percent = 0;
			}
			else if(percent == 1)
			{
				percent = 1.01;
			}
			achievement_right_panel_mc.achievement_comp_list_mc.syncScrollPosition(percent);
			_isSynchronizing = false;
		}
		
		private function onCompareListScrollChange(evt:SliderEvent):void
		{
			if(_isSynchronizing){
				return;
			}
			_isSynchronizing = true;
			var percent:Number = evt.value / 100;
			if(percent == 0.01)
			{
				percent = 0;
			}
			else if(percent == 1)
			{
				percent = 1.01;
			}
			achievement_list_mc.syncScrollPosition(percent);
			_isSynchronizing = false;
		}
		
		public function setState(is_compare:Boolean):void
		{
			achievement_progress_left_mc.visible = is_compare;
			achievement_right_panel_mc.visible = is_compare;
			
			if (is_compare)
			{
				achievement_list_mc.setListPos(43);
				achievement_list_mc.setListHeight(380);
				achievement_list_mc.updateListLayout();

				achievement_list_mask_mc.y = 43;
				achievement_list_mask_mc.height = 380;
				achievement_list_scrollbar_mc.y = 43;
			}
			else
			{
				achievement_list_mc.setListPos(7);
				achievement_list_mc.setListHeight(418);
				achievement_list_mc.updateListLayout();
				
				achievement_list_mask_mc.y = 2;
				achievement_list_mask_mc.height = 418;
				achievement_list_scrollbar_mc.y = 2;
			}
		}

		public function updateData(roleName:String, point:int, complete:int, total:int, roleNameComp:String, pointComp:int, completeComp:int, totalComp:int):void
		{
			var percent:Number = 0;
			achievement_progress_left_mc.setScore(complete, total);
			percent = Number(complete / total);
			achievement_progress_left_mc.setProgressPercent(percent);
			
			achievement_right_panel_mc.updateCompareData(roleNameComp, pointComp, completeComp, totalComp);
		}

		public function updateList(data:Array):void
		{
			achievement_list_mc.updateList(data);
			achievement_right_panel_mc.updateList(data);
		}
		
		public function updateListData(data:Array):void
		{
			achievement_list_mc.updateListData(data);
			achievement_right_panel_mc.updateListData(data);
		}
		
		public function scrollList(id:int):void
		{
			achievement_list_mc.scrollList(id);
		}
	}
}