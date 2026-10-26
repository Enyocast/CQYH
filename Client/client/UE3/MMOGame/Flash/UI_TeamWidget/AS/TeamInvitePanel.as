package UI_TeamWidget.AS{
	
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import flash.display.MovieClip;
	import scaleform.clik.events.ButtonEvent;
	
	public class TeamInvitePanel extends MyPanel
	{
		public var invite_btn:Button;
		public var cancel_btn:Button;
		public var friend_tab:RadioButton;
		public var recent_tab:RadioButton;
		public var guid_tab:RadioButton;
		public var tabTitle:MovieClip
		/*public var Btn_Sort0:Button;
		public var Btn_Sort1:Button;
		public var Btn_Sort2:Button;
		public var Btn_Sort3:Button;
		public var Btn_Sort4:Button;
		*/
		public var Invite_List:ScrollingList;
		
		override protected  function configUI():void 
		{		
		    ShowMode="BC";
			super.configUI();
			friend_tab.addEventListener(ButtonEvent.CLICK, onTabClickHandler);
			recent_tab.addEventListener(ButtonEvent.CLICK, onTabClickHandler );
			guid_tab.addEventListener(ButtonEvent.CLICK, onTabClickHandler );
			
			invite_btn.addEventListener(MouseEvent.CLICK, onClickInvite);
			cancel_btn.addEventListener(MouseEvent.CLICK, onClickCancel);
			friend_tab.selected = true;
		    
			//UCUpdateTitle("YaoQing");
		}
		
		public function UCUpdateTitle(titleStr:String):void
		{
			SetWindowTitle(titleStr);
		}

		private function onTabClickHandler(evt:ButtonEvent):void
		{
			var btn:RadioButton=evt.currentTarget as RadioButton;
			if(btn && btn.selected==true)
			{
				if(btn == friend_tab)
				{
					ExternalInterface.call("ASShowInviteFriendList");
				}
				else if(btn==recent_tab){
					ExternalInterface.call("ASShowInviteRecentList");
				}else{
					ExternalInterface.call("ASShowInviteGuiderList");
				}
			}
		}
		
		private function onClickInvite(evt:MouseEvent):void
		{
			ExternalInterface.call("ASClickInviteOk");
		}
		
		private function onClickCancel(evt:MouseEvent):void
		{
			ExternalInterface.call("ASClickInviteCancel");
		}
		
		public function UCUpdateInvitePlayerList(data:Array):void
		{
			Invite_List.dataProvider = new DataProvider(data);
			Invite_List.validateNow();
			Invite_List.invalidateData();
		}
	}
}