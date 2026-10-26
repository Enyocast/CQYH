package UI_WorldMap.WorldMapAS3
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MapMarkIcon;
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollBar;
	import ActionScript3.TreeListData;
	import ActionScript3.Common.CustomSlider;
	
	import UI_WorldMap.WorldMapAS3.MapAddUserMarkPanel;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.IndexEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.events.SliderEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.text.TextField;
	import flash.display.DisplayObject;
	import flash.text.TextFormat;
	import scaleform.clik.controls.ListItemRenderer;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import UI_ChatWidget.AS3.ChatTextField;
	import UI_Minimap.MinimapAS3.MapConst;
	
	public class WorldMapPanel extends MyPanel
	{
		public var btnMoveLeft_mc:Button;
		public var btnMoveRight_mc:Button;
		public var btnMoveUp_mc:Button;
		public var btnMoveDown_mc:Button;
		
		public var btn_back:Button;
		
		public var mapZone_mc:MovieClip;
		public var mapMaskZone_mc:MovieClip;
		public var MapNpcView_mc:MovieClip;
		public var MapTopView_mc:MovieClip;
		public var MapPathView_mc:MovieClip;
		public var MapInfoViewMc:MovieClip;
		public var bigMap:BigMap;
		
		public var UserMarkPanelMc:MapAddUserMarkPanel;
		
		public var ToggleTaskBtn:CheckBox;
		public var ToggleStaticMarkBtn:CheckBox;
		
		public var mapMarksFilter_tf:ChatTextField;
		public var MapMarksList_mc:ScrollingList;
		//public var MapList_mc:DropdownMenu;
		//public var MapTaskList_mc:DropdownMenu;
		public var sliderStep:CustomSlider;
		
		public var dragStartX:Number = 0;
		public var dragStartY:Number = 0;
		public var _MouserDownX:Number = 0;
		public var _MouserDownY:Number = 0;
		public var _OffsetX:Number = 0;
		public var _OffsetY:Number = 0;
		public var _CanMapDrag:Boolean = false;
		public var _IsMapDragging:Boolean = false;
		private var currentValue:int=1;
		public var tab1:RadioButton;
		public var tab2:RadioButton;
		public var bool:Boolean=false;
		public var txt_y:TextInput;
		public var txt_x:TextInput;
		public var lb_x:MovieClip;
		public var lb_y:MovieClip;
		public var btn_goto:Button;
		override protected  function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			txt_x.textField.restrict="\\-0-9";
			txt_y.textField.restrict="\\-0-9";
			mapMarksFilter_tf.maxChars=10;
			mapMarksFilter_tf.addEventListener( "inputcopy",inputcopy);
			mapMarksFilter_tf.addEventListener( Event.CHANGE, onMarksFilterChange );
			btn_goto.addEventListener(MouseEvent.CLICK,gotoHandler);
			currentValue=sliderStep.value;
			_OffsetX = mapMaskZone_mc.x;
			_OffsetY = mapMaskZone_mc.y;
			btn_back.visible=false;
			this.removeEventListener( Event.ENTER_FRAME, Update,false);
			this.addEventListener( Event.ENTER_FRAME, Update);
			
			//地图标记弹出框
			UserMarkPanelMc.init();
			//
			ToggleTaskBtn.addEventListener( MouseEvent.CLICK, ToggleTaskNpc );
			ToggleStaticMarkBtn.addEventListener( MouseEvent.CLICK, ToggleFuncNpc );

			//地图
			mapZone_mc.addEventListener( MouseEvent.MOUSE_DOWN, MouseDownInMap );
			mapZone_mc.addEventListener( MouseEvent.MOUSE_UP, MapDragComplete );
			mapZone_mc.addEventListener( MouseEvent.CLICK, MouseClickInMap );
			mapZone_mc.addEventListener( MouseEvent.ROLL_OUT, MapDragCompleteOutside );
			mapZone_mc.addEventListener( MouseEvent.MOUSE_WHEEL, MapZoomByWheel );
			btn_back.addEventListener(MouseEvent.CLICK,backHandler);
			
			MapNpcView_mc = mapZone_mc.MapNpcView_mc;
			MapNpcView_mc.mouseEnabled=false;
			MapTopView_mc= mapZone_mc.MapTopView_mc;
			MapTopView_mc.mouseEnabled=false;
			MapPathView_mc = mapZone_mc.MapPathView_mc;
			if( MapPathView_mc != null ){
				MapPathView_mc.mouseChildren = true;
				MapPathView_mc.mouseEnabled = false;
			}
			
			MapInfoViewMc = mapZone_mc.MapExtraInfo_mc
			if( MapInfoViewMc != null ){
				MapInfoViewMc.mouseChildren = true;
				MapInfoViewMc.mouseEnabled = false;
			}
			sliderStep.addEventListener(SliderEvent.VALUE_CHANGE,changeHandler);
			sliderStep.addEventListener(MouseEvent.MOUSE_UP,MapDragCompleteOutside);
			MapMarksList_mc.addEventListener(ListEvent.ITEM_CLICK, onClickFindMapMark);
			MapMarksList_mc.addEventListener(ListEvent.INDEX_CHANGE,onCategoryListChange);
			MapMarksList_mc.addEventListener(ListEvent.ITEM_DOUBLE_CLICK, onDClickToMoveToMapMark);
			//MapMarksList_mc.addEventListener(ListEvent.ITEM_ROLL_OVER, onRollOverMapMarkInList);
			//MapMarksList_mc.addEventListener(ListEvent.ITEM_ROLL_OUT, onRollOutMapMarkInList);
			UCChangeWorldMapTabBtn(0);
			UCChangeWorldMapContent(0);
			UCUpdateWorldMapPointsList([]);
			//ExternalInterface.call( "RegisterWorldMap", this );

			/*
			//地图移动
			btnMoveLeft_mc.autoRepeat = true;
			btnMoveLeft_mc.addEventListener( MouseEvent.CLICK, function _MoveMapBtnClick( e:Event ){ MoveMapBtn( e, -4, 0 ); } );
			
			btnMoveRight_mc.autoRepeat = true;
			btnMoveRight_mc.addEventListener( MouseEvent.CLICK, function _MoveMapBtnClick( e:Event ){ MoveMapBtn( e, 4, 0 ); } );
			
			btnMoveUp_mc.autoRepeat = true;
			btnMoveUp_mc.addEventListener( MouseEvent.CLICK, function _MoveMapBtnClick( e:Event ){ MoveMapBtn( e, 0, -4 ); } );
			
			btnMoveDown_mc.autoRepeat = true;
			btnMoveDown_mc.addEventListener( MouseEvent.CLICK, function _MoveMapBtnClick( e:Event ){ MoveMapBtn( e, 0, 4 ); } );
			*/
			//UCUpdateNewMapMarkIcon( 16, 0, 30, 30, 45 );
			//所有地图列表
			//MapList_mc.addEventListener(ListEvent.INDEX_CHANGE, onClickChangeMap);
			//ChangeMap_btn.addEventListener( MouseEvent.CLICK, onClickChangeMap );
			//testData();
		}

		private function backHandler(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASShowWorldMapTabPanel",1);
		}
		
		public function UCUpdateUnitedMapTiles(dat:Array):void
		{
			if(dat!=null){
				bigMap.updateTilesData(dat);
			}
		}
		//获取地图节点数据
		public function UCGetMapNode():Array
		{
			if( bigMap == null ){
				return [];
			}
			return bigMap.UCGetMapNode();
		}
		
		private function gotoHandler(evt:MouseEvent):void
		{
			var inputPosX:int;
			var inputPosY:int;
			if(txt_x.text.length>0){
				inputPosX=parseInt(txt_x.text);
			}
			if(txt_y.text.length>0){
				inputPosY=parseInt(txt_y.text);
			}
			ExternalInterface.call( "ASInputCoodinateAndMoveTo", inputPosX, inputPosY);
		}
		
		//=====================================================================================================================
		public function Update( e:Event )
		{
			if(_CanMapDrag){
				var offX = root.mouseX - dragStartX;
				var offY = root.mouseY - dragStartY;
				dragStartX = root.mouseX;
				dragStartY = root.mouseY;
				
				if( ( -0.01 < offX && offX < 0.01 ) && ( -0.01 < offY && offY < 0.01 ) ){
					return;
				}
				_IsMapDragging = true;
				
				ExternalInterface.call( "ASMapDrag", offX, offY );
			}
		}
		//------------------------------------------------------------------------------------------------------------------------
		//
		function MouseDownInMap( e:Event )
		{
			var mouseEvent:MouseEventEx = e as MouseEventEx;
			
			
			if( mouseEvent.buttonIdx == MouseEventEx.LEFT_BUTTON )
			{
				//屏蔽拖动
				//begin to drag
				_CanMapDrag = true;
				
				dragStartX = root.mouseX;
				dragStartY = root.mouseY;
				_MouserDownX = dragStartX;
				_MouserDownY = dragStartY;
			}
			else if( mouseEvent.buttonIdx == MouseEventEx.RIGHT_BUTTON )
			{
				_CanMapDrag = false;
				
				var rightDownPosX:int = root.mouseX - ( x +  mapMaskZone_mc.x + mapMaskZone_mc.width / 2 );
				var rightDownPosY:int = root.mouseY - ( y +  mapMaskZone_mc.y + mapMaskZone_mc.height / 2 );
				ExternalInterface.call( "ASAddOrRemoveMarkMap", rightDownPosX, rightDownPosY );
				
			}
		}
		//
		function MouseClickInMap( e:Event )
		{
			var mouseEvent:MouseEventEx = e as MouseEventEx;
			
			if( mouseEvent.buttonIdx == MouseEventEx.LEFT_BUTTON )
			{
				if( _MouserDownX != root.mouseX || _MouserDownY != root.mouseY )
				{
					return;
				}
				var clickPosX:int = root.mouseX - ( x +  mapMaskZone_mc.x + mapMaskZone_mc.width / 2 );
				var clickPosY:int = root.mouseY - ( y +  mapMaskZone_mc.y + mapMaskZone_mc.height / 2 );
				ExternalInterface.call( "ASMoveToMapPos", clickPosX, clickPosY );
			}
		}
		//
		function MapDragComplete( e:Event )
		{
			_CanMapDrag = false;
			_IsMapDragging = false;
		}
		//
		function MapDragCompleteOutside( e:Event )
		{
			MapDragComplete( e );
		}
		//==============================================================================================================
		public function UCAddMapMark( newMarkObj:MovieClip ):void
		{
			newMarkObj.addEventListener( MouseEvent.ROLL_OVER, ShowMapMarkHint );
			newMarkObj.addEventListener( MouseEvent.ROLL_OUT, HideMapMarkHint );
		}
		//
		public function UCInitMapMark( newMarkObj:MovieClip, id:int, type:int, frameName:String ):void
		{
			var markObj:MapMarkIcon = newMarkObj as MapMarkIcon;
			if( markObj == null ){
				return;
			}
			if(type==MapConst.NearBoss || type==MapConst.GlobalTeammate || type==MapConst.NpcGroup)
			{ 
			    UCChangeMapMarkLayer(markObj);
/*				if(newMarkObj.parent && newMarkObj.parent.name!=this.MapTopView_mc.name)
				{
					 newMarkObj.parent.removeChild(newMarkObj);
					 this.MapTopView_mc.addChild(newMarkObj);
				}*/
			}
			else if(type==MapConst.NearMonster)
			{
				markObj.parent.setChildIndex(markObj,0);
			}
			markObj.InitType( id, type, frameName );
		}
		
		private function UCChangeMapMarkLayer( markObj:MapMarkIcon):void
		{//交换层级
			var markParentMc:MovieClip = markObj.parent as MovieClip;
			var curNum:int = markParentMc.numChildren;
            markParentMc.setChildIndex( markObj, curNum-1 );
		}
		//==============================================================================================================
		public function UCInitNewMapMarkIcon( markType:int, markIdx:int, isToShow:Boolean, markName:String ):void
		{
			var inMc:MovieClip = GetMapMarkUIObjectContainer( markType );
			if( inMc == null ){
				return;
			}
			var mcName:String = "NewMapMarkIcon"+"_"+markIdx;
			var newMarkMc:DisplayObject = MapInfoViewMc.getChildByName( mcName ) as DisplayObject;
			if( newMarkMc == null ){
				if( markType == MapConst.ExtaInfo ){
					var mc:MovieClip = new (getDefinitionByName("NewMarkMc") as Class)();
					mc.mouseChildren=false;
					mc.mouseEnabled=false;
                    mc.newMarkTextField.htmlText = markName;
					newMarkMc=mc as DisplayObject;
					newMarkMc.name = mcName;
					MapInfoViewMc.addChild( newMarkMc );
				}
			}
			else{
				if( markType == MapConst.ExtaInfo ){
					var exitMc:MovieClip = newMarkMc as MovieClip;
					if( exitMc != null){
						exitMc.newMarkTextField.htmlText = markName;
					}
				}
				newMarkMc.visible = isToShow;
			}
		}
		
		public function UCUpdateNewMapMarkIcon( markType:int, markIdx:int, iconPosX:int, iconPosY:int, rotationAngle:Number ):void
		{
			var inMc:MovieClip = GetMapMarkUIObjectContainer( markType );
			if( inMc == null ){
				return;
			}
			
			var mcName:String = "NewMapMarkIcon"+"_"+markIdx;
			var markMc:DisplayObject = inMc.getChildByName( mcName ) as DisplayObject;
			if( markMc != null ){
				markMc.x = iconPosX;
				markMc.y = iconPosY;
				markMc.rotation = rotationAngle;
			}
			else{
				UCInitNewMapMarkIcon( markType, markIdx, false, "自动创建" );
				ExternalInterface.call( "ASShowWorldMapMarkHint", "UCUpdateNewMapMarkIcon movieClip"+iconPosY+" not Found" );
			}
		}
		//==============================================================================================================
		function ShowMapMarkHint( e:Event )
		{
			var markMc:MapMarkIcon = e.target as MapMarkIcon;
			ExternalInterface.call( "ASShowWorldMapMarkHint", markMc.Type, markMc.ID );
		}
		//
		function HideMapMarkHint( e:Event )
		{
			ExternalInterface.call( "ASHideWorldMapMarkHint");
		}
		
		protected function changeHandler(e:SliderEvent):void
		{
			if(bool==true){
				bool=false;
				return;
			}
			var v:Number=e.value;
			v=sliderStep.maximum-v;
			currentValue=e.value;
			ExternalInterface.call( "ASWorldMapZoomTo",v );
		}
		//=====================================================================================================================
		function MapZoomClick( e:Event, isZoomIn:Boolean )
		{
			var mouseEvent:MouseEventEx = e as MouseEventEx;
			
			if( mouseEvent.buttonIdx == MouseEventEx.LEFT_BUTTON )
			{
				ExternalInterface.call( "ASWorldMapZoom", isZoomIn );
			}
		}
		//=====================================================================================================================
		function MapZoomByWheel( e:Event )
		{
			var mouseEvent:MouseEventEx = e as MouseEventEx;
			if( mouseEvent == null){
				return;
			}
			
			ExternalInterface.call( "ASWorldMapZoom", mouseEvent.delta > 0 );
		}
		//=====================================================================================================================
		public function onMarksFilterChange( e:Event ):void
		{
			var searchStr:String = e.target.text;
			filterData(searchStr);
		}
		
		private function inputcopy(evt:Event):void
		{
			var searchStr:String=mapMarksFilter_tf.textField.text;
			filterData(searchStr);
		}
		
		private function filterData(dat:String):void
		{
			MapMarksList_mc.scrollPosition=0;
			var marksData:Array;
			marksData = (MapMarksList_mc.dataProvider as TreeDataProvider).getRoot();
			
			var dl:uint = marksData.length;
			var markInfo:TreeListData;
            for (var i:uint = 0; i < dl; i++) {
				markInfo = marksData[i] as TreeListData;
				markInfo.visible = ( markInfo.label.indexOf( dat ) >= 0 );
            }
			
			MapMarksList_mc.invalidateData();
			MapMarksList_mc.validateNow();
		}
		function onCategoryListChange( event:ListEvent ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}
		//==========================================================================
		public function onClickFindMapMark(e:ListEvent)
		{
			var targetList:ScrollingList = e.target as ScrollingList;
			if (targetList != null)
			{
				var Provider:TreeDataProvider= targetList.dataProvider as TreeDataProvider;

				if( Provider != null )
				{
					Provider.handleListItemClick( e );
					//trace( "Provider.requestItemAt(e.index) as TeleportNodesData : " ,Provider.requestItemAt(e.index) as TeleportNodesData )
					var itemData:TreeListData = Provider.requestItemAt(e.index) as TreeListData;
					
					if( itemData.type == 0 )
					{
						var mapMarkData:MapStaticMarkData = itemData as MapStaticMarkData;
						//ExternalInterface.call( "ASFindThisMapMark", mapMarkData.Index );
						ExternalInterface.call( "ASMoveToThisMapMark", mapMarkData.Index );
						targetList.invalidateData();
					}
					else
					{
						targetList.invalidateData();
					}
					
				}
			}
		}
		//
		public function onDClickToMoveToMapMark(e:ListEvent)
		{
			var targetList:ScrollingList = e.target as ScrollingList;
			if (targetList != null)
			{
				var Provider:TreeDataProvider= targetList.dataProvider as TreeDataProvider;

				if( Provider != null )
				{
					Provider.handleListItemClick( e );
					//trace( "Provider.requestItemAt(e.index) as TeleportNodesData : " ,Provider.requestItemAt(e.index) as TeleportNodesData )
					var itemData:TreeListData = Provider.requestItemAt(e.index) as TreeListData;
					
					if( itemData.type == 0 )
					{
						var mapMarkData:MapStaticMarkData = itemData as MapStaticMarkData;
						
						ExternalInterface.call( "ASMoveToThisMapMark", mapMarkData.Index );
					}
					else
					{
						targetList.invalidateData();
					}
				}
			}
		}
		//==============================================================================================================
		public function onRollOverMapMarkInList(e:ListEvent)
		{
			if( e == null ){
				return;
			}
			var listItem:MapMarkListItem = e.itemRenderer as MapMarkListItem;
			//trace("===================onRollOverMapMarkInList", listItem.ListItemClass_mc.detailItemData);
			if( listItem != null && listItem.isDetailItem ){
				var listDetailItem:MapMarkListDetailItem = listItem.ListItemDetail_mc as MapMarkListDetailItem;
				var itemData:MapStaticMarkData = listDetailItem.detailItemData as MapStaticMarkData;
				ExternalInterface.call("ASShowTipsWorldMapMarkListItem", listItem, itemData.Index, itemData.label );
			}
			
		}
		//-------------------------------------------------------------------------------------------------------------
		public function onRollOutMapMarkInList(e:ListEvent)
		{
			if( e == null ){
				return;
			}
			
			var listItem:MapMarkListItem = e.itemRenderer as MapMarkListItem;
			ExternalInterface.call("ASHideTipsWorldMapMarkListItem", listItem);
		}
		//==============================================================================================================
		public function UCUpdateWorldMapPointsList( data:Array ):void
		{
			MapMarksList_mc.dataProvider = new TreeDataProvider(data);
			MapMarksList_mc.validateNow();
			MapMarksList_mc.invalidateData();
		}
		
		/**
		 * 初始化设置滑调的最大值，最小值 
		 * @param maxValue
		 * @param curvalue
		 * 
		 */		
		public function UCUpdateSliderValue(maxValue:int,curvalue:int):void
		{
			bool=true;
			sliderStep.maximum=maxValue;
			sliderStep.value=maxValue-curvalue;
			currentValue=maxValue-curvalue;
		}
		
		//=====================================================================================================================
