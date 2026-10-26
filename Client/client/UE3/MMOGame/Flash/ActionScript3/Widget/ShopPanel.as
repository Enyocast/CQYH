package ActionScript3.Widget{

	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import ActionScript3.Widget.UWindow;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	import flash.events.FocusEvent;
	import flash.events.MouseEvent;
	import scaleform.gfx.FocusEventEx;
	import scaleform.gfx.FocusManager;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.MyIconConponent;
	import flash.text.TextField;
	import ActionScript3.MyWindowsFrame;
	import UI_ShopWidget.AS3.ShopTypeData;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ButtonEvent;
	import ActionScript3.Common.Utils.StyleType;

	public class ShopPanel extends MyPanel
	{
		public var btn_repairAll:Button;
		public var btn_repair:Button;
		public var btn_prev:Button;
		public var btn_next:Button;
		
		public var ShopContent:MovieClip;
		public var PageCtrl:MovieClip;
		public var PageNum:TextField;
		
		public var tab0_mc:RadioButton;
		public var tab1_mc:RadioButton;
		public var tab2_mc:RadioButton;
		public var tab3_mc:RadioButton;
		
		public var SKILL_SHOP:int = 5000;
		public var POSY_SHOP:int = 5500;
		
		override protected  function configUI():void 
		{
			ShowMode="BC";
			super.configUI();

			btn_repair = ShopContent.getChildByName("btn_repair") as Button;
			if( btn_repair )
			{
				btn_repair.addEventListener( MouseEvent.CLICK , ClickRepair );
				btn_repair.addEventListener( MouseEvent.ROLL_OVER, ShowRepairTips);
				btn_repair.addEventListener( MouseEvent.ROLL_OUT, HideRepairTips);
			}
			btn_repairAll = ShopContent.getChildByName("btn_repairAll") as Button;
			if( btn_repairAll )
			{
				btn_repairAll.addEventListener( MouseEvent.CLICK , ClickRepairAll );
				btn_repairAll.addEventListener( MouseEvent.ROLL_OVER, ShowRepairAllTips);
				btn_repairAll.addEventListener( MouseEvent.ROLL_OUT, HideRepairAllTips);
			}
			
			if( tab0_mc )
			{
				tab0_mc.addEventListener(ButtonEvent.CLICK,clickTab0);
			}
			if( tab1_mc )
			{
				tab1_mc.addEventListener(ButtonEvent.CLICK,clickTab1);
			}
			if( tab2_mc )
			{
				tab2_mc.addEventListener(ButtonEvent.CLICK,clickTab2);
			}
			if( tab3_mc )
			{				
				tab3_mc.addEventListener(ButtonEvent.CLICK,clickTab3);
			}
			if( ShopContent )
			{
				ShopContent.updateShow(false);
				PageCtrl = ShopContent.getChildByName("PageCtrl") as MovieClip;
				if( PageCtrl )
				{
					if( btn_prev == null )
					{
						btn_prev = PageCtrl.getChildByName( "btn_prev" ) as Button;
						if( btn_prev )
						{
							btn_prev.addEventListener( MouseEvent.CLICK , ClickPagePrev );
						}
					}
					if( btn_next == null )
					{
						btn_next = PageCtrl.getChildByName( "btn_next" ) as Button;
						if( btn_next )
						{
							btn_next.addEventListener( MouseEvent.CLICK , ClickPageNext );
						}
					}
					if( PageNum == null )
					{
						PageNum = PageCtrl.getChildByName( "tF_pageNum" ) as TextField;
					}
				}
			}
			SetTabVisible(false);
			//UCSelectFilter(1);
			//UCGraySlot("NPCShopList0",true);
		}
		
				
		private function ShowRepairAllTips(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_RepairAll", btn_repairAll);
		}
		
		private function HideRepairAllTips(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_RepairAll", btn_repairAll);
		}
		
		public function SetPageButton( data:Object )
		{
			if( btn_prev )
			{
				btn_prev.enabled = data.preEnable;
			}
			if( btn_next )
			{
				btn_next.enabled = data.nextEnable;
			}
			if( PageNum )
			{
				PageNum.text = data.PageNumTxt;
			}
		}
		
		public function SetPanelText( dat:Object )
		{
			if( dat == null )
			{
				return;
			}
			this.SetWindowTitle(dat.titleName);
			if( btn_repair )
			{
				btn_repair.label = dat.btn0;
			}
			if( btn_repairAll )
			{
				btn_repairAll.label = dat.btn1;
			}
		}
		
		public function SetTabVisible(v:Boolean):void
		{
			tab0_mc.visible = v;
			tab1_mc.visible = v;
			tab2_mc.visible = v;
			tab3_mc.visible = v;
			
		}
		public function UCUpdateTabLabel(dat1:String,index:int,itemType:int):void
		{
			PageCtrl.visible=true;
			switch(index)
			{
			case 0:
					tab0_mc.visible = true;
					tab0_mc.label = dat1;
					tab0_mc.itemid = itemType;
				break;
					
			case 1:
					tab1_mc.visible = true;
					tab1_mc.label = dat1;
					tab1_mc.itemid = itemType;
				break;
			case 2:
					tab2_mc.visible = true;
					tab2_mc.label = dat1;
					tab2_mc.itemid = itemType;
				break;
			case 3:
					tab3_mc.visible = true;
					tab3_mc.label = dat1;
					tab3_mc.itemid = itemType;
				break;
			}
		}
		
		override public function UCGetWidth():int
		{
			return this.InfoDragButton_mc.width;
		}
		
		override public function UCGetHeight():int
		{
			return this.InfoDragButton_mc.height;
		}
		
		function CloseShop()
		{
			ExternalInterface.call( "ASNPCShopClose" );
		}
		
		private function ClickRepair(evt:MouseEvent):void
		{
			if( (evt as MouseEventEx).buttonIdx == 0)//左键
			{
				ExternalInterface.call( "ASNPCShopRepair" );
			}
		}
		
		private function ClickRepairAll(evt:MouseEvent):void
		{
			if( (evt as MouseEventEx).buttonIdx == 0)//左键
			{
				ExternalInterface.call( "ASNPCShopRepairAll" );
			}
		}

		private function ClickPagePrev(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASNPCShopPagePrev" );
		}

		private function ClickPageNext(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASNPCShopPageNext" );
		}

		private function clickTab0(evt:ButtonEvent):void
		{
			hide(tab0_mc.itemid);
			ExternalInterface.call("ASNpcShopTab",tab0_mc.itemid);
		}
		private function clickTab1(evt:ButtonEvent):void
		{
			hide(tab1_mc.itemid);
			ExternalInterface.call("ASNpcShopTab",tab1_mc.itemid);
		}
		private function clickTab2(evt:ButtonEvent):void
		{
			hide(tab2_mc.itemid);
			ExternalInterface.call("ASNpcShopTab",tab2_mc.itemid);
		}
		private function clickTab3(evt:ButtonEvent):void
		{
			hide(tab3_mc.itemid);
			ExternalInterface.call("ASNpcShopTab",tab3_mc.itemid);
		}
		
		public function hide(type:int):void
		{
			if(type==15){
				PageCtrl.visible=false;
			}else{
				PageCtrl.visible=true;
			}
		}
		
		//控制复选框默认值
		public function UCSelectFilter(shopId:int):void
		{
			if(shopId == SKILL_SHOP || shopId == POSY_SHOP)
			{
				ShopContent.SelectCheckBox();
			}
			ShopContent.updateShow(false);
		}
		
		//更新成就道义值
		public function UCUpdateText(num:String):void
		{
			ShopContent.updateText(num);
		}
		
		public function UCUpdateShopType(data:ShopTypeData):void
		{
			ShopContent.UpdateShopType(data);
		}
		
		private function ShowRepairTips(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowRepairTips", btn_repair);
		}
		
		private function HideRepairTips(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideRepairTips", btn_repair);
		}
		
		public function UCGraySlot(n:String , gray:Boolean ):void
		{
			var slot:MyItemSlot = ShopContent.getChildByName(n) as MyItemSlot;
			
			if (!slot)
			{
				return;
			}
			if (gray)
			{
				
				slot.filters = [ StyleType.getInstance().getBlackFilter()];
			}
			else
			{
				slot.filters = null;
			}
		}
		
	}
}