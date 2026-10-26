package UI_WorldMap.WorldMapAS3 {
	
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	public class MapTile extends Button {
		
		public var gray:MovieClip;
		public var mapTips:String="";
        private var _mapLevel:String;
		private var _mapName:String="";
		private var _mapId:int=0;
		public var _mapTips:String;
		public var _achieveID:int;//成就ID
		public var textField1:TextField;
		public var textField2:TextField;
		public var level:String;//等级描述
		
		override protected function configUI():void 
		{
			super.configUI();
			addEvent();
			if(_mapLevel=="暂未开放"){
				textField2.textColor=0xc2c2c2;
				var format:TextFormat=textField2.defaultTextFormat;
				textField2.defaultTextFormat=format;
				format.size=10;
				removeEvent();
			}
			textField2.text=_mapLevel;
			textField2.y=textField1.y+17;
			//this.addEventListener(MouseEvent.MOUSE_OVER,overHandler);
			//this.addEventListener(MouseEvent.MOUSE_OUT,outHandler);
		}
		
/*		private function overHandler(evt:MouseEvent):void
		{
            ExternalInterface.call( "ASShowTipsUnitedMapTile", this,mapTips );
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASHideTipsUnitedMapTile");
		}*/
		
		private function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASClickToWorldMap", 0, MapID, MapRegionName);
		}
		
		public function updateData(dat:String,isGray:Boolean):void
		{
			level=dat;
			if(isGray==false){
				addEvent();
			}else{
				removeEvent();
			}
		}
		
		private function addEvent():void
		{
			gray.visible=false;
			this.enabled=true;
			this.removeEventListener(MouseEvent.CLICK,clickHandler);
			this.addEventListener(MouseEvent.CLICK,clickHandler);
		}
		
		public function removeEvent():void
		{
			gray.visible=true;
			this.enabled=false;
			this.removeEventListener(MouseEvent.CLICK,clickHandler);
		}
		
		[Inspectable(defaultValue = "0")]
		public function get AchieveID():int
		{
			return _achieveID;
		}
		public function set AchieveID(value:int):void
		{
			_achieveID = value;
		}
		
		[Inspectable(defaultValue = "")]
		public function get MapTips():String
		{
			return _mapTips;
		}
		public function set MapTips(value:String):void
		{
			_mapTips = value;
		}
		
		[Inspectable(defaultValue = "")]
		public function get MapLevel():String
		{
			return _mapLevel;
		}
		public function set MapLevel(value:String):void
		{
			_mapLevel = value;
		}
		
		[Inspectable(defaultValue = "")]
		public function get MapRegionName():String
		{
			return _mapName;
		}
		public function set MapRegionName(value:String):void
		{
			_mapName = value;
		}
	    [Inspectable(defaultValue = "0")]
		public function get MapID():int
		{
			return _mapId;
		}
		public function set MapID(value:int):void
		{
			_mapId = value;
		}
	}
	
}
