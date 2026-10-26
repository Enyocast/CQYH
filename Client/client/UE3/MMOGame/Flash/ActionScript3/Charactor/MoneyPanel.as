package ActionScript3.Charactor
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;


	public class MoneyPanel extends UIComponent
	{
		public var list_money_mc:ScrollingList;
		//public var InfoDragButton_mc:Button;

		override protected function configUI():void
		{
			super.configUI();
			list_money_mc.selectedIndex = 0;
			list_money_mc.addEventListener(ListEvent.INDEX_CHANGE, handleListChange, false, 0, true);
			list_money_mc.addEventListener(ListEvent.ITEM_CLICK, handleListItemClick, false, 0, true);
			//list_money_mc.addEventListener(ListEvent.ITEM_ROLL_OVER, handleListItemRollOver, false, 0, true);
			//list_money_mc.addEventListener(ListEvent.ITEM_ROLL_OUT, handleListItemRollOut, false, 0, true);

			//testList();
		}

/*		public function testList():void
		{
			var itemsData:Array = new Array();
			for (var i:int = 1; i < 28; i++)
			{
				itemsData.push({label:"货币名字 " + i, index:i ,type:0, deepth:0, visible:true, WeeklyMoney:i, WeeklyMoneyLimit:100, Money:i, MoneyTypeString:"E_MONEYTYPE_BF", Tips1:"Tips1", Tips2:"Tips2" });
			}

			updateMoneyData(itemsData);
		}*/


		public function updateMoneyData( data:Array ):void
		{
			list_money_mc.dataProvider = new TreeDataProvider(data);
			list_money_mc.validateNow();
			list_money_mc.invalidateData();
		}

		public function handleListChange( event:Event ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}

		public function handleListItemClick( event:ListEvent ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				var Provider:TreeDataProvider = targetList.dataProvider as TreeDataProvider;
				if (Provider!=null)
				{
					Provider.handleListItemClick( event );
					var obj:Object = Provider.requestItemAt(event.index);
					if (obj.type > 0)
					{
						//ExternalInterface.call( "ASChangeReputationType",obj.ID, obj.type );
					}
				}
				targetList.invalidateData();
			}
		}

/*		public function handleListItemRollOver(event:ListEvent ):void
		{
			var itemRenderer:ListItem_Money = event.itemRenderer as ListItem_Money;
			if (itemRenderer != null)
			{
				itemRenderer.handleListItemRollOver();
			}
		}

		public function handleListItemRollOut(event:ListEvent ):void
		{
			var itemRenderer:ListItem_Money = event.itemRenderer as ListItem_Money;
			if (itemRenderer != null)
			{
				itemRenderer.handleListItemRollOut();
			}
		}*/

	}
}