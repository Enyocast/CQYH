package ActionScript3.Widget
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.ui.Keyboard;
	import flash.utils.getDefinitionByName;

	import ActionScript3.FaceMap;
	import ActionScript3.MyPanel;

	import UI_ChatWidget.AS3.ChatTextField;

	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.gfx.Extensions;
	import ActionScript3.Common.Events.ParamEvent;
	import scaleform.clik.core.CLIK;
	import flash.utils.Dictionary;
	import scaleform.clik.managers.FocusHandler;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import scaleform.clik.events.InputEvent;
	import UI_ChatWidget.AS3.ChatTabButton;
	import scaleform.clik.events.ComponentEvent;
	import UI_ChatWidget.AS3.Chat_InputArea;
	import flash.text.TextField;
	import scaleform.clik.controls.CheckBox;
	import flash.utils.setTimeout;
	import flash.utils.clearTimeout;
	import flash.text.TextFormat;

	public class ChatPanel extends MyPanel
	{
		public var InputBlock_mc:Chat_InputArea;
		public var TopLable_mc:ChatTabButton;
		public var PopFace:FacePanel;
		public var btn_set:CheckBox;
		public var ChatCleanbutton_mc:Button;
		public var Chathidebutton_mc:Button;

		public var SendButton:Button;
		//public var OptionButton:Button;
		public var chatText:ChatTextField;
		public var ChatListView_mc:ChatListView;
		public var FaceButton:Button;

		private const MaxBg:int = 3;//最大背景
		private var bHide:int = 0;//0正常最大到三

		public var ChatBg_mc:MovieClip;
		private var mc_lock:MovieClip

		var _TabList:Array;
		
		public var chatIndex:int = 0;
		public var chatIndexMax:int = 0;
		public var _chatHistoryArr:Array = new Array(100);

		public var bShowBg:Boolean = false;//是否显示背景

		public var trumpet_mc:chat_Trumpet;

		public var lastPlayerName:String = "";
		
		public var _onShowChatInput:Function;
		public var timer:Timer;
		private var _timer:int;
        private var _eventType:int;
		
		public var nCurrentChannel:int=1;//当前频道
		
		private const TrumpetChannel:int=7;//传音
		private const TipsChannel:int=6;//提示
		private const SystemChannel:int=5;//系统 
		private const PrivateChannel:int=4;//私聊
		private const NearChannel:int=1;//附近
		private const GuildChannel:int=2;//公会
		private const TeamChannel:int=3;//队伍
		private const WorldChannel:int=0;//世界
		
		private var timerUpdate:uint=0;
		override protected function configUI():void
		{
			ShowMode = "Chat";
			super.configUI();
			_TabList = [];
			Extensions.enabled = true;
			FaceMap.enable();
			if (InputBlock_mc)
			{
				FaceButton = InputBlock_mc.getChildByName("FaceButton_mc") as Button;
				chatText = InputBlock_mc.getChildByName("NewInput_mc") as ChatTextField;
				SendButton = InputBlock_mc.getChildByName("enter_mc") as Button;
				if (SendButton)
				{
					SendButton.addEventListener(MouseEvent.CLICK , sendToGame );
				}
				InputBlock_mc.addEventListener( KeyboardEvent.KEY_DOWN , OnPushEnter , false, 0, true);
				if (FaceButton)
			    {
				    FaceButton.addEventListener(MouseEvent.CLICK , clickFaceButton );
				    if (PopFace)
				    {
					   PopFace.visible = false;
					   PopFace.clickfunc = SelectFace;
				    }
			     }
			}
			CreateChannel();
			this.addEventListener(MouseEvent.ROLL_OVER, onRollOverChatPanel);
			this.addEventListener(MouseEvent.ROLL_OUT, onRollOutChatPanel);
			btn_set.addEventListener(ButtonEvent.CLICK,lockChatHandler);
			mc_lock=btn_set.getChildByName("mc_lock") as MovieClip;
			this.playEffect(false);
			ChatCleanbutton_mc.addEventListener(MouseEvent.CLICK,clearChatHandler);
			Chathidebutton_mc.addEventListener(MouseEvent.CLICK,hideChat);
			
			Chathidebutton_mc.addEventListener( MouseEvent.ROLL_OVER, ChatShowTips);
			Chathidebutton_mc.addEventListener( MouseEvent.ROLL_OUT, ChatHideTips);
			Chathidebutton_mc.itemid=0;
			ChatCleanbutton_mc.addEventListener( MouseEvent.ROLL_OVER, ChatShowTips);
			ChatCleanbutton_mc.addEventListener( MouseEvent.ROLL_OUT, ChatHideTips);
			ChatCleanbutton_mc.itemid=1;
			btn_set.addEventListener( MouseEvent.ROLL_OVER, ChatShowTips);
			btn_set.addEventListener( MouseEvent.ROLL_OUT, ChatHideTips);
			btn_set.itemid=2;

			SetChatCtrlVisible(false);
			UCSetDropDownListIndex(1);//设置聊天频道

			trumpet_mc.visible = false;
			trumpet_mc.txt_trumpet.listItem_tf.wordWrap = true;
			//UCUpdateTrumpetMsg("的的大的大的的的得到的大的掉的大的的得到的大的掉的大的的得到的大的掉的大的的得到的大的掉的大掉的大掉的大",true,false);
			timer=new Timer(60000);
			timer.stop();
			UCSetDropDownList([0,0,0,0,0,0,0]);
			stageChangeHandler(null);
			//UCShowPrivateTabEffect(4);
			//chatText.appendHtml(" <a href='event:,18,89900003,181HA03,1,I,HA0,HA0,A,22,1,0,0,0,0,0,0,0,0,0,0,0'><u><font color='#ffffff' >&lt;古朴的乌木剑&gt;</font></u></a> ");
			/*this.Test();
			TimerManager.getInstance().add(3000,Test);*/

			
			//UCUpdateChannelTabClicked();
			//UCShowChatBackBg(true);

			//UCSetPrivateChatName("/bs ");
		}

		override protected function handleStageChange(event:Event):void
		{
			super.handleStageChange(event);
			if (stage)
			{
				this.addEventListener(KeyboardEvent.KEY_DOWN, onChatInputKeyDown );
				this.addEventListener( KeyboardEvent.KEY_UP, onChatInputKeyUp );
				stage.addEventListener(MouseEvent.MOUSE_DOWN, handleStageClick);
			}
		}

		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.y = cavasHeight - 416;
		}

		private function onRollOverChatPanel( e:MouseEvent ):void
		{
			ExternalInterface.call( "ASonRollChatPanel",true);
			clearTimeout(timerUpdate);//清楚定时器
			SetChatCtrlVisible(true);
			ChatListView_mc.ISScroll=false;
		}

		private function onRollOutChatPanel( e:MouseEvent ):void
		{
			rollOut();
		}
		
		public function rollOut():void
		{
			if (bShowBg && chatText && root.stage.focus == chatText.textField)
			{
				return;
			}
			ExternalInterface.call( "ASonRollChatPanel",false);
			SetChatCtrlVisible(false);
			timerUpdate=setTimeout(ScrollHandler,61);//间隔61毫秒执行滚动聊天事件
		}
		
		private function ScrollHandler():void
		{
			ChatListView_mc.ISScroll=true;
			ChatListView_mc.UpdateView();
		}

		private function SetChatCtrlVisible(bShow:Boolean):void
		{
			if (! ChatListView_mc.visible)
			{
				return;
			}
			ChatBg_mc.visible = bShow;
			this.MaskUI = bShow;
		}

		public function OnPushEnter( e:KeyboardEvent ):void
		{
			//trace("OnPushEnter================================");
			//UCShowChatBackBg(true);
			if (root.stage.focus == chatText.textField)
			{
				if (e.keyCode == 13)
				{
					if(InputBlock_mc.visible==false)
					{
						InputBlock_mc.visible=true;
						chatText.textField.selectable=true;
					}
					else
					{
						InputBlock_mc.visible=!InputBlock_mc.visible;
						sendToGame();
						PopFace.visible = false;
						this.ClearTextInputFocus();
						SetChatCtrlVisible(false);
					}
				}
				else if(e.keyCode == 27)
				{// ESC hide
					InputBlock_mc.visible = false;
					PopFace.visible = false;
					UCShowChatBackBg(false);
					this.ClearTextInputFocus();
					e.stopImmediatePropagation();
					e.stopPropagation();
					
					if(_onShowChatInput != null)
					{
						_onShowChatInput(false);
					}
				}
				
				if (nCurrentChannel != TrumpetChannel)
				{
					chatText.textField.maxChars = 120;
				}
				else
				{
					chatText.textField.maxChars = 60;
				}
			}
		}

		private function handleStageClick( e:MouseEvent ):void
		{
			if (! visible)
			{
				return;
			}
			if (  mouseX > 0 && mouseX < width && mouseY < 0 && mouseY < height )
			{
				if (root.stage.focus == chatText.textField)
				{

				}
			}
			else
			{

				if (chatText && root.stage.focus == chatText)
				{
					root.stage.focus =null;//发送聊天内容的时候焦点干掉
				}
			}
		}

		private function onChatInputKeyUp(e:KeyboardEvent):void
		{
			//按↑的时候，将箭头置于末尾
			if ((e as KeyboardEvent).keyCode == Keyboard.UP)
			{
				chatText.textField.setSelection(chatText.textField.text.length,chatText.textField.text.length);
			}
		}
		
		private function onChatInputKeyDown(e:KeyboardEvent):void
		{
			if (chatText==null)
			{
				return;
			}
			var p:int=0;
			if(_chatHistoryArr)
			{
				p = chatIndex % _chatHistoryArr.length;
			}
			if (e.keyCode == Keyboard.UP)
			{
				chatText.clear();
				if (_chatHistoryArr && _chatHistoryArr[p] && p < _chatHistoryArr.length && (_chatHistoryArr[p].toString().length > 0))
				{
					UCAppendInput(_chatHistoryArr[p]);
				}
				chatIndex--;
				if (chatIndex<=0)
				{
					chatIndex = 0;
				}

				chatText.MoveToEnd();
			}
			else if (e.keyCode == Keyboard.DOWN)
			{
				chatText.clear();
				chatIndex++;
				if (chatIndex>=chatIndexMax)
				{
					chatIndex = chatIndexMax - 1;
				}
				if (_chatHistoryArr && _chatHistoryArr[p] && p < _chatHistoryArr.length  && (_chatHistoryArr[p].toString().length > 0))
				{
					UCAppendInput(_chatHistoryArr[p]);
				}

				chatText.MoveToEnd();
			}
			else if (e.keyCode == Keyboard.TAB)
			{
				if (root.stage.focus == chatText.textField)
				{
					ChangeChnnelByTab();
				}
			}
			e.stopImmediatePropagation();
			e.stopPropagation();
			e.preventDefault();
		}

		public function SetTextInputFocus():void
		{
			if (chatText && root.stage.focus == chatText.textField)
			{
				return;
			}
			FocusHandler.getInstance().setFocus(chatText.textField);
		}
		
		public function ClearTextInputFocus():void
		{
			if (chatText && root.stage.focus == null)
			{
				return;
			}
			FocusHandler.getInstance().setFocus(null);
		}

		public function UCShowPrivateName():void
		{
			if (nCurrentChannel == PrivateChannel)
			{
				if (lastPlayerName != null && lastPlayerName.length > 0)
				{
					chatText.clear();
					UCAppendInput(lastPlayerName);
				}
			}
		}

