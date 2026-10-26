package ActionScript3.PlayerInfoWidget
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import UI_SkillTree.SkillTreeAS3.ActiveSkillsListItemInscription;
	import UI_SkillTree.SkillTreeAS3.BtnStateController;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.UILoader;
	
	public class SkillViewSingleItem extends BtnStateController
	{
		public var skill_frame_mc:MovieClip;
		public var NewMc:MovieClip;
		
		public var ActiveMainSkillSlot:UILoader;
		public var SkillNameTf:TextField;
		public var SkillLvTitleTf:TextField;
		public var SkillLvTf:TextField;
		public var SkillRequireLvTitleTf:TextField;
		public var SkillRequireLvTf:TextField;

		public var MaxLevelMc:MovieClip;
		public var inscription_sign_mc:ActiveSkillsListItemInscription;
		public var selected_mc:MovieClip;
		
		public var SkillNameTf_selected:TextField;
		public var SkillLvTf_selected:TextField;
		
		public var SkillNameTf_disabled:TextField;
		
		public var ListItemData:SkillViewSingleItemData;
		public var UniqueSkillID:int;
		
		override protected function configUI():void
		{
			super.configUI();
			//this.enabled = true;
			this.mouseEnabled = true;
			/*this.addEventListener(MouseEvent.MOUSE_DOWN, handleMousePress);
			this.addEventListener(MouseEvent.MOUSE_UP, handleMouseRelease);
			this.addEventListener(MouseEvent.ROLL_OVER, handleMouseRollOver);
			this.addEventListener(MouseEvent.ROLL_OUT, handleMouseRollOut);
*/
			this.mouseChildren = true;
			
			ActiveMainSkillSlot.mouseEnabled = true;
			ActiveMainSkillSlot.addEventListener(MouseEvent.ROLL_OVER, handleRollOverSkillSlot);
			ActiveMainSkillSlot.addEventListener(MouseEvent.ROLL_OUT, handleRollOutSkillSlot);
			
			inscription_sign_mc.mouseEnabled = true;
			
			NewMc.mouseEnabled = false;
		}
		
		override public function set selected(value:Boolean):void
		{
			if (_selected == value)
			{
				return;
			}
			
			_selected = value;
			updateState();
			updateSelectedElement(value);
		}
		
		function UpdateData(data:Object):void
		{
			ListItemData = data as SkillViewSingleItemData;
			if( !ListItemData ){
				visible = false;
				return;
			}
			visible = true;
			if( ListItemData.IsDisabled ){
				var hintLowLevel:Boolean = ( ListItemData.SkillRequireLv > 0 );
				SkillRequireLvTitleTf.visible = hintLowLevel;
				SkillRequireLvTf.visible = hintLowLevel;
				SkillRequireLvTf.text = String( ListItemData.SkillRequireLv );
				gotoAndStop("disabled");
			}
			else{
				SkillRequireLvTitleTf.visible = false;
				SkillRequireLvTf.visible = false;
				gotoAndStop("up");
			}
			_selected = false;
			//text
			trace("ActiveMainSkillSlot.source",ListItemData.SkillIconName);
			
			ActiveMainSkillSlot.source = "img://" + ListItemData.SkillIconName;
			UniqueSkillID = ListItemData.SkillID;
			
			if(ListItemData.IsCurrent){
				selected = true;
				var itemGroup:SkillViewListItem = parent as SkillViewListItem;
				itemGroup.setSelectedItemId(itemid);
			}else{
				updateSelectedElement(false);//update text
			}
			//
			NewMc.visible = ListItemData.IsNew;
			//
			if( ListItemData.IsMaxLv ){
				MaxLevelMc.visible = true;
			}
			else{
				MaxLevelMc.visible = false;
			}
			if(inscription_sign_mc)
				inscription_sign_mc.updateData(ListItemData.RuneSkillID, ListItemData.SkillInscriptionType);
			
			var skillFrameLabel:String = (ListItemData.RuneSkillID > 0 && !ListItemData.IsDisabled) ? "type_inscription":"type_normal";
			if(skill_frame_mc)
				skill_frame_mc.gotoAndStop(skillFrameLabel);
			if(inscription_sign_mc)
				inscription_sign_mc.visible = !ListItemData.IsDisabled;
			if(SkillLvTf){
				SkillLvTf.visible = !ListItemData.IsDisabled;
			}
		}
		
		private function updateSelectedElement(value:Boolean):void
		{
			if(value){
				SkillNameTf_selected.text = ListItemData.SkillName;
				SkillLvTf_selected.text = String( ListItemData.SkillLv );
			}else{
				if( ListItemData.IsDisabled ){
					SkillNameTf_disabled.text = ListItemData.SkillName;
				}else{
					SkillNameTf.text = ListItemData.SkillName;
					SkillLvTf.text = String( ListItemData.SkillLv );
				}
			}
		}
		
		//
		private function handleMouseRollOver(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			if( !ListItemData.IsDisabled &&　!selected){
				onThisRollOver();
			}
		}
		
		//
		function handleMouseRollOut(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			if( !ListItemData.IsDisabled){
				onThisRollOut();
			}
		}
		
		//
		function handleMousePress(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			if( !ListItemData.IsDisabled &&　!selected){
				selected = true;
				onThisMouseDown( event );
				var itemGroup:SkillViewListItem = parent as SkillViewListItem;
				itemGroup.setSelectedItemId(itemid);
				//itemGroup.skillGroupType != -1
				ExternalInterface.call( "ASSetSkill", itemGroup.skillGroupType, ListItemData.SkillID );
			}
		}
		
		//
		function handleMouseRelease(event:MouseEvent):void
		{
			if( !ListItemData ){
				return;
			}
			//
			if( !ListItemData.IsDisabled ){
				onThisMouseUp( event );
			}
		}
		
		//===================================================================
		function handleRollOverSkillSlot(event:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_SkillTreeActiveSkillView", this);
		}
		
		//
		function handleRollOutSkillSlot(event:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_SkillTreeActiveSkillView" );
		}
	}
}