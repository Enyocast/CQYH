package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip
	import flashx.textLayout.formats.Float;
	import ActionScript3.MyRuneButton;
	import ActionScript3.MyRuneActiveButton;
	import ActionScript3.Widget.MySkillPanel;
	import scaleform.clik.core.UIComponent;
	
	public class MySkillPassiveModify extends UIComponent
	{
		
		public var btn_confirm:Button;
		public var btn_cancel:Button;

		public var innerFrameArrow_mc:MovieClip;
		public var mcHighLight:MovieClip;
		public var CurrentSpellSlot0:Button;
		public var CurrentSpellSlot1:Button;
		public var CurrentSpellSlot2:Button;

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
		public var spell10:Button;
		public var spell11:Button;
		public var spell12:Button;
		public var spell13:Button;
		public var spell14:Button;
		public var spell15:Button;
		public var spell16:Button;
		public var spell17:Button;
		public var spell18:Button;
		public var spell19:Button;

		public var CurrentPassiveSlotId:int;
		public var SelectAbilityId:int;

		
		function init()
		{
			//mapScroll_mc.SetHeight(530);
			
		}
		override protected  function configUI():void
		{
			super.configUI();

			btn_confirm.label="确认";
			btn_cancel.label="取消";

			btn_cancel.addEventListener( "click",CancelAbilityBtn );
			btn_confirm.addEventListener( "click",ConfirmAbilityBtn );
		}	


		public function SelectMainPassive(  id:int )
		{
			trace("SelectMainPassive() ::"+id);
			//var Obj:Button = ( Button )this.getChildByName("CurrentSpellSlot"+i);
			var tObj:Button;
			tObj = ( Button )( this["CurrentSpellSlot"+id] );
			var newPos:int =  tObj.x + tObj.width / 2.0 -100;
			//Tween 
			trace("===[tObj]"+tObj+"  [newPos]"+newPos +"  [HighLightHalfWidth]"+ mcHighLight.width / 2.0 );
			//背面光
			mcHighLight.x = newPos-mcHighLight.width / 2.0 ;
			//mcHighLight.x  =  tObj.x ;
			//定位小箭头
			innerFrameArrow_mc.x = newPos-innerFrameArrow_mc.width / 2.0 
			//通知刷新
			CurrentPassiveSlotId = id;
			ExternalInterface.call("ASSetCurrentPassive",CurrentPassiveSlotId );
		}
		public function ConfirmAbilityBtn()
		{
			trace("ConfirmAbilityBtn()::");
			parent['SpellConsole'].visible=true  ;
			parent['PassiveModify'].visible=false ;
			//  CurrentPassiveSlotId 上换成了 SelectAbilityId
			ExternalInterface.call("ASConfirmPassive");
		}

		public function CancelAbilityBtn()
		{
			parent['SpellConsole'].visible=true  ;
			parent['PassiveModify'].visible=false ;
			ExternalInterface.call("ASSkillPageJump",0);
		}
	}
}