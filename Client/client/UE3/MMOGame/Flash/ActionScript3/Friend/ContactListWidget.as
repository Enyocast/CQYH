package ActionScript3.Friend
{

	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;

	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyShowText;
	import flash.display.Sprite;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.Friend.ContactListContent;
	import ActionScript3.MyActivePanel;
	import flash.events.Event;
	import ActionScript3.MyTipButton;
	import flash.text.TextField;
	import ActionScript3.Friend.ContactListStatic;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.utils.getDefinitionByName;
	import flash.geom.Point;
	import scaleform.clik.events.ComponentEvent;

	//好友面板
	public class ContactListWidget extends MyPanel
	{
		public var ContactListContentWidget:ContactListContent;

		public var MyFriendStatus:UIComponent;

		public var tab0:MyTipButton;
		public var tab1:MyTipButton;
		public var tab2:MyTipButton;
		public var tab3:MyTipButton;
		public var tab4:MyTipButton;

		public var searchPanel:MovieClip;
		
		protected var _classItemRef:Class;

		public function UpdateBaseInfo( data:Object ):void
		{
			if (ContactListContentWidget)
			{
				if (ContactListContentWidget.HeadIcon)
				{
					ContactListContentWidget.HeadIcon.source = data.headIcon;
				}
				if (ContactListContentWidget.playerName)
				{
					ContactListContentWidget.playerName.text = data.playerName;
				}
			}
		}

		public function SetPanelText( data:Object ):void
		{
			if (ContactListContentWidget)
			{
				ContactListContentWidget.SetPanelText(data);
			}

			if (tab0 && tab1 && tab2 && tab3 && tab4)
			{
				tab0.label = data.tab0;
				tab1.label = data.tab1;
				tab2.label = data.tab2;
				tab3.label = data.tab3;
				tab4.label = data.tab4;
			}
		}

		override protected function configUI():void
		{
			ShowMode="Friend";
			super.configUI();
			this.SetWindowTitle("好友");
			var i:int;
			var btnStateText:Array = new Array("在线","忙碌","离开");

			if (searchPanel)
			{
				searchPanel.visible = false;
				for (i = 0; i < 6; i++)
				{
					var item:Button = searchPanel.getChildByName( "playerItem"+i ) as Button;

					if (item)
					{
						item.itemid = i;
						item.addEventListener( ButtonEvent.CLICK , ClickSearch );
						item.addEventListener( MouseEvent.CLICK , ClickFriendItem );
					}
				}
			}
			if (MyFriendStatus)
			{
				hide();
				for (i = 0; i < 3; i++)
				{
					var itemButton:Button = MyFriendStatus.getChildByName("status"+i) as Button;
					var itemStatus_mc = itemButton.getChildByName("status_mc") as MovieClip;
					var stateText = itemButton.getChildByName("textField") as TextField;
					itemStatus_mc.gotoAndStop(i+1);
					stateText.text = btnStateText[i];
					itemButton.itemid = i+1;
					itemButton.addEventListener( ButtonEvent.CLICK , ClickFriendStatus );
				}
			}

			if (tab0 && tab1 && tab2 && tab3 && tab4)
			{
				tab0.addEventListener( ButtonEvent.CLICK , clickTab0 );
				tab1.addEventListener( ButtonEvent.CLICK , clickTab1 );
				tab2.addEventListener( ButtonEvent.CLICK , clickTab2 );
				tab3.addEventListener( ButtonEvent.CLICK , clickTab3 );
				tab4.addEventListener( ButtonEvent.CLICK , clickTab4 );
			}
			stageChangeHandler(null);
			//this.testData();
			if(_classItemRef==null)
			{
				_classItemRef = getDefinitionByName("ContactListRender") as Class;
			}
			this.addEventListener(ComponentEvent.HIDE,hideHandler);
		}
		
		private function hideHandler(evt:Event):void
		{
			hide();
		}
		
		private function hide():void
		{
			if (MyFriendStatus)
			{
				MyFriendStatus.visible=false;
			}
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=cavasWidth-760;
		}
		
		public function SetEnumValue( data:Object ):void
		{
			ContactListStatic.AFK = data.afk;
			ContactListStatic.BUSY = data.busy;
			ContactListStatic.OFFLINE = data.offline;
			ContactListStatic.ONLINE = data.online;
		}

		private function clickTab0(evt:ButtonEvent):void
		{
			if(ContactListContentWidget)
				ContactListContentWidget.ShowFriendList();
		}

		private function clickTab1(evt:ButtonEvent):void
		{
			if(ContactListContentWidget)
				ContactListContentWidget.ShowNearContactList();
		}

		private function clickTab2(evt:ButtonEvent):void
		{
			if(ContactListContentWidget)
				ContactListContentWidget.ShowEnemyList();
		}

		private function clickTab3(evt:ButtonEvent):void
		{
			if(ContactListContentWidget)
				ContactListContentWidget.ShowBlackList();

		}
		
		private function clickTab4(evt:ButtonEvent):void
		{
			if(ContactListContentWidget)
				ContactListContentWidget.ShowKillInfo();
		}

		private function ClickFriendStatus( e:ButtonEvent ):void
		{
			var itembutton = e.target as Button;
			if (itembutton)
			{
				ContactListContentWidget.ChangeStatus( itembutton.itemid );
			}
			hide();
		}

		private function ClickSearch( e:ButtonEvent ):void
		{
			var itembutton = e.currentTarget as Button;
			if (itembutton)
			{
				ExternalInterface.call( "ASClickSearchItem", itembutton.itemid );
			}
		}
/*		private function testData():void
		{
            var member:Object = { name:"好友",lv:20,classTxt:"ass",location:"?",sign:"hehe",roleId:11,stats:2,iconPath:""};
            var member2:Object = { name:"好友",lv:20,classTxt:"ass",location:"?",sign:"hehe",roleId:11,stats:3,iconPath:""};
			var dat = { groupId:0 , memberNum:5 , onlineNum:2 ,memberList:[member,member,member2,member,member] };
			var dat1 = { groupId:2 , memberNum:1 , onlineNum:2 ,memberList:[member2] };
            CreateNewGroup( "组1" , 0 );
            CreateNewGroup( "组2" , 1 );
			CreateNewGroup( "组3" , 2 );
		    SetFriendListData( dat,1 );
			SetFriendListData( dat1,1 );
		}
*/
		public function SetFriendListData(dat:Object,type:int):void
		{
			if(ContactListContentWidget)
			{
				ContactListContentWidget.setFriendData(dat,type);
			}
		}
		
		public function CreateNewGroup(GroupName:String , GroupId:int):void
		{
			if(ContactListContentWidget)
			{
				ContactListContentWidget.CreateNewGroup(GroupName,GroupId);
			}
		}
		
		public function DeleteGroup(GroupId:int):void
		{
			if(ContactListContentWidget)
			{
				ContactListContentWidget.DeleteGroup(GroupId);
			}
		}

		public function SetSearchData( searchData:Object ):void
		{
			if ( searchPanel == null || searchData == null )
			{
				return;
			}
			
			var data:Array = searchData.searchArray;

			var size:int =0;
			if(data)
			{
				size=data.length;
			}
			var i:int = 0;
			for (i = 0; i < 6; i++)
			{
				var item:Button = searchPanel.getChildByName( "playerItem"+i ) as Button;
				if ( i < size )
				{
					item.visible = true;
					var itemData = data[i];
					//这个函数其实是不依赖子控件存在的
					ContactListStatic.SetItemValue( item , itemData.name , itemData.lv , itemData.classTxt , itemData.location , itemData.sign , itemData.roleId , itemData.stats , itemData.iconPath );
				}
				else
				{
					item.visible = false;
				}
			}
			var desc:TextField = searchPanel.getChildByName("desc") as TextField;
			if (desc)
			{
				desc.y = size * 43 + 10;
				desc.text = searchData.descText;
			}

		}
		
		protected function ClickFriendItem(e:MouseEvent):void
		{
			if ((e as MouseEventEx).buttonIdx == 1)
			{
				var Item = e.target as _classItemRef;
				if (Item)
				{
					var pos:Point = new Point();
					pos.x = Item.x + Item.width;
					pos.y = Item.y;
					pos = Item.parent.localToGlobal(pos);
					var NameText:TextField = Item.getChildByName("tF_playerName") as TextField;
					ExternalInterface.call( "ASFriendItemRightClick",pos.x, pos.y,Item , Item.itemid,NameText.text);
				}
			}
		}
	}
}