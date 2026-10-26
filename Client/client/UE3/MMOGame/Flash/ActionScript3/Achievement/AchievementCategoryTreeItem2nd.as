
package ActionScript3.Achievement
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.display.MovieClip;	
	import flash.text.TextField;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.controls.StateUIComponent;
	
	public class AchievementCategoryTreeItem2nd extends StateUIComponent 
	{
		public var titleName:TextField;
		public var titleCount:TextField;
		
		public function AchievementCategoryTreeItem2nd() 
		{
			// constructor code
			titleName = this.getChildByName("titleName") as TextField;
			titleCount = this.getChildByName("titleCount") as TextField;
			titleName.text = "";
			titleCount.text = "";
		}
		
		public function updateItemData(data:Object):void
		{
			var achievement_data:AchievementData = data as AchievementData;
			if (achievement_data)
			{
				titleName.text = achievement_data.label;
				titleCount.text = achievement_data.percent;
			}
		}
		
		override public function updateState():void
		{
			super.updateState();
			if (_mouseOver)
			{
				titleName.textColor = titleCount.textColor = 0xCBBDA7;
			}
			else
			{
				titleName.textColor = titleCount.textColor = 0xC0B19B;
			}
			
			if (_selected)
			{
				titleName.textColor = titleCount.textColor = 0xEDE5D9;
			}
		}
	}
}

