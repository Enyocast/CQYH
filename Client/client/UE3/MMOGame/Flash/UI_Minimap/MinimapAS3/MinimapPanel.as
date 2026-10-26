package UI_Minimap.MinimapAS3{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	import flash.utils.Timer;
	import flash.utils.getDefinitionByName;
	import flash.utils.getTimer;
	
	import ActionScript3.GameDispathcher;
	import ActionScript3.MapMarkIcon;
	import ActionScript3.MyPanel;
	import ActionScript3.Common.TimerManager;
	import ActionScript3.Common.Events.ParamEvent;
	
	import UI_Minimap.MinimapAS3.LevelBar;
	import UI_Minimap.MinimapAS3.SceneLinesDropDownListData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.gfx.MouseEventEx;
	
	public class MinimapPanel extends MyPanel
	{
		public var SceneIconMc:MovieClip;
		public var SceneLinesList_mc:MapDropdownMenu;
		public var CurSelectedSceneLineIdx:int = 0;
		public var btnMinimapZoomIn:Button;
		public var btnMinimapZoomOut:Button;
		public var ZoneMap:Button;
		public var BattleEnterToggleBtn:Button;
		//public var ButtonHoverHintMc:HoverHintPanel;
		public var ButtonHoverHintMc:MovieClip;
		public var mapcoord_mc:TextField;
		public var ArenaEntToggleBtn:Button;
		
		var ButtonHoverContextTextFormat:String;
		var ReplaceTextChar:String = "TIME";
		
		public var ToggleShowMapBtn:Button;
		public var SwitchMapShowTypeBtn:Button;
		public var PlayerArraw_mc:MovieClip;
		public var mapblock_mc:MovieClip;
		
		public var FBAidBtn:Button;
//		public var ShoppingMallBtn:Button;
//		public var ActivityBrn:Button;
		public var DayTime_mc:MovieClip;
		//public var PathFind_mc:MovieClip;
		public var TraceRelationBar_mc:LevelBar;
		public var MiniMapTraceBtn:Button;
		
		public var MapPathView_mc:MovieClip;
		public var MapNpcView_mc:MovieClip;
		public var MapTopView_mc:MovieClip;
		public var MapClick_mc:MovieClip;
		public var MapBgMc:MovieClip;
		public var mapMaskZone_mc:MovieClip;
		public var btn_sign:MovieClip;
		
		private const MAXMAILS:int = 140;
		private const TOOMUCH:int = 100;
		
		
		public var CountTimer:Timer = new Timer(1000);
		public var CountBeginTime1:uint = 0;
		public var CountDownCurTime1:uint = 0;
		public var TotalTime1:uint = 30;
		private var _isCountDown:Boolean = false;
		
		public var CountDownTimer2:Timer = new Timer(1000);
		public var CountDownBeginTime2:uint = 0;
		public var CountDownCurTime2:uint = 0;
		public var TotalTime2:uint = 0;
		public var pktype:MapType;
		
		override protected function configUI():void
		{  
			ShowMode="MAP";
			super.configUI();
            pktype.gotoAndStop(1);

			if( ZoneMap )
			{
				ZoneMap.addEventListener( MouseEvent.CLICK,ClickZoneMap );
			}
			
			ToggleShowMapBtn.addEventListener( MouseEvent.CLICK, onClickToggleShowMapBtn );
			ToggleShowMapBtn.addEventListener( MouseEvent.ROLL_OVER, onHoverToggleShowMapBtn );
			ToggleShowMapBtn.addEventListener( MouseEvent.ROLL_OUT, onOutHoverToggleShowMapBtn );
			SwitchMapShowTypeBtn.addEventListener( MouseEvent.CLICK, onClickSwitchMapShowTypeBtn );
			SwitchMapShowTypeBtn.visible = false;
			//
			SceneIconMc.addEventListener(MouseEvent.ROLL_OVER, onShowHintMapType);
			SceneIconMc.addEventListener(MouseEvent.ROLL_OUT, onHideHintMapType);
			
			mapcoord_mc.mouseEnabled=false;
			PlayerArraw_mc.mouseEnabled=false;
			//PlayerArraw_mc.mouseChildren=false;
			//MapPathView_mc.mouseChildren = false;
			MapPathView_mc.mouseEnabled = false;
			MapNpcView_mc.mouseEnabled=false;
			MapTopView_mc.mouseEnabled=false;
			MapClick_mc.addEventListener(MouseEvent.CLICK,MouseClickInMap);

			//SceneLinesList_mc.addEventListener(ListEvent.ITEM_CLICK, onClickChangeSceneLine);

			ButtonHoverHintMc.x = BattleEnterToggleBtn.x;
			ButtonHoverHintMc.y = BattleEnterToggleBtn.y + BattleEnterToggleBtn.height;
			ButtonHoverHintMc.visible = false;

			//battle btn
			BattleEnterToggleBtn.visible = false;
			BattleEnterToggleBtn.addEventListener(MouseEvent.CLICK, onClickBattleInfo);
			BattleEnterToggleBtn.addEventListener(MouseEvent.ROLL_OVER, onHintBattleInfo);
			BattleEnterToggleBtn.addEventListener(MouseEvent.ROLL_OUT, onHideHintBattleInfo);
			
			//Arena btn
			if( ArenaEntToggleBtn != null ){
				ArenaEntToggleBtn.visible = false;
				ArenaEntToggleBtn.addEventListener(MouseEvent.CLICK, onClickArenaEntToggleBtn);
			}
			//FB aid button
			FBAidBtn.visible = false;
			FBAidBtn.addEventListener(MouseEvent.CLICK, onClickFBAidBtn);

			DayTime_mc.gotoAndStop(0);
			var type_mc:MovieClip = DayTime_mc.getChildByName("WeatherType_mc") as MovieClip;
			if (type_mc)
			{
				type_mc.visible = false;
			}
			DayTime_mc.visible = false;
			
			(btn_sign.clipPin_mc as MovieClip).addEventListener( MouseEvent.ROLL_OVER, PinShowTips);
			(btn_sign.clipPin_mc as MovieClip).addEventListener( MouseEvent.ROLL_OUT, PinHideTips);
			
			//edit by wph@2015_02_05: implement function in journey trace panel
			MiniMapTraceBtn.visible = false;

			
			TraceRelationBar_mc.setExpand(false);
			TraceRelationBar_mc.visible = false;
			stageChangeHandler(null);
			var linesDatas:Array = new Array();
			for (var j:int = 1; j <2; j++)
			{
				var singleLineData:SceneLinesDropDownListData = new SceneLinesDropDownListData ;
				singleLineData.lineID = j*10;
				singleLineData.label = singleLineData.lineID + "线";
				singleLineData.lineState=j;
				linesDatas.push(singleLineData);
			}
			UCUpdateSceneLinesList(linesDatas, 0);
			//testData();
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=cavasWidth-476+228;
		}
		
		private function MouseClickInMap(evt:MouseEvent):void
		{
			var mouseEvent:MouseEventEx = evt as MouseEventEx;
			if( mouseEvent.buttonIdx == MouseEventEx.LEFT_BUTTON )
			{
				var clickPosX:int = root.mouseX - ( x +  mapMaskZone_mc.x + mapMaskZone_mc.width / 2 );
				var clickPosY:int = root.mouseY - ( y +  mapMaskZone_mc.y + mapMaskZone_mc.height / 2 );
				ExternalInterface.call( "ASMoveToMinimapPos", clickPosX, clickPosY );
			}
		}
		
		private function PinShowTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_PinValue", this);
		}
		
		private function PinHideTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_PinValue", this);
		}
		
		private function clickTraceBtn(e:MouseEvent):void
		{
			MiniMapTraceBtn.selected = !MiniMapTraceBtn.selected;
			if(MiniMapTraceBtn.selected)
			{
				//TraceRelationBar_mc.setExpand(true);
				ExternalInterface.call( "ASShowMiniMapTrace");
			}
			else
			{
				//TraceRelationBar_mc.setExpand(false);
				ExternalInterface.call( "ASHideMiniMapTrace");
			}
		}
		
		//=====================================================================================================================
		public function UCAddMapMark( newMarkObj:MovieClip ):void
		{
			newMarkObj.addEventListener( MouseEvent.ROLL_OVER, ShowMapMarkHint );
			newMarkObj.addEventListener( MouseEvent.ROLL_OUT, HideMapMarkHint );
			newMarkObj.addEventListener(MouseEvent.CLICK,clickMapMarkHint);
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
			markObj.InitType( id, type, frameName, 14);
		}
		
        private function UCChangeMapMarkLayer( markObj:MapMarkIcon):void
		{//层级交换 
			var markParentMc:MovieClip = markObj.parent as MovieClip;
			var curNum:int = markParentMc.numChildren;
            markParentMc.setChildIndex( markObj, curNum-1 );
		}
		//=====================================================================================================================
		function ShowMapMarkHint( e:Event ):void
		{
			var markMc:MapMarkIcon = e.target as MapMarkIcon;
			ExternalInterface.call( "ASShowMinimapMarkHint", markMc.Type, markMc.ID );
		}
		
		private function clickMapMarkHint(evt:MouseEvent):void
		{
			var mouseEvent:MouseEventEx = evt as MouseEventEx;
			if( mouseEvent.buttonIdx == MouseEventEx.LEFT_BUTTON )
			{
				var clickPosX:int = root.mouseX - ( x +  mapMaskZone_mc.x + mapMaskZone_mc.width / 2 );
				var clickPosY:int = root.mouseY - ( y +  mapMaskZone_mc.y + mapMaskZone_mc.height / 2 );
				ExternalInterface.call( "ASMoveToMinimapPos", clickPosX, clickPosY );
			}
		}
		//
		function HideMapMarkHint( e:Event ):void
		{
			ExternalInterface.call( "ASHideMinimapMarkHint" );
		}
		//=====================================================================================================================
		function onShowHintMapType( e:Event ):void
		{
			ExternalInterface.call( "ASShowHintMapType", e.target );
		}
		//
		function onHideHintMapType( e:Event ):void
		{
			ExternalInterface.call( "ASHideHintMapType" );
		}
		
		private function ClickZoomIn(evt:MouseEvent):void
		{
			ExternalInterface.call("ASMinimapZoomIn");
		}

		private function ClickZoomOut(evt:MouseEvent):void
		{
			ExternalInterface.call("ASMinimapZoomOut");
		}

		private function ClickZoneMap(evt:MouseEvent):void
		{
			ExternalInterface.call("OpenWorldMap");
		}
		//-------------------------------------------------------------------------------------------------------------------------
		function onClickToggleShowMapBtn( e:Event ):void
		{
			onOutHoverToggleShowMapBtn(null);
			ExternalInterface.call("ASToggleShowMap");
		}
		function onHoverToggleShowMapBtn( e:Event ):void
		{
			ExternalInterface.call("ASShowTipsToggleShowMap");
		}
		function onOutHoverToggleShowMapBtn( e:Event ):void
		{
			ExternalInterface.call("ASHideTips");
		}
		//-------------------------------------------------------------------------------------------------------------------------
		function onClickSwitchMapShowTypeBtn( e:Event ):void
		{
			ExternalInterface.call("ASToggleMap");
		}
		//-------------------------------------------------------------------------------------------------------------------------
		public function ToggleShowMap( isMapShow:Boolean ):void
		{
			onHoverToggleShowMapBtn(null);
			if( PlayerArraw_mc != null ){
				PlayerArraw_mc.visible = isMapShow;
			}
			//ZoneMap
			if( ZoneMap != null ){
				ZoneMap.visible = isMapShow;
			}
			//SwitchMapShowTypeBtn
			/*
			if( SwitchMapShowTypeBtn != null ){
				SwitchMapShowTypeBtn.visible = isMapShow;
			}
			*/
			//MapPathView_mc
			if( MapPathView_mc != null ){
				MapPathView_mc.visible = isMapShow;
			}
			//MapNpcView_mc
			if( MapNpcView_mc != null ){
				MapNpcView_mc.visible = isMapShow;
			}
			if(MapTopView_mc)
			{
				MapTopView_mc.visible=isMapShow;
			}
			if(MapClick_mc)
			{
				MapClick_mc.visible=isMapShow;
			}
			//mapblock_mc
			if( mapblock_mc != null ){
				mapblock_mc.visible = isMapShow;
			}
			//MapBgMc
			if( MapBgMc != null ){
				MapBgMc.visible = isMapShow;
			}
			if(ToggleShowMapBtn){
				if(isMapShow==true){
					ToggleShowMapBtn.rotation=0;
					ToggleShowMapBtn.x=225;
					ToggleShowMapBtn.y=232;
				}else{
					ToggleShowMapBtn.rotation=180;
					ToggleShowMapBtn.x=225+ToggleShowMapBtn.width;
					ToggleShowMapBtn.y=232+ToggleShowMapBtn.height;
				}
			}
			//PathFind_mc
			/*
			if( PathFind_mc != null ){
				PathFind_mc.visible = isMapShow;
			}
			*/
		}
		//-------------------------------------------------------------------------------------------------------------------------
		function onClickClosePathFind()
		{
			//ExternalInterface.call("ASStopPathFind");
			//PathFind_mc.visible = false;
		}
		
		//=====================================================================================================================
