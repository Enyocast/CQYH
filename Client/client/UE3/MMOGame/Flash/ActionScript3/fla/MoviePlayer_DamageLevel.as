package ActionScript3.fla
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;
	
	
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.Label;

	import ActionScript3.Widget.TeamPanel;


	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import flash.ui.Mouse;
	//import flash.utils.tim
	import ActionScript3.DropIcon;
	//import ActionScript3.Widget.ContactWidget;
	//import ActionScript3.Widget.ContactLevel;
	//import ActionScript3.Widget.ContactListWidget;
	import flash.utils.getDefinitionByName;
	import ActionScript3.MyActivePanel;
	import ActionScript3.Widget.MyRClickMenu;
	import ActionScript3.MyIconConponent;
	import ActionScript3.Widget.MyDamageLevel;
	import scaleform.clik.controls.Button;
	import flash.display.DisplayObject;
	import flash.display.StageScaleMode;
	//import ActionScript3.Widget.FriendChatHintPanel;
	//import ActionScript3.Widget.TaskPopPanel;
	import ActionScript3.Widget.ShopPanel;
	import ActionScript3.Widget.MyDamageLevel;
	import ActionScript3.fla.MoviePlayerBase;
	import ActionScript3.MyPanel;


	public class MoviePlayer_DamageLevel extends MoviePlayerBase
	{
		public var DamageLevel_mc:MyDamageLevel ;
		
		//var timerTest:Timer = new Timer(33);

		override function initStage()
		{			
			
			ExternalInterface.call( "RegisterDamageLevel" , DamageLevel_mc );			
			
			super.initStage();
			
			//DamageLevel_mc.AddNewAttack(100,100,999, 0,0,0 );
			//timerTest.addEventListener(TimerEvent.TIMER, updateTest);
			//timerTest.start();
		}
		
		//public function updateTest()
		//{
		//	DamageLevel_mc.UpdatePos(0.033);
		//}


	}
}