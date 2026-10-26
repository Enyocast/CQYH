package UI_SkillTree.SkillTreeAS3
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.UILoader;
	
	//test
	//import UI_SkillTree.SkillTreeAS3.ActiveSkillListPanel;
	//import UI_SkillTree.SkillTreeAS3.ActiveDetailSkillsListPanel;
	//import UI_SkillTree.SkillTreeAS3.ActiveDetailSkillsListItemData;
	
	public class ActiveSkillListSingleItem extends BtnStateController
	{
		public var skill_frame_mc:MovieClip;
		//public var NewMc:MovieClip;
		
		public var ActiveMainSkillSlot:UILoader;
		public var SkillNameTf:TextField;
		public var SkillLvTitleTf:TextField;
		public var SkillLvTf:TextField;
		public var SkillRequireLvTitleTf:TextField;
		public var SkillRequireLvTf:TextField;
		
		public var LevelUpBtn:Button;
		//public var btn_inscription:Button;
		public var MaxLevelMc:MovieClip;
		public var inscription_sign_mc:ActiveSkillsListItemInscription;
		public var selected_mc:MovieClip;
		
		public var SkillNameTf_selected:TextField;
		public var SkillLvTf_selected:TextField;
		
		public var SkillNameTf_disabled:TextField;
		
		public var ListItemData:ActiveSkillListItemSingleData;
		public var UniqueSkillID:int;
		
		override protected function configUI():void
		{
			super.configUI();
			//this.enabled = true;
			this.mouseEnabled = true;
			this.addEventListener(MouseEvent.MOUSE_DOWN, handleMousePress);
			this.addEventListener(MouseEvent.MOUSE_UP, handleMouseRelease);
			this.addEventListener(MouseEvent.ROLL_OVER, handleMouseRollOver);
			this.addEventListener(MouseEvent.ROLL_OUT, handleMouseRollOut);

			this.mouseChildren = true;
			
			LevelUpBtn.addEventListener(MouseEvent.CLICK, onClickSkillLevelUp);
			LevelUpBtn.addEventListener(MouseEvent.ROLL_OVER, onRollOverSkillLvUpBtn);
			LevelUpBtn.addEventListener(MouseEvent.ROLL_OUT, onRollOutSkillLvUpBtn);
			//LevelUpBtn.visible = false;
			
			ActiveMainSkillSlot.mouseEnabled = true;
			ActiveMainSkillSlot.addEventListener(MouseEvent.ROLL_OVER, handleRollOverSkillSlot);
			ActiveMainSkillSlot.addEventListener(MouseEvent.ROLL_OUT, handleRollOutSkillSlot);
			
			inscription_sign_mc.mouseEnabled = true;
			inscription_sign_mc.addEventListener(MouseEvent.ROLL_OVER, handleRollOverInscriptionSign);
			inscription_sign_mc.addEventListener(MouseEvent.ROLL_OUT, handleRollOutInscriptionSign);
			
			//NewMc.mouseEnabled = false;
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
			ListItemData = data as ActiveSkillListItemSingleData;
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
			if(ListItemData.IsCurrent){
				selected = true;
				var itemGroup:ActiveSkillListItem = parent as ActiveSkillListItem;
				itemGroup.setSelectedItemId(itemid);
			}else{
				updateSelectedElement(false);//update text
			}
			//
			//NewMc.visible = ListItemData.IsNew;
			//
			if( ListItemData.IsMaxLv ){
				LevelUpBtn.visible = false;
				MaxLevelMc.visible = true;
			}
			else{
				LevelUpBtn.visible = (ListItemData.CanLvUp && !ListItemData.IsDisabled);
				MaxLevelMc.visible = false;
			}
			inscription_sign_mc.updateData(ListItemData.RuneSkillID, ListItemData.SkillInscriptionType);
			var skillFrameLabel:String = (ListItemData.RuneSkillID > 0 && !ListItemData.IsDisabled) ? "type_inscription":"type_normal";
			skill_frame_mc.gotoAndStop(skillFrameLabel);
			inscription_sign_mc.visible = !ListItemData.IsDisabled;
			if(SkillLvTf){
				SkillLvTf.visible = !ListItemData.IsDisabled;
			}
			//slot
			//SkillSlot.SetSlotType( ListItemData.SkillSlotType );
			//SkillSlot.SetData( 0, ListItemData.SkillIconName, ListItemData.SkillID, "", 0, -1, -1 );
			if( ListItemData.SkillIconName.length == 0 ){
				ActiveMainSkillSlot.source = "img://MMO_UIIcon.icon.blank";
			}
			else{
				ActiveMainSkillSlot.source = "img://" + ListItemData.SkillIconName;
			}
			
			//var listItemRenderParent:ListItemRenderer = parent as ListItemRenderer;
			//trace( "=======IMG"+listItemRenderParent.index+"_"+ListItemData.ItemIdx+" :", ActiveMainSkillSlot.source );
			UniqueSkillID = ListItemData.SkillID;
		}
		
		private function updateSelectedElement(value:Boolean):void
		{
			var name_tf:TextField;
			if(value){
				SkillNameTf_selected.text = ListItemData.SkillName;
				SkillLvTf_selected.text = String( ListItemData.SkillLv );
				name_tf = SkillNameTf_selected;
			}else{
				if( ListItemData.IsDisabled ){
					SkillNameTf_disabled.text = ListItemData.SkillName;
					name_tf = SkillNameTf_disabled;
				}else{
					SkillNameTf.text = ListItemData.SkillName;
					SkillLvTf.text = String( ListItemData.SkillLv );
					name_tf = SkillNameTf;
				}
			}
			if(name_tf.numLines > 1){
				name_tf.y = 0;
			}else{
				name_tf.y = 8;
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
			//ignore LevelUpBtn click
			if(event.target == LevelUpBtn){
				return; 
			}
			if( !ListItemData.IsDisabled &&　!selected){
				selected = true;
				onThisMouseDown( event );
				var itemGroup:ActiveSkillListItem = parent as ActiveSkillListItem;
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
			
			//ExternalInterface.call("ASHideTips_SkillTreeActiveSkill" );
			
			//trace( "parent :", parent );//ListItemRenderer
			//trace( "parent.parent :", parent.parent );//
			//trace( "parent.parent.parent :", parent.parent.parent );//AllActiveSkillsScrollList
			//trace( "parent.parent.parent.parent :", parent.parent.parent.parent.x );//ActiveSkillListPanelMc
			//trace( "parent.parent.parent.parent.parent :", parent.parent.parent.parent.parent.x );//skillTreePanel
			
//			var mouseDownPosX:Number = root.mouseX - parent.parent.x - parent.parent.parent.parent.x - parent.parent.parent.parent.parent.x;
//			var mouseDownPosY:Number = root.mouseY - parent.parent.y - parent.parent.parent.parent.y - parent.parent.parent.parent.parent.y;
//			var activeSkillPanel:ActiveSkillListPanel = parent.parent.parent.parent as ActiveSkillListPanel;
//			
//			var activeSkillPanel:ActiveSkillListPanel = parent.parent.parent.parent as ActiveSkillListPanel;
//			var listItemRenderParent:ListItemRenderer = parent as ListItemRenderer;
//			var scrollingListGParent:ScrollingList = parent.parent.parent as ScrollingList;
//			
//			var posX:Number = ( ( ListItemData.ItemIdx + 1 ) * 185 ) * listItemRenderParent.actualScaleX;
//			//var posY:Number = ( listItemRenderParent.index - scrollingListGParent.scrollPosition ) * listItemRenderParent.actualHeight;
//			var posY:Number = listItemRenderParent.y;//listItemRenderParent.index * 100 - scrollingListGParent.scrollPosition;
//			//trace( "==========listItemRenderParent.actualHeight:",listItemRenderParent.actualHeight, "listItemRenderParent.y:", listItemRenderParent.y, " Index: ", scrollingListGParent.scrollPosition );
//			
//			TestData();
//			activeSkillPanel.DetailActiveSkillListPanelMc.visible = true;
//			activeSkillPanel.DetailActiveSkillListPanelMc.x = posX;
//			activeSkillPanel.DetailActiveSkillListPanelMc.y = posY;
//			
//
//			ExternalInterface.call( "ASShowSkillDetail", this, ListItemData.SkillID, posX, posY );
		}
		
		//===================================================================
		function handleRollOverSkillSlot(event:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_SkillTreeActiveSkill", this);
		}
		
		//
		function handleRollOutSkillSlot(event:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_SkillTreeActiveSkill" );
		}
		
		
		function onClickSkillLevelUp(event:MouseEvent):void
		{
			ExternalInterface.call( "ASLevelUpSkill", ListItemData.SkillID );
		}
		
		//
		function onRollOverSkillLvUpBtn(event:MouseEvent):void
		{
			ExternalInterface.call( "ASShowTips_SkillLvUpBtn", LevelUpBtn, ListItemData.SkillID );
		}
		
		//
		function onRollOutSkillLvUpBtn(event:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_SkillLvUpBtn" );
		}
		
		//To confirm
		function handleRollOverInscriptionSign(event:MouseEvent):void
		{
			ExternalInterface.call( "ASShowTips_SkillTreeRuneSkill", inscription_sign_mc);
		}
		
		//To confirm
		function handleRollOutInscriptionSign(event:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_SkillTreeRuneSkill" );
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