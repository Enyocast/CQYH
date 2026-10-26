package UI_SkillSetting.SkillSettingAS3
{
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	//import ActionScript3.ItemSlot.MyItemSlot;
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.controls.Button;
	import ActionScript3.controls.StateUIComponent;
	//test
	import UI_SkillSetting.SkillSettingAS3.SkillSettingPanel;
	import UI_SkillSetting.SkillSettingAS3.SkillListItemData;
	
	public class SkillSettingBtn extends UIComponent
	{
		public var KegTypeMc:MovieClip;
		public var SettingBtn:Button;
		public var OnIconSettingBtn:Button;
		public var LockMc:MovieClip;
		
		//public var SkillSlot:MyItemSlot;
		public var SkillSlot:UILoader;
		public var SkillNameTf:TextField;
		public var SkillLvTf:TextField;
		public var SkillLvTitleTf:TextField;
		
		public var AutoSetBtn:Button;
		//public var SkillRuneMc:MovieClip;
		public var SkillRuneNameTf:TextField;
		public var SkillRuneLvTf:TextField;
		public var SkillRuneLvTitleTf:TextField;
		
		//public var IsSelected:Boolean;
		
		public var NewFlag:MovieClip;
		public var FuncBtn:Button;
		
		public var _SettingBtnType:int;
		public var IsLocked:Boolean;
		public var _IsSetting:Boolean;
		
		//public var MainSkillID:int;
		//public var RuneSkillID:int;
		public var MainSkillLv:int;
		public var RuneSkillLv:int;
		public var UniqueMainSkillID:int;
		public var UniqueRuneSkillID:int;
		public var UniqueSkillID:int;
		public var HasRune:Boolean;
		
		public var KegTypeMcPosY:int;
		//public var SettingBtnPosY:int;
		//public var SkillSlotPosY:int;
		public var SkillNameTfPosY:int;
		public var SkillLvTfPosY:int;
		public var SkillLvTitleTfPosY:int;
		
		public var AutoSetBtnPosY:int;
		//public var SkillRuneMcPosY:int;
		public var SkillRuneNameTfPosY:int;
		public var SkillRuneLvTfPosY:int;
		public var SkillRuneLvTitleTfPosY:int;
		
		public var NewFlagPosY:int;
		public var FuncBtnPosY:int;
		//
		override protected function configUI():void 
		{
			super.configUI();
			
			mouseChildren = true;
			
			FuncBtn.visible = false;
			AutoSetBtn.visible = false;
			
			//IsSelected = false;
			SettingBtn.addEventListener( MouseEvent.MOUSE_OVER, MouseRollOverSkillSettingBtn );
			SettingBtn.addEventListener( MouseEvent.MOUSE_OUT, MouseRollOutSkillSettingBtn );
			SettingBtn.addEventListener( MouseEvent.CLICK, BeingSettingSkill );
			SettingBtn.addEventListener( MouseEvent.MOUSE_DOWN, MousePressSkillSettingBtn );
			SettingBtn.addEventListener( MouseEvent.MOUSE_UP, MouseUpSkillSettingBtn );
			//
			OnIconSettingBtn.addEventListener( MouseEvent.MOUSE_OVER, MouseRollOverSkillIconBtn );
			OnIconSettingBtn.addEventListener( MouseEvent.MOUSE_OUT, MouseRollOutSkillIconBtn );
			OnIconSettingBtn.addEventListener( MouseEvent.CLICK, BeingSettingSkill );
			OnIconSettingBtn.addEventListener( MouseEvent.MOUSE_DOWN, MousePressSkillSettingBtn );
			OnIconSettingBtn.addEventListener( MouseEvent.MOUSE_UP, MouseUpSkillSettingBtn );
			//
			LockMc.addEventListener( MouseEvent.MOUSE_OVER, MouseRollOverLockMc );
			LockMc.addEventListener( MouseEvent.MOUSE_OUT, MouseRollOutLockMc );
			//
			AutoSetBtn.addEventListener( MouseEvent.CLICK, AutoSetSkill );
			AutoSetBtn.addEventListener( MouseEvent.MOUSE_OVER, MouseRollOverAutoSetBtn );
			AutoSetBtn.addEventListener( MouseEvent.MOUSE_OUT, MouseRollOutAutoSetBtn );
			//
			FuncBtn.addEventListener( MouseEvent.CLICK, MakeEquipRune );
			FuncBtn.addEventListener( MouseEvent.MOUSE_OVER, MouseRollOverFuncBtn );
			FuncBtn.addEventListener( MouseEvent.MOUSE_OUT, MouseRollOutFuncBtn );
			
			//
			KegTypeMcPosY = KegTypeMc.y;
			//SkillSlotPosY = SkillSlot.y;
			SkillNameTfPosY = SkillNameTf.y;
			SkillLvTfPosY = SkillLvTf.y;
			SkillLvTitleTfPosY = SkillLvTitleTf.y;
			
			AutoSetBtnPosY = AutoSetBtn.y;
			//SkillRuneMcPosY = SkillRuneMc.y;
			SkillRuneNameTfPosY = SkillRuneNameTf.y;
			SkillRuneLvTfPosY = SkillRuneLvTf.y;
			SkillRuneLvTitleTfPosY = SkillRuneLvTitleTf.y;
			
			NewFlagPosY = NewFlag.y;
			FuncBtnPosY = FuncBtn.y;
			//
			SetSkill( false, true, "", 0, "", -1 );
		}
		
		//==========================================================================================
		public function BeingSettingSkill( e:Event )
		{
			ExternalInterface.call("ASBeginSettingSkill", _SettingBtnType );
			
			//test
			//TestBeingSettingSkill();
		}
		function TestBeingSettingSkill()
		{
			var skillSettingPanel:SkillSettingPanel = parent as SkillSettingPanel;// parent["SkillListPanelMc"];
			skillSettingPanel.SkillListPanelMc.visible = true;
			
			var itemsData:Array = new Array();
			for (var i:int = 1; i <= 10; i++)
			{
				var skillItemData:SkillListItemData = new SkillListItemData ;
				skillItemData.IsNew = ( i == 2 || i == 5);
				skillItemData.IsRecommend = ( i == 4 );
				skillItemData.IsCurrent = ( i == 3 );
				skillItemData.SkillName = "技能" + i;
				skillItemData.SkillLv = i;
				skillItemData.SkillRequireLv = i*2;
				skillItemData.IsDisabled = ( i > 4 );
				skillItemData.SkillSlotType = 0;
				skillItemData.SkillID = i+1000;
				skillItemData.SkillIconName = "xxx";
				
				itemsData.push( skillItemData );
			}
			
			skillSettingPanel.UCSetSkillList( 0, itemsData );
			
			//
			//UpdateSettingState( !IsSetting );
			//test end
		}
		//==========================================================================================
		public function AutoSetSkill( e:Event )
		{
			AutoSetBtn.visible = false;
			
			ExternalInterface.call("ASAutoSetSkill", _SettingBtnType );
		}
		
		//
		public function ActiveAutoSetBtn( isActive:Boolean )
		{
			AutoSetBtn.visible = isActive;
		}
		//
		public function ActiveFastMakeEquipRune( isActive:Boolean )
		{
			FuncBtn.visible = isActive;
		}
		
		//==========================================================================================
		public function get IsNewSlot():Boolean
		{
			return NewFlag.visible;
		}
		public function set IsNewSlot( setValue:Boolean )
		{
			NewFlag.visible = setValue;
		}
		
		//==========================================================================================
		public function get SettingBtnType():int
		{
			return _SettingBtnType;
		}
		public function set SettingBtnType( setValue:int )
		{
			_SettingBtnType = setValue;
			KegTypeMc.gotoAndStop( _SettingBtnType*10 + 1 );
		}
		
		//==========================================================================================
		public function SetSkill( isNew:Boolean, isLocked:Boolean, skillName:String, skillLv:int, iconName:String, skillID:int )
		{
			var hasSkill:Boolean = ( skillID >= 0 );
			
			//MainSkillID = skillID;
			MainSkillLv = skillLv;
			UniqueMainSkillID = skillID;
			
			
			IsLocked = isLocked;
			LockMc.visible = IsLocked;
			if( isNew ){
				NewFlag.visible = true;
				NewFlag.gotoAndPlay( 1 );
			}
			else{
				NewFlag.gotoAndStop( 1 );
				NewFlag.visible = false;
			}
			
			SkillSlot.visible = hasSkill;
			SkillNameTf.visible = hasSkill;
			SkillLvTitleTf.visible = hasSkill;
			SkillLvTf.visible = hasSkill;
			
			UniqueSkillID = -1;
			if( hasSkill ){
				UniqueSkillID = UniqueMainSkillID;
				
				SkillNameTf.text = skillName;
				SkillLvTf.text = String(skillLv);
				
				//SkillSlot.SetData( 0, iconName, skillID, "", 0, -1, -1 );
				SkillSlot.source = "img://" + iconName;
			}
			
			//主技能更新了，老的符文技能也没意义了
			SetSkillRune( false, "", 0, -1 );
		}
		//==========================================================================================
		//public function SetSkillRune( hasRune:Boolean, skillRuneIconName:String, skillRuneText:String )
		public function SetSkillRune( hasRune:Boolean, skillRuneName:String, skillRuneLv:int, skillID:int )
		{
			//SkillRuneMc.visible = hasRune;
			HasRune = hasRune;
			RuneSkillLv = skillRuneLv;
			UniqueRuneSkillID = skillID;
				
			SkillRuneNameTf.visible = HasRune;
			
			SkillRuneLvTitleTf.visible = HasRune;
			SkillRuneLvTf.visible = HasRune;
			
			if( HasRune ){
				//RuneSkillID = hasRune ? skillID : -1;
				UniqueSkillID = UniqueRuneSkillID;
				
				//SkillRuneMc.source = "img://" + skillRuneIconName;
				SkillRuneNameTf.text = skillRuneName;
				SkillRuneLvTf.text = String(skillRuneLv);
			}
		}
		
		//==========================================================================================
		/*
		public function get itemIndex():int
		{
			return SkillSlot.itemIndex;
		}
		public function set itemIndex( setValue:int )
		{
			SkillSlot.itemIndex = setValue;
		}
		
		public function get itemid():int
		{
			return SkillSlot.itemid;
		}
		public function set itemid( setValue:int )
		{
			SkillSlot.itemid = setValue;
		}
		*/
		//
		public function MouseRollOverSkillSettingBtn( e:Event )
		{
			//gotoAndPlay( SettingBtn.state );
			if( _IsSetting ){
				gotoAndPlay( "selected_over" );
			}
			else{
				gotoAndPlay("over");
			}
			
			//
			ModiyContentPosY( 0 );
		}
		
		public function MouseRollOverSkillIconBtn( e:Event )
		{
			ExternalInterface.call("ASShowTips_SkillSettingActive", this );
		}
		//
		public function MouseRollOutSkillSettingBtn( e:Event )
		{
			//gotoAndPlay( SettingBtn.state );
			if( _IsSetting ){
				gotoAndPlay( "selected_up" );
			}
			else{
				gotoAndPlay("up");
			}
			//
			ModiyContentPosY( 0 );
		}
		
		public function MouseRollOutSkillIconBtn( e:Event )
		{
			ExternalInterface.call("ASHideTips_SkillSettingActive", this );
		}
		//
		public function MousePressSkillSettingBtn( e:Event )
		{
			//gotoAndPlay( SettingBtn.state );
			if( _IsSetting ){
				gotoAndPlay( "selected_down" );
			}
			else{
				gotoAndPlay("down");
			}
			//
			ModiyContentPosY( 1 );
		}
		//
		public function MouseUpSkillSettingBtn( e:Event )
		{
			//gotoAndPlay( SettingBtn.state );
			if( _IsSetting ){
				gotoAndPlay( "selected_over" );
			}
			else{
				gotoAndPlay("over");
			}
			//
			ModiyContentPosY( 0 );
		}
		//=================================================================
		public function UpdateSettingState( isSelected:Boolean, curStateFrame:String ):void
		//public function UpdateSettingState( isSelected:Boolean ):void
		{
			_IsSetting = isSelected;
			
			//SettingBtn.selected = _IsSetting;
			
			var prefix:String = "";
			if( _IsSetting ){
				prefix = "selected_";
			}
			if( curStateFrame == "null" || curStateFrame == "out" || curStateFrame.length == 0 ){
				curStateFrame = "up";
			}
			//
			if( curStateFrame == "out" ){
				curStateFrame = "up";
			}
			//
			if( curStateFrame == "release" ){
				curStateFrame = "over";
			}
			
			var frameName:String = prefix + curStateFrame;
			//ExternalInterface.call( "ASTrace", frameName );
			gotoAndStop( frameName );
		}
		//
		public function get IsSetting():Boolean
		{
			return _IsSetting;
		}
		//=================================================================
		public function MouseRollOverAutoSetBtn( event:Event ):void
		{
			ExternalInterface.call( "ASShowTips_AutoSetSkillBtn", AutoSetBtn );
		}
		//
		public function MouseRollOutAutoSetBtn( event:Event ):void
		{
			ExternalInterface.call( "ASHideTips_AutoSetSkillBtn" );
		}
		//=================================================================
		//铸魂
		public function MakeEquipRune( e:Event )
		{
			ExternalInterface.call("ASMakeEquipRune", _SettingBtnType );
		}
		//
		public function MouseRollOverFuncBtn( event:Event ):void
		{
			ExternalInterface.call( "ASShowTips_MakeEquipRuneBtn", FuncBtn );
		}
		//
		public function MouseRollOutFuncBtn( event:Event ):void
		{
			ExternalInterface.call( "ASHideTips_MakeEquipRuneBtn" );
		}
		//=================================================================
		public function MouseRollOverLockMc( event:Event ):void
		{
			ExternalInterface.call( "ASShowTips_SkillSettingBtnLock", LockMc, _SettingBtnType );
		}
		//
		public function MouseRollOutLockMc( event:Event ):void
		{
			ExternalInterface.call( "ASHideTips_SkillSettingBtnLock" );
		}
		//
		public function ModiyContentPosY( offsetY:int)
		{
			KegTypeMc.y = KegTypeMcPosY + offsetY;
			//SettingBtn.y = SettingBtnPosY + offsetY;
			//SkillSlot.y = SkillSlotPosY + offsetY;
			SkillNameTf.y = SkillNameTfPosY + offsetY;
			SkillLvTf.y = SkillLvTfPosY + offsetY;
			SkillLvTitleTf.y = SkillLvTitleTfPosY + offsetY;
			
			AutoSetBtn.y = AutoSetBtnPosY + offsetY;
			//SkillRuneMc.y = SkillRuneMcPosY + offsetY;
			SkillRuneNameTf.y = SkillRuneNameTfPosY + offsetY;
			SkillRuneLvTf.y = SkillRuneLvTfPosY + offsetY;
			SkillRuneLvTitleTf.y = SkillRuneLvTitleTfPosY + offsetY;
			
			NewFlag.y = NewFlagPosY + offsetY;
			FuncBtn.y = FuncBtnPosY + offsetY;
		}
	}
}