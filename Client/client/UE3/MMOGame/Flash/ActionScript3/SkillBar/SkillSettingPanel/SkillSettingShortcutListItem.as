package ActionScript3.SkillBar.SkillSettingPanel
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.UILoader;

	public class SkillSettingShortcutListItem extends ListItemTreeRenderer
	{
		//public var DisableMaskMc:MovieClip;
		//public var TypeMc:MovieClip;
		//public var SkillListItemBtn:Button;
		public var NewMc:MovieClip;
		public var RecommendMc:MovieClip;
		public var CurrentMc:MovieClip;
		
		//public var SkillSlot:MyItemSlot;
		public var SkillSlot:UILoader;
		public var SkillNameTf:TextField;
		public var SkillLvTitleTf:TextField;
		public var SkillLvTf:TextField;
		public var SkillRequireLvTitleTf:TextField;
		public var SkillRequireLvTf:TextField;
		
		public var ListItemData:SkillSettingShortcutListItemData;
		
		//public var MainSkillID:int;
		//public var RuneSkillID:int;
		//public var SkillLv:int;
		public var UniqueSkillID:int;
		
		override protected function configUI():void
		{
			super.configUI();
			
			//this.addEventListener(MouseEvent.ROLL_OVER, onRollOverListItem);
			//this.addEventListener(MouseEvent.ROLL_OUT, handleMouseRollOut);
			addEventListener(MouseEvent.ROLL_OVER, handleMouseRollOver, false, 0, true);
            addEventListener(MouseEvent.ROLL_OUT, handleMouseRollOut, false, 0, true);
           // addEventListener(MouseEvent.MOUSE_DOWN, handleMousePress, false, 0, true);
            //addEventListener(MouseEvent.CLICK, handleMouseRelease, false, 0, true);
			//addEventListener(MouseEvent.CLICK, onClickListItem);
			
			NewMc.gotoAndStop( 1 );
			NewMc.visible = false;
				
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(UpdateData);
		}

		function UpdateData(data:Object):void
		{
			ListItemData = data as SkillSettingShortcutListItemData;
			if( !ListItemData ){
				visible = false;
				return;
			}
			
			visible = true;
			selectable = false;
			//
			if( ListItemData.IsNew ){
				NewMc.visible = true;
				NewMc.gotoAndPlay( 1 );
			}
			else{
				NewMc.gotoAndStop( 1 );
				NewMc.visible = false;
			}
			
			RecommendMc.visible = ListItemData.IsRecommend;
			CurrentMc.visible = ListItemData.IsCurrent;
			
			//text
			SkillNameTf.text = ListItemData.SkillName;
			SkillLvTf.text = String( ListItemData.SkillLv );
			if( ListItemData.IsDisabled ){
				var hintLowLevel:Boolean = (  ListItemData.SkillRequireLv > 0 );
				SkillRequireLvTitleTf.visible = hintLowLevel;
				SkillRequireLvTf.visible = hintLowLevel;
				SkillRequireLvTf.text = String( ListItemData.SkillRequireLv );
				
				setState("disabled");
				//enabled = false;
			}
			else{
				SkillRequireLvTitleTf.visible = false;
				SkillRequireLvTf.visible = false;
				
				//setState("up");
				//enabled = true;
			}
			
			//slot
			if( ListItemData.SkillIconName.length == 0 ){
				SkillSlot.source = "img://MMO_UIIcon.icon.blank";
			}
			else{
				SkillSlot.source = "img://" + ListItemData.SkillIconName;
			}
			//SkillSlot.SetSlotType( ListItemData.SkillSlotType );
			//SkillSlot.SetData( 0, ListItemData.SkillIconName, ListItemData.SkillID, "", 0, -1, -1 );
			//MainSkillID = ListItemData.SkillID;
			//RuneSkillID = 0;
			//SkillLv = ListItemData.SkillLv;
			UniqueSkillID = ListItemData.SkillID;
		}
		
		//
		override public function set selected(value:Boolean):void {
			return;
			//
			if( ListItemData != null && !ListItemData.IsDisabled ){
				super.selected = value;
			}
		}
		//
		//function onRollOverListItem( event:Event )
		override protected function handleMouseRollOver(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			if( !ListItemData.IsDisabled ){
				super.handleMouseRollOver( event );
			}
			
			ExternalInterface.call("ASShowTips_SkillSettingActive", this );
		}

		//function onRollOutListItem( e:Event )
		override protected function handleMouseRollOut(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			if( !ListItemData.IsDisabled ){
				super.handleMouseRollOut( event );
			}
			
			//
			//SkillSlot.dispatchEvent( e );
			ExternalInterface.call("ASHideTips_SkillSettingActive", this );
		}
		
		//
		override protected function handleMousePress(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			if( !ListItemData.IsDisabled ){
				super.handleMousePress( event );
			}
		}
		
		//
		override protected function handleMouseRelease(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			if( !ListItemData.IsDisabled ){
				super.handleMouseRelease( event );
			}
			else{
				//为了在disable下发送点击消息,非disable下在ListEvent.ITEM_CLICK中处理
				//不调用super.handleMouseRelease( event )将没有ListEvent.ITEM_CLICK事件
				ExternalInterface.call( "ASSetSkill", ListItemData.SkillSlotType, ListItemData.SkillID );
			}
			
		}
		
		//
		function onClickListItem( event:Event )
		{
			if( !ListItemData ){
				return;
			}
			ExternalInterface.call( "ASSetSkill", ListItemData.SkillSlotType, ListItemData.SkillID );
		}
		
	}

}