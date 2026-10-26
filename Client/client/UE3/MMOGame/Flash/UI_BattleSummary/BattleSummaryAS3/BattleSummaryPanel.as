package UI_BattleSummary.BattleSummaryAS3
{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import UI_BattleSummary.BattleSummaryAS3.BtlScoreListPanel;
	import UI_BattleSummary.BattleSummaryAS3.BtlDescPanel;
	
	public class BattleSummaryPanel extends MyPanel
	{
		public var iCurTab:int;
		
		//public var ToggleSummary_btn:Button;
		public var tab0_mc:MyTipButton;
		public var tab1_mc:MyTipButton;
		
		public var BattlePanelBg_mc:MovieClip;
		
		//leave battle button
		public var LeaveBattle_btn:Button;
		public var Toggle_btn:Button;
		
		//
		public var TeamScore_mc:MovieClip;
		//
		public var BattleScorePanelMC:BtlScoreListPanel;
		public var BattleDescPanelMC:BtlDescPanel;

		override protected function configUI():void
		{
			super.configUI();
			//
			
			ExternalInterface.call( "RegisterBattleSummary", this );
			//
			
			//tab0_mc.MWTabIcon_mc.gotoAndStop("battle0");
			//tab1_mc.MWTabIcon_mc.gotoAndStop("battle1");
			tab0_mc.addEventListener( MouseEvent.CLICK, function _contentChange(e:Event){ contentChange(e,0);} );
			tab1_mc.addEventListener( MouseEvent.CLICK, function _contentChange(e:Event){ contentChange(e,1);} );
			
			LeaveBattle_btn.addEventListener( MouseEvent.CLICK, LeaveBattle );
			//
			Toggle_btn.addEventListener( MouseEvent.CLICK, ToggleThisPanel );
			UCShowContent(0);
			
			//
			TeamScore_mc.teamNum_mc2.Init( 6, 17, false );
			TeamScore_mc.teamNum_mc1.Init( 6, 17, true );
			//TeamScore_mc.teamNum_mc2.SetNumber( 1 );
			//TeamScore_mc.teamNum_mc1.SetNumber( 0 );
			
			//test
			//UCSetScore( 1, 10000 );
			//UCSetScore( 2, 10000 );
		}
		//
		function contentChange( e:Event, idx:int )
		{
			//UCShowContent( idx );
			//
			ExternalInterface.call( "ASUpdateBattleSummary", idx );
		}
		//
		public function UCSetScore( teamIdx:int, score:int ):void
		{
			if( teamIdx == 2 ){
				TeamScore_mc.teamNum_mc2.SetNumber( score );
			}
			else{
				TeamScore_mc.teamNum_mc1.SetNumber( score );
			}
		}
		//
		public function UCShowContent( idx:int )
		{
			iCurTab = idx;

			tab0_mc.selected = false;
			tab1_mc.selected = false;
			
			switch( iCurTab )
			{
				case 0:
				tab0_mc.selected = true;
				BattleScorePanelMC.visible = true;
				BattleDescPanelMC.visible = false;
				
				//SetPanelDrag( BattleScorePanelMC.BtnDragPanel );
				break;
				
				case 1:
				tab1_mc.selected = true;
				BattleScorePanelMC.visible = false;
				BattleDescPanelMC.visible = true;
				
				//SetPanelDrag( BattleScorePanelMC.BtnDragPanel );
				break;
				
				default:
				break;
			}
		}
		//
		public function UCFlashBattleScoreList( scoreData:Array):void
		{
			BattleScorePanelMC.updateScoreList( scoreData );
		}
		/*
		function ToggleBattleSummary( e:Event ):void
		{
			ExternalInterface.call( "ToggleBattleSummary" );
		}
		*/
		//
		function LeaveBattle( e:Event ):void
		{
			ExternalInterface.call( "ASLeaveBattle" );
		}
		//
		function ToggleThisPanel( e:Event ):void
		{
			ExternalInterface.call( "ASOnPanelClose" , PanelName);
		}
	}
}