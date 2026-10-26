package ActionScript3.Friend
{

	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.FaceMap;
	import ActionScript3.MyPanel;
	import ActionScript3.Common.CustomScrollBar;
	import ActionScript3.Widget.FacePanel;
	
	import UI_ChatWidget.AS3.ChatTextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import flash.events.MouseEvent;
	import ActionScript3.MyShowText;
	import scaleform.clik.events.ComponentEvent;
	import scaleform.clik.managers.FocusHandler;

	//好友聊天
	public class ContactWidget extends MyPanel
	{
		public var btn_FontColor:Button;
		public var btn_Face:Button;
		public var btn_Sendmsg:Button;

		public var btn_Minimize:Button;
		public var Sprite_Input:MovieClip;
		public var Sprite_Show:MovieClip;

		public var textAreaInput:ChatTextField;
		public var TextShowArea_mc:MyShowText;
		public var PopFacePanel:FacePanel;
		public var chatLogScrollBar:CustomScrollBar;
		public var chatInputScrollBar:CustomScrollBar;

		public var friendList_mc:ScrollingList;
		public var WindowId:int = 0;
		public var tF_playerName:TextField;
		public var ContactStatus:MovieClip;

		var CurColor:int = 0;

		var CtrlPush:Boolean = false;
		var nCurRoleID:int = 0;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			if ( chatInputScrollBar)
			{
				chatInputScrollBar.height=96;
				textAreaInput.textField.multiline=true;
				textAreaInput.textField.wordWrap=true;
				chatInputScrollBar.scrollTarget = textAreaInput;
			}
			TextShowArea_mc.mouseChildren=true;

			if (btn_Sendmsg)
			{
				btn_Sendmsg.addEventListener( ButtonEvent.CLICK , sendToGame ,false,0,true );
			}
			if (btn_Face && PopFacePanel)
			{
				//这个先注释掉，但这个是要的啊！
				PopFacePanel.visible = false;
				btn_Face.addEventListener( ButtonEvent.CLICK , AddFace ,false,0,true );

				PopFacePanel.clickfunc = ClickFace;
			}
			if (textAreaInput)
			{
				textAreaInput.addEventListener( KeyboardEvent.KEY_DOWN  , OnClickEnter , false, 0, true);
			}
			root.stage.addEventListener( KeyboardEvent.KEY_DOWN  , OnStageKeyDownCtrl , false, 0, true);
			root.stage.addEventListener( KeyboardEvent.KEY_UP  , OnStageKeyUpCtrl , false, 0, true);

			if (btn_Minimize)
			{
				btn_Minimize.addEventListener( ButtonEvent.CLICK ,MiniMize ,false,0,true );
			}
			if (btn_close)
			{
				btn_close.addEventListener( ButtonEvent.CLICK ,Close ,false,0,true );
			}

			friendList_mc.addEventListener(ListEvent.ITEM_CLICK,  OnClickSelectedRoleChat);
			
			ContactStatus.visible=false;
			this.addEventListener(ComponentEvent.HIDE,hideHandler);
			this.addEventListener(ComponentEvent.SHOW,showHandler);
			//TestData();
		}
		
		private function showHandler(evt:Event):void
		{
			setInputFocus();
		}
		
		private function hideHandler(evt:Event):void
		{
			if(textAreaInput && root.stage.focus==textAreaInput.textField)
			   FocusHandler.getInstance().setFocus(null);
		}

		private function OnStageKeyDownCtrl(e:KeyboardEvent):void
		{
			if (e.keyCode == 17)
			{
				CtrlPush = true;
			}
		}

		private function OnStageKeyUpCtrl( e:KeyboardEvent ):void
		{
			if (e.keyCode == 17)
			{
				CtrlPush = false;
			}
		}

		private function MiniMize(evt:ButtonEvent):void
		{
			ExternalInterface.call( "ASContactWidgetMiniMize", name );
		}
		private function Close(evt:ButtonEvent):void
		{
			ExternalInterface.call( "ASContactWidgetClose", name );
		}

		private function ClickFace(index:int ):void
		{
			var faceString:String = FaceMap.getFaceString(index);
			textAreaInput.appendText(faceString);
			setInputFocus();
		}

		private function OnClickEnter( e:KeyboardEvent ):void
		{
			if (e.keyCode == 13 && CtrlPush)
			{
				sendToGame(null); 
				hideHandler(null);
			}
		}

		public function sendToGame(evt:ButtonEvent):void
		{
			if (textAreaInput.textField.length>0){
				if(textAreaInput.text.indexOf("</TEXTFORMAT>")>0){
					if(textAreaInput.text.indexOf("<A HREF=")>-1){
						textAreaInput.filterNewLine(true);
					}else{
						textAreaInput.filterNewLine(false);
					}
				}
				if(nCurRoleID > 0)
					ExternalInterface.call( "ASSendFriendChatByRoleID", nCurRoleID , textAreaInput.text );
				textAreaInput.clear();
			}
		}

		private function AddFace(evt:ButtonEvent):void
		{//先禁用
			PopFacePanel.visible = ! PopFacePanel.visible;
		}
		
		public function UCDataFriendChatList(dataList:Array):void
		{
			nCurRoleID = 0;
			friendList_mc.dataProvider = new DataProvider(dataList);
			friendList_mc.validateNow();
			friendList_mc.invalidateData();
			ContactStatus.visible=false;
			if(dataList)
			{
				for(var n:int = 0; n < dataList.length; ++n)
				{
					var data:FriendNameListItemData = dataList[n] as FriendNameListItemData;
					if(data.Selected)
					{
						friendList_mc.selectedIndex=n;
						nCurRoleID = data.RoleID;
						updatePlayerName(data.OnLine,data.RoleName);
						break;
					}
				}
			}
			if(nCurRoleID > 0)
			{
				if(this.visible==true)
			       setInputFocus();
				ExternalInterface.call( "ASSelectRoleChatWnd" ,nCurRoleID );
			}
				
		}
		private function OnClickSelectedRoleChat(e:ListEvent):void
		{
			var itemData:FriendNameListItem = e.itemRenderer as FriendNameListItem;
			if(itemData && itemData.friendData)
			{
				nCurRoleID = itemData.friendData.RoleID;
				itemData.clear();//选中以后计算清0
				updatePlayerName(itemData.friendData.OnLine,itemData.friendData.RoleName);
				ExternalInterface.call( "ASSelectRoleChatWnd" ,nCurRoleID );
								
				setInputFocus();
			}
		}
		
		private function setInputFocus():void
		{
			if(textAreaInput && root.stage.focus==textAreaInput.textField)
			{
				return;
			}
			FocusHandler.getInstance().setFocus(textAreaInput.textField);//焦点重新设置为文本输入框
		}
		
		public function updatePlayerName(ty:int,str:String):void
		{
			ContactStatus.visible=true;
			if( ty == 0)
			{
				ContactStatus.gotoAndStop("online");
			}
			else 
			{
				ContactStatus.gotoAndStop(ty + 1);
			}

			tF_playerName.text = str;
		}
		
		//设置页签闪烁
		public function UCShowRoleItemEffec(index:int):void
		{//找到页签
		    var item:FriendNameListItem=friendList_mc.getRendererAt(index) as FriendNameListItem;
			if(item)
			{
				item.UCShowEffect();
			}
		}
/*		function TestData():void
		{
			var DataList = new Array;
			for(var n:int = 0; n < 25; ++n)
			{
				var data:FriendNameListItemData = new FriendNameListItemData;
				data.RoleID =  n +1;
				data.OnLine = n %4;
				data.RoleName = "Test Name"+n;
				data.MsgNum=n;
				data.Selected = (n==5);
				DataList.push(data);
			}
			UCDataFriendChatList(DataList);
			UCShowRoleItemEffec(1);
		}*/
	}

}