/*		function onClickChangeMap( e:Event )
		{
			var itemData:MapDropDownListData = MapList_mc.dataProvider.requestItemAt(  MapList_mc.selectedIndex ) as MapDropDownListData;
			
			if( itemData != null )
			{
				ExternalInterface.call( "ASChangeMap",  itemData.inputedID1,  itemData.inputedID2 );
			}
		}*/
		//
		public function UCUpdateWorldMapMapList( data:Array, selIdx:int ):void
		{
/*			MapList_mc.dataProvider = new DataProvider(data);
            MapList_mc.invalidateData();
            MapList_mc.selectedIndex = selIdx;
            MapList_mc.validateNow();*/
		}
		
		//是否显示返回按钮
		public function UCShowBack(dat:Boolean):void
		{
			btn_back.visible=dat;
		}
		
		//选中地图不改变标签页选项卡
		public function UCChangeWorldMapTabBtn(enumIdx:int):void
		{
			switch( enumIdx )
			{
				case 0:
				tab1.selected=true;
				tab1.removeEventListener(MouseEvent.CLICK,onClickToCurrentMap);
				tab2.addEventListener(MouseEvent.CLICK,onClickToUnitedMap);
				break;
				
				case 1:
				tab2.selected=true;
				tab1.addEventListener(MouseEvent.CLICK,onClickToCurrentMap);
				tab2.removeEventListener(MouseEvent.CLICK,onClickToUnitedMap);
				break;
			}
		}
		
		public function UCChangeWorldMapContent( enumIdx:int ):void
		{
			ChangeWorldMapContent( enumIdx );
		}
		
		private function ChangeWorldMapContent( enumIdx:int ):void
		{
			switch( enumIdx )
			{
				case 0:
				this.bigMap.visible=false;
				showWorldMap(true);
				break;
				
				case 1:
				this.bigMap.visible=true;
				showWorldMap(false);
				break;
			}
		}
		
		private function onClickToCurrentMap(e:MouseEvent):void
		{
			ChangeWorldMapContent(0);
			UCChangeWorldMapTabBtn(0);
			ExternalInterface.call( "ASShowWorldMapTabPanel", 0 );
		}
		
		private function onClickToUnitedMap(e:MouseEvent):void
		{
			ChangeWorldMapContent(1);
			UCChangeWorldMapTabBtn(1);
			ExternalInterface.call( "ASShowWorldMapTabPanel", 1 );
		}
		
		private function showWorldMap(bl:Boolean):void
		{
			lb_x.visible=bl;
			lb_y.visible=bl;
			txt_x.visible=bl;
			txt_y.visible=bl;
			btn_goto.visible=bl;
			mapMarksFilter_tf.visible=bl;
			MapMarksList_mc.visible=bl;
		}

		//=====================================================================================================================
		function onClickFindMapTask( e:ListEvent )
		{
			if( e == null ){
				ExternalInterface.call( "ASTrace", "onClickFindMapTask listEvent is NULL" );
				return;
			}
			var itemData:MapDropDownListData = e.itemData as MapDropDownListData;
			if( itemData != null )
			{
				ExternalInterface.call( "ASFindMapTask",  itemData.inputedID1 );
			}
		}
		//
		public function UCUpdateWorldMapTaskList( data:Array ):void
		{
/*			MapTaskList_mc.dataProvider = new DataProvider(data);
            MapTaskList_mc.invalidateData();
            MapTaskList_mc.selectedIndex = -1;
            MapTaskList_mc.validateNow();*/
			
		}
		//=====================================================================================================================
		public function ToggleTaskNpc( e:Event )
		{
			var isChecked:Boolean = ToggleTaskBtn.selected;
			ExternalInterface.call( "ASToggleTaskNpc",  ToggleTaskBtn.selected );
		}
		//
		public function ToggleFuncNpc( e:Event )
		{
			var isChecked:Boolean = ToggleStaticMarkBtn.selected;
			ExternalInterface.call( "ASToggleFuncNpc",  ToggleStaticMarkBtn.selected );
		}
		//
		public function MoveMapBtn( e:Event, offX:Number, offY:Number )
		{
			ExternalInterface.call( "ASMapDrag", offX, offY );
		}
		//=====================================================================================================================
		public function UCResetMapContent()
		{
			UserMarkPanelMc.visible = false;
			UserMarkPanelMc.close();
			//MapList_mc.close();
			//MapTaskList_mc.close();
		}
		//=====================================================================================================================
		public function UCUpdateWorldMapShareUserMarkkList( data:Array ):void
		{
			UserMarkPanelMc.UpdateWorldMapShareUserMarkkList( data );
		}
		
		public function UCSetUserMarkPanelIconName( dat:String ):void
		{
			UserMarkPanelMc.SetUserMarkPanelIconName( dat );
		}
		
		public function UCSetXY(offX:int,offY:int):void
		{
			txt_x.text=offX.toString();
			txt_y.text=offY.toString();
		}
		
		public function GetMapMarkUIObjectContainer(type:int):MovieClip
		{
			switch(type)
			{
				case MapConst.PathPoint:
				{
					return this.MapPathView_mc;
				}
/*				case MapConst.GlobalTeammate:
				{
					return this.MapTopView_mc;
				}
				case MapConst.NearBoss:
				{
					return this.MapTopView_mc;
				}*/
				case MapConst.ExtaInfo:
				{
					return this.MapInfoViewMc;
				}
				default:
				{
					return this.MapNpcView_mc;
				}
			}
		}
