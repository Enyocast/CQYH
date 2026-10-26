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

	public class NormalPracticePanel extends MyPanel
	{
		public var btn_Enter:Button;
		public var btn_Stop:Button;
		public var btn_Close:Button;
		public var ActiveSlot:MyItemSlot;
		public var CostType0:RadioButton;
		public var CostType1:RadioButton;
		public var CostType2:RadioButton;
		public var timeLeft_mc:MovieClip;
		public var Progress:MovieClip;
		public var ListGroup:ButtonGroup;
		public var NowActiveId:int;
		public var IsStarted:Boolean;
		public var SkillPercent:int;
		public var ani_mc:MovieClip;
		var OriX:int;
		
		function init()
		{
		

		}
		
		override protected  function configUI():void
		{
			super.configUI();
			
			NowActiveId = 0;
			IsStarted = false;
			SkillPercent = 0;
			
			btn_Enter.addEventListener( "click",ConfirmNormalPractice );
			btn_Stop.addEventListener( "click",StopNormalPractice );
			btn_Close.addEventListener( "click",Close );
			
			//CostType0.addEventListener( "click",ChooseNormalParcticeType );
			
			ListGroup = ButtonGroup.getGroup("NormalPractice", this);
			ListGroup.addEventListener(Event.CHANGE, handleGroup1Change, false, 0, true);

			ExternalInterface.call("SetLabelByID",CostType0,"MMOGame.Skill.NormalSkillUpType0" );
			ExternalInterface.call("SetLabelByID",CostType1,"MMOGame.Skill.NormalSkillUpType1" );
			ExternalInterface.call("SetLabelByID",CostType2,"MMOGame.Skill.NormalSkillUpType2" );
			OriX = this.x;
			
			trace("NormalPracticePanel ListGroup Length:"+ListGroup.length );
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
				ExternalInterface.call("ASStopPracticeAndClose",NowActiveId,1 );
			}
		}
		
		public function ClosePanel()
		{
			this.visible = false;
		}
		
		public function ChooseNormalParcticeType( evt:Event )
		{
			ExternalInterface.call("ASChooseNormalParcticeType",evt.target );
		}

		public function ConfirmNormalPractice()
		{
			//this.visible=false ;
			ExternalInterface.call("ASStartNormalPractice");
		}
		
		public function StopNormalPractice()
		{
			//this.visible=false ;
			ExternalInterface.call("ASStopPractice",NowActiveId );
		}
		
		public function SetNormalPracticeData( inActiveId:int,HasFastPracticing:Boolean,TimeLeft:String,
											inPercent:int,inType:int,IsPracticing:Boolean )
		{
			trace("SetNormalPracticeData() ");
			this.visible = true;
			NowActiveId = inActiveId;
			SetStarted( IsPracticing );
			timeLeft_mc.tF_timeLeft.text = TimeLeft;
			Move2R( parent['FastPractice'].visible );
			//Move2R( HasFastPracticing );
			if( inType < 0 )
				inType = 0;
			else if( inType > ListGroup.length )
				inType = ListGroup.length;
			ListGroup.setSelectedButtonByIndex( inType-1 );
		}
		
		public function SetStarted( inStarted:Boolean )
		{
			IsStarted = inStarted;
			if( IsStarted )
			{
				btn_Enter.visible = false;
				btn_Stop.visible  = true ;
				timeLeft_mc.visible  = true;
				CostType0.enabled = false;
				CostType1.enabled = false;
				CostType2.enabled = false;
				ani_mc.gotoAndPlay("normal");
				
			}
			else
			{
				btn_Enter.visible = true ;
				btn_Stop.visible  = false;
				timeLeft_mc.visible  = false;
				CostType0.enabled = true;
				CostType1.enabled = true;
				CostType2.enabled = true;
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
		
		public function Move2R( IsMove:Boolean )
		{
			if( IsMove )
			{
				this.x = OriX + this.width;
			}
			else
			{
				this.x = OriX;
			}
		}

	}
}