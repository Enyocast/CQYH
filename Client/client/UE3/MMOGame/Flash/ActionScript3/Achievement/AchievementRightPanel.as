//
//成就系统主面板
//
package ActionScript3.Achievement
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollBar;
	import ActionScript3.MyScrollPanel;
	import ActionScript3.MyTipButtonNew;
	import ActionScript3.Common.CustomScrollBar;
	
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.utils.Padding;

	public class AchievementRightPanel extends UIComponent
	{
		public var achievement_comp_name_tf:TextField;
		public var achievement_comp_point_tf:TextField;
		public var achievement_comp_list_mc:AchievementCompList;
		public var achievement_comp_progress_mc:MovieClip;
		
		public var achievement_comp_scrollbar_mc:CustomScrollBar

		override protected function configUI():void
		{
			super.configUI();
			achievement_comp_list_mc.setListPos(112);
			achievement_comp_list_mc.setListHeight(380);
			achievement_comp_list_mc.setScrollBar(achievement_comp_scrollbar_mc, 380);
		}

		//
		// call from UC
		//
		public function updateCompareData(roleNameComp:String, pointComp:int, completeComp:int, totalComp:int)
		{
			achievement_comp_point_tf.text = String(pointComp);
			achievement_comp_name_tf.text = roleNameComp;
			
			var percent:Number = 0;
			achievement_comp_progress_mc.setScore(completeComp, totalComp);
			percent = Number(completeComp / totalComp);
			achievement_comp_progress_mc.setProgressPercent(percent);
		}
		
		public function updateList(data:Array)
		{
			achievement_comp_list_mc.updateList(data);
		}
		
		public function updateListData(data:Array):void
		{
			
			achievement_comp_list_mc.updateListData(data);
		}
	}
}


























