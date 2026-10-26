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
	import ActionScript3.Widget.NormalPracticePanel;
	import ActionScript3.Widget.FastPracticePanel;
	import scaleform.clik.core.UIComponent;
	

	public class MySkillActiveModify extends UIComponent
	{
		public var NormalPractice:NormalPracticePanel;
		public var FastPractice:FastPracticePanel;
		public var btn_NormalPractice:Button;
		public var btn_FastPractice:Button;
		
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var CurrentSpellSlot:Button;
		public var btn_arrow_left:Button;
		public var btn_arrow_right:Button;

		public var ActivePageNum:TextField;

		public var spell0:Button;
		public var spell1:Button;
		public var spell2:Button;
		public var spell3:Button;
		public var spell4:Button;
		public var spell5:Button;
		public var spell6:Button;
		public var spell7:Button;
		public var spell8:Button;
		public var spell9:Button;

		public var btn_rune0:MyRuneButton;
		public var btn_rune1:MyRuneButton;
		public var btn_rune2:MyRuneButton;
		public var btn_rune3:MyRuneButton;
		public var btn_rune4:MyRuneButton;

		public var btn_active0:MyRuneActiveButton;
		public var btn_active1:MyRuneActiveButton;
		public var btn_active2:MyRuneActiveButton;
		public var btn_active3:MyRuneActiveButton;
		public var btn_active4:MyRuneActiveButton;

		public var CurrentActiveSlotId:int;
		public var SelectAbilityId:int;
		
		public var highlight:MovieClip;
		public var mask_fill:MovieClip;
		public var tF_spellPoint:TextField;
		
		var OriX:int;
		var MaskWidth:int;
		var HighLightWidth:int;
		var IsDebug:Boolean;
		
		public function UcEnableSkillUp( enable:Boolean )
		{
			btn_NormalPractice.enabled =  enable;
			btn_FastPractice.enabled =  enable;
		}

		public function SetSkillPoint( SPoint:int ,SkillProgress:int )
		{
			IsDebug = false;
			trace("SetSkillPoint" +SkillProgress );
			if( SkillProgress < 0 )
				SkillProgress = 0;
			else if( SkillProgress > 100 )
				SkillProgress = 100;
			tF_spellPoint.text = String( SPoint );
			mask_fill.x = OriX - (100-SkillProgress )*0.01* MaskWidth;
			if( SkillProgress < 10 )
			{
				highlight.visible = false;
			}
			else
			{
				highlight.visible = true;
				highlight.x = mask_fill.x + MaskWidth -HighLightWidth;
			}
		}

		function init()
		{
			//mapScroll_mc.SetHeight(530);

		}
		override protected  function configUI():void
		{
			super.configUI();

			btn_confirm.addEventListener( "click",ConfirmAbilityBtn );
			btn_cancel.addEventListener( "click",CancelAbilityBtn );
			btn_arrow_left.addEventListener( "click",ActiveLastPage );
			btn_arrow_right.addEventListener( "click",ActiveNextPage );
			btn_NormalPractice.addEventListener( "click",ClickNormalPractice );
			btn_FastPractice.addEventListener( "click",ClickFastPractice );
			
			
			NormalPractice.visible = false;
			FastPractice.visible = false;
			
			OriX = mask_fill.x;
			MaskWidth = mask_fill.width;
			HighLightWidth = highlight.width;
			trace("Active Modify 0==========================");

			btn_confirm.label="确认";
			btn_cancel.label="取消";

			trace("Active Modify 1==========================");

			/*btn_rune0.SetCurDur(2003,10,10,true);
			btn_rune1.SetCurDur(2003,1,20,true);
			btn_rune2.SetCurDur(2004,0,30,true);
			btn_rune3.SetCurDur(2005,0,40,false);
			btn_rune4.SetCurDur(2006,10,50,false);*/
			SetActivePageNum(1,1);
			SetSkillPoint( 0, 0 );
			trace("Active Modify 2==========================");

			//trace("MySkillPanel::configUI ended");	
		}	
		
		public function ClickNormalPractice( )
		{
			if( IsDebug )
			{
				NormalPractice.visible = !NormalPractice.visible;
				if( NormalPractice.visible )
				{
					NormalPractice.SetNormalPracticeData( 1003,true, "65min20s",80,2,true);
					NormalPractice.SetPercent(2,40,100);
				}
			}
			ExternalInterface.call("ASClickNormalPractice",true );
		}
		
		public function ClickFastPractice( )
		{
			if( IsDebug )
			{
				FastPractice.visible = !FastPractice.visible;
				if( FastPractice.visible )
				{
					FastPractice.SetFastPracticeData( 1003,80);
					FastPractice.SetPercent(1,30,100);
					FastPractice.SetStarted( true );
				}
			}
			ExternalInterface.call("ASClickFastPractice",true );
		}
		
		public function SelectMainActive(  id:int )
		{
			trace("SelectMainActive() ::"+id);
			//Tween 
			//通知刷新
			CurrentActiveSlotId = id;
			ExternalInterface.call("ASSetCurrentActive",CurrentActiveSlotId );
		}

		public function ConfirmAbilityBtn()
		{
			trace("ConfirmAbilityBtn()::");
			if( parent['SpellConsole'] != null )
				parent['SpellConsole'].visible=true  ;
			else
				trace("Can't find SpellConsole");
			parent['ActiveModify'].visible=false ;
			//  CurrentActiveSlotId 上换成了 SelectAbilityId
			ExternalInterface.call("ASConfirmActive");
		}

		public function CancelAbilityBtn()
		{
			parent['SpellConsole'].visible=true  ;
			parent['ActiveModify'].visible=false ;
			ExternalInterface.call("ASSkillPageJump",0);
		}

		public function ActiveLastPage()
		{
			ExternalInterface.call("ASActiveLastPage",0);
		}

		public function ActiveNextPage()
		{
			ExternalInterface.call("ASActiveNextPage",0);
		}

		public function SetActivePageNum(  iNow:int,iTotal:int )
		{
			ActivePageNum.text= iNow+"/"+iTotal;
		}

		public function UnselecteAllRune()
		{
			trace("====UnselecteAllRune()");
			btn_rune0.selected = false;
			btn_rune1.selected = false;
			btn_rune2.selected = false;
			btn_rune3.selected = false;
			btn_rune4.selected = false;
		}
	}
}