/*		function onClickChangeSceneLine( e:Event ):void
		{
			var itemData:SceneLinesDropDownListData = SceneLinesList_mc.dataProvider.requestItemAt(  SceneLinesList_mc.selectedIndex ) as SceneLinesDropDownListData;
			
			if( itemData != null )
			{
				ExternalInterface.call( "ASChangeSceneLine",  itemData.lineID );
			}
		}*/
		//
		public function UCUpdateSceneLinesList( data:Array, selIdx:int ):void
		{
			var dp:DataProvider = new DataProvider(data);
			if(data.length>1){
				SceneLinesList_mc.menuRowCount=4;
			}
			SceneLinesList_mc.dataProvider = dp;
            SceneLinesList_mc.invalidateData();
			
			SceneLinesList_mc.validateNow();
			SceneLinesList_mc.addEventListener(MouseEvent.MOUSE_OVER,overHandler);
			SceneLinesList_mc.addEventListener(MouseEvent.MOUSE_OUT,outHandler);
			SceneLinesList_mc.addEventListener(MouseEvent.CLICK,clickHandler);
			if(data.length>0){
				var item:SceneLinesDropDownListData=data[selIdx];
				if(item){
					SceneLinesList_mc.LineState=item.lineState;
				}
			}
			SceneLinesList_mc.selectedIndex = selIdx;
			CurSelectedSceneLineIdx = selIdx;
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			return;
		}
		
		private function overHandler(evt:MouseEvent):void
		{
			var itemData:SceneLinesDropDownListData = SceneLinesList_mc.dataProvider.requestItemAt(  SceneLinesList_mc.selectedIndex ) as SceneLinesDropDownListData;
			if( itemData != null ){
				ExternalInterface.call("ASShowTips_MapLineInfo",itemData.lineState);
			}
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_MapLineInfo");
		}
		
		
		public function UCSetCurSceneLines( selIdx:int ):void
		{
			if(SceneLinesList_mc)
			{
				SceneLinesList_mc.selectedIndex = selIdx;
			    CurSelectedSceneLineIdx = selIdx;
			}
		}
		//
		public function UCResetSceneLinesList():void
		{
			if(SceneLinesList_mc && SceneLinesList_mc.selected)
			{
				SceneLinesList_mc.close();
			}
		}
		
