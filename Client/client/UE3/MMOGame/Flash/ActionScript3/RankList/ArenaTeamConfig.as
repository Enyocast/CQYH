package ActionScript3.RankList
{
	
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import ActionScript3.TreeListData;
	import flash.text.TextField;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.MyTipButton;
	
	
	public class ArenaTeamConfig extends MyPanel
	{
		public var srollinglist_mc:ScrollingList;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			this.MyWindowsFrame_mc.btn_close.visible=false;
			(this.MyWindowsFrame_mc.getChildByName("divide") as MovieClip).visible=false;
			srollinglist_mc.addEventListener(ListEvent.ITEM_CLICK, OnArenaListItemClick);
		}
		
		public function UCUpdateConfigListData( data:Array ):void
		{
			if(null != data && srollinglist_mc != null)
			{
				srollinglist_mc.dataProvider = new DataProvider(data);
				srollinglist_mc.validateNow();
				srollinglist_mc.invalidateData();
			}
			else
				trace("ArenaTeamConfig->UpdateConfigListData failed!");
		}
		
		private function OnArenaListItemClick(e:ListEvent):void
		{
			//var listItem:ListItem_Person = e.itemRenderer as ListItem_Person;
			//if(null != listItem)
				//ExternalInterface.call( "ASPersonListItemClick", listItem.PersonData.Id);
		}
		
	}
	
}
