package UI_WarehouseWidget.AS3 {
	
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ButtonEvent;
	import ActionScript3.ItemSlot.MyItemSlot;
	import flash.utils.getDefinitionByName;
	import ActionScript3.Common.Utils.StyleType;
	
	public class WareHousePanel extends MyPanel {
		
		public var BtnLock_mc:Button;
		public var BtnSort_mc:Button;
		public var tab0_mc:RadioButton;
		public var tab1_mc:RadioButton;
		public var tab2_mc:RadioButton;
		public var tab3_mc:RadioButton;
		public var tab4_mc:RadioButton;
		
		override protected  function configUI():void
		{
			super.configUI();
			BtnSort_mc.addEventListener(MouseEvent.CLICK, onSort);
			var i:int = 0;
			for(i = 0; i < 5; i++)
			{
				var tab:RadioButton = this.getChildByName( "tab"+i+"_mc" ) as RadioButton;
				if (tab)
				{
					tab.itemid = i;
					tab.addEventListener( ButtonEvent.CLICK , clickTab );
				}
			}
		}
		
		private function clickTab(e:ButtonEvent):void
		{
			var tab:RadioButton = e.currentTarget as RadioButton;
			if (tab)
			{
				ExternalInterface.call( "ASWareHouseTabChange" , tab.itemid );
			}
		}
		
		public function SetPanelText( data:Object ):void
		{
			this.SetWindowTitle(data.panelName);
		}
		
		private function onSort(evt:MouseEvent):void
		{
			BtnSort_mc.enabled = false;
			ExternalInterface.call("ASSortWarehouse");
		}
		
		public function UCUpdateSortTimer(secondsLeft:int):void
		{
			BtnSort_mc.label =  secondsLeft.toString();
		}
		
		public function UCEnableSort(e:Boolean, str:String):void
		{
			BtnSort_mc.enabled = e;
			BtnSort_mc.label = str;
		}
		
		public function UCGraySlot( mc:MyItemSlot , gray:Boolean ):void
		{
			if (! mc)
			{
				return;
			}
			if (gray)
			{
				mc.filters = [ StyleType.getInstance().getBlackFilter()];
			}
			else
			{
				mc.filters = null;
			}
		}
	}
	
}