/*		public function UCChangeMapMarkLayer( markObj:MapMarkIcon):void
		{
			if( markObj == null ){
				return;
			}
			var markParentMc:MovieClip = markObj.parent as MovieClip;
			var curNum:int = markParentMc.numChildren;
			var i:int=0;
			for(i=0;i<curNum;i++){
				var mc:MapMarkIcon=markParentMc.getChildAt(i) as MapMarkIcon;
				trace(mc);
				if(mc){
					trace(mc.frameName);
					if(mc.frameName=="ally" ||  mc.frameName=="boss")
					{
						markParentMc.setChildIndex( mc, curNum-1 );
					}
				}
			}
		}*/
		
		//=======================================================================================================================
		//副本按钮
		function onClickFBAidBtn( evt:Event ):void
		{
			//if( (evt as MouseEventEx).buttonIdx == 1)
			//{
				var posX:int = root.mouseX;
				var posY:int = root.mouseY ;
				ExternalInterface.call( "ASClickFbInfo", posX, posY );
				
			//}
		}
		//
		public function UCStartFBTimeCountDown( totalFBSecond:int ):void
		{
			if( TotalTime1 > 0 ){
				//正在倒计时
				CountTimer.removeEventListener(TimerEvent.TIMER, FBTimeCountHandle);
				CountTimer.stop();
			}
			//
			if(totalFBSecond >= 0)
			{
				TotalTime1 = totalFBSecond * 1000;
				_isCountDown = true;
			}
			else
			{
				TotalTime1 = - 1 * totalFBSecond * 1000;
				_isCountDown = false;
			}
			CountBeginTime1 = getTimer();
			
			CountTimer.addEventListener(TimerEvent.TIMER, FBTimeCountHandle);
			CountTimer.start();
		}
		//
		public function StopFBTimeCountDown():void
		{
			if( TotalTime1 > 0 ){
				CountTimer.stop();
				CountTimer.removeEventListener(TimerEvent.TIMER, FBTimeCountHandle);
			}
			//
			TotalTime1 = 0;
		}
		//
		function FBTimeCountHandle():void
		{
			CountDownCurTime1 = getTimer();
			var leftTime:int;
			if(_isCountDown)
			{
				leftTime = (int)((TotalTime1 - CountDownCurTime1 + CountBeginTime1 + 999) / 1000 );
			}
			else
			{
				leftTime = (int)((TotalTime1 + CountDownCurTime1 - CountBeginTime1 + 999) / 1000 );
			}
			
			if (leftTime <= 0 ){
				StopFBTimeCountDown();
				leftTime = 0;
				ExternalInterface.call( "ASNotifyFBTimesUp" );
			}
			
			var displayString:String = FormatTimeString( leftTime );
			//
			FBAidBtn.label = displayString;
		}
		
		//--------------------------------------------------------------------------------------------------------------------
		function FormatTimeString( second:int ):String
		{
			var displayString:String = "";
			//时
			if( second >= 3600 ){
				var hour:int = (int)( second / 3600 );
				if( hour < 10 ){
					displayString += "0";
				}
				displayString += hour;
				displayString += ":";
			}
			else{
				//displayString += "00:";
			}
			//分
			if( second >= 60 ){
				var min:int = (int)( second % 3600 / 60 );
				if( min < 10 ){
					displayString += "0";
				}
				displayString += min;
				displayString += ":";
			}
			else{
				displayString += "00:";
			}
			//秒
			var sec:int = (int)( second % 60 );
			if( sec < 10 ){
				displayString += "0";
			}
			displayString += sec;
			
			return displayString;
		}
		//------------------------------------------------------------------------------------------------------------------------
		//
		public function UCStartBattleQueueTimeCountDown( totalSecond:int ):void
		{
			if( TotalTime2 > 0 ){
				//正在倒计时
				CountDownTimer2.removeEventListener(TimerEvent.TIMER, BattleQueueTimeCountDownHandle);
				CountDownTimer2.stop();
			}
			//
			TotalTime2 = totalSecond * 1000;
			CountDownBeginTime2 = getTimer();
			
			CountDownTimer2.addEventListener(TimerEvent.TIMER, BattleQueueTimeCountDownHandle);
			CountDownTimer2.start();
		}
		//
		public function StopBattleQueueTimeCountDown():void
		{
			if( TotalTime2 > 0 ){
				CountDownTimer2.stop();
				CountDownTimer2.removeEventListener(TimerEvent.TIMER, BattleQueueTimeCountDownHandle);
			}
			//
			TotalTime2 = 0;
		}
		//
		function BattleQueueTimeCountDownHandle():void
		{
			CountDownCurTime2 = getTimer();
			var leftTime:int = (int)((TotalTime2 - CountDownCurTime2 + CountDownBeginTime2 + 999) / 1000 );
			if (leftTime <= 0 ){
				StopBattleQueueTimeCountDown();
				leftTime = 0;
				ExternalInterface.call( "ASNotifyBattleQueueTimesUp" );
			}
			
			if( ButtonHoverHintMc.visible ){
				SetBattleBtnHoverHintContent();
			}
		}
		//------------------------------------------------------------------------------------------------------------------
		function onClickBattleInfo( e:Event ):void
		{
			var posX:int = root.mouseX;
			var posY:int = root.mouseY;
			ExternalInterface.call("ASClickBattleInfo", posX, posY);
		}
		//
		function onHintBattleInfo( e:Event ):void
		{
			ExternalInterface.call( "ASHintBattleInfo" );
			//CountDownCurTime2 = getTimer();
			//var passedTime:int = (int)((CountDownCurTime2 - CountDownBeginTime2 + 999) / 1000 );
			//var timeString:String = FormatTimeString( passedTime );
			//ButtonHoverHintMc.x = BattleEnterToggleBtn.x;
			//ButtonHoverHintMc.y = BattleEnterToggleBtn.y + BattleEnterToggleBtn.height;
			//ExternalInterface.call("ASHintBattleInfo", e.target, timeString );
		}
		//
		function onHideHintBattleInfo( e:Event ):void
		{
			ExternalInterface.call("ASHideHintBattleInfo");
		}
		//=======================================================================================================================
		public function SetHoverHintTitle( titleText:String ):void
		{
			//ButtonHoverHintMc.SetHintTitleText( titleText );
			var titleTf:TextField = ButtonHoverHintMc.TitleTf as TextField;
			if( titleTf != null ){
				titleTf.text = titleText;
			}
		}
		//
		public function ShowBattleBtnHoverHint( contentTextFormat:String ):void
		{
			ButtonHoverHintMc.visible = true;
			ButtonHoverContextTextFormat = contentTextFormat;
			SetBattleBtnHoverHintContent();
		}
		//
		function SetBattleBtnHoverHintContent():void
		{
			CountDownCurTime2 = getTimer();
			var passedTime:int = (int)((CountDownCurTime2 - CountDownBeginTime2 + 999) / 1000 );
			var timeString:String = FormatTimeString( passedTime );
			//
			var contentTf:TextField = ButtonHoverHintMc.ContentTf as TextField;
			if( contentTf != null ){
				var pos:int = ButtonHoverContextTextFormat.indexOf( ReplaceTextChar );
				if( pos >= 0 ){
					var contentText:String = ButtonHoverContextTextFormat.slice( 0 , pos ) + timeString + ButtonHoverContextTextFormat.slice( pos + ReplaceTextChar.length );
					//ExternalInterface.call( "ASTrace", contentText );
					contentTf.htmlText = contentText;
				}
				else{
					contentTf.htmlText = ButtonHoverContextTextFormat;
				}
			}
		}
		//=======================================================================================================================
		public function onClickArenaEntToggleBtn():void
		{
			ExternalInterface.call("ASToggleArenaEnt");
		}
		//=======================================================================================================================
		public function UCUpdateDayTime(time:int):void
		{
			DayTime_mc.gotoAndStop(time);
		}
		
		public function UCSetPathFindState(state:int):void
		{
			/*
			if (state == 1)
			{
				PathFind_mc.visible = true;
			}
			else
			{
				PathFind_mc.visible = false;
			}
			PathFind_mc.visible = false;
			*/
		}
		
		public function UpdateTraceRelation(data:Object):void
		{
			if(TraceRelationBar_mc!=null){
				TraceRelationBar_mc.updateData(data);
			}
		}
		
		public function UCUpdateWeather(type:int):void
		{
			var type_mc:MovieClip = DayTime_mc.getChildByName("WeatherType_mc") as MovieClip;
			if (type_mc)
			{
				switch (type)
				{
					case 0 :
						type_mc.visible = false;
						break;
					case 1 :
						type_mc.visible = false;
						break;
					case 2 :
						type_mc.visible = true;
						type_mc.gotoAndPlay("fog");
						break;
					case 3 :
						type_mc.visible = true;
						type_mc.gotoAndPlay("thunder");
						break;
					case 4 :
						type_mc.visible = true;
						type_mc.gotoAndPlay("rain");
						break;
					case 5 :
						type_mc.visible = true;
						type_mc.gotoAndPlay("snow");
						break;
					case 6 :
						type_mc.visible = true;
						type_mc.gotoAndPlay("storm");
						break;
					case 7 :
						type_mc.visible = false;
						type_mc.gotoAndPlay("eclip");
						break;
				}
			}
		}
		
		
		//更新信号源
		public function UCupdateSign(dat:Object):void
		{
			var ftp:int=dat.ftp;
			var sign:int=dat.sign;
			var fotmat:TextFormat=new TextFormat();
			fotmat.align=TextFormatAlign.RIGHT;
			(btn_sign.txtSign as TextField).text=ftp.toString();
			btn_sign._sign.gotoAndStop(sign);
			UpdateFPSTips();
		}
		
		public function UpdateFPSTips():void
		{
			ExternalInterface.call("ASUpdateFPSTips", this);
		}
		
		public function SetMapZoneType(param:int):void
		{
			pktype.SetMapZoneType(param);
		}
		
		public function GetMapMarkUIObjectContainer(type:int):MovieClip
		{
			switch(type)
			{
				case MapConst.PathPoint:
				{
					return this.MapPathView_mc;
				}
				default:
				{
					return this.MapNpcView_mc;
				}
			}
		}
		
