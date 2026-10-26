
package ActionScript3.Mall
{
	import ActionScript3.MyPanel;
	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.NumericStepper;
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
	import scaleform.clik.events.IndexEvent;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	
	public class MallGoodsBuyPanel extends MyPanel
	{

		public var btnGiveFriend_mc:Button;
		public var buyGoods_mc:Button;
		
		public var ItemName_mc:TextField;
		public var oldPrice_mc:TextField;
		public var nowPrice_mc:TextField;
		public var ItemCost0_mc:TextField;
		public var ItemCost1_mc:TextField;
		public var goodsDescrible_mc:TextField;
		public var haveGold_tf:TextField;
		public var costMoney_tf:TextField;
		public var leftMoney_tf:TextField;
		public var leftMoneyHint_tf:TextField;
		public var buyGoodsIcon_mc:MyItemSlot;
		public var numInput_mc:NumericStepper;

		public var buyAim_tf:TextField;
		
		public var goodsData:MallGoodsData = null;
		public var nNum:int = 1;
		public var nGoldMoney = 100;
		public var nPriceSingle = 1;
		public var strMoney:String = String("<IMG SRC='img://MMO_UIIcon.MoneyIcon.MoneyBullion'>");
		
		override protected  function configUI():void 
		{		
			trace("------MallGoodsBuyPanel  super.configUI:");
			super.configUI();			

			btnGiveFriend_mc.addEventListener(MouseEvent.CLICK, OnClickGive);
			buyGoods_mc.addEventListener(MouseEvent.CLICK, OnClickBuy);
			numInput_mc.addEventListener(IndexEvent.INDEX_CHANGE, OnUpdateMoneyCost);
						
			ExternalInterface.call("RegisterBuyGoodsPanel", this);
			ExternalInterface.call( "ASTrace", "MallGoodsBuyPanel");
			
			var datass:MallGoodsData = new MallGoodsData;
			datass.ItemDescrible = "dssadsadasa";
			datass.ItemName = "name";
			UCUpdateGoodsData(datass);
			UCUpdateGoldMoney(0);
			SetWindowTitle("");
		}

		public function UCUpdateGoodsData(data:Object):void
		{
			leftMoneyHint_tf.visible = false;
			goodsData = data as MallGoodsData;
			if(goodsData)
			{
				nPriceSingle = goodsData.ItemCostValue;
				
				ItemName_mc.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				ItemName_mc.wordWrap 	= 			true;
				ItemName_mc.htmlText 	= 			goodsData.ItemName;
				ItemName_mc.height 	= 				ItemName_mc.textHeight;
				
				ItemCost0_mc.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				ItemCost0_mc.wordWrap 	= 			true;
				ItemCost0_mc.htmlText 	= 			goodsData.ItemCost0;
				ItemCost0_mc.height 	= 			ItemCost0_mc.textHeight;
				
				ItemCost1_mc.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				ItemCost1_mc.wordWrap 	= 			true;
				ItemCost1_mc.htmlText 	= 			goodsData.ItemCost1;
				ItemCost1_mc.height 	= 			ItemCost1_mc.textHeight;
				
				ItemCost0_mc.visible = (goodsData.ItemCost0 != "");
				oldPrice_mc.visible = (goodsData.ItemCost0 != "");
				
				ItemCost1_mc.visible = (goodsData.ItemCost1 != "");
				nowPrice_mc.visible = (goodsData.ItemCost1 != "");
				
				goodsDescrible_mc.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				goodsDescrible_mc.wordWrap 	= 			true;
				goodsDescrible_mc.htmlText 	= 			goodsData.ItemDescrible;
				goodsDescrible_mc.height 	= 			goodsDescrible_mc.textHeight;
			}
			numInput_mc.value = 1;
		}
		
		public function UCUpdateGoldMoney(nGold:int):void
		{
			nGoldMoney = nGold;
			//haveGold_tf.text = nGold.toString();
			haveGold_tf.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
			haveGold_tf.wordWrap 	= 			true;
			haveGold_tf.htmlText 	= 			 nGold.toString() + strMoney;
			haveGold_tf.height 	= 			haveGold_tf.textHeight;
				
			numInput_mc.value = 1;
			OnUpdateMoneyCost();
		}
		protected function OnClickGive(e:MouseEvent):void
		{
			if(goodsData)
				ExternalInterface.call("ASClickGiveFriend", goodsData.ItemID,nNum);
		}
		protected function OnClickBuy(e:MouseEvent):void
		{
			if(goodsData)
				ExternalInterface.call("ASClickBuyGoods",  goodsData.ItemID,nNum );
		}
		public function UCSetBuyAimPlayerName(str:String):void
		{
			buyAim_tf.text = str;
		}
		protected function OnUpdateMoneyCost(e:IndexEvent=null):void
		{
			if(goodsData)
			{
				trace("---OnUpdateMoneyCost");
				nNum = numInput_mc.value;
				if(nNum>1){
					numInput_mc.enabled=false;
				}
				var leftM:int = nGoldMoney - nPriceSingle * nNum;
				leftMoneyHint_tf.visible = (leftM < 0);
				//leftMoney_tf.text = (leftM < 0)? "0":leftM.toString();
				//costMoney_tf.text =  (nPriceSingle * nNum).toString();
				
				leftMoney_tf.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				leftMoney_tf.wordWrap 	= 			true;
				leftMoney_tf.htmlText 	= 			((leftM < 0)? "0":leftM.toString()) + strMoney;
				leftMoney_tf.height 	= 			leftMoney_tf.textHeight;
				
				costMoney_tf.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				costMoney_tf.wordWrap 	= 			true;
				costMoney_tf.htmlText 	= 			(nPriceSingle * nNum).toString() + strMoney;
				costMoney_tf.height 	= 			costMoney_tf.textHeight;

			}
		}
	}
}