package UI_VIP.AS3 {
	
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	
	public class ItemGrid extends UIComponent {
		
		public var btn:Button;
		public var item_name:TextField;
		public var item_icon:MyItemSlot;
		public var item_gold:TextField;
		public var id:int;
		public function ItemGrid() {
			super();
		}
		override protected  function configUI():void {
			super.configUI();
			btn.addEventListener(MouseEvent.CLICK,clickHandler);
			item_icon.DisableDrag = true;
			item_icon.enabled = false;
		}
		
		protected function clickHandler(e:MouseEvent):void
		{
		    ExternalInterface.call("ASBuyVipLevel", id);
		}
		
		public function updateData(dat:VipGoods):void
		{
			id=dat.ItemID;
			item_name.htmlText=dat.ItemName;
			item_gold.htmlText=dat.ItemCost;
			item_icon.SetData(1, dat.ItemIcon, 0, "", 0, -1, -1);
			
		}
	}
	
}