/*		private function testData():void
		{
			var testMapMark:MovieClip;
			var testMapMark1:MovieClip = new (getDefinitionByName("MapMarkIconAOG") as Class);
			MapTopView_mc.addChild( testMapMark1 );
			testMapMark1.x = 30;
			testMapMark1.y = 30;
			testMapMark1.InitType(1,1,"boss");
			UCAddMapMark( testMapMark1 );
			
			var testMapMark2:MovieClip = new (getDefinitionByName("MapMarkIconAOG") as Class);
			MapNpcView_mc.addChild( testMapMark2 );
			testMapMark2.x = 60;
			testMapMark2.y = 40;
			testMapMark2.InitType(2,2,"monster");
			UCAddMapMark( testMapMark2 );
						testMapMark = new (getDefinitionByName("MapMarkIconAOG") as Class);
			MapNpcView_mc.addChild( testMapMark );
			testMapMark.x = 30;
			testMapMark.y = 50;
			testMapMark.InitType(3,3,"npc");
			UCAddMapMark( testMapMark );
						testMapMark = new (getDefinitionByName("MapMarkIconAOG") as Class);
			MapNpcView_mc.addChild( testMapMark );
			testMapMark.x = 30;
			testMapMark.y = 60;
			testMapMark.InitType(4,4,"ally");
			UCAddMapMark( testMapMark );
			UCInitMapMark(testMapMark2 as MapMarkIcon,5,9,"boss");
			
			//ButtonHoverContextTextFormat = "<P>排队时间:TIME</P><P>预计时间:未知</P>";
			//UCStartBattleQueueTimeCountDown( 120 );
			//UCStartFBTimeCountDown(20*60);//test
		}*/
	}
}