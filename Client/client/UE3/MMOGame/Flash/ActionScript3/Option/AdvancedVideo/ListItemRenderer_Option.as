package ActionScript3.Option.AdvancedVideo
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Option.SliderSound;
	
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.CoreList;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.events.SliderEvent;
	
	public class ListItemRenderer_Option extends ListItemRenderer
	{
		/*
enum ESystemSettingType
{
	SST_UNKNOWN = 0,
	SST_STRING  =  1,
	SST_INT  =2,	
	SST_ENUM =3,
	SST_FLOAT =4,
	SST_BOOL   = 5,
	SST_ANY
};
		*/
		
		private static const SST_INT:int = 2;
		private static const SST_ENUM:int = 3;
		private static const SST_FLOAT:int = 4;
		private static const SST_BOOL:int = 5;
		
		
		public var slider:SliderSound;
		public var ddm:DropdownMenu;
		public var check_button:CheckBox;
		public var txt_itemTitle:TextField;
		public var txt_value:TextField;
		
		protected var _itemData:OptionItemData;
		protected var _isDataUpdate:Boolean = false;

		
		public function ListItemRenderer_Option()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			txt_itemTitle.text = ""; 
			txt_value.text = "";
			txt_value.visible = false;
			slider.visible = false;
			ddm.visible = false;
			check_button.visible = false;
			slider.addEventListener(SliderEvent.VALUE_CHANGE, onSliderValueChange, false, 0, true);
			ddm.addEventListener(ListEvent.INDEX_CHANGE, onDropdownMenuClick, false, 0, true);
			check_button.addEventListener(Event.SELECT, onCheckButtonSelect, false, 0, true);
			
			txt_itemTitle.mouseEnabled = true;
			txt_itemTitle.addEventListener( MouseEvent.ROLL_OVER, ShowTips);
			txt_itemTitle.addEventListener( MouseEvent.ROLL_OUT, HideTips);
		}
		
		private function ShowTips(e:MouseEvent):void
		{
			if(_itemData == null){
				return;
			}
			ExternalInterface.call("ASShowTips_Option", this, _itemData.optionKey);
		}
		
		private function HideTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_Option");
		}

		protected function onSliderValueChange(evt:SliderEvent):void
		{
			if(_isDataUpdate){
				return;
			}
			//trace("ListItemRenderer_Option::onSliderValueChange: evt.value " + evt.value);
			if(!isNaN(evt.value)){
				_itemData.sliderValue = evt.value;
			}
			notifyListItemChange();
		}
		
		protected function onDropdownMenuClick(evt:ListEvent):void
		{
			if(_isDataUpdate){
				return;
			}
		//	trace("ListItemRenderer_Option::onDropdownMenuClick: selectedIndex "  + (evt.currentTarget.dataProvider as DataProvider).requestItemAt(evt.index));
			_itemData.ddmSelectedIndex = evt.index;
			notifyListItemChange();
		}
		
		protected function onCheckButtonSelect(evt:Event):void
		{
			if(_isDataUpdate){
				return;
			}
		//	trace("ListItemRenderer_Option::onCheckButtonSelect: " + (evt.currentTarget as CheckBox).selected);
			_itemData.checkButtonSelected = (evt.currentTarget as CheckBox).selected;
			notifyListItemChange();
		}
		
		//haven't add event of value changing when renderers set up, need implement new list class if want the list dispatch change event by itself.
		protected function notifyListItemChange():void
		{
			if(parent && parent.parent){
				(parent.parent as CoreList).dispatchEvent(new Event(Event.CHANGE));
			}
		}
		
		override public function setData(data:Object):void
		{
			super.setData(data);
			if(data != null)
			{
				_itemData = data as OptionItemData;
				if(_itemData != null)
				{	
					var type:int = _itemData.type;
					txt_value.visible 	= slider.visible =  (type == SST_INT || type == SST_FLOAT);
					ddm.visible 		=  (type == SST_ENUM);
					check_button.visible=  (type == SST_BOOL);
					
					if(slider.visible)
					{
						var maxV:Number = _itemData.MaxValue;
						var minV:Number = _itemData.MinValue;
						var step:Number = _itemData.byDetalStep;
						if(maxV > 0.001)
						{
							slider.maximum = maxV;
							slider.minimum = minV;
							if(step > 0.0001)
							slider.snapInterval = step;
						}
					}
					
					_isDataUpdate = true;
					txt_itemTitle.text = _itemData.title;
					if(slider.visible){
						slider.value = Number(_itemData.sliderValue);
					}
					else if(ddm.visible ){
						(ddm.dataProvider as DataProvider).setSource(_itemData.ddmListData);
						ddm.selectedIndex = _itemData.ddmSelectedIndex;
					}
					else if(check_button.visible){
						check_button.selected = _itemData.checkButtonSelected;
					}
					_isDataUpdate = false;
				}
			}
		}
	}
}