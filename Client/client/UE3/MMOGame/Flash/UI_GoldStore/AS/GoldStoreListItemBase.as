package UI_GoldStore.AS
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MoneyInput;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.gfx.MouseEventEx;
	
	public class GoldStoreListItemBase extends ListItemTreeRenderer 
	{
		public var unitPrice_txt_mc:TextField;
		public var txt_num_of_sell:TextField;
		
		public var money_Unit = 10000;
		
		public function GoldStoreListItemBase()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			unitPrice_txt_mc.mouseEnabled=false;
			txt_num_of_sell.mouseEnabled=false;
			setUpdateDataCallBack(updateData);
		}
		
		function updateData(data:Object):void
		{
			
		}	
		
	}
	
}
