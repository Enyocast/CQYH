package ActionScript3.Friend
{

	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MyScrollBar;
	import ActionScript3.MyScrollPanel;
	import ActionScript3.MyTipButton;
	import ActionScript3.Common.CustomScrollBar;
	
	import UI_ChatWidget.AS3.ChatTextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.SliderEvent;
	import scaleform.gfx.Extensions;
	import scaleform.gfx.TextEventEx;
	import scaleform.clik.controls.TextInput;

	//这个类是好友的实体
	public class ContactListContent extends UIComponent
	{
		public var textInput_signature:TextInput;
		public var textInput_search:TextInput;
		public var scrollBar:CustomScrollBar;
		public var ContactListRender:RadioButton;

		//默认好友组
		public var ContactListTitle:Button;
		
		public var ContactStatusButton:Button;
		public var MyFriendStatus:UIComponent;

		//
		public var KillInfo_tf:TextField;

		public var btn_msgSum:Button;
		public var btn_addContact:Button;

		public var PlayerTips:MovieClip;
		public var HeadIcon:UILoader;
		public var playerName:TextField;

		public var StatusButton:Button;
		public var SearchClearButton:Button;
		public var SearchButton:Button;

		var _FriendContent:FriendListContent;

		//var _classItemRef:Class;
		//var _classTitleRef:Class;
		var _DefaultGroupFriendList:Array;

		var _FriendContentHeight:int = 0;
		
		//public var _FriendContent:MovieClip;
		//黑名单
		var _BlackListContent:BlackListContent;
		//仇人
		var _EnemyListContent:EnemyListContent;
		//最近联系人
		var _nearContactListContent:NearContactListContent;

		var MaskLevel:Sprite;
		
		private static const KILL_INFO_TF_MAX_NUMLINES:int = 18;
		
		public function ContactListContent()
		{
			super();
		}

		override protected function configUI():void
		{
			Extensions.enabled = true;
			//_classTitleRef = getDefinitionByName("ContactListTitle") as Class;
			//_classItemRef = getDefinitionByName("ContactListRender") as Class;
			_DefaultGroupFriendList = []  ;

			super.configUI();

			if (ContactStatusButton)
			{
				ContactStatusButton.addEventListener( MouseEvent.CLICK,ClickStatusButton );
				ContactStatusButton.addEventListener( MouseEvent.ROLL_OVER, ShowStateTips);
				ContactStatusButton.addEventListener( MouseEvent.ROLL_OUT, HideStateTips);
			}

			if ( MyFriendStatus == null )
			{
				MyFriendStatus = parent.getChildByName("MyFriendStatus") as UIComponent;
			}

			//好友-空容器
			if (! _FriendContent)
			{
				_FriendContent = new FriendListContent  ;
				_FriendContent.x = ContactListStatic.frameBg.x;
				_FriendContent.y = ContactListStatic.frameBg.y;
				_FriendContent.PlayerTips = PlayerTips;
				//_FriendContent.addEventListener(MouseEvent.MOUSE_WHEEL,testHandler);
				addChild( _FriendContent );
			}

			if (! _BlackListContent)
			{
				_BlackListContent = new BlackListContent  ;
				_BlackListContent.x = ContactListStatic.frameBg.x;
				_BlackListContent.y = ContactListStatic.frameBg.y;
				addChild( _BlackListContent );
			}
			if (! _EnemyListContent)
			{
				_EnemyListContent = new EnemyListContent;
				_EnemyListContent.x = ContactListStatic.frameBg.x;
				_EnemyListContent.y = ContactListStatic.frameBg.y;
				addChild( _EnemyListContent );
			}
			if (! _nearContactListContent)
			{
				_nearContactListContent = new NearContactListContent  ;
				_nearContactListContent.x = ContactListStatic.frameBg.x;
				_nearContactListContent.y = ContactListStatic.frameBg.y;
				addChild( _nearContactListContent );
			}

			if (PlayerTips)
			{
				PlayerTips.visible = false;
			}

			if (textInput_signature)
			{
				textInput_signature.addEventListener( Event.CHANGE , ChangeSignature);
				textInput_signature.addEventListener(FocusEvent.FOCUS_OUT, FocusOutSearch);
				textInput_signature.addEventListener(FocusEvent.FOCUS_IN, FocusInSearch);
			}
			if (textInput_search)
			{
				textInput_search.addEventListener("inputcopy",inputCopyHandler);// 监听上层使用了复制粘贴的功能
				textInput_search.addEventListener( Event.CHANGE , ChangeSearch );
				textInput_search.addEventListener(FocusEvent.FOCUS_OUT, FocusOutSearch );
				textInput_search.addEventListener(FocusEvent.FOCUS_IN, FocusInSearch );
			}
			if ( scrollBar)
			{//_pageScrollSize
				scrollBar.height = ContactListStatic.frameBg.height;
			}
			if (SearchClearButton)
			{
				SearchClearButton.addEventListener(MouseEvent.CLICK,ClickSearchClear);
			}

			if (SearchButton)
			{
				SearchButton.visible = false;
			}

			if (btn_addContact)
			{
				btn_addContact.addEventListener( MouseEvent.CLICK , AddContact ,false,0,true);
			}
			if (btn_msgSum)
			{
				btn_msgSum.addEventListener( MouseEvent.CLICK , ClickMsgButton ,false,0,true);
			}
			
			if( KillInfo_tf )
			{
				KillInfo_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
				KillInfo_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
				KillInfo_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
				KillInfo_tf.styleSheet = new StyleSheet;
			}

			//生成遮罩层
				MaskLevel = new Sprite();
				MaskLevel.x = ContactListStatic.frameBg.x;
				MaskLevel.y = ContactListStatic.frameBg.y;
				MaskLevel.graphics.beginFill(0x000000,0);
				MaskLevel.graphics.drawRect( 0 , 0 , ContactListStatic.frameBg.width , ContactListStatic.frameBg.height );
				MaskLevel.graphics.endFill();

				addChild(MaskLevel);

			//test
			SetPanelText( {defaultSearchText:"请输入",defaultSignTxt:"请输入签名"} );
			//UpdateKillInfo( "<a href='event:,3,10140141,337A71,1,0,C00,C00,0,1,F03,2A3,1HA1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,E0'><u><font color='#A335EE' size='13'>&lt;学徒小刀&gt;</font></u></a>" );
			ChangeStatus(1);
			this.addEventListener(MouseEvent.MOUSE_WHEEL,wheelHandler);
		}
		
		private function wheelHandler(evt:MouseEvent):void
		{
			if(scrollBar.enabled)
			{
				scrollBar.position -= (evt.delta > 0 ? 1 : -1) * 20;
			}
		}

		private function ShowStateTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_State", this);
		}
		
		private function HideStateTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_State", this);
		}
		
		public function setFriendData(dat:Object,type:int):void
		{
			switch(type)
			{
				case 1:
				{
					if(_FriendContent)
					{
						_FriendContent.SetFriendGroupListData(dat);
						if(_FriendContent.visible)
						{
							updateScrollTarget(_FriendContent);
						}
					}
					break;
				}
				case 0:
				{
					if(_nearContactListContent)
					{
						_nearContactListContent.SetNearListData(dat as Array);
						if(_nearContactListContent.visible)
						{
							updateScrollTarget(_nearContactListContent);
						}
					}
					break;
				}
				case 2:
				{
					if(_BlackListContent)
					{
						_BlackListContent.SetBlackListData(dat as Array);
						if(_BlackListContent.visible)
						{
							updateScrollTarget(_BlackListContent);
						}
					}
                    break;
				}
				default:
				{
					if(_EnemyListContent)
					{
						_EnemyListContent.SetEnemyListData(dat as Array);
						if(_EnemyListContent.visible)
						{
							updateScrollTarget(_EnemyListContent);
						}
					}
					break;
				}
				
			}
		}
		
		public function CreateNewGroup(GroupName:String , GroupId:int):void
		{
			if(_FriendContent)
			{
				_FriendContent.CreateNewGroup(GroupName,GroupId);
			}
		}
		
		public function DeleteGroup(GroupId:int):void
		{
			if(_FriendContent)
			{
				_FriendContent.DeleteGroup(GroupId);
			}
		}
		
		public function onFriendGroupUpdated():void
		{
			updateScrollTarget(_FriendContent);
		}

		public function SetPanelText( data:Object ):void
		{
			if (textInput_signature)
			{
				textInput_signature.defaultText = data.defaultSignTxt;
				updateTextFormat(true,textInput_signature);
			}

			if (textInput_search)
			{
				textInput_search.defaultText=data.defaultSearchText;
				updateTextFormat(true,textInput_search);
			}
			if (ContactStatusButton)
			{
				//ContactStatusButton.label = data.statusButtonText;
			}
		}
		
		public function UpdateKillInfo( killInfoText:String )
		{
			KillInfo_tf.htmlText = killInfoText;
			if(KillInfo_tf.visible)
			{
				updateScrollTarget(KillInfo_tf);
			}
		}
		
		public function ShowFriendList():void
		{
			updateScrollTarget(_FriendContent);
			_BlackListContent.visible = false;
			_EnemyListContent.visible = false;
			_nearContactListContent.visible = false;
			KillInfo_tf.visible = false;
			
			_FriendContent.visible = true;
			_FriendContent.mask = MaskLevel;
		}

		public function ShowEnemyList():void
		{
			updateScrollTarget(_EnemyListContent);
			_BlackListContent.visible = false;
			_FriendContent.visible = false;
			_nearContactListContent.visible = false;
			KillInfo_tf.visible = false;
			_EnemyListContent.visible = true;
			_EnemyListContent.mask = MaskLevel;
		}

		public function ShowKillInfo():void
		{
			_BlackListContent.visible = false;
			_FriendContent.visible = false;
			_nearContactListContent.visible = false;
			KillInfo_tf.visible = true;
			_EnemyListContent.visible = false;
			
			updateScrollTarget(KillInfo_tf);
		}

		public function ShowBlackList():void
		{
			updateScrollTarget(_BlackListContent);
			_BlackListContent.visible = true;
			_EnemyListContent.visible = false;
			_FriendContent.visible = false;
			_nearContactListContent.visible = false;
			KillInfo_tf.visible = false;
			_BlackListContent.mask = MaskLevel;
		}

		public function ShowNearContactList():void
		{
			updateScrollTarget(_nearContactListContent);
			_nearContactListContent.visible = true;
			_BlackListContent.visible = false;
			_EnemyListContent.visible = false;
			_FriendContent.visible = false;
			KillInfo_tf.visible = false;
			_nearContactListContent.mask = MaskLevel;
		}
		
		private function updateScrollTarget(value:Object):void
		{
			if(value is ContactListBase)
			{
				var list:ContactListBase = value as ContactListBase;
				if(list.scrollEnable)
				{
					enableScrollBar();
					scrollBar.setScrollProperties(list.bottomScrollV - list.scrollV, 1, list.maxScrollV, 20);
				}
				else
				{
					disableScrollBar();
				}
			}
			else if(value is TextField)
			{
				var killInfoTF:TextField = value as TextField;
				if(killInfoTF.numLines > KILL_INFO_TF_MAX_NUMLINES)
				{
					enableScrollBar();
				}
				else
				{
					disableScrollBar();
				}
			}
			else
			{
				disableScrollBar();
			}
			
			function enableScrollBar():void
			{
				if(scrollBar.enabled == false)
				{
					scrollBar.enabled = true;
				}
				scrollBar.scrollTarget = value;
				scrollBar.position = 0;
			}
			
			function disableScrollBar():void
			{
				if(scrollBar.enabled == true)
				{
					scrollBar.position = 0;
					scrollBar.scrollTarget = null;
					scrollBar.position = NaN;
					scrollBar.enabled = false;
				}
			}
		}

		private function ClickSearchClear(evt:MouseEvent):void
		{
			if (textInput_search)
			{
				textInput_search.text = "";
				ChangeSearch(null);
			}
		}

		private function ChangeSearch(evt:Event):void
		{
			updateTextFormat(false,textInput_search);
			ExternalInterface.call( "ASFriendChangeSearchText", textInput_search.text );
		}
		private function inputCopyHandler(evt:Event):void
		{
			ExternalInterface.call( "ASFriendChangeSearchText", textInput_search.text );
		}
		private function ChangeSignature(evt:Event):void
		{
			updateTextFormat(false,textInput_signature);
		}
				
		private function updateTextFormat(bl:Boolean,input:TextInput):void
		{
			input.textField.maxChars=10;
			input.textField.condenseWhite=true;
			input.textField.restrict="^ ";
			if(bl)
			{
				input.defaultTextFormat.color=0x85919E;
				input.textField.setTextFormat(input.defaultTextFormat);
			}
			else
			{
				input.defaultTextFormat.color=0xFFFFFF;
				input.textField.setTextFormat(input.defaultTextFormat);
			}
		}
		
		private function FocusInSearch( evt:FocusEvent ):void
		{
			var input:ChatTextField=evt.currentTarget as ChatTextField;
			updateTextFormat(false,input);
		}

		private function FocusOutSearch( evt:FocusEvent ):void
		{
			var input:ChatTextField=evt.currentTarget as ChatTextField;
			if(input.text.length>0)
			{
				updateTextFormat(false,input);
			}
			else
			{
				updateTextFormat(true,input);
			}
			if(input.name=="textInput_signature")
			{
				textInput_signature.textField.setSelection(0,0);
			    ExternalInterface.call( "ASFriendChangeSignature", textInput_signature.text );
			}
		}
		
		private function ClickStatusButton(evt:MouseEvent):void
		{
			if (MyFriendStatus)
			{
				MyFriendStatus.visible = ! MyFriendStatus.visible;
			}
		}

		public function ChangeStatus( Status:int ):void
		{
			var stat:MovieClip = ContactStatusButton.getChildByName("ContactStatus") as MovieClip;
			if (stat)
			{
				if(Status == 0)
				{
					stat.gotoAndStop(4);
				}
				else
				{
					stat.gotoAndStop(Status);
				}
			}
			ExternalInterface.call( "ASFriendChangeStatus" , Status - 1);
		}

		private function AddContact(evt:MouseEvent):void
		{
			ExternalInterface.call("ASFriendAddFriend");
		}

		private function ClickMsgButton(evt:MouseEvent):void
		{
			ExternalInterface.call("ASFriendMsgButton");
		}
		
		private function onLinkOverCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		private function onLinkOutCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		private function onLinkCallBack(e:TextEvent):void
		{
			if( (e is TextEventEx) )
			{
				var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
				var buttonIdx:int = (e as TextEventEx).buttonIdx;
				ExternalInterface.call( "ASLinkCallBack" , commandParameter , buttonIdx );
			}
		}

	}
}