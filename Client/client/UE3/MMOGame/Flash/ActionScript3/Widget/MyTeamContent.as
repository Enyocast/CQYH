package ActionScript3.Widget
{
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.RadioButton;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	import scaleform.gfx.Extensions;
	import flash.geom.Point;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.data.DataProvider;
	import flash.text.TextFieldAutoSize;
	import UI_ChatWidget.AS3.ChatTextField;
	import flash.text.TextField;
	import scaleform.clik.controls.TextInput;
	
	public class MyTeamContent extends UIComponent
	{
		public var btn_teamExpand:Button;
		public var btn_leaveTeam:Button;
		public var btn_invite:Button;
		//public var AssignTypeButton:Button;
		public var tf_type:TextField;
		public var AssignTypeFree:RadioButton;
		public var AssignTypeTurn:RadioButton;
		
		public var AutoTeamButton:Button;
		public var tf_autoteam:TextField;
		public var teamName:TextField;
		public var TeamNameTxt:ChatTextField;
		public var inputBg:MovieClip;
		public var memberItem20:MovieClip;
		public var memberItem5:MovieClip;
		public var SaveNameButton:Button;
		//public var TeamAuctionLimit:DropdownMenu;

		static var NormalTeamMemberLimit:int = 5;
		static var LargeTeamMemberLimit:int = 11;
		
		public var _guide_location:MovieClip;
		
		override protected  function configUI():void {
			Extensions.enabled = true;
			super.configUI();
			//if( memberItem20 )
				//memberItem20.visible = false;
			if( SaveNameButton )
				SaveNameButton.addEventListener(MouseEvent.CLICK , ClickSaveNameButton );
			if( btn_teamExpand )
				btn_teamExpand.addEventListener(MouseEvent.CLICK , ClickTeamExpand );
			if( btn_leaveTeam )
				btn_leaveTeam.addEventListener(MouseEvent.CLICK , ClickLeaveTeam );
			if( AssignTypeFree )
				AssignTypeFree.addEventListener(MouseEvent.CLICK , ClickAssignFree );
			if( AssignTypeTurn )
				AssignTypeTurn.addEventListener(MouseEvent.CLICK , ClickAssignTurn );
			if( AutoTeamButton )
				AutoTeamButton.addEventListener(MouseEvent.CLICK , ClickAutoTeamButton );
			if( btn_invite )
				btn_invite.addEventListener(MouseEvent.CLICK, ClickInviteTeam );
				
			var i:int;
			var item:RadioButton
			if( memberItem5 )
			{
				
				for( i = 0 ; i< NormalTeamMemberLimit ; i ++ )
				{
					item =  memberItem5.getChildByName("MyTeamItem"+i) as RadioButton;
					if( item!= null )
					{
						item.addEventListener( MouseEvent.CLICK , ClickPlayerItem );
						item.itemid = i;
					}
				}
			}
			if( memberItem20 )
			{
				
				for( i = 0 ; i< LargeTeamMemberLimit ; i ++ )
				{
					item =  memberItem20.getChildByName("MyTeamItem"+i) as RadioButton;
					if( item!= null )
					{
						item.addEventListener( MouseEvent.CLICK , ClickPlayerItem );
						item.itemid = i;
					}
				}
			}
			
			//TeamAuctionLimit.addEventListener(Event.CHANGE , LimitChange );
			
			//var aa:Array = ["Take", "Tina", "Michael", "Wendy", "Marc", "Frank", "Artem", "Dave", "Judy"];
			//SetDropDownMenu(aa);
			//SetTeamAuctionColorLimit(3);
			//AutoTeamButton["team_name1"].text = "自动组队";
			//AutoTeamButton["team_name2"].text = "手动组队";
			
			//memberItem20.visible = true;
			//memberItem5.visible = false;
			//SetOnLineState(0,20,0);
			
			_guide_location.visible = true;
			_guide_location.mouseChildren = false;
			_guide_location.mouseEnabled = false;
		}
		
		
		
//		function LimitChange( e:Event )
//		{
//			ExternalInterface.call( "ASTeamAuctionLimitChange",TeamAuctionLimit.selectedIndex );
//		}
		
		public function SetTeamAuctionColorLimit( idx:int ):void
		{
			//TeamAuctionLimit.selectedIndex = idx;
		}
		
		public function SetDropDownMenu( data:Array ):void
		{
			//TeamAuctionLimit.dataProvider =new DataProvider(data);
		
		}
		
		public function SetOnLineState(nIndex:int,nType:int,bOnline:Boolean):void
		{
			if(nType == 20)
			{
				if(memberItem20)
				{
					var item:MyTeamItem20 =  memberItem20.getChildByName("MyTeamItem"+nIndex) as MyTeamItem20;
					if(item)
						item.updateState(bOnline);
				}
			}
			else
			{
				if(memberItem5)
				{
					var item1:MyTeamItem =  memberItem5.getChildByName("MyTeamItem"+nIndex) as MyTeamItem;
					if(item1)
						item1.updateState(bOnline);
				}
			}
			if(TeamNameTxt)
			 TeamNameTxt.textField.maxChars = 10;
		}
		
		public function UCSetAutoTeamVisible(bl:Boolean):void
		{
			tf_autoteam.visible=bl;
			AutoTeamButton.visible=bl;
			if(bl)
			{
				teamName.y=inputBg.y=TeamNameTxt.y=308;
				SaveNameButton.y=307;
				AssignTypeFree.y=tf_type.y=AssignTypeTurn.y=334;
				tf_autoteam.y=AutoTeamButton.y=362;
			}
			else
			{
				teamName.y=inputBg.y=TeamNameTxt.y=316;
				SaveNameButton.y=315;
				AssignTypeFree.y=tf_type.y=AssignTypeTurn.y=350;
			}
		}
		
		private function ClickAutoTeamButton(e:MouseEvent):void
		{
			var Butt:Button = e.target as Button;
			if( Butt )
			{
				ExternalInterface.call( "ASAutoTeam", !Butt.selected );
			}
		}
		
		private function ClickInviteTeam(e:MouseEvent):void
		{
			ExternalInterface.call("ASClickShowTeamInvite");
		}
		
		private function ClickPlayerItem(e:MouseEvent):void
		{
			if( e is MouseEventEx )
			{
				var Item = e.target as RadioButton;
				if( Item )
				{
					var pos:Point = new Point;
					
					pos.x = Item.x + Item.width;
					pos.y = Item.y ;
					pos = Item.parent.localToGlobal( pos);
					if( (e as MouseEventEx).buttonIdx == 1)
					{
						ExternalInterface.call( "ASTeamMemberUIRightClick",pos.x, pos.y, Item.itemid );
					}
					else if((e as MouseEventEx).buttonIdx == 0)
					{
						ExternalInterface.call( "ASTeamMemberUILeftClick",pos.x, pos.y, Item.itemid );
					}
				}
			}
		}
		
		private function ClickSaveNameButton(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamSaveName" );
		}
		
		private function ClickTeamExpand(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamTeamExpand" );
		}
		
		private function ClickLeaveTeam(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamCreateOrLeave" );
		}
				
		private function ClickAssignFree(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamChangeAssignTypeFree" );
		}
		private function ClickAssignTurn(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamChangeAssignTypeTurn" );
		}
	}
}