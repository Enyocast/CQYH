
package ActionScript3.Mall
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.DropdownMenu;

	public class MallGoodsPanel extends UIComponent
	{
		public var dropHot_mc:DropdownMenu;
		public var dropAvaible_mc:DropdownMenu;
		
		public var pagectrl_mc:MovieClip;
		public var money1_gold:TextField;
		public var btnAddGold_mc:Button;
		
		public var tArrGoods:Array = [];
		
		override protected  function configUI():void 
		{		
			trace("------ActivityPanel  super.configUI:");
			super.configUI();			

			for(var n :int = 0; n < 15; ++n)
			{
				 var goods:MallGoodsItem = this.getChildByName( "goods"+n+"_mc" ) as MallGoodsItem;
				 tArrGoods.push(goods);
			}
			
			var btnPrePage:Button = pagectrl_mc.getChildByName("btn_prev") as Button;
			if( btnPrePage)
				 btnPrePage.addEventListener(MouseEvent.CLICK, 		onClickPrePage);
			var btnNextPage:Button = pagectrl_mc.getChildByName("btn_next") as Button;
			if( btnNextPage)
				 btnNextPage.addEventListener(MouseEvent.CLICK, 	 onClickNextPage);
				 
			btnAddGold_mc.addEventListener(MouseEvent.CLICK, 		onClickAddMoney);
			
			dropHot_mc.addEventListener(ListEvent.INDEX_CHANGE, HotMenuItemClick);
			dropAvaible_mc.addEventListener(ListEvent.INDEX_CHANGE, NewMenuItemClick);
			
			ExternalInterface.call( "ASTrace", "MallGoodsPanel");
			testMallData();
		}
		public function HotMenuItemClick()
		{
			trace("------HotMenuItemClick");
			ExternalInterface.call("ASClickDropMenuHotType", dropHot_mc.selectedIndex);
		}
		public function NewMenuItemClick()
		{
			trace("------HotMenuItemClick");
			ExternalInterface.call("ASClickDropMenuAvaibleType", dropAvaible_mc.selectedIndex);
		}
		public function InitDropMenuList(nIndex:int,dataProvider:Array)
		{
			var dropMenu:DropdownMenu = null;
			if(nIndex == 0)
			{
				dropMenu = dropHot_mc;
			}
			else if(nIndex == 1)
			{
				dropMenu = dropAvaible_mc;
			}
			
			if(dropMenu == null)
				return;
			var size_str:String = "";
			for(var i:int = 0; i < dataProvider.length; ++i)
			{
				size_str += dataProvider[i];
				if (i < dataProvider.length - 1)
					size_str += "=";
			}
			dropMenu.datastring = size_str;
			dropMenu.SplitData();
			dropMenu.selectedIndex = 0;
		}
		public function testMallData()
		{
			var tItem = new Array;
			
			for(var n:int = 0;n < 14;++n)
			{
				var data:MallGoodsData = new MallGoodsData;
				data.ItemName = "medicine" + n;
				data.ItemID = n + 1;
				data.ItemCost0 = "money0 200";
				data.ItemCost1 = "money1 2200";
				data.ItemType = n%3 + 1;
				tItem.push(data);
			}
			UpdateGoodsList(tItem);
			
			var tARR:Array = new Array;
			tARR.push("Newssss1");
			tARR.push("Newssss2");
			tARR.push("Newssss3");
			tARR.push("Newssss4");
			InitDropMenuList(0,tARR);
			
			tARR.push("Newssss5");
			tARR.push("Newssss6");
			InitDropMenuList(1,tARR);
		}
		
		public function onClickAddMoney()
		{
			ExternalInterface.call("ASAddGoldMoney", this);
		}
		public function onClickPrePage()
		{
			ExternalInterface.call("ASClickPrePage", this);
		}
		public function onClickNextPage()
		{
			ExternalInterface.call("ASClickNextPage", this);
		}
		public function UpdatePageNum(nPage:String)
		{
			var page_tf:TextField = pagectrl_mc.getChildByName("tF_pageNum") as TextField;
			if( page_tf)
				 page_tf.text = nPage;
		}
		public function UpdateMoney(nMoney:int)
		{
			money1_gold.htmlText = nMoney.toString()+"<IMG SRC='img://MMO_UIIcon.MoneyIcon.MoneyBullion'>";
		}
		public function UpdateGoodsList(dataProvider:Array)
		{
			if(dataProvider == null)
				return;
			for(var n:int = 0; n < tArrGoods.length; ++n)
			{
				if(n < dataProvider.length)
					tArrGoods[n].updateData(dataProvider[n]);
				else
					tArrGoods[n].updateData(null);
			}
		}
	}
}