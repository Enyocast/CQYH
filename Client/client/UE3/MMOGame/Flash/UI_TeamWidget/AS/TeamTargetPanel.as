package UI_TeamWidget.AS{
	
	import ActionScript3.MyPanel;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	public class TeamTargetPanel extends MyPanel
	{
		public var DropdownMenu_mc:DropdownMenu;
		public var activity_fb_tab:RadioButton;
		public var activity_tab:RadioButton;
		public var fb_tab:RadioButton;
		public var ok_btn:Button;
		public var cancel_btn:Button;
		//public var detail:TeamDetail;
		
		public var item_test:TeamFBListItem;
		public var target_list:ScrollingList;
		
		public var targetId:int = -1;
		public var targetType:int = -1;
		
		public var bSkipOnce = false;
		var activityLastTarget:TeamFBListItem = null;
		
		override protected  function configUI():void 
		{		
		    ShowMode="BC";
			super.configUI();
			activity_fb_tab.selected = true;
			
			ok_btn.addEventListener(MouseEvent.CLICK, onClickChangeTargetOk);
			cancel_btn.addEventListener(MouseEvent.CLICK, onClickChangeTargetCancel);
			target_list.addEventListener(ListEvent.ITEM_CLICK, onListItemClick);
			activity_fb_tab.addEventListener(MouseEvent.CLICK, onClickShowActivityFBTargetList);
			activity_tab.addEventListener(MouseEvent.CLICK, onClickShowActivityTargetList);
			fb_tab.addEventListener(MouseEvent.CLICK, onClickShowFBTargetList);
			
			DropdownMenu_mc.addEventListener(Event.CHANGE , onFBDifficultyFilterChange);
			
			//testData();
		}
		
/*		private function testData():void
		{
				var dataR:Array = [];
				for(var n:int = 0; n < 15; ++n)
				{
					var da:Object = new Object;
					da.difficulty = 2;
					da.text_0 = n.toString();
					da.text_1 = "13";
					da.text_2 = "14";
					dataR.push(da);
				}
				UCUpdateTargetList(dataR);
		}*/
		
		private function onClickChangeTargetOk(evt:MouseEvent):void
		{
			item_test.testFunc();
			ExternalInterface.call("ASClickChangeTargetOk", targetType, targetId);
		}
		
		private function onClickChangeTargetCancel(evt:MouseEvent):void
		{
			ExternalInterface.call("ASCancelChangeTarget");
		}
		
		public function UCUpdateTargetList(data:Array):void
		{
			activityLastTarget = null;
			//detail.SetTeamGroupListData(data);
			target_list.dataProvider = new DataProvider(data);
			target_list.validateNow();
			target_list.invalidateData();
		}
		
		public function UCUpdateDifficultyFilterDropDown(data:Object):void
		{
			DropdownMenu_mc.datastring = data.StringData;
			DropdownMenu_mc.SplitData();
			
			if(DropdownMenu_mc.selectedIndex != data.SelectedIndex)
			{
				bSkipOnce = true;
				DropdownMenu_mc.selectedIndex = data.SelectedIndex;
			}
				
			if(data.EnableDropDown)
			{
				DropdownMenu_mc.enabled = true;
			}
			else
			{
				DropdownMenu_mc.enabled = false;
			}
		}
		
		private function onClickShowActivityFBTargetList(evt:MouseEvent):void
		{
			DropdownMenu_mc.enabled = false;
			ExternalInterface.call("ASShowActivityFBTargetList");
		}
		
		private function onClickShowActivityTargetList(evt:MouseEvent):void
		{
			DropdownMenu_mc.enabled = false;
			ExternalInterface.call("ASShowActivityTargetList");
		}
		
		private function onClickShowFBTargetList(evt:MouseEvent):void
		{
			DropdownMenu_mc.enabled = true;
			ExternalInterface.call("ASShowFBTargetList", DropdownMenu_mc.selectedIndex);
		}
		
		private function onFBDifficultyFilterChange(e:Event):void
		{
			if(bSkipOnce)
			{
				bSkipOnce = false;
			}
			else
			{
				if(DropdownMenu_mc.enabled)
					ExternalInterface.call("ASShowFBTargetList", DropdownMenu_mc.selectedIndex);
			}
		}
		
		private function onListItemClick( event:ListEvent ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var activityTarget:TeamFBListItem = event.itemRenderer as TeamFBListItem;
			    if(activityTarget)
			    {
				   targetId = activityTarget.targetId;
				   targetType = activityTarget.targetType;
			    }
				list.invalidateData();
			}
		}
	}
}