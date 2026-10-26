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

	public class ArenaQueue extends MyPanel
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
			//if(MinimizeButton)
			//{
			//MinimizeButton.addEventListener(MouseEvent.CLICK , clickMinimize , false , 0 , true );
			//}

			//TeamItemList = new Array  ;
			//for (var i:int = 0; i < 5; i++)
			//{
			//var item:UIComponent = this.getChildByName("MyTeamItem"+i) as UIComponent;
			//TeamItemList.push( item );
			//}

			ExternalInterface.call( "RegisterArenaQueue", this );

			//SetHint( {title:"1V1排队",content:"耐心等待"} );
			//setTeamNum(1);
			//setTeamMember( 0 , "haha" , "刺客" , 20 , false);
		}

		function clickIcon( e:Event )
		{
//			if (LeaveButton)
//			{
//				LeaveButton.visible = ! LeaveButton.visible;
//			}

			ExternalInterface.call( "ASArenaQueueClickIcon", this );
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

		/*
		public function setTeamNum( num:int )
		{
		for( var i:int = 0 ; i < TeamItemList.length ; i++ )
		{
		var item:UIComponent = TeamItemList[i] as UIComponent;
		if( item )
		{
		if( i < num )
		{
		item.visible = true;
		}
		else
		{
		item.visible = false;
		}
		}
		}
		}
		
		public function setTeamMember( pos:int , memberName:String , className:String , lv:int , leader:Boolean )
		{
		var item:UIComponent = TeamItemList[pos] as UIComponent;
		if( item )
		{
		var team_name:TextField = item.getChildByName("team_name") as TextField;
		if(team_name)
		{
		team_name.text = memberName;
		}
		
		var leaderclass:TextField = item.getChildByName("leaderclass") as TextField;
		if(leaderclass)
		{
		leaderclass.text = className;
		}
		
		var leaderlv:TextField = item.getChildByName("leaderlv") as TextField;
		if(leaderlv)
		{
		leaderlv.text = String(lv);
		}
		
		var teamLeaderTag:MovieClip = item.getChildByName("teamLeaderTag") as MovieClip;
		if(teamLeaderTag)
		{
		teamLeaderTag.visible = leader?true:false;
		}
		}
		}
		*/

		function clickLeave()
		{
			ExternalInterface.call( "ASArenaQueueLeave" );
		}

		function clickMinimize()
		{
			ExternalInterface.call( "ASArenaQueueMinimize" );
		}

	}
}