/*		function clickChatOption( e:ButtonEvent ):void
		{
			ExternalInterface.call( "ASChatClickChatOption");
		}
*/
		private function SelectFace(index:int):void
		{//插入表情后，影藏背景输入提示
		    this.InputBlock_mc.show(false);
			chatText.InsertFace( index );
			SetTextInputFocus();
		}

		public function CreateChannel():void
		{
			if (TopLable_mc)
			{
				var i:int=0;
				for(i=0;i<8;i++)
				{
					var chatTab:Button=TopLable_mc.getChildByName("chatTab_"+i) as Button;
					var checkBtn:CheckBox=TopLable_mc.getChildByName("radioBtn_"+i) as CheckBox;
					if(chatTab)
					{
						chatTab.itemid=i;
						if(i==this.SystemChannel)
						{
							chatTab.mouseEnabled=false;
						}
						else
						{
							if(i==this.PrivateChannel)
							{
								(chatTab.getChildByName("chatTabEffect") as MovieClip).gotoAndStop(1);
							}
							chatTab.addEventListener(ButtonEvent.CLICK,ClickChannelTab );//切换聊天频道
						}
					   _TabList.push(chatTab);
					}
					if(checkBtn)
					{
						checkBtn.addEventListener(ButtonEvent.CLICK,FilterChannelTab );//切换聊天频道
						checkBtn.itemid=i;
					}
				}
			}
		}
		
		private function FilterChannelTab(e:ButtonEvent ):void
		{
			var radioBtn:CheckBox=e.currentTarget as CheckBox;
			if(radioBtn)
			{
				ExternalInterface.call("ASHideTips_PlainText",radioBtn );//隐藏tips
				var str:String="MMOGame.Chat.ShowChannel";
			    if(radioBtn && radioBtn.selected==true)
			    {
				    str="MMOGame.Chat.HideChannel";
			    }
				if(radioBtn.itemid==this.PrivateChannel && radioBtn.selected==true){
				    var chk:Button=_TabList[this.PrivateChannel] as Button;
			        if(chk)
			        {
				       (chk.getChildByName("chatTabEffect") as MovieClip).gotoAndStop(1);
			        } 
				}
			    ExternalInterface.call("ASGetStringByID",radioBtn,"tipsHtml",str);
			    ExternalInterface.call("ASShowTips_PlainText",radioBtn );
				ExternalInterface.call( "ASChatOptionClickFilter" , radioBtn.itemid , radioBtn.selected );
			}
		}
		
		private function ClickChannelTab( e:ButtonEvent ):void
		{//切换当前频道
			var btn:Button=e.currentTarget as Button;
			if (btn)
			{
			    ChangeChanelClear();
				this.nCurrentChannel=btn.itemid;
				if (nCurrentChannel == this.WorldChannel || nCurrentChannel == this.TrumpetChannel)
			    {
				   chatText.clear();
			    }
				ExternalInterface.call( "ASChatChannelChange",nCurrentChannel);
				UCSetDropDownListIndex(nCurrentChannel);
				UCShowPrivateName();
				SetTextInputFocus();//设置焦点;
				bShowBg = true;
			}
		}
		
		private function ChangeChnnelByTab():void
		{//Tab切换频道
		    ChangeChanelClear();
		    nCurrentChannel++;
			if(nCurrentChannel>this.TrumpetChannel)
			{
				nCurrentChannel=this.WorldChannel;//切换到世界频道
			}
			if(nCurrentChannel>this.PrivateChannel)
			{
				nCurrentChannel=this.TrumpetChannel;//跳到传音频道 
			}
			UCSetDropDownListIndex(nCurrentChannel);
			ExternalInterface.call( "ASChatChannelChange",nCurrentChannel);
		}
		
		private function ChangeChanelClear():void
		{//改变当前频道
			if (nCurrentChannel == PrivateChannel)
			{
			   chatText.clear();
			}
			this.InputBlock_mc.visible=true;
			this.InputBlock_mc.show();
		}

		public function getHide():Boolean
		{//获取窗口状态
			var bl:Boolean=false;
			if(bHide==MaxBg)
			{
				bl=true;
			}
			return bl;
		}

		private function clickFaceButton(e:MouseEvent):void
		{
			PopFace.visible = ! PopFace.visible;
		}

		public function sendToGame():void
		{
			if (chatText.textField.length > 0)
			{
				ChatListView_mc.ISScroll=true;
				chatIndexMax++;
				chatIndex = chatIndexMax - 1;
				if (chatText.text.indexOf("</TEXTFORMAT>") > 0)
				{
					if (chatText.text.indexOf("<A HREF=") > -1)
					{
						chatText.filterNewLine(true);
					}
					else
					{
						chatText.filterNewLine(false);
					}
				}
				if (chatIndexMax<=100)
				{
					_chatHistoryArr[chatIndex] = chatText.text;
				}
				else
				{
					_chatHistoryArr[chatIndex % 100] = chatText.text;
				}
				ExternalInterface.call( "ASSendChat", chatText.text);
				this.ClearTextInputFocus();//发送聊天内容的时候焦点干掉
			}
			chatText.clear();
			
		}

		public function UCAppendInput(msg:String):void
		{
			if(this.InputBlock_mc)
			{
				this.InputBlock_mc.show();
			}
			chatText.appendHtml(msg);
			SetTextInputFocus();
		}

		public function UCClearChatMsg():void
		{
			ChatListView_mc.ClearChatMsg();
		}

		public function UCAddChatMsg(chatMsg:Array):void
		{
			ChatListView_mc.AddChatMsg(chatMsg);
		}

		public function UCUpdateChannelTabClicked(index:int):void
		{
			for (var i:int = 0; i<_TabList.length; i++)
			{
				if (i != index -1)
				{
					_TabList[i].selected = false;
				}
				else
				{
					_TabList[i].selected = true;
					_TabList[i].click = true;
					ExternalInterface.call( "ASChannelTab", _TabList[i].itemid );
				}
			}
		}

		public function UCShowChatBackBg(v:Boolean):void
		{
		    if(this.btn_set && this.btn_set.selected==true){
				playEffect(true);
				return;//当锁定状态不处理回车事件
			}
			SetChatCtrlVisible(v);
			bShowBg = v;
			if (v)
			{//设置文本
			    SetTextInputFocus();
				UCShowPrivateName();
				ExternalInterface.call( "ASChatChannelChange",nCurrentChannel);
			}
			else
			{
				if (chatText && root.stage.focus == chatText.textField)
				{
					this.ClearTextInputFocus();
				}
				PopFace.visible = false;
			}
			if(bShowBg==false && this.InputBlock_mc)
			{//只有等于影藏的时候才处理
				this.InputBlock_mc.visible=false;
			}
		}
		
		private function playEffect(bl:Boolean):void
		{
			mc_lock.visible=bl;
			if(bl)
			{
				mc_lock.gotoAndPlay(1);
			}
			else
			{
				mc_lock.gotoAndStop(1);
			}
		}

		public function UCShowTrumpet(v:Boolean):void
		{
			if (v==false)
			{
				this.InputBlock_mc.show(true);
			}
			else
			{
				this.InputBlock_mc.show(false);
			}
		}

		public function UCUpdateTrumpetMsg(msg:String, v:Boolean,bGM:Boolean=false):void
		{
			var gm_txt:MovieClip=trumpet_mc.tf_gm;
			gm_txt.visible=bGM;
			var tf_content:TextField=trumpet_mc.txt_trumpet.listItem_tf;
			var format:TextFormat=tf_content.defaultTextFormat;
			if(bGM==true)
			{
				format.indent=83;
			}
			else
			{
				format.indent=45
			}
		    tf_content.htmlText = msg;
			tf_content.defaultTextFormat=format;
			tf_content.setTextFormat(format);
			trumpet_mc.visible = v;
		}

		public function UCSetPrivateChatName(playerName:String):void
		{
			this.nCurrentChannel = PrivateChannel;
			UCSetDropDownListIndex(nCurrentChannel);
			ExternalInterface.call( "ASChatChannelChange",nCurrentChannel);
				
			lastPlayerName = playerName;
			ChangeChanelClear();
			UCAppendInput(playerName);

           	this.SetTextInputFocus();
		}

		public function UCShowPrivateTabEffect(idx:int):void
		{
			if (idx >= _TabList.length)
			{
				return;
			}
			var btn:Button=_TabList[this.PrivateChannel] as Button;
			var checkBtn:CheckBox=TopLable_mc.getChildByName("radioBtn_4") as CheckBox;
			if(checkBtn.selected==false)
			{
				(btn.getChildByName("chatTabEffect") as MovieClip).gotoAndPlay(1);
			} 
		}
		
		private function hideChat(evt:MouseEvent):void
		{
			if(this.btn_set.selected==true)
			{
				this.playEffect(true);
				return;
			}
			bHide ++;
			if(bHide>MaxBg)
			{
				bHide=0;//重新开始计算
			}
			var bl:Boolean=getHide();
            TopLable_mc.visible = !bl;
			ChatBg_mc.visible = !bl;
			ChatListView_mc.visible = !bl;
			this.MaskUI = !bl;
			btn_set.visible = !bl;
		    ChatCleanbutton_mc.visible = !bl;
			if (bl)
			{
				InputBlock_mc.visible = !bl;
				PopFace.visible = false;
			}
			else
			{
				UpdateTextShowArea();
			}
			
			rollOut();
			
		}

		private function UpdateTextShowArea():void
		{//更新文本显示区域
		    var _y:int=0;//正常为0
			var _h:int=this.cavasHeight-180;//高度上限
		    switch(bHide)
			{
				case 0:
				{
					if(y>0)
					{
					   _y=-234;
					}
					else
					{
						_y=0;
					}
					break;
				}
				case 1:
				{
					_y=78;
					break;
				}
				case 2:
				{
					_y=156;
					break;
				}
			}
			trumpet_mc.y -=_y;
		    ChatBg_mc.y -=_y;
			ChatBg_mc.height+=_y;
			ChatListView_mc.y -=_y;
			ChatListView_mc.SetLogicSize(ChatListView_mc.width,ChatListView_mc.height+=_y);
			ChatListView_mc.UpdateView();
		}
		
		//清空频道信息
		private function clearChatHandler(e:MouseEvent):void
		{
			ExternalInterface.call( "ASChatCleanAll");
			UCClearChatMsg();
		}
		
		private function lockChatHandler(e:ButtonEvent):void
		{
			this.removeEventListener(MouseEvent.MOUSE_OVER, onRollOverChatPanel);
			this.removeEventListener(MouseEvent.MOUSE_OUT, onRollOutChatPanel);
			this.playEffect(false);//关闭动画
			var bl:Boolean=this.btn_set.selected;
			if(bl==true)
			{//锁定的时候（锁定的时候聊天不滚动）
				SetChatCtrlVisible(false);
				this.TopLable_mc.visible=false;
				ChatListView_mc.mouseChildren=false;
				ChatListView_mc.mouseEnabled=false;
				this.mouseEnabled=false;
			}
			else
			{//解锁
			    this.mouseEnabled=true;
				this.TopLable_mc.visible=true;
				ChatListView_mc.mouseChildren=true;
				ChatListView_mc.mouseEnabled=true;
				this.addEventListener(MouseEvent.MOUSE_OVER, onRollOverChatPanel);
			    this.addEventListener(MouseEvent.MOUSE_OUT, onRollOutChatPanel);
			}
			ExternalInterface.call("ASChatLockChat",bl);
		}
		
	    public function UCSetDropDownList(dat:Array):void
		{//设置频道选中项
		    this.TopLable_mc.updateTAbCheckBox(dat);
		}

		public function UCSetDropDownListIndex(idx:int):void
		{//重置当前频道 
			this.nCurrentChannel=idx;
			if(InputBlock_mc)
			{
				InputBlock_mc.setHtmlTips(idx);
				if(nCurrentChannel==this.WorldChannel)
				{
					InputBlock_mc.show(true);
				}
			}
		}
		
		private function ChatShowTips(e:MouseEvent):void
		{
			var btn:Button=e.target as Button;
			if(btn==null){
				return;
			}
			var str:String="";
			switch(btn.itemid)
			{
				case 0:
				{
					str="MMOGame.Chat.Hide";
					break;
				}
				case 1:
				{
					str="MMOGame.Chat.Clean";
					break;
				}
				default:
				{
					if(btn.selected==true)
					{
						str="MMOGame.Chat.Lock";
					}
					else
					{
						str="MMOGame.Chat.UnLock";
					}
					break;
				}
			}
			ExternalInterface.call("ASGetStringByID",this,"tipsHtml",str);
			ExternalInterface.call("ASShowTips_PlainText",this );
		}

		private function ChatHideTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_PlainText",this );
		}

		public function UCSetTimeEvent(eventType:int,secTotal:int,secInteval:int):void
		{
			clearTimer();
			_eventType=eventType;
			_timer=secTotal/secInteval;
			secInteval=secInteval*1000;
			if(_timer>0)
			{
				timer.delay=secInteval;
				timer.addEventListener(TimerEvent.TIMER,step);
			    timer.start();
			}
		}
		
		private function step():void
		{
			_timer--;
			ExternalInterface.call( "ASTimeEvent",_eventType);
			if(_timer<=0)
			{
				clearTimer();
			}
		}
		
		private function clearTimer():void
		{
			_timer=0;
			timer.stop();
			timer.removeEventListener(TimerEvent.TIMER,step);
		}

		public function UCAppendChatMsg(msg:String):void
		{

		}
		
		public function UCSetDropDownListData(dat:Array):void
		{

		}
		public function SetFilterChannelNum( newNum:int ):void
		{

		}

		public function SetFilterChannel( pos:int , channelName:String )
		{

		}


/*		public function testDropDownList()
		{
		var arr:Array = new Array();
		arr.push("0");
		arr.push("1");
		arr.push("2");
		arr.push("3");
		arr.push("4");
		arr.push("7");
		UCSetDropDownListData(arr);
		UCSetDropDownList(arr);
		}
		*/

		/*        public function Test():void
		{
		var itemsData:Array = new Array();
		for (var i=0; i<8; i++)
		{
		var item:Object = new Object  ;
		item.htmlText =i+ "<img src='img://MMO_UIIcon.ChatChannelIcon.ChatChannelWorld' vspace='0'/><FONT COLOR='#ff8000'> <a href='event:,4,4769,1231s'><u><FONT COLOR='#6ae6fc'>[1231s]</FONT></u></a> :   <a href='event:,3,99910113,1B48F5D,1,3,B00,B00,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,26'><u><font color='#ffffff' >&lt;短斧&gt;</font></u></a>  </FONT>";
		itemsData.push(item);
		}
		//UCClearChatMsg();
		UCAddChatMsg(itemsData);
		}*/

	}
}