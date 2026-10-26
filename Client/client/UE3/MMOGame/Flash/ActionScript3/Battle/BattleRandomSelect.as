package ActionScript3.Battle{
	import ActionScript3.ItemSlot.IconSlot
	//import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;
	//import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	public class BattleRandomSelect extends UIComponent
	{
		//战场列表
		public var BattlesList_mc:ScrollingList;
		//战场描述
		public var BtlDescTf:TextField;
		//物品奖励
		public var BtlAwardItemsIcon0:IconSlot;
		//经验奖励
		public var BtlAwardExpTf:TextField;
		
		override protected function configUI():void
		{
			trace("------BattleRandomSelect  super.configUI:");
			super.configUI();
			
			BattlesList_mc.addEventListener(ListEvent.ITEM_CLICK, onClickBattle);
			/*
			//test
			var itemsData:Array = new Array();
			for (var i:int = 1; i < 30; i++)
			{
				var battleItemData:BattlesListItemData = new BattlesListItemData ;
				battleItemData.BattleID = i;
				battleItemData.BattleIconIdx = i;
				battleItemData.BattleSelected = false;//Boolean(i % 2);
				battleItemData.BattleName = "战场" + i;
				itemsData.push(battleItemData);
			}
			updateBattlesList(itemsData);
			//test end
			*/
			updateBattlesList( null );
		}
		//
		public function updateBattlesList( data:Array ):void
		{
			trace("======BattleRandomSelect::updateBattlesList" , BattlesList_mc , data);
			
			BattlesList_mc.dataProvider = new DataProvider(data);
			BattlesList_mc.validateNow();
			BattlesList_mc.invalidateData();
		}
		//
		public function onClickBattle(e:ListEvent)
		{
			var item:BattlesListItem = e.itemRenderer as BattlesListItem;
			
			var toggleState:Boolean = item.battleData.BattleSelected ? false : true;
			trace( "BattleSelected :" + item.battleData.BattleSelected + ">>" + toggleState )
			item.battleData.BattleSelected = toggleState;
			item.listBattleSelect_mc.gotoAndPlay( toggleState ? "unChk" : "chkEnd" );
			
			ExternalInterface.call( "ASToggleBattle", item.battleData.BattleID, toggleState );
		}
	}
}