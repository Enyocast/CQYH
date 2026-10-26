package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import flash.display.MovieClip
	import flashx.textLayout.formats.Float;
	import ActionScript3.MyRuneButton;
	//import ActionScript3.MyRuneAvartaButton;
	import ActionScript3.Widget.MySkillPanel;
	import scaleform.clik.core.UIComponent;
	
	public class MySkillAvartaModify extends UIComponent
	{
		
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var innerFrameArrow_mc:MovieClip;
		public var mcHighLight:MovieClip;
		public var CurrentSpellSlot0:Button;
		public var CurrentSpellSlot1:Button;
		public var CurrentSpellSlot2:Button;

		public var spell0:RadioButton;
		public var spell1:RadioButton;
		public var spell2:RadioButton;
		public var spell3:RadioButton;
		public var spell4:RadioButton;
		
		
		public var avarta0:RadioButton;
		public var avarta1:RadioButton;
		public var avarta2:RadioButton;
		public var avarta3:RadioButton;
		public var avarta4:RadioButton;
		public var avarta5:RadioButton;
		public var avarta6:RadioButton;
		public var avarta7:RadioButton;
		public var avarta8:RadioButton;
		public var avarta9:RadioButton;

		public var CurrentAvartaSlotId:int;
		public var SelectAbilityId:int;
		
		public var btn_arrow1_left:Button;
		public var btn_arrow1_right:Button;
		
		public var btn_arrow2_left:Button;
		public var btn_arrow2_right:Button;

		function init()
		{
			//mapScroll_mc.SetHeight(530);
			
		}
		override protected  function configUI():void
		{
			super.configUI();

			btn_confirm.label="确认";
			btn_cancel.label="取消";

			btn_confirm.addEventListener( "click",ConfirmAbilityBtn );
			btn_cancel.addEventListener( "click",CancelAbilityBtn );
			
			btn_arrow1_left.addEventListener( "click",AvartaLastPage );
			btn_arrow1_right.addEventListener( "click",AvartaNextPage );
			
			btn_arrow2_left.addEventListener( "click",AvartaRuneLastPage );
			btn_arrow2_right.addEventListener( "click",AvartaRuneNextPage );
		}	
		
		public function AvartaLastPage()
		{
			ExternalInterface.call("ASAvartaLastPage",0);
		}
		
		public function AvartaNextPage()
		{
			ExternalInterface.call("ASAvartaNextPage",0);
		}
		
		public function AvartaRuneLastPage()
		{
			ExternalInterface.call("ASAvartaRuneLastPage",0);
		}
		
		public function AvartaRuneNextPage()
		{
			ExternalInterface.call("ASAvartaRuneNextPage",0);
		}

		public function SelectMainAvarta(  id:int )
		{
			trace("SelectMainAvarta() ::"+id);
			//var Obj:Button = ( Button )this.getChildByName("CurrentSpellSlot"+i);
			var tObj:Button;
			tObj = ( Button )( this["CurrentSpellSlot"+id] );
			var newPos:int =  tObj.x + tObj.width / 2.0 -110;
			//Tween 

			//背面光
			mcHighLight.x = newPos-mcHighLight.width / 2.0;
			//定位小箭头
			innerFrameArrow_mc.x = newPos-innerFrameArrow_mc.width / 2.0 
				//通知刷新
				CurrentAvartaSlotId = id;
			ExternalInterface.call("ASSetCurrentAvarta",CurrentAvartaSlotId );
		}

		public function ConfirmAbilityBtn()
		{
			trace("ConfirmAbilityBtn()::");
			parent['SpellConsole'].visible=true  ;
			parent['AvartaModify'].visible=false ;
			//  CurrentAvartaSlotId 上换成了 SelectAbilityId
			ExternalInterface.call("ASConfirmAvarta");
		}
		
		public function CancelAbilityBtn()
		{
			parent['SpellConsole'].visible=true  ;
			parent['AvartaModify'].visible=false ;
			ExternalInterface.call("ASSkillPageJump",0);
		}
	}
}