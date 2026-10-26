package UI_WorldMap.WorldMapAS3 {
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.CheckBox;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import scaleform.clik.events.ButtonEvent;

	public class BigMap extends UIComponent {
		public var tile_0:MapTile;
		public var tile_1:MapTile;
		public var tile_2:MapTile;
		public var tile_3:MapTile;
		public var tile_4:MapTile;
		public var tile_5:MapTile;
		public var tile_6:MapTile;
		public var tile_7:MapTile;
		public var tile_8:MapTile;
		public var tile_9:MapTile;
		public var tile_10:MapTile;
		public var tile_11:MapTile;
		public var tile_12:MapTile;
		public var tile_13:MapTile;
		public var tile_14:MapTile;
		public var tile_15:MapTile;
		public var tile_16:MapTile;
		public var tile_17:MapTile;
		public var tile_18:MapTile;
		public var tile_19:MapTile;
		public var tile_20:MapTile;
		public var tile_21:MapTile;
		public var tile_22:MapTile;
		public var tile_23:MapTile;
		public var tile_24:MapTile;
		public var tile_25:MapTile;
		public var tile_26:MapTile;
		private const maxTile:int=27;//地图最大元素
		public var MapList:Array=[];
		public var MapNodeList:Array=[];
		public var showMapLevel:CheckBox;

		override protected function configUI():void 
		{
			super.configUI();
			showMapLevel.addEventListener(ButtonEvent.CLICK,checkHandler);
			initData();
			//testData();
		}
		
		private function initData():void
		{
			var i:int=0;
			for(i=0;i<maxTile;i++){
				var btn:MapTile=this.getChildByName("tile_"+i) as MapTile;
				if(btn!=null){
					btn.textField2.visible=showMapLevel.selected;
					var obj:Object={};
					obj.MapID=btn.MapID;
					obj.MapRegionName=btn.MapRegionName;
					obj.AchieveID=btn.AchieveID;
					MapNodeList.push(obj);
					MapList.push(btn.MapID);
				}
			}
		}
		
		private function checkHandler(evt:ButtonEvent):void
		{
		    var isChecked:Boolean = showMapLevel.selected;
			showTips(showMapLevel.selected);
			//ExternalInterface.call( "ASToggleShowUnitedMapTileLevel",  showMapLevel.selected );
		}
		
		public function UCToggleShowUnitedMapTileLevel(dat:Boolean):void
		{
			showMapLevel.selected=dat;
			showTips(showMapLevel.selected);
		}
		
		//显示详细描述
		private function showTips(bk:Boolean):void
		{
				var i:int=0;
			    for(i=0;i<maxTile;i++){
				var btn:MapTile=this.getChildByName("tile_"+i) as MapTile;
				   if(btn!=null){
					  btn.textField2.visible=bk;
				   }
			   }
		}
		
		//获取地图节点数据
		public function UCGetMapNode():Array
		{
			if(MapNodeList.length==0)
			{
				initData();
			}
			return MapNodeList;
		}
		
/*		private function testData():void
		{
			var i:int=0;
			var arr:Array=[];
			for(i=0;i<20;i++){
				var obj:MapItemData=new MapItemData();
				if(MapList[i]){
					obj.id=MapList[i];
				}else{
					obj.id=1111;
				}
				obj.level=i+"+"+(i*10);
				obj.isGray= Boolean(i%2);
				trace(obj.id+"obj.isGray"+obj.isGray);
				arr.push(obj);
			}
			updateTilesData(arr);
		}*/
		
		public function updateTilesData(dat:Array):void
		{
			var idx:int=-1;
			var j:int=0;
			var l:int=dat.length;
			for(j=0;j<l;j++){
				var obj:MapItemData=dat[j];
				idx=MapList.indexOf(obj.id);
				var btn:MapTile=this.getChildByName("tile_"+idx) as MapTile;
				if(btn){
					btn.updateData(obj.level,obj.isGray);
				}
			}
		}
		
	}
	
}
