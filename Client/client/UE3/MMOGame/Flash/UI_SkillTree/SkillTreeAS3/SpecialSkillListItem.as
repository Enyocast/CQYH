package UI_SkillTree.SkillTreeAS3
{
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import UI_SkillTree.SkillTreeAS3.SpecialSkillListSingleItem;
	import UI_SkillTree.SkillTreeAS3.SpecialSkillListItemData;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;

	public class SpecialSkillListItem extends ListItemTreeRenderer
	{
		public var ListItem1:SpecialSkillListSingleItem;
		public var ListItem2:SpecialSkillListSingleItem;
		public var ListItem3:SpecialSkillListSingleItem;
		public var ListItem4:SpecialSkillListSingleItem;
		
		public var ListItemData:SpecialSkillListItemData;
		
		override protected function configUI():void
		{
			super.configUI();
			
			this.mouseChildren = true;
			//this.addEventListener(MouseEvent.ROLL_OVER, onRollOverListItem);
			//this.addEventListener(MouseEvent.ROLL_OUT, onRollOutListItem);
			//this.addEventListener(MouseEvent.CLICK, onClickListItem);
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(UpdateData);
		}

		function UpdateData(data:Object):void
		{
			ListItemData = data as SpecialSkillListItemData;
			if( !ListItemData ){
				visible = false;
				return;
			}
			
			visible = true;
			//
			//trace( "ListItemData.ShowMask", ListItemData.ShowMask );
			ListItem1.visible = ( ( ListItemData.ShowMask & 0x1 ) > 0 );
			//trace( "ListItem1.visible", ListItem1.visible );
			ListItem2.visible = ( ( ListItemData.ShowMask & 0x2 ) > 0 );
			//trace( "ListItem2.visible", ListItem2.visible );
			ListItem3.visible = ( ( ListItemData.ShowMask & 0x4 ) > 0 );
			//trace( "ListItem3.visible", ListItem3.visible );
			ListItem4.visible = ( ( ListItemData.ShowMask & 0x8 ) > 0 );
			//trace( "ListItem4.visible", ListItem4.visible );
			
			if( ListItem1.visible ){
				ListItem1.UpdateData( ListItemData.SingleData1 );
			}
			if( ListItem2.visible ){
				ListItem2.UpdateData( ListItemData.SingleData2 );
			}
			if( ListItem3.visible ){
				ListItem3.UpdateData( ListItemData.SingleData3 );
			}
			if( ListItem4.visible ){
				ListItem4.UpdateData( ListItemData.SingleData4 );
			}
		}
		
		
	}
}