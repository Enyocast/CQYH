package ActionScript3.Battle
{

	import ActionScript3.MyItemSlotShow;
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
	import scaleform.clik.core.UIComponent;
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;

	public class ArenaHint extends MyPanel
	{
		//public var MyTeamItem0:UIComponent;
		//public var MyTeamItem1:UIComponent;
		//public var MyTeamItem2:UIComponent;
		//public var MyTeamItem3:UIComponent;
		//public var MyTeamItem4:UIComponent;

		public var LeaveButton:Button;
		//public var MinimizeButton:Button;

		public var BaseIconButton:Button;
		//public var TeamItemList:Array;
		public var hint:MovieClip;

		override protected function configUI():void
		{
			super.configUI();

			if (LeaveButton)
			{
				LeaveButton.addEventListener(MouseEvent.CLICK , clickLeave , false , 0 , true );
				LeaveButton.visible = false;
			}

			if (BaseIconButton)
			{
				BaseIconButton.addEventListener( MouseEvent.CLICK , clickIcon , false , 0 , true );
				BaseIconButton.addEventListener( MouseEvent.MOUSE_OVER , overIcon , false , 0 , true );
				BaseIconButton.addEventListener( MouseEvent.MOUSE_OUT , outIcon , false , 0 , true );
			}

			if (hint)
			{
				hint.visible = false;
			}
			

			ExternalInterface.call( "RegisterArenaHint", this );

			//SetHint( {title:"1V1ÅŶÓ",content:"ÄÍÐĵȴý"} );
			//setTeamNum(1);
			//setTeamMember( 0 , "haha" , "´̿Í" , 20 , false);
		}

		function clickIcon( e:Event )
		{

			ExternalInterface.call( "ASArenaHintClickIcon", this );
		}

		function overIcon( e:Event )
		{
			if (hint)
			{
				hint.visible = true;
			}
		}

		function outIcon( e:Event )
		{
			if (hint)
			{
				hint.visible = false;
			}

		}

		public function SetHintText( data:Object )
		{
			if (hint)
			{
				var title = hint.getChildByName("title") as TextField;
				if (title)
				{
					title.text = data.title;
				}
				var content = hint.getChildByName("content") as TextField;
				if (content)
				{
					content.text = data.content;
				}
			}
		}
		
		public function SetPanelText( data:Object )
		{
			if(BaseIconButton)
			{
				BaseIconButton.label = data.baseText;
			}
			if(LeaveButton)
			{
				LeaveButton.label = data.leaveText;
			}
		}
		
		public function ToggleLeaveButton()
		{
			if(LeaveButton)
			{
				LeaveButton.visible = !LeaveButton.visible;
			}
		}
		
		public function ShowLeaveButton( show:Boolean )
		{
			if(LeaveButton)
			{
				LeaveButton.visible = show;
			}
		}
		

		function clickLeave()
		{
			ExternalInterface.call( "ASArenaHintLeave" );
		}



	}
}