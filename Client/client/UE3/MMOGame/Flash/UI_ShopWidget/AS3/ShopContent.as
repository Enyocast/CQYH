package UI_ShopWidget.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	public class ShopContent extends UIComponent {
		
		public var btn_repairAll:Button;
        public var btn_repair:Button;
        public var PageCtrl:MovieClip;
        public var txt_title:TextField;
		public var txt_num:TextField;
		public var _Titlebg:MovieClip;
        public var checkboxFilter_mc:CheckBox;
		public const ACHIEVEMENT:int=1;
		public const FAITH:int=2;
		//public var NPCShopList0:MyItemSlot;
		override protected function configUI():void 
		{
			super.configUI();
			checkboxFilter_mc.label="可用物品筛选";
			checkboxFilter_mc.validateNow();
            checkboxFilter_mc.addEventListener(ButtonEvent.CLICK,OnShopFilterToggle);
			//NPCShopList0.SetCD(1,3600);
		}
		private function OnShopFilterToggle(evt:ButtonEvent):void
        {
	        ExternalInterface.call( "NPCShopUsebleFilterToggle",checkboxFilter_mc.selected );
        }
		public function SelectCheckBox():void
		{
			checkboxFilter_mc.selected = true;
			ExternalInterface.call( "NPCShopUsebleFilterToggle",true );
		}
		
		public function updateShow(bool:Boolean):void
		{
			_Titlebg.visible=bool;
			txt_title.visible=bool;
			txt_num.visible=bool;
		}
		
		public function updateText(num:String):void
		{
			txt_num.htmlText=num;
		}
		
		public function UpdateShopType(dat:ShopTypeData):void
		{
			if(dat.Achiecement==true)
			{
				updateShow(true);
				txt_title.text="成就点数";
				txt_num.htmlText=dat.AchiecementNum;
			}
			else if(dat.Faith==true)
			{
				updateShow(true);
				txt_title.text="道义值";
				txt_num.htmlText=dat.FaithNum;
			}
			else
			{
				updateShow(false);
			}
			
		}
		
	}
	
}
