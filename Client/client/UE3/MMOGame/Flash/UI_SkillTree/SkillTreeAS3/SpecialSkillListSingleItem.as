package UI_SkillTree.SkillTreeAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import ActionScript3.ItemSlot.MyItemSlot;
	import UI_SkillTree.SkillTreeAS3.SpecialSkillListItemData;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.UILoader;
	import UI_SkillTree.SkillTreeAS3.BtnStateController;
	
	public class SpecialSkillListSingleItem extends BtnStateController
	{
		public var SkillSlot:MyItemSlot;
		public var SkillNameTf:TextField;
		public var SkillRequireTf:TextField;
		
		public var ListItemData:SpecialSkillListItemSingleData;
		public var UniqueSkillID:int;
		
		import scaleform.clik.controls.ListItemRenderer;
		import scaleform.clik.controls.ScrollingList;
		
		override protected function configUI():void
		{
			super.configUI();
			
			mouseChildren = true;
			//removeEventListener(MouseEvent.ROLL_OVER, onRollOver);
			//removeEventListener(MouseEvent.ROLL_OUT, onRollOut);
			//removeEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			//removeEventListener(MouseEvent.MOUSE_UP, onMouseUp);
			
			//ListItemBtn.addEventListener(MouseEvent.MOUSE_DOWN, handleMousePress);
			//ListItemBtn.addEventListener(MouseEvent.CLICK, handleMouseRelease);
			//ListItemBtn.addEventListener(MouseEvent.ROLL_OVER, handleMouseRollOver);
			//ListItemBtn.addEventListener(MouseEvent.ROLL_OUT, handleMouseRollOut);

		}

		function UpdateData(data:Object):void
		{
			ListItemData = data as SpecialSkillListItemSingleData;
			if( !ListItemData ){
				visible = false;
				return;
			}
			
			visible = true;
			
			//text
			SkillNameTf.text = ListItemData.SkillName;
			SkillRequireTf.text = ListItemData.SkillRequire;
			
			//slot
			UniqueSkillID = ListItemData.SkillID;
			
			SkillSlot.SetSlotType( ListItemData.TipsType );
			SkillSlot.SetData(0, ListItemData.SkillIconName, UniqueSkillID, "", 0, -1, -1);				
			//
			SkillSlot.DisableDrag = ( ListItemData.IsDisabled || !ListItemData.CanDrag );
		}
		
		//
		function handleMouseRollOver(event:MouseEvent):void
		{

		}
		
		//
		function handleMouseRollOut(event:MouseEvent):void
		{

		}
		
		//
		function handleMousePress(event:MouseEvent):void
		{

		}
		
		//
		function handleMouseRelease(event:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_SkillTreeActiveSkill" );
			
		}
		
		/*
		//test
		public function TestData()
		{
			var itemsData:Array = new Array();
			var itemIdx:int = 0;
			for (var i:int = 1; i <= 6; i++)
			{
				var listItem:ActiveDetailSkillsListItemData = new ActiveDetailSkillsListItemData ;
				//

				listItem.SkillName = "测试符文技能"+itemIdx
				listItem.SkillID = itemIdx + 1000
				listItem.SkillIconName = "";
				++itemIdx;
				
				itemsData.push( listItem );
			}
			
			var activeSkillPanel:ActiveSkillListPanel = parent.parent.parent.parent as ActiveSkillListPanel;
			var targetPanel:ActiveDetailSkillsListPanel = activeSkillPanel.DetailActiveSkillListPanelMc;
			targetPanel.UpdateSkillScrollList( itemsData );
		}
		*/
	}
}