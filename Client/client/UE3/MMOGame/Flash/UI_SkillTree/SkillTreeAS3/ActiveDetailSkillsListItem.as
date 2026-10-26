package UI_SkillTree.SkillTreeAS3
{
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	//import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import UI_SkillTree.SkillTreeAS3.ActiveDetailSkillsListItemData;
	//import UI_SkillTree.SkillTreeAS3.ActiveDetailSkillsListItemEquipSlot;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.UILoader;

	public class ActiveDetailSkillsListItem extends ListItemTreeRenderer
	{
		public var SkillSlot:UILoader;
		public var SkillNameTf:TextField;
		//public var SkillLvTf:TextField;
		
		public var ListItemData:ActiveDetailSkillsListItemData;
		public var UniqueSkillID:int
		
		override protected function configUI():void
		{
			super.configUI();
			
			mouseChildren = true;
			
			SkillSlot.addEventListener(MouseEvent.ROLL_OVER, onRollOverSkillSlot);
			SkillSlot.addEventListener(MouseEvent.ROLL_OUT, onRollOutSkillSlot);
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(UpdateData);
		}
		//
		function UpdateData(data:Object):void
		{
			ListItemData = data as ActiveDetailSkillsListItemData;
			if( !ListItemData ){
				visible = false;
				return;
			}
			
			visible = true;
			
			UniqueSkillID = ListItemData.SkillID;
			//skill
			SkillNameTf.text = ListItemData.SkillName;
			//SkillLvTf.text = String( ListItemData.SkillLv );
			
			//skill slot
			//SkillSlot.SetData( 0, ListItemData.SkillIconName, ListItemData.SkillID, "", 0, -1, -1 );
			if( ListItemData.SkillIconName.length == 0 ){
				SkillSlot.source = "img://MMO_UIIcon.icon.blank";
			}
			else{
				SkillSlot.source = "img://" + ListItemData.SkillIconName;
			}
		}
		//===========================================================================
		override public function set selected(value:Boolean):void
		{
			return;
		}
		
		//
		override protected function handleMouseRollOver(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			gotoAndStop( "over" );
			//
			onRollOverSkillSlot( event );
		}

		//function onRollOutListItem( e:Event )
		override protected function handleMouseRollOut(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			gotoAndStop( "up" );
			//
			onRollOutSkillSlot( event );
		}
		
		//
		override protected function handleMousePress(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			gotoAndStop( "down" );
		}
		
		//
		override protected function handleMouseRelease(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			gotoAndStop( "over" );
		}
		//=====================================================================
		function onRollOverSkillSlot( e:Event )
		{
			if( !ListItemData ){
				return;
			}
			//
			ExternalInterface.call("ASShowTips_SkillTreeActiveSkill", this );
		}

		function onRollOutSkillSlot( e:Event )
		{
			if( !ListItemData ){
				return;
			}
			//
			ExternalInterface.call("ASHideTips_SkillTreeActiveSkill" );
		}
	}

}