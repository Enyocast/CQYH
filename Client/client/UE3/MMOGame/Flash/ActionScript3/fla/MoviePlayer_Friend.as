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

	import ActionScript3.DropIcon;
	import ActionScript3.Friend.ContactWidget;
	import ActionScript3.Friend.ContactLevel;
	import ActionScript3.Friend.ContactListWidget;
	import flash.utils.getDefinitionByName;
	import ActionScript3.MyActivePanel;
	import ActionScript3.Widget.MyRClickMenu;
	import ActionScript3.MyIconConponent;
	import ActionScript3.Widget.MyDamageLevel;
	import scaleform.clik.controls.Button;
	import flash.display.DisplayObject;
	import flash.display.StageScaleMode;
	
	//import ActionScript3.Widget.ShopPanel;
	import ActionScript3.Friend.ContactListWidget;
	import ActionScript3.Friend.FriendChatHintPanel;
	
	import ActionScript3.fla.MoviePlayerBase;

	public class MoviePlayer_Friend extends MoviePlayerBase
	{
		public var ContactWidgetPanel:ContactListWidget;
		public var FriendChatHint:FriendChatHintPanel
		public var FriendChatLevel_mc:ContactLevel;
		public var chatContact_mc:ContactDialog;
		//var inited:Boolean = false;

		//override function initStage()
		//{			
			//ExternalInterface.call( "registerContactLevel" , FriendChatLevel_mc );
			
			//super.initStage();
		//}
	}
}