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
	import flash.ui.Mouse;
	//import flash.utils.tim
	import ActionScript3.DropIcon;
	
	import flash.utils.getDefinitionByName;
	import ActionScript3.MyActivePanel;
	import ActionScript3.Widget.MyRClickMenu;
	import ActionScript3.MyIconConponent;
	import ActionScript3.Widget.MyDamageLevel;
	import scaleform.clik.controls.Button;
	import flash.display.DisplayObject;
	import flash.display.StageScaleMode;
	
	import ActionScript3.Widget.ShopPanel;
	
	
	import ActionScript3.fla.MoviePlayerBase;
	import ActionScript3.MyPanel;
	import ActionScript3.MsgInfo.MsgInfoPanel;

	public class MoviePlayer_MsgInfo extends MoviePlayerBase
	{
		public var MessageInfo_mc:MsgInfoPanel;

		//var inited:Boolean = false;

		override function initStage()
		{			
			//trace("init");

			
			
			super.initStage();
		}


	}
}