
package ActionScript3.Achievement
{
	import ActionScript3.Achievement.AchievementCategoryTreeItem1st;
	import ActionScript3.Achievement.AchievementCategoryTreeItem2nd;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import scaleform.clik.core.CLIK;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	public class AchievementCategoryTreeItem extends ListItemTreeRenderer 
	{
		public var achievement_category_tree_item_1st:AchievementCategoryTreeItem1st;
		public var achievement_category_tree_item_2nd:AchievementCategoryTreeItem2nd;
		
		var itemState:Number = 0;
		
		public function AchievementCategoryTreeItem()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateItemData);
		}
		
		public function updateItemData(data:Object):void
		{
			var achievement_data:AchievementData = data as AchievementData;
			if (achievement_data)
			{
				visible = true;
				this.enabled = true;
				
				achievement_category_tree_item_1st.visible = false;
				achievement_category_tree_item_2nd.visible = false;
				
				if (achievement_data.deepth == 0)
				{
					achievement_category_tree_item_1st.updateItemData(data);
					achievement_category_tree_item_1st.visible = true;
					achievement_category_tree_item_1st.selected = achievement_data.isSelected;
				}
				else
				{
					achievement_category_tree_item_2nd.updateItemData(data);
					achievement_category_tree_item_2nd.visible = true;
					achievement_category_tree_item_2nd.selected = achievement_data.isSelected;
				}
			}
			else
			{
				visible = false;
			}
		}
		
		protected override function handleMouseRollOver(event:MouseEvent):void
		{
			super.handleMouseRollOver(event);
		}

		protected override function handleMouseRollOut(event:MouseEvent):void
		{
			super.handleMouseRollOut(event);
		}

		protected override function handleMousePress(event:MouseEvent):void
		{
			super.handleMousePress(event);
		}

		protected override function handleMouseRelease(event:MouseEvent):void
		{
			super.handleMouseRelease(event);
		}

		protected override function handleReleaseOutside(event:MouseEvent):void
		{
			super.handleReleaseOutside(event);
		}
	}
}

