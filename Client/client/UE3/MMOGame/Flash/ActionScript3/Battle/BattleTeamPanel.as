package ActionScript3.Battle
{
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	//import scaleform.clik.events.ButtonEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.controls.TextInput;
	import ActionScript3.MyScrollPanel;
	import flash.utils.getDefinitionByName;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.MouseEventEx;
	import flash.geom.Point;
	import flash.display.MovieClip;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.TreeDataProvider;
	import ActionScript3.MyWindowsFrame;

	public class BattleTeamPanel extends MyPanel
	{
		//public var LeaveTeam:Button;
		public var ClosePanel:Button;

		//const TeamMemberNum:int = 7;

		public var BattleTable0:MovieClip;
		public var BattleTable1:MovieClip;
		public var TeamList:ScrollingList;

		public var TextContent:Array;
		public var TabButton:Array;
		public var AddButton:Button;
		
		public var teamIcon:UILoader;

		var _frameSingle:Array;
		var _frameTeam:Array;
		var _btnSingle:Array;
		var _btnTeam:Array;

		public var TextValue0:TextField;
		public var TextValue1:TextField;
		public var TextValue2:TextField;
		public var TextValue3:TextField;
		public var TextValue4:TextField;
		public var TextValue5:TextField;
		public var TextValue6:TextField;
		public var TextValue7:TextField;

		public var bg:MyWindowsFrame;

		const ContentTextNum:int = 6;
		const ButtonTextNum:int = 5;
		

		override protected function configUI():void
		{
			if (bg)
			{
				this.btn_close = bg.btn_close;
				this.InfoDragButton_mc = bg.InfoDragButton_mc;
			}

			super.configUI();

			_frameSingle = new Array(ContentTextNum);
			_frameTeam = new Array(ContentTextNum);
			TextContent = new Array(ContentTextNum);

			TabButton = new Array(ButtonTextNum);
			_btnSingle = new Array(ButtonTextNum);
			_btnTeam = new Array(ButtonTextNum);

			if (BattleTable0)
			{
				BattleTable0.addEventListener( MouseEvent.CLICK , clickTurn1To1 , false , 0 , true );
			}

			if (BattleTable1)
			{
				BattleTable1.addEventListener( MouseEvent.CLICK , clickTurn5To5 , false , 0 , true );
			}

			for (var i:int = 0; i < TextContent.length; i++)
			{
				TextContent[i] = this.getChildByName("TextContent"+i) as TextField;
			}

			for (i = 0; i < TabButton.length; i++)
			{
				TabButton[i] = this.getChildByName("TabTitle"+i);
			}
			
			if( AddButton )
			{
				AddButton.addEventListener( MouseEvent.CLICK , clickAddMember , false , 0 , true );
			}

			//test
			//var a:Object = { label:"总结", index:0, type:0, deepth:0, visible:true ,MemberRoleId:11, MemberName:"1",MemberClass:"战士",MemberBattleCount:20,MemberGrade:"1-3",MemberRate:"56%"};
			//var b:Object = { label:"总结", index:0, type:0, deepth:0, visible:true ,MemberRoleId:21, MemberName:"2",MemberClass:"战士",MemberBattleCount:22,MemberGrade:"1-3",MemberRate:"56%"};
			
			//TeamList.dataProvider = new TreeDataProvider([ a , a , a , b , b ]);

			//SetPanelText( { titleName:"gg" , btnSingleArray:[ "1" , "1" , "1" , "1" , "1" ] , contentSingleArray:["","","","",""] });
			//UCTurnOneToOne( null );
			//trace(_frameTeam[10]);
		}

		public function UpdateTeamList( data:Array )
		{
			if (TeamList)
			{
				TeamList.dataProvider = new TreeDataProvider(data);
			}

		}

		public function SetPanelText( data:Object )
		{
			if (! data)
			{
				return;
			}

			if ( bg && bg.tF_windowTitle )
			{
				bg.tF_windowTitle.text = data.titleName;
			}
			
			if( AddButton )
			{
				AddButton.label = data.addButton;
			}

			var btnSingleArray = data.btnSingleArray;

			for (var i:int = 0; i < btnSingleArray.length; i++)
			{

				if ( btnSingleArray[i] != undefined )
				{
					_btnSingle[i] = btnSingleArray[i];
				}
			}

			var btnTeamArray = data.btnTeamArray;
			if (btnTeamArray)
			{
				for (i = 0; i < btnTeamArray.length; i++)
				{
					if ( btnTeamArray[i] != undefined )
					{
						_btnTeam[i] = btnTeamArray[i];
					}
				}
			}

			var contentSingleArray = data.contentSingleArray;
			if (contentSingleArray)
			{
				for (i = 0; i < contentSingleArray.length; i++)
				{
					
					if ( contentSingleArray[i] != undefined )
					{
						_frameSingle[i] = contentSingleArray[i];
						
					}
					
				}
			}

			var contentTeamArray = data.contentTeamArray;
			if (contentTeamArray)
			{
				for (i = 0; i < contentTeamArray.length; i++)
				{
					if ( contentTeamArray[i] != undefined )
					{
						_frameTeam[i] = contentTeamArray[i];
					}
				}
			}
			/*
			_btnSingle[0] = "名字";
			_btnSingle[1] = "职业";
			_btnSingle[2] = "个人场次";
			_btnSingle[3] = "胜-负";
			_btnSingle[4] = "胜率";
			
			_btnTeam[0] = "名字";
			_btnTeam[1] = "职业";
			_btnTeam[2] = "个人场次";
			_btnTeam[3] = "胜-负";
			_btnTeam[4] = "个人贡献点";
			
			_frameTeam[0] = "5V5";
			_frameTeam[1] = "积分";
			_frameTeam[2] = "排名";
			_frameTeam[3] = "战队";
			_frameTeam[4] = "队伍场次";
			_frameTeam[5] = "胜-负";
			_frameTeam[6] = "个人场次";
			
			_frameSingle[0] = "1V1";
			_frameSingle[1] = "积分";
			_frameSingle[2] = "排名";
			_frameSingle[3] = "个人";
			_frameSingle[4] = "场次";
			_frameSingle[5] = "胜-负";
			_frameSingle[6] = "胜率";
			*/
		}

		public function UCTurnOneToOne( data:Object )
		{
			for (var i:int = 0; i < TextContent.length; i++)
			{
				if (TextContent[i] as TextField)
				{
					TextContent[i].text = _frameSingle[i];
				}
			}

			for (i = 0; i < TabButton.length; i++)
			{
				if (TabButton[i])
				{
					TabButton[i].label = _btnSingle[i];
				}
			}

			if (AddButton)
			{
				AddButton.visible = false;
			}

			if (data)
			{

				if (TextValue0)
				{
					TextValue0.text = data.score;
				}
				if (TextValue1)
				{
					TextValue1.text = data.rank;
				}
				if (TextValue2)
				{
					TextValue2.text = data.arenaCount;
				}
				if (TextValue3)
				{
					TextValue3.text = data.win;
				}
				if (TextValue4)
				{
					TextValue4.text = data.lose;
				}
				if (TextValue5)
				{
					TextValue5.text = data.rate;
				}
				if (TextValue6)
				{
					TextValue6.text = data.myName;
				}
				if(TextValue7)
				{
					TextValue7.text = data.period;
				}
			}
		}

		public function UCTurnFiveToFive( data:Object )
		{
			//team templete
			for (var i:int = 0; i < TextContent.length; i++)
			{
				if (TextContent[i] as TextField)
				{
					TextContent[i].text = _frameTeam[i];
				}
			}

			for (i = 0; i < TabButton.length; i++)
			{
				if (TabButton[i])
				{
					TabButton[i].label = _btnTeam[i];
				}
			}

			if (data)
			{

				if (TextValue0)
				{
					TextValue0.text = data.score;
				}
				if (TextValue1)
				{
					TextValue1.text = data.rank;
				}
				if (TextValue2)
				{
					TextValue2.text = data.teamCount;
				}
				if (TextValue3)
				{
					TextValue3.text = data.win;
				}
				if (TextValue4)
				{
					TextValue4.text = data.lose;
				}
				if (TextValue5)
				{
					TextValue5.text = data.singleCount;
				}
				if (TextValue6)
				{
					TextValue6.text = data.teamName;
				}
				if(TextValue7)
				{
					TextValue7.text = data.period;
				}

				if (AddButton)
				{
					AddButton.visible = data.isLeader;
				}
			}

		}

		public function clickTurn1To1()
		{
			ExternalInterface.call( "ASBattleTeamTurnOneToOne" );
			//test;
			//UCTurnOneToOne( { score:"104" , rank:"25" , arenaCount:"10" , win:"9" , lose:"1" , rate:"90%"  } );
		}

		public function clickTurn5To5()
		{

			ExternalInterface.call( "ASBattleTeamTurnFiveToFive" );
			//test;
			//UCTurnFiveToFive({ score:"124" , rank:"111" , teamCount:"12" , win:"9" , lose:"3" , singleCount:"3"  });
		}

		function clickRoleMember( e:MouseEventEx )
		{
			if (e.buttonIdx == 1 && e.target is RadioButton)
			{
				var item:RadioButton = e.target as RadioButton;
				var pos:Point = new Point  ;

				pos.x = item.x + item.width;

				pos.y = item.y;

				pos = item.parent.localToGlobal(pos);

				ExternalInterface.call( "ASBattleTeamRightClick",pos.x, pos.y,item , item.itemid );
			}
		}

		function clickLeaveButton( e:Event )
		{
			ExternalInterface.call( "ASBattleTeamLeave" );
		}

		function clickCloseButton( e:Event )
		{
			if (btn_close)
			{
				btn_close.dispatchEvent(e);
			}
		}
		
		function clickAddMember( e:Event )
		{
			ExternalInterface.call( "ASBattleTeamAddMember" );
		}

	}
}