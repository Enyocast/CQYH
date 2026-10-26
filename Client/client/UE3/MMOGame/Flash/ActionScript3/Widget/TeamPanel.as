package ActionScript3.Widget
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.display.MovieClip;
	import ActionScript3.Widget.MyTeamContent;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.Widget.MyNearbyTeamContent;


	public class TeamPanel extends MyPanel
	{
		public var myTeam_mc:MyTeamContent;
		public var nearbyPlayerContent_mc:MyNearbyPlayerContent;
		public var nearbyTeamContent_mc:MyNearbyTeamContent;

		public var tab0_mc:RadioButton;
		public var tab1_mc:RadioButton;
		public var tab2_mc:RadioButton;
		
/*		public var change_target_btn:Button;
		public var clear_target_btn:Button;
		public var team_target:TextField;*/
		
		override protected function configUI():void
		{
            ShowMode="BC";
			super.configUI();
			tab0_mc.addEventListener( MouseEvent.CLICK , ClickTab );
			tab0_mc.itemid = 0;
			tab1_mc.addEventListener( MouseEvent.CLICK , ClickTab );
			tab1_mc.itemid = 1;
			tab2_mc.addEventListener( MouseEvent.CLICK , ClickTab );
			tab2_mc.itemid = 2;
/*			if (change_target_btn)
			{
				change_target_btn.addEventListener(MouseEvent.CLICK, ClickChangeTeamTarget);
				clear_target_btn.addEventListener(MouseEvent.CLICK, ClickClearTeamTarget);
			}*/

			//SetPanelText( { panelName:"duiwu",buttonTeamExpand:"kuoz",buttonSaveName:"save",buttonLeaveTeam:"leave",;
			// buttonInvitePlayer:"invite",buttonEnterTeam:"enter"} );
		}

		private function ClickTab( e:MouseEvent ):void
		{
			if (e.target is Button)
			{
				ExternalInterface.call("ASTeamTabChange" , (e.target as Button).itemid );
			}
		}
		
		public function SetDropDownMenu( dat:Array ):void
		{
			if(myTeam_mc)
			{
				myTeam_mc.SetDropDownMenu(dat);
			}			
		}
		
		public function SetTeamAuctionColorLimit( idx:int ):void
		{
			if(myTeam_mc)
				myTeam_mc.SetTeamAuctionColorLimit(idx);
		}
		
/*		public function ClickChangeTeamTarget():void
		{
			ExternalInterface.call("ASClickChangeTeamTarget");
		}
		public function ClickClearTeamTarget():void
		{
			ExternalInterface.call("ASClickClearTeamTarget");
		}*/
		
		public function SetTeamTargetText(targetText:String):void
		{
/*			team_target.autoSize 	= 	TextFieldAutoSize.LEFT;
			team_target.wordWrap 	= 	true;
			team_target.htmlText 	= 	targetText;*/
		}
		
		public function addStringToField( tField:TextField, txtString:String, txtFormat:TextFormat):void
		{
			var index = tField.length;
			tField.appendText(txtString);
			//tField.setTextFormat(txtFormat,index,tField.length);
		}
		
		public function UCSetAutoTeamVisible(bl:Boolean):void
		{
			if(myTeam_mc)
			{
				myTeam_mc.UCSetAutoTeamVisible(bl);
			}
		}

		public function SetPanelText( data:Object ):void
		{
			this.SetWindowTitle(data.panelName);
			if (myTeam_mc)
			{
				myTeam_mc.btn_teamExpand.label = data.buttonTeamExpand;
				myTeam_mc.SaveNameButton.label = data.buttonSaveName;
				myTeam_mc.btn_leaveTeam.label = data.buttonLeaveTeam;
			}
			if (nearbyPlayerContent_mc)
			{
				nearbyPlayerContent_mc.InvitePlayer.label = data.buttonInvitePlayer;

			}
			if (nearbyTeamContent_mc)
			{
				nearbyTeamContent_mc.EnterTeam.label = data.buttonEnterTeam;
			}
			if (tab0_mc)
			{
				tab0_mc.label = data.tab0;
			}
			if (tab1_mc)
			{
				tab1_mc.label = data.tab1;
			}
			if (tab2_mc)
			{
				tab2_mc.label = data.tab2;
			}
		}
		public function UCSetOnLineState(nIndex:int,nType:int,bOnline:Boolean):void
		{
			if(myTeam_mc)
				myTeam_mc.SetOnLineState(nIndex,nType,bOnline);
		}
/*		function FindChild( obj:Object )
		{
			if ( obj is TextField )
			{
				trace( (obj as TextField).defaultTextFormat.font +":"+   (obj as TextField).name  );
			}
			else if ( obj is MovieClip )
			{
				var i:int;

				for (i = 0; i< (  obj as MovieClip ).numChildren; i++)
				{
					FindChild( (  obj as MovieClip ).getChildAt( i ) );
				}

			}
		}*/

	}
}