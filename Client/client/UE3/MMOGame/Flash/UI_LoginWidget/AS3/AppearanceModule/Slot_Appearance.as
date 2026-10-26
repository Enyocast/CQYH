package UI_LoginWidget.AS3.AppearanceModule
{
	import ActionScript3.ItemSlotData;
	
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.UILoader;
	
	public class Slot_Appearance extends ListItemRenderer
	{
		public var slot_mc:UILoader;
		protected var _itemSlotData:ItemSlotData;
		
		public function Slot_Appearance()
		{
			super();
		}
		
		override protected function configUI():void
		{
			// TODO Auto Generated method stub
			super.configUI();
		}
		
		override public function setData(data:Object):void
		{
			// TODO Auto Generated method stub
			super.setData(data);
			var itemData:ItemData_Appearance = data as ItemData_Appearance;
			if(itemData != null){
				slot_mc.source = itemData.imageSrc;
/*				if(_itemSlotData == null){
					_itemSlotData = new ItemSlotData();
				}
				_itemSlotData.iconName = itemData.imageSrc;
				_itemSlotData.slotID = itemData.id;
				slot_mc.SetDataObj(_itemSlotData);*/
			}
		}
	}
}