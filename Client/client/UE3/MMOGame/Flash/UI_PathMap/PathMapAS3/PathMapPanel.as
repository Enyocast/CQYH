package UI_PathMap.PathMapAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.MapMarkIcon;
	//import ActionScript3.MyTipButton;
	import ActionScript3.MyPanel;
	
	import flash.utils.getDefinitionByName;
	
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.events.Event;
	
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import UI_Minimap.MinimapAS3.MapConst;
	import ActionScript3.Common.Events.ParamEvent;

	public class PathMapPanel extends MyPanel
	{
		public var mapZone_mc:MovieClip;
		public var mapMaskZone_mc:MovieClip;
		public var MapNpcView_mc:MovieClip;
		public var MapTopView_mc:MovieClip;
		public var MapPathView_mc:MovieClip;
		public var BackToMinimapBtn:Button;
		//public var BackToMinimapBtn:MyTipButton;
		//public var BackToMinimapBtn:Button;
		
		override protected  function configUI():void
		{
			ShowMode = "TRB";
			super.configUI();
			BackToMinimapBtn.addEventListener(MouseEvent.CLICK,onClickHandler);

			mapZone_mc.mouseChildren = true;
			
			MapNpcView_mc = mapZone_mc.MapNpcView_mc;
			MapNpcView_mc.mouseEnabled=false;
			
			MapTopView_mc= mapZone_mc.MapTopView_mc;
			MapTopView_mc.mouseEnabled=false;
			
			MapPathView_mc = mapZone_mc.MapPathView_mc;
			if( MapPathView_mc != null ){
				MapPathView_mc.mouseChildren = true;
				MapPathView_mc.mouseEnabled = false;
			}
			/*
			//test
			var testMapMark:MapMarkIconAOG = new MapMarkIconAOG();
			MapNpcViewMc.addChild( testMapMark );
			testMapMark.x = 30;
			testMapMark.y = 30;
			testMapMark.gotoAndStop( "ally" );
			UCAddMapMark( testMapMark );
			*/
			
			//BackToMinimapBtn.addEventListener( MouseEvent.CLICK, onClickBackToMinimap );
			//
			ExternalInterface.call( "RegisterPathMap", this );
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=cavasWidth-724+362;
		}
		
		private function onClickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASPathMapToMinimap");
		}
		//
		public function onClickBackToMinimap( e:Event )
		{
			ExternalInterface.call( "ASPathMapToMinimap" );
		}
		//=====================================================================================================================
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
			if(type==MapConst.NearBoss || type==MapConst.GlobalTeammate)
			{ 
				if(newMarkObj.parent && newMarkObj.parent.name!=this.MapTopView_mc.name)
				{
					 newMarkObj.parent.removeChild(newMarkObj);
					 this.MapTopView_mc.addChild(newMarkObj);
				}
			}
			markObj.InitType( id, type, frameName );
		}
		//=====================================================================================================================
		function ShowMapMarkHint( e:Event )
		{
			var markMc:MapMarkIcon = e.target as MapMarkIcon;
			
			ExternalInterface.call( "ASShowPathMapMarkHint", markMc.Type, markMc.ID );
		}
		//
		function HideMapMarkHint( e:Event )
		{
			//var markMc:MapMarkIcon = e.target as MapMarkIcon;
			
			ExternalInterface.call( "ASHidePathMapMarkHint" );
		}
		//==============================================================================================================
		public function UCChangeMapMarkLayer( markObj:MovieClip, layerIdx:int ):void
		{
			if( markObj == null ){
				return;
			}
			
			var markParentMc:MovieClip = markObj.parent as MovieClip;
			var curNum = markParentMc.numChildren;
			if( layerIdx >= curNum ){
				layerIdx = curNum - 1;
			}
			markParentMc.setChildIndex( markObj, layerIdx );
			//trace("UCChangeMapMarkLayer", layerIdx );
		}
		public function UCMoveUpMapMark( markObj:MovieClip, standardMarkObj:MovieClip ):void
		{
			MapNpcView_mc.setChildIndex( markObj, MapNpcView_mc.getChildIndex( standardMarkObj ) );
			//trace("UCChangeMapMarkLayer", layerIdx );
		}
		//
		public function UCMoveDownMapMark( markObj:MovieClip, standardMarkObj:MovieClip ):void
		{
			MapNpcView_mc.setChildIndex( markObj, MapNpcView_mc.getChildIndex( standardMarkObj ) - 1 );
			//trace("UCChangeMapMarkLayer", layerIdx );
		}
		
		public function GetMapMarkUIObjectContainer(type:int):MovieClip
		{
			switch(type)
			{
				case MapConst.PathPoint:
				{
					return this.MapPathView_mc;
				}
				case MapConst.GlobalTeammate:
				{
					return this.MapTopView_mc;
				}
				case MapConst.NearBoss:
				{
					return this.MapTopView_mc;
				}
				default:
				{
					return this.MapNpcView_mc;
				}
			}
		}
	}
}