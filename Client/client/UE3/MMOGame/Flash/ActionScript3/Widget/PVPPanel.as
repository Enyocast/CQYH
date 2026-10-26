package ActionScript3.Widget{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.display.MovieClip;
	//import ActionScript3.MyItemSlotShow;
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	//import ActionScript3.Battle.BattlePanel;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	//import ActionScript3.Battle.BattleRandomSelect;
	import ActionScript3.Battle.BattleTeamPanel;
	import ActionScript3.Battle.ArenaPanel;
	
	public class PVPPanel extends MyPanel
	{
		public var iCurTab:int;
		//public var tab0_mc:MyTipButton;
		//public var tab1_mc:MyTipButton;
		//public var BattlePanelMC:BattlePanel;
		public var ArenaPanel_mc:ArenaPanel;

		override protected function configUI():void
		{
			super.configUI();
			//
			
			//tab0_mc.MWTabIcon_mc.gotoAndStop("battle2");
			//tab1_mc.MWTabIcon_mc.gotoAndStop("battle3");
			
			ExternalInterface.call( "RegisterPVP", this );
			
			//
			//tab0_mc.addEventListener( "click", function _contentChange(e:Event){ contentChange(e,0);} );
			//tab1_mc.addEventListener( "click", function _contentChange(e:Event){ contentChange(e,1);} );

			//ShowContent(0);
			ArenaPanel_mc.visible = true;
		}
		/*
		//
		function contentChange( e:Event, idx:int )
		{
			ShowContent( idx );
			//
			//ExternalInterface.call( "UpdatePVPPanel", iCurTab );
		}
		//
		function ShowBattlePanel()
		{
			tab0_mc.selected = true;
			if( BattlePanelMC )
			{
				BattlePanelMC.SetActive( true );				
				SetPanelDrag( BattlePanelMC.BtnDragBattlePanel );
				ArenaPanel_mc.visible = false;
			}
		}
		
		function ShowArenaPanel()
		{
			tab1_mc.selected = true;
			if( BattlePanelMC )
			{
				BattlePanelMC.SetActive( false );				
				SetPanelDrag( null );
				ArenaPanel_mc.visible = true;
			}
		}
		
		public function ShowContent( idx:int )
		{
			iCurTab = idx;

			tab0_mc.selected = false;
			tab1_mc.selected = false;
			
			switch( iCurTab )
			{
				case 0:
					ShowBattlePanel();
				
				break;
				
				case 1:
					ShowArenaPanel();
				break;
				
				default:
				break;
			}
		}
		*/
	}
}