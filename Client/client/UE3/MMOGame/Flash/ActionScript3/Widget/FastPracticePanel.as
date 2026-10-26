package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip
	import flash.text.TextField;
	import flashx.textLayout.formats.Float;
	import ActionScript3.MyRuneButton;
	import ActionScript3.MyRuneActiveButton;
	import ActionScript3.Widget.MySkillPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.RadioButton;
	import flash.events.Event;
	import scaleform.clik.controls.ButtonGroup;

	public class FastPracticePanel extends MyPanel
	{
		public var btn_Enter:Button;
		public var btn_Stop:Button;
		public var btn_Close:Button;
		public var ActiveSlot:MyItemSlot;
		public var CostType0:RadioButton;
		public var CostType1:RadioButton;
		public var Item0:Button;
		public var Item1:Button;
		public var Item2:Button;
		//public var Item3:MovieClip;
		public var Progress:MovieClip;
		public var ListGroup:ButtonGroup;
		public var NowActiveId:int;
		public var IsStarted:Boolean;
		public var SkillPercent:int;
		public var ani_mc:MovieClip;

		function init()
		{

		}

		override protected function configUI():void
		{
			super.configUI();
			
			NowActiveId = 0;
			IsStarted = false;
			SkillPercent = 0;
			
			btn_Enter.addEventListener( "click", ConfirmFastPractice );
			btn_Stop.addEventListener( "click", StopFastPractice );
			btn_Close.addEventListener( "click", Close );
			
			Item0.addEventListener( "click", UseFastPracticeItem );
			Item1.addEventListener( "click", UseFastPracticeItem );
			Item2.addEventListener( "click", UseFastPracticeItem );
			
			ListGroup = ButtonGroup.getGroup("FastPractice", this);
			ListGroup.addEventListener(Event.CHANGE, handleGroup1Change, false, 0, true);

			ExternalInterface.call("SetLabelByID", CostType0, "MMOGame.Skill.FastSkillUpType0" );
			ExternalInterface.call("SetLabelByID", CostType1, "MMOGame.Skill.FastSkillUpType1" );
			
			CostType1['gold_mc'].gotoAndStop(2);
		}
		
		public function UseFastPracticeItem( e:Event )
		{
			trace("UseFastPracticeItem " +e );
			ExternalInterface.call("ASUseFastPracticeItem",(e.target as Button).itemid );
		}
		
		protected function handleGroup1Change( event:Event ):void 
		{
			//trace("NormalPractice's selectedIndex changed: " + ListGroup.selectedIndex);
			ExternalInterface.call("ASChooseNormalParcticeType",ListGroup.selectedIndex +1 );
		}
		
		
		public function Close()
		{
			if( !IsStarted )
			{
				ClosePanel()
			}
			else
			{
				// 1为心练 2为魂练
				ExternalInterface.call("ASStopPracticeAndClose",NowActiveId,2 );
			}
		}
		
		public function ClosePanel()
		{
			if( parent['NormalPractice'].visible )
				parent['NormalPractice'].Move2R( false );
			this.visible = false;
		}

		public function ConfirmFastPractice()
		{
			//this.visible = false;
			ExternalInterface.call("ASStartFastPractice");
		}

		public function StopFastPractice()
		{
			//this.visible = false;
			ExternalInterface.call("ASStopPractice",NowActiveId );
		}
		
		//魂练既然开始传入 则一定开始
		public function SetFastPracticeData( inActiveId:int, inPrecent:int )
		{
			trace("SetFastPracticeData() ActiveId:" , inActiveId , "  InPercent:" , inPrecent );
			NowActiveId = inActiveId;
			this.visible = true;
			//只有面板开着的状态才会魂练
			ListGroup.setSelectedButtonByIndex( 0 );
		}
		
		public function SetStarted( inStarted:Boolean )
		{
			IsStarted = inStarted;
			if( IsStarted )
			{
				btn_Enter.visible = false;
				btn_Stop.visible  = true ;
				CostType0.enabled = false;
				CostType1.enabled = false;
				Item0.enabled = true;
				Item1.enabled = true;
				Item2.enabled = true;
				trace(" Ani_mc Play Nooraml");
				ani_mc.gotoAndPlay("normal");
			}
			else
			{
				btn_Enter.visible = true ;
				btn_Stop.visible  = false;
				CostType0.enabled = true;
				CostType1.enabled = true;
				Item0.enabled = false;
				Item1.enabled = false;
				Item2.enabled = false;
				ani_mc.gotoAndStop( 0 );
			}
		}
		
		public function SetPercent( NowLv:Number,NowProgress:Number,MaxProgress:Number )
		{
			var Percent:Number;
			Percent = ( NowProgress / MaxProgress )*100;
			trace("NormalPracticePanel SetPercent" +Percent );
			
			if( Percent >=0 && Percent <= 100  )
			{
				if( !Progress.visible  )
					Progress.visible  = true;
				SkillPercent = Percent;
				Progress.SetPercent( NowLv, NowProgress, MaxProgress );
			}
			else
			{
				Progress.visible  = false;
			}
		}
	}
}