/*		private function testData():void
		{
			var testMapMark:MovieClip = new (getDefinitionByName("MapMarkIconAOG") as Class);
			MapInfoViewMc.addChild( testMapMark );
			testMapMark.x = 30;
			testMapMark.y = 30;
			testMapMark.gotoAndStop( "ally" );
			UCAddMapMark( testMapMark );
			UCInitMapMark(testMapMark,0,1,"ally");
			
			//UCInitNewMapMarkIcon( 15, 0, true, "比奇省" );
			//UCUpdateNewMapMarkIcon( 15, 0, 30, 30, 45 );
						
//            var mapDatas:Array = new Array();
//			for (var i:int = 1; i < 30; i++)
//			{
//				var mapData:MapDropDownListData = new MapDropDownListData ;
//				mapData.inputedID1 = i+1000;
//				mapData.listIndex = i;
//				mapData.label = "地图" + i;
//				mapDatas.push(mapData);
//			}
//			UCUpdateWorldMapMapList(mapDatas, 3);
//			var taskDatas:Array = new Array();
//			for (var j:int = 1; j < 30; j++)
//			{
//			var taskData:MapDropDownListData = new MapDropDownListData ;
//			taskData.inputedID1 = j+1000;
//			taskData.listIndex = j;
//			taskData.label = "任务" + j;
//			taskDatas.push(taskData);
//			}
//			UCUpdateWorldMapTaskList(taskDatas);
		}*/
		
		/*private function testDrop():void
		{
			var itemsData:Array = new Array();
			var idx:int = 0;
			
			var npcMarkTitle:TreeListData = new TreeListData ;
			npcMarkTitle.index = idx;
			npcMarkTitle.type = 2;
			npcMarkTitle.deepth = 0;
			npcMarkTitle.visible = true;
			npcMarkTitle.label = "NPC";
			
			itemsData.push(npcMarkTitle);
			for (; idx <= 20; idx++)
			{
				var npcMarkData:MapStaticMarkData = new MapStaticMarkData ;
				npcMarkData.index = idx;
				npcMarkData.type = 0;
				npcMarkData.deepth = 1;
				npcMarkData.visible = true;
				npcMarkData.label = "NPC功能" + idx;
				npcMarkData.ExtName = "NPC名字";
				npcMarkData.Index = idx + 2000;
				
				itemsData.push(npcMarkData);
			}
			
			var fbMarkTitle:TreeListData = new TreeListData ;
			fbMarkTitle.index = idx;
			fbMarkTitle.type = 2;
			fbMarkTitle.deepth = 0;
			fbMarkTitle.visible = true;
			fbMarkTitle.label = "副本";
			
			itemsData.push(fbMarkTitle);
			for ( ; idx <= 30; idx++)
			{
				var fbnMarkData:MapStaticMarkData = new MapStaticMarkData ;
				fbnMarkData.index = idx;
				fbnMarkData.type = 0;
				fbnMarkData.deepth = 1;
				fbnMarkData.visible = true;
				fbnMarkData.label = "副本名字" + idx;
				//fbnMarkData.IconType = "entrance";
				fbnMarkData.ExtName = "";
				fbnMarkData.Index = idx + 3000;
				
				itemsData.push(fbnMarkData);
			}
			
			UCUpdateWorldMapPointsList(itemsData);
		}*/
	}
}