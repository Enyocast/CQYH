
package ActionScript3.Mall
{
	import ActionScript3.MyPanel;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ButtonEvent;
	import flash.display.MovieClip;


	public class MallPanel extends MyPanel
	{
		public var mallGoodsPanel_mc:MallGoodsPanel;
		public var mallHomePanel_mc:MallHomePanel;
		public var tArrHotGoods:Array;
		
		public var homePageBtn_mc:RadioButton;
		public var mallItemBtn_mc:RadioButton;
		public var mallItemBtn1_mc:RadioButton;
		public var mallItemBtn2_mc:RadioButton;
		public var mallNotice_mc:MallGoodsNoticeUnit;
		
		
		override protected  function configUI():void 
		{		
		    ShowMode="BC";
			super.configUI();			
			
			homePageBtn_mc.addEventListener(MouseEvent.CLICK, OnClickPanelPage0 );
			mallItemBtn_mc.addEventListener(MouseEvent.CLICK, OnClickPanelPage1 );
			mallItemBtn1_mc.addEventListener(MouseEvent.CLICK, OnClickPanelPage2 );
			mallItemBtn2_mc.addEventListener(MouseEvent.CLICK, OnClickPanelPage3 );
			
			mallItemBtn1_mc.visible = false;
			mallItemBtn2_mc.visible = false;
			
			ExternalInterface.call( "ASTrace", "MallPanel");
			ExternalInterface.call("RegisterMallPanel", this);
			
			UCUpdatePageNum("1/1");
			UCMallUpdateGoldMoney(0);
			
			tArrHotGoods = new Array;
			for(var i:int = 0; i < 5; ++i)
			{
				 var goods:MallHomeHotItem = this.getChildByName( "hotGoods"+i+"_mc" ) as MallHomeHotItem;
				 tArrHotGoods.push(goods);
			}
			testHot();
		}
		
		public function OnClickPanelPage0()
		{
			ShowPanelByIndex(0);
		}
		public function OnClickPanelPage1()
		{
			ShowPanelByIndex(1);
		}
		public function OnClickPanelPage2()
		{
			ShowPanelByIndex(2);
		}
		public function OnClickPanelPage3()
		{
			ShowPanelByIndex(3);
		}

		public function ShowPanelByIndex(nIndex:int)
		{
			mallHomePanel_mc.visible = (nIndex == 0);
			mallGoodsPanel_mc.visible = (nIndex > 0);
			ExternalInterface.call("ASClickMallTap", nIndex);
		}
		public function UCSetMallTab(nIndex:int)
		{
			mallHomePanel_mc.visible = (nIndex == 0);
			mallGoodsPanel_mc.visible = (nIndex > 0);
			homePageBtn_mc.selected = (nIndex == 0);
			mallItemBtn_mc.selected = (nIndex == 1);
			mallItemBtn1_mc.selected = (nIndex == 2);
			mallItemBtn2_mc.selected = (nIndex == 3);
		}
		public function UCInitDropMenuList(nIndex:int,dataProvider:Array)
		{
			mallGoodsPanel_mc.InitDropMenuList(nIndex,dataProvider);
		}
		public function UCUpdatePageNum(nPage:String)
		{
			mallGoodsPanel_mc.UpdatePageNum(nPage);
		}
		public function UCUpdateGoodsList(dataProvider:Array)
		{
			mallGoodsPanel_mc.UpdateGoodsList(dataProvider);
		}
		public function UCMallUpdateGoldMoney(nMoney:int)
		{
			mallGoodsPanel_mc.UpdateMoney(nMoney);
			mallHomePanel_mc.UpdateMoney(nMoney);
		}
		public function UCUpdateMallHotList(dataProvider:Array)
		{
			if(dataProvider == null)
				return;
			for(var n:int = 0; n  < 5; ++n)
			{
				if(n < dataProvider.length)
					tArrHotGoods[n].updateData(dataProvider[n]);
				else
					tArrHotGoods[n].updateData(null);
			}
		}
		public function UCUpdateMallHomeShowData( data:Array )
		{
			ExternalInterface.call( "ASTrace", " MallPanel  UCUpdateMallHomeShowData");
			mallHomePanel_mc.UpdateMallHomeShowData(data);
		}
		
		public function UCUpdateNewNotice(data:Array)
		{
			mallNotice_mc.UpdateNewNotice(data);
		}
		public function testHot()
		{
			var tItem = new Array;
			
			for(var n:int = 0;n < 5;++n)
			{
				var data:MallGoodsData = new MallGoodsData;
				data.ItemName = "medicine" + n;
				data.ItemID = n + 1;
				data.ItemCost0 = "money0 100";
				data.ItemCost1 = "money1 24300";
				data.ItemType = n%3 + 1;
				data.ItemIndex = n + 1;
				tItem.push(data);
				trace("-testHot",data);
			}
			
			UCUpdateMallHotList(tItem);
		}
	}
}