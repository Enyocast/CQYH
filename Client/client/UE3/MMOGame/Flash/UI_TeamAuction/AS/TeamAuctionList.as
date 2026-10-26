package UI_TeamAuction.AS
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;

	public class TeamAuctionList extends MyPanel
	{
		public var AcutionList_lst:ScrollingList;
		public var giveUpAll_btn:Button;

		override protected function configUI():void
		{
			super.configUI();
			SetWindowTitle("组队拍卖");
			giveUpAll_btn.addEventListener(MouseEvent.CLICK, ClickGiveUpAll);
			AcutionList_lst.addEventListener(ListEvent.ITEM_CLICK, handleListItemClick, false, 0, true);
		}

		public function updateData(AcutionListData:Array):void
		{
			AcutionList_lst.dataProvider = new TreeDataProvider(AcutionListData);
			AcutionList_lst.validateNow();
			AcutionList_lst.invalidateData();
		}
		
		//放弃全部
		private function ClickGiveUpAll(e:MouseEvent):void 
		{
			ExternalInterface.call("ASTeamAuctionGiveUpAll");
		}
		
		private function handleListItemClick(event:ListEvent):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}
	}
}