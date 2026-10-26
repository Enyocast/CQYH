package  ActionScript3.SkillBar.SkillSettingPanel
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	public class SkillSettingShortcutPanel extends UIComponent
	{
		private const KEY_NAME_MOUSE_LEFT:String = "左";
		private const KEY_NAME_MOUSE_RIGHT:String = "右";
		//for panel position;
		private const TYPE_INDEX_NORMAL:Array = [2,3,4,5,0,1];
		private const TYPE_INDEX_SPECIAL:Array = [1,2,3,4,5,0];
		private const PANEL_INIT_OFFSET_X:Number = -104;
		private const PANEL_INIT_OFFSET_Y:Number = -380;
		private const OFFSET_X:Number = 50;
		private const OFFSET_Y:Number = -1.5;
		//技能类型
		public var SkillType:int;
		public var SkillListTypeMc:MovieClip;
		//技能列表
		public var SkillScrollListMc:ScrollingList;
		public var SkillListCloseBtn:Button;
		
		private var _startPosX:Number = -46;
		private var _startPosY:Number = -473;
		
		private var _curTypeIndex:Array;
		
		override protected function configUI():void
		{
			super.configUI();
			SkillScrollListMc.addEventListener(ListEvent.ITEM_CLICK, onClickSkill);
			SkillListCloseBtn.addEventListener(MouseEvent.CLICK, onClickToClose);
			UpdateSkillScrollList( null );
			visible = false;
			//UCSetCtrlType(0);
		}
		
		public function setButtonsPos(posX:Number, posY:Number):void
		{
			_startPosX = posX + PANEL_INIT_OFFSET_X;
			_startPosY = posY + PANEL_INIT_OFFSET_Y;
		}
		
		public function UCSetCtrlType( type:int)
		{
			if(type==0){
				_curTypeIndex = TYPE_INDEX_NORMAL;
			}else{
				_curTypeIndex = TYPE_INDEX_SPECIAL;
			}
		}
		
		//test code
		public function TestBeingSettingSkill(buttonClickIndex:int)
		{
			var itemsData:Array = new Array();
			for (var i:int = 1; i <= 10; i++)
			{
				var skillItemData:SkillSettingShortcutListItemData = new SkillSettingShortcutListItemData() ;
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
			UCSetSkillShortcutPanelData( buttonClickIndex, "Q",itemsData );
			UCSetSkillShortcutPanelVisible(true);
		}
		
		//interface
		public function UCSetSkillShortcutPanelVisible(bVisible:Boolean):void
		{
			visible = bVisible;
		}
		
		//interface
		public function UCSetSkillShortcutPanelData(skillListType:int, titleString:String, skillData:Array):void
		{
			SetSkillType(skillListType, titleString);
			UpdateSkillScrollList(skillData);
		}
		
		//
		private function SetSkillType( type:int, titleString:String )
		{
			SkillType = type;
			if(titleString == KEY_NAME_MOUSE_LEFT){
				SkillListTypeMc.gotoAndStop( "Slot0" );
			}else if(titleString == KEY_NAME_MOUSE_RIGHT){
				SkillListTypeMc.gotoAndStop( "Slot1" );
			}else if(titleString != null){
				SkillListTypeMc.gotoAndStop( "Slot2" );
				var tf:TextField = SkillListTypeMc.getChildByName('txt_key_string') as TextField;
				if(tf != null){
					tf.text = titleString;
				}
			}
			//SkillListTypeMc.gotoAndStop( "Slot"+ SkillType );
			updatePosition();
		}
		
		private function updatePosition():void
		{
			//TODO: get button index to sync position.
			this.x = _startPosX + _curTypeIndex.indexOf(SkillType) * OFFSET_X;
			this.y = _startPosY + _curTypeIndex.indexOf(SkillType) * OFFSET_Y;
		}
		//
		private function UpdateSkillScrollList( data:Array ):void
		{
			SkillScrollListMc.selectedIndex = -1;
			SkillScrollListMc.dataProvider = new DataProvider(data);
			SkillScrollListMc.validateNow();
			SkillScrollListMc.invalidateData();
		}
		//
		private function onClickSkill(e:ListEvent)
		{
			var targetList:ScrollingList = e.target as ScrollingList;
			if( targetList == null ){
				ExternalInterface.call( "ASTrace", "onClickSkill ScrollingList not found" );
				return;
			}
			
			var listDataProvider:DataProvider = targetList.dataProvider as DataProvider;
			if( listDataProvider == null ){
				ExternalInterface.call( "ASTrace", "onClickSkill DataProvider not found" );
				return;
			}
			
			//listDataProvider.handleListItemClick( e );
			
			var itemData:SkillSettingShortcutListItemData = listDataProvider.requestItemAt(e.index) as SkillSettingShortcutListItemData;
			ExternalInterface.call( "ASSetSkill", SkillType, itemData.SkillID );
			
			//test
			//visible = false;
		}
		
		//
		private function onClickToClose( evt:Event )
		{
			ExternalInterface.call( "ASCloseSkillList" );
		}
	}
}