package UI_SkillTree.SkillTreeAS3
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import scaleform.clik.data.DataBinding;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import ActionScript3.MyPanel;
	
	public class HeavenGasExchangePanel extends MyPanel
	{
		public var gasItemList_mc:HeavenGasItemList;
		public var allGasNum_tf:TextField;
		public var ConfirmExchange_mc:Button;
		public var nSelID:int  =  0;
		
		override protected function configUI():void
		{
			trace("=======HeavenGasExchangePanel 1");
			super.configUI();
			trace("=======HeavenGasExchangePanel 2");
			gasItemList_mc.addEventListener(ListEvent.ITEM_CLICK, onClickItem);
			trace("=======HeavenGasExchangePanel 3");
			ConfirmExchange_mc.addEventListener(MouseEvent.CLICK, onClickConfirmExchange );
			trace("=======HeavenGasExchangePanel 4");
			ExternalInterface.call( "RegisterHeavenGasExchange", this);
			
		}
		
		public function UCUpdateHeavenGasItemList(data:Array):void
		{
			trace("=======UCUpdateHeavenGasItemList 1");
			gasItemList_mc.dataProvider = new DataProvider(data);
			gasItemList_mc.validateNow();
			gasItemList_mc.invalidateData();
			
			trace("=======UCUpdateHeavenGasItemList 2");
		}
		
		public function UCUpdateGasMoney( nNum:int )
		{
			allGasNum_tf.text = nNum.toString();
		}
		public function onClickItem(e:ListEvent)
		{
			var item:HeavenGasExchangeListItem = e.itemRenderer as HeavenGasExchangeListItem;
			
			nSelID = item.ItemData.GasID;
		}
		
		public function onClickConfirmExchange()
		{
			/*var testArr:Array = new Array;
			for(var n:int = 0; n < 20; ++n)
			{
				var data:HeavenGasExchangeData = new HeavenGasExchangeData;
				data.GasName = n.toString();
				data.IconName0 = "14.swf";
				testArr.push(data);
			}
			UCUpdateHeavenGasItemList(testArr);*/
			ExternalInterface.call("ASClickExchangeGasItem", nSelID);
		}
	}
}