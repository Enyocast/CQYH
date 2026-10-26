package ActionScript3.Battle{
	import ActionScript3.MyItemSlotShow;
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	//import scaleform.clik.events.ButtonEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.Battle.BattleRandomSelect;
	import ActionScript3.Battle.BattleFreeSelect;
	import ActionScript3.MyItemSlotShow;

	public class BattlePanel extends MyPanel
	{
		//拖动按钮
		public var BtnDragBattlePanel:Button;
		//首先可入
		public var BtlQuickSelectBtn:Button;
		
		//战场选择按钮
		public var BtlBtns0:RadioButton;
		public var BtlBtns1:RadioButton;
		
		//随机战场
		public var RandomSelect_mc:BattleRandomSelect;
		//自选战场
		public var FreeSelect_mc:BattleFreeSelect;
		
		//团队加入
		public var BtlTeamJoinBtn:Button;
		//个人加入
		public var BtlSingleJoinBtn:Button;
		//离开
		public var BtlLeaveBtn:Button;
		
		//
		public var IsRandomMode:Boolean;
		
		override protected function configUI():void
		{
			super.configUI();
			
			ExternalInterface.call( "RegisterPVPBattle", this );
			
			BtlQuickSelectBtn.addEventListener( MouseEvent.CLICK, QuickSelectBattle );
			
			BtlBtns0.addEventListener( MouseEvent.CLICK, function _SelectBattle(e:Event){ SelectBattle(e,0);} );
			BtlBtns1.addEventListener( MouseEvent.CLICK, function _SelectBattle(e:Event){ SelectBattle(e,1);} );
			
			//BtlTeamJoinBtn.label = "小队加入";
			BtlTeamJoinBtn.addEventListener( "click", TeamJoin );
			
			//BtlSingleJoinBtn.label = "个人加入";
			BtlSingleJoinBtn.addEventListener( "click", SingleJoin );
			
			//BtlLeaveBtn.label = "离开队列";
			BtlLeaveBtn.addEventListener( "click", Leave );
			
			//
			ResetPanel();
		}
		//
		public function ResetPanel()
		{
			IsRandomMode = false;
			
			RandomSelect_mc.visible = false;
			FreeSelect_mc.visible = true;
		}
		//
		public function SetActive( isActive:Boolean )
		{
			if( isActive ){
				//SetPanelDrag( BtnDragBattlePanel );
				visible = true;
			}
			else{
				//SetPanelDrag( null );
				visible = false;
			}
		}
		//
		function QuickSelectBattle( e:Event )
		{
			/*
			if( !IsRandomMode ){
				SetBattlePanelMode( true );
			}
			*/
			
			ExternalInterface.call( "ASQuickSelectBattle" );
			//trace("RandomSelect_mc.visible :" + RandomSelect_mc.visible);
			//trace("FreeSelect_mc.visible :" + FreeSelect_mc.visible);
		}
		//
		function SelectBattle( e:Event, idx:int )
		{
			/*
			if( IsRandomMode ){
				SetBattlePanelMode( false );
			}
			*/
			
			ExternalInterface.call( "ASSelectBattle", idx );
		}
		//
		public function SetBattlePanelMode( isRandomSelect:Boolean )
		{
			IsRandomMode = isRandomSelect;
			
			RandomSelect_mc.visible = IsRandomMode;
			FreeSelect_mc.visible = !IsRandomMode;
		}
		//
		function TeamJoin( e:Event )
		{
			ExternalInterface.call( "ASTeamJoinBattle" );
		}
		//
		function SingleJoin( e:Event )
		{
			ExternalInterface.call( "ASSingleJoinBattle" );
		}
		//
		function Leave( e:Event )
		{
			ExternalInterface.call( "ASLeaveBattle" );
		}
		//
		public function UCFlashRandomBattleList( battlesData:Array):void
		{
			RandomSelect_mc.updateBattlesList( battlesData );
			//BattlePanel.UCFlashRandomBattleList( battlesData );
		}
		//
		public function UCSetBattlePanelMode( isRandom:Boolean ):void
		{
			//ExternalInterface.call( "ASTrace", "UCSetBattlePanelMode called" );
			SetBattlePanelMode( isRandom );
		}
	}
}