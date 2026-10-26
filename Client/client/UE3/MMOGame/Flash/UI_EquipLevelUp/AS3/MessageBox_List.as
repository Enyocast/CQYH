package UI_EquipLevelUp.AS3
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.geom.Rectangle;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	
	public class MessageBox_List extends MyPanel
	{
		public var txt_title:TextField;
		public var btn_confirm:Button;
		public var compensation_list:ScrollingList;
		
		private var _listData:DataProvider = new DataProvider();
		
		public function MessageBox_List()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function setData(data:UpgradeResultData):void
		{
			if(data == null || data.compensationMaterialList == null) {
				compensation_list.visible = false;
				return;
			}
			txt_title.text = data.messageTitle;
			
			_listData.cleanUp();
			_listData.setSource(data.compensationMaterialList);
			compensation_list.visible = true;
			compensation_list.dataProvider = _listData;
			compensation_list.validateNow();
		}
	}
}