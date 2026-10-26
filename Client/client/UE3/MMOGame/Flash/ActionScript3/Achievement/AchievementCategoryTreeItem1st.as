
package ActionScript3.Achievement
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	import ActionScript3.controls.StateUIComponent;
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.core.UIComponent;
	
	public class AchievementCategoryTreeItem1st extends StateUIComponent 
	{
		public var titleName:TextField;
		public var titleCount:TextField;
		
		public function AchievementCategoryTreeItem1st() 
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
			if (_mouseDown)
			{
				titleName.textColor = titleCount.textColor = 0x9B8E7A;
			}
			else
			{
				if (_mouseOver)
				{
					titleName.textColor = titleCount.textColor = 0xCBBDA7;
				}
				else
				{
					titleName.textColor = titleCount.textColor = 0xC0B19B;
				}
			}
			
			if (_selected)
			{
				titleName.textColor = titleCount.textColor = 0xEDE5D9;
			}
		}
	}
}

