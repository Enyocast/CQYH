
package ActionScript3.Mall
{
	import ActionScript3.MyPanel;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import ActionScript3.Common.CustomSlider;
    import scaleform.clik.events.SliderEvent;
	
	public class MallEquipRolePanel extends MyPanel
	{
		public var onOff_mc:Button;
		public var role_turnright_mc:Button;
		public var role_turnleft_mc:Button;
		public var sendChat_mc:Button;
		public var ActorPic_mc:MovieClip;
		public var slider:CustomSlider;
		
		
		override protected  function configUI():void 
		{		
			trace("------MallFriendPanel  super.configUI:");
			super.configUI();			
			
			sendChat_mc.addEventListener(MouseEvent.CLICK, SendInfoToChat );
			onOff_mc.addEventListener(MouseEvent.CLICK, TakeOnOFf );
			
			role_turnleft_mc.addEventListener( ButtonEvent.PRESS , RoleTurnLeft );
			role_turnleft_mc.addEventListener( ButtonEvent.CLICK ,TurnRelease );
			role_turnleft_mc.addEventListener( ButtonEvent.RELEASE_OUTSIDE ,TurnRelease );
				
			role_turnright_mc.addEventListener( ButtonEvent.PRESS ,RoleTurnRight );
			role_turnright_mc.addEventListener( ButtonEvent.CLICK ,TurnRelease );
			role_turnright_mc.addEventListener( ButtonEvent.RELEASE_OUTSIDE ,TurnRelease );
			slider.addEventListener(SliderEvent.VALUE_CHANGE,changeHandler);
			slider.minimum=50;
			slider.maximum=100;
			slider.value=82;
			 ShowMode="BC";
			ExternalInterface.call("RegisterEquipRolePanel", this);
		}
		
		protected function changeHandler(e:SliderEvent):void
		{
			var v:Number=e.value;
			ActorPic_mc.scaleX=v/100;
			ActorPic_mc.scaleY=v/100;
			
		}

		public function SendInfoToChat()
		{
			ExternalInterface.call("ASClickSendToChat");
		}
		public function TakeOnOFf()
		{
			ExternalInterface.call("ASClickTakeOnOff");
		}
		public function RoleTurnRight()
		{
			ExternalInterface.call("ASClickTurnRight");
		}
		public function RoleTurnLeft()
		{
			ExternalInterface.call("ASClickTurnLeft");
		}
		function TurnRelease()
		{
			ExternalInterface.call("ASReleasTurn");
		}
	}
}