package ActionScript3.Option.AdvancedVideo
{
	import flash.events.Event;
	
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	public class AdvancedPanel extends UIComponent
	{
		public var list_option:ScrollingList;
		protected var _listData:DataProvider = new DataProvider();
		protected var _defaultData:Array;
		
		public function AdvancedPanel()
		{
			super();
		}

		public function get listData():DataProvider
		{
			return _listData;
		}

		override protected function configUI():void
		{
			super.configUI();
			
			//test
			//UCSetOptionListData(getTestConfigData());
		}
		
		public function defaultValue():void
		{
			if(_defaultData != null){
				UCSetOptionListData(getDataCopy(_defaultData));
			}
		}
		
		public function UCSetOptionListData(data:Array):void
		{
			_listData.cleanUp();
			_listData.setSource(data);
			list_option.invalidateData();
			list_option.dataProvider = _listData;
			list_option.validateNow();
			if(_defaultData == null && data != null){
				_defaultData = getDataCopy(data);
			}
		}
		
		private function getDataCopy(data:Array):Array
		{
			var dataCopy:Array = [];
			var len:int = data.length;
			var itemData:OptionItemData;
			var copyItem:OptionItemData;
			
			for(var i:int = 0; i < len; ++i)
			{
				itemData = data[i];
				if(itemData){
					copyItem = new OptionItemData();
					copyItem.optionKey 				= itemData.optionKey;
					copyItem.type 					= itemData.type;
					copyItem.title 					= itemData.title;
					copyItem.sliderValue 			= itemData.sliderValue;
					copyItem.MaxValue				= itemData.MaxValue;
					copyItem.MinValue				= itemData.MinValue;
					copyItem.byDetalStep			= itemData.byDetalStep;
					copyItem.ddmListData 			= itemData.ddmListData;//hasn't copy because would not be changed.
					copyItem.ddmSelectedIndex 		= itemData.ddmSelectedIndex;
					copyItem.checkButtonSelected 	= itemData.checkButtonSelected;
				}
				dataCopy.push(copyItem);
			}
			return dataCopy;
		}
		
		//test code
		private static const SST_INT:int = 2;
		private static const SST_ENUM:int = 3;
		private static const SST_FLOAT:int = 4;
		private static const SST_BOOL:int = 5;
		private static const NUM_OF_CONFIG_ITEM:int = 10;
		private static const ITEM_TITEL_LIST:Array = ['贴图分辨率','阴影表现','提升阴影质量','可视距离','事物视野距离','地形视野距离','特效视野距离','我的特效品质','他人的特效品质','图形效果品质']; 
		
		private function getTestConfigData():Array
		{
			var data:Array = new Array();
			var resolutionConfig:OptionItemData = new OptionItemData();
			resolutionConfig.type = SST_ENUM;
			resolutionConfig.title = '分辨率';
			resolutionConfig.ddmListData = ['1280x720','1280x768','1280x800','1280x960','1440x900','1600x1200','1920x1080'];
			resolutionConfig.ddmSelectedIndex = 0;
			data.push(resolutionConfig);
			
			var fullscreenConfig:OptionItemData = new OptionItemData();
			fullscreenConfig.type = SST_BOOL;
			fullscreenConfig.title = '全屏';
			fullscreenConfig.checkButtonSelected = false;
			data.push(fullscreenConfig);
			
			var itemData:OptionItemData;
			for(var i:int = 0; i < NUM_OF_CONFIG_ITEM; i++)
			{
				itemData = new OptionItemData();
				itemData.optionKey = "optionKey";
				itemData.type = SST_FLOAT;
				itemData.title = ITEM_TITEL_LIST[i];
				itemData.MaxValue = 5;
				itemData.MinValue = 1
				itemData.sliderValue = 1 + 0.1 * int(4 * Math.random() + 1);
				itemData.byDetalStep = 0.1;
				data.push(itemData);
			}
			return data;
		}
	}
}