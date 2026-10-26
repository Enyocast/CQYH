package ActionScript3.NPCDialog
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import scaleform.gfx.TextEventEx;
	import flash.events.TextEvent;
	import flash.text.TextField;
	import ActionScript3.Widget.BuffPanel;
	import flash.events.MouseEvent;
	import flash.text.TextFieldAutoSize;
	import ActionScript3.Quest.QuestDetailData;
	import flash.display.Sprite;
	import flash.display.DisplayObject;
	//import ActionScript3.Quest.QuestTraceListItem;
	import scaleform.clik.events.ButtonEvent;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.Quest.QuestAwardIconData;
	import scaleform.clik.controls.UILoader;

	public class NPCDialogContent extends UIComponent
	{
		public var _btn_reject:Button;
		public var _btn_accept:Button;
		public var _btn_submit:Button;
		public var _btn_abort:Button;
		public var _btn_close_diag:Button;
		
		// 用于新手引导挂接控件
		public var _guide_quest:MovieClip;
		public var _guide_npc:MovieClip;
		
		public var _award_money_caption:TextField;
		public var _award_money_count:TextField;
		public var _award_money_caption_ex:TextField;
		public var _award_money_count_ex:TextField;
		public var _award_exp_caption:TextField;
		public var _award_exp_count:TextField;
		//public var _line_mc:MovieClip;
		public var _btn_page_prev:Button;
		public var _btn_page_next:MovieClip;

		public var _diag_txt:TextField;
		//public var awardTitle:TextField;
		public var mc_title:MovieClip;
		public var mc_line:MovieClip;
		public var _award_mc:MovieClip;
        public var btn_hit:Button;
		public var _award_select_title_txt:TextField;
		public var _award_select_mc:MovieClip;
		public var _awardTitleBg_mc:MovieClip; //任务奖励标题背景

		public var _parentPanel:INPCDialogPanel;

		var _diagData:Array;
		var _currentPageIndx:int;
		//var _optionButtonContainer:Sprite;
		var _optionButtonList:Array;
		var _currentSelectAward:int;
		
		public var _showPageNavOnQuest:Boolean;

		public var _award_icon_list:Array;
		public var _award_select_icon_list:Array;

		public static const C_MinDiagTxtHeight = 40;
		public static const C_AwardItemHeight = 60;

		override protected function configUI():void
		{
			super.configUI();
			_optionButtonList = new Array  ;
			_award_icon_list = new Array  ;
			_award_select_icon_list = new Array  ;

			initIcon(_award_mc, _award_icon_list);
			initIcon(_award_select_mc, _award_select_icon_list);

			_btn_reject.addEventListener(MouseEvent.CLICK, onReject);
			_btn_close_diag.addEventListener(MouseEvent.CLICK, onReject);
			_btn_accept.addEventListener(MouseEvent.CLICK, onAccept);
			_btn_submit.addEventListener(MouseEvent.CLICK, onSubmit);
			_btn_abort.addEventListener(MouseEvent.CLICK, onAbort);
			btn_hit.addEventListener(MouseEvent.CLICK,onClickHandler);

			_btn_page_prev.addEventListener(MouseEvent.CLICK, onPrevPage);
			_btn_page_next.addEventListener(MouseEvent.CLICK, onNextPage);


			var descTxt:TextField = _diag_txt;
			descTxt.autoSize = flash.text.TextFieldAutoSize.LEFT;
			descTxt.wordWrap = true;
			descTxt.addEventListener(TextEvent.LINK, onLinkCallBack);
			descTxt.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			descTxt.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);

			var i:int;
			for (i = 0; i < 4; i++)
			{
				var iconMc:MovieClip = _award_select_mc.getChildByName( "_awardIcon" + i ) as MovieClip;

				iconMc.addEventListener(MouseEvent.CLICK, onSelectAward);
			}
			//_optionButtonContainer = new Sprite;
			//this.addChild(_optionButtonContainer);
			_guide_quest.visible = true;
			_guide_quest.mouseChildren = false;
			_guide_quest.mouseEnabled = false;
			
			_guide_npc.visible = true;
			_guide_npc.mouseChildren = false;
			_guide_npc.mouseEnabled = false;
		}
		
		private function onClickHandler(evt:MouseEvent):void
		{
			if(evt.target ==btn_hit){
				onNextPage(null);
			}
		}

		function initIcon(mc:MovieClip, arr:Array)
		{
			var i:int;
			for (i = 0; i < 4; i++)
			{
				var iconMc:MovieClip = mc.getChildByName( "_awardIcon" + i ) as MovieClip;

				arr.push(iconMc);
			}
		}

		public function fillAwardItemIcon(itemIdx:int, iconMc:MovieClip, idx:int, itemTemplateID:Number, itemCnt:int, itemName:String, iconName:String)
		{
			if (iconName == "")
			{
				iconMc.visible = false;
			}
			else
			{

				var awardItem:MyItemSlot = iconMc.getChildByName("_iconSlot") as MyItemSlot;
				var itemNameTxt:TextField = iconMc.getChildByName("_itemNameTxt") as TextField;
				var itemCount:TextField = iconMc.getChildByName("_itemCount") as TextField;

				iconMc.visible = true;
				//awardItem.itemIndex = itemIdx;
				//awardItem.itemSlotIcon.IconLoader_mc.source = "img://" + iconName;
				//awardItem.containerID = -1;
				//awardItem.slotID = -1;
				//awardItem.SlotType = -1;
				//awardItem.ItemTemplateID = itemTemplateID;
				
				awardItem.SetSlotType(19);
				awardItem.SetData(1, iconName, itemTemplateID, "", 0, -1, -1);
							
				itemNameTxt.htmlText = itemName;
				itemCount.text = "x" + itemCnt.toString();
			}
		}

		function clearSelect()
		{
			var i:int;
			for (i = 0; i < 4; i++)
			{
				var iconMc:MovieClip = _award_select_mc.getChildByName( "_awardIcon" + i ) as MovieClip;

				var awardItemIcon:MyItemSlot = iconMc.getChildByName("_iconSlot") as MyItemSlot;
				awardItemIcon.selected = false;
			}
		}
		
		function onSelectAward(e:MouseEvent)
		{
			//var iconMc:MovieClip = e.target as MovieClip;
			//var awardItem:MyItemSlot = iconMc.getChildByName("_iconSlot") as MyItemSlot;
			var awardItem:MyItemSlot = e.target as MyItemSlot;
			if(awardItem == null)
			{
				return;
			}
			
			clearSelect();
			
			awardItem.selected = true;
			if(this.getCurrentPageData().quest_detail_data.quest_is_compassable)
			{
				var selectIndex:int = -1;
				var i:int;
				for (i = 0; i < 4; i++)
				{
					var iconMc:MovieClip = _award_select_mc.getChildByName( "_awardIcon" + i ) as MovieClip;
					var awardItemIcon:MyItemSlot = iconMc.getChildByName("_iconSlot") as MyItemSlot;
					var select_border:MovieClip = awardItemIcon.getChildByName("_select_border") as MovieClip
					if (select_border.visible == true)
					{
						selectIndex = i;
						break;
					}
				}
				
				ExternalInterface.call( "ASSelectAward", awardItem, selectIndex, awardItem.ItemTemplateID);
			}
		}

		function onLinkCallBack(e:TextEvent)
		{
			playSound("menu_click");
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}

		function onLinkOverCallBack(e:TextEventEx)
		{
			playSound("menu_highlight");
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		function onLinkOutCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		function updatePageBtnVisible()
		{
			this._btn_page_prev.visible = _currentPageIndx > 0;
			this._btn_page_next.visible = _currentPageIndx < _diagData.length - 1;
		}

		function setPageBtnVisible(v:Boolean)
		{
			this._btn_page_prev.visible = v;
			this._btn_page_next.visible = v;			
		}

		function onPrevPage(e:MouseEvent):void
		{
			if (_currentPageIndx > 0)
			{
				--_currentPageIndx;
				ExternalInterface.call( "ASNPCDialogPage", _currentPageIndx );
				updatePageBtnVisible();// 先更新，后面任务页面会隐藏
				updateToPage(_currentPageIndx);
			}
		}

		function onNextPage(e:MouseEvent):void
		{
			if (_currentPageIndx < (_diagData.length-1))
			{
				++_currentPageIndx;
				ExternalInterface.call( "ASNPCDialogPage", _currentPageIndx );
				updatePageBtnVisible();
				updateToPage(_currentPageIndx);
			}
		}
		
		function setQuestButtonsVisible(v:Boolean)
		{
			this._btn_accept.visible = v;
			this._btn_reject.visible = v;
			this._btn_submit.visible = v;
			this._btn_abort.visible = false;
			this._btn_close_diag.visible = v;
			
			this._guide_quest.visible = v;
		}
		
		function updateQuestButtons()
		{			
			setQuestButtonsVisible(false);
			
			var dat:NPCDialogData = getCurrentPageData();
			if (dat != null)
			{
				if (! dat.quest_detail_data.quest_is_accepted)
				{
					this._btn_accept.visible = true;
					this._btn_reject.visible = true;
				}
				else
				{
					this._btn_submit.visible = true;
					this._btn_close_diag.visible = true;
					
					if (dat.quest_detail_data.quest_is_compassable)
					{
						this._btn_submit.enabled = true;
					}
					else
					{
						this._btn_submit.enabled = false;
					}
				}
				
				this._guide_quest.visible = this._btn_accept.visible || this._btn_reject.visible || this._btn_submit.visible || this._btn_close_diag.visible;
			}
			else
			{
				ExternalInterface.call("ASTrace", "---- [NPCDialogContent::updateQuestButtons] diag data is null!");
			}
		}

		function onReject()
		{
			ExternalInterface.call("ASCloseDialog");
		}

		function onAccept()
		{
			var dat:NPCDialogData = getCurrentPageData();
			ExternalInterface.call("ASAcceptQuest", dat.quest_detail_data.quest_id, dat.quest_share, dat.quest_share_id);				
		}
		
		function onSubmit()
		{
			var dat:NPCDialogData = getCurrentPageData();
			ExternalInterface.call("ASSubmitQuest", dat.quest_detail_data.quest_id);
		}
		
		function onAbort()
		{
			var dat:NPCDialogData = getCurrentPageData();
			ExternalInterface.call("ASAbortQuest", dat.quest_detail_data.quest_id);
		}

		public function updateDiagData(dat:Array)
		{
			resetAll();
			_diagData = dat;
			updateToPage(0);
		}

		function showAwardMoney(v:Boolean)
		{						
			_award_money_caption.visible = v;			
			_award_money_count.visible = v;			
			_award_money_caption_ex.visible = v;			
			_award_money_count_ex.visible = v;
			_award_exp_caption.visible = v;
			_award_exp_count.visible = v;
		}
		
		function showAwrard(v:Boolean)
		{
			this._award_mc.visible = v;
			//this._award_title_txt.visible = v;
			this._awardTitleBg_mc.visible = v;
            this.mc_title.visible=v;
			this._award_select_mc.visible = v;
			this._award_select_title_txt.visible = v;
			
			showAwardMoney(v);
		}

		private function resetAll():void
		{
			this._diag_txt.visible = false;
			
			this.setQuestButtonsVisible(false);
			
			this._btn_page_next.visible = false;
			this._btn_page_prev.visible = false;
			

			_currentSelectAward = -1;

			showAwrard(false);			
			if(_optionButtonList)
			{
				var l:int=_optionButtonList.length;
				var i:int=l-1;
				for(i;i>=0;i--)
				{
					this.removeChild(_optionButtonList[i]);
					_optionButtonList.pop();
				}
			}
		}

		function updateToPage(i:int)
		{
			_currentPageIndx = i;
			if (i < _diagData.length)
			{
				updateDiagContents(getDiagData(i));
			}
		}

		function getDiagData(i:int):NPCDialogData
		{
			if (i < this._diagData.length)
			{
				return _diagData[i] as NPCDialogData;
			}

			return null;
		}

		function getCurrentPageData():NPCDialogData
		{
			return getDiagData(_currentPageIndx);
		}

		function updateDiagContents(dat:NPCDialogData):void
		{
			resetAll();

			this._parentPanel.setNPCName(dat.diag_npc_name);

			switch (dat.diag_type)
			{
				case NPCDialogData.DiagDataType_Dialog :
					this.updateDiagContent(dat);
					break;

				case NPCDialogData.DiagDataType_QuestAccept :
					this.updateQuestContent(dat.quest_detail_data);
					break;
			}

		}

		function setupDiagTxt(txt:String)
		{
			this._diag_txt.visible = true;
			this._diag_txt.wordWrap = true;
			this._diag_txt.autoSize = flash.text.TextFieldAutoSize.LEFT;
			this._diag_txt.htmlText = txt;
			if (_diag_txt.textHeight < C_MinDiagTxtHeight)
			{
				this._diag_txt.height = C_MinDiagTxtHeight;
			}
			else
			{
				this._diag_txt.height = this._diag_txt.textHeight;
			}
		}

		function updateDiagContent(dat:NPCDialogData):void
		{
			if (dat != null)
			{
				this.setupDiagTxt(dat.diag_text);
				
				setQuestButtonsVisible(false);

               var nextY:int =_diag_txt.y+105;

			    this._awardTitleBg_mc.visible=false;

				if (dat.option_list != null)
				{
					var lenght:int=dat.option_list.length;
					if(lenght>0){
				    this._awardTitleBg_mc.visible=true;
					for (var i:int = 0; i < lenght; ++i)
					{
						var opt:NPCDialogOptionData = dat.option_list[i] as NPCDialogOptionData;

						var btn:OptionButton = new OptionButton();

						btn._optionID = opt.option_id;
						btn.label = opt.option_label;
						btn.y = nextY;
						btn.x = this._diag_txt.x;
						btn.validateNow();
						
						btn.visible = true;
						btn.addEventListener(ButtonEvent.CLICK, onActionClick);
		
						var iconLoader:UILoader = btn.getChildByName("_option_icon") as UILoader;
						
						if(iconLoader != null && opt.option_icon != null)
						{
							//ExternalInterface.call("ASTrace", "************ updateDiagContent 8:" + opt.option_icon);						
							if(opt.option_icon.length > 0)
							{
								// 不正确的source参数会出问题
								iconLoader.source = opt.option_icon;
							}
							
							//ExternalInterface.call("ASTrace", "************ updateDiagContent 8A:" + opt.option_icon.length);													
							iconLoader.visible = opt.option_icon.length > 0;
							
						}
						
						//ExternalInterface.call("ASTrace", "************ updateDiagContent 9:" + opt.toString());						
						
						nextY +=  btn.height;
						//ExternalInterface.call("ASTrace", "************ Create Diag Option:" + opt.toString());

						//this._optionButtonContainer.addChild(btn as DisplayObject);
						_optionButtonList.push(btn);
						this.addChild(btn);
					}

					//this._optionButtonContainer.height = nextY;
				   }
			    }
				updatePageBtnVisible();
				updatePageBtnPos(nextY);
			}
			else
			{
				ExternalInterface.call("ASTrace", "---- [NPCDialogContent::updateDiagContent] diag data is null!");
			}
		}
		
		function updatePageBtnPos(nextY:int):void
		{
			if((nextY-145)>60){
				_awardTitleBg_mc.height=nextY-145;
			}else{
				_awardTitleBg_mc.height=60;
			}
			if(_awardTitleBg_mc.visible==true){
				mc_line.y=152+_awardTitleBg_mc.height-3;
			}else{
				mc_line.y=152;
			}
		}
		
		function updateQuestContent(dat:QuestDetailData):void
		{
			ExternalInterface.call( "ASSelectAward", null, -1, 0);
			if (dat != null)
			{
				clearSelect();
				setupDiagTxt(dat.quest_desc);
				
				updateQuestButtons();
				
				//_line_mc.visible = true;
				var nextY:int = this._diag_txt.y + this._diag_txt.height + 10;

				var i:int = 0;
				var awardDat:QuestAwardIconData;

				_awardTitleBg_mc.visible = true;				
				this.mc_title.visible=true;
/*				if ((dat.quest_awards != null && dat.quest_awards.length) > 0
					|| (dat.quest_award_select != null && dat.quest_award_select.length > 0))
				{
					// 离上面的文本框多20像素

				}
				else
				{
					// 只显示金钱和经验，需要靠下显示
					
				}*/
				
				// _awardTitleBg_mc 高度单独算
				nextY = this._awardTitleBg_mc.y + 30;				

				if (dat.quest_awards != null && dat.quest_awards.length > 0)
				{					
					//this._award_title_txt.visible = true;
					//this._award_title_txt.y = nextY;
					//nextY +=  this._award_title_txt.height;					
					
					this._award_mc.visible = true;
					this._award_mc.y = nextY;
					nextY +=  C_AwardItemHeight;//this._award_mc.height; SlotItem有闪光特效

					for (i = 0; i < dat.quest_awards.length; ++i)
					{
						if (i < _award_icon_list.length)
						{
							awardDat = dat.quest_awards[i] as QuestAwardIconData;
							if (awardDat != null)
							{
								this.fillAwardItemIcon(awardDat.item_index, _award_icon_list[i] as MovieClip, i, awardDat.item_template_id, awardDat.item_count, awardDat.item_name, awardDat.icon_img_name);
							}
						}
					}

					for (i = i; i < _award_icon_list.length; ++i)
					{
						this.fillAwardItemIcon(awardDat.item_index, _award_icon_list[i] as MovieClip, i, 0, 0, "", "");
					}
				}



				if (dat.quest_award_select != null && dat.quest_award_select.length > 0)
				{
					this._award_select_title_txt.visible = true;
					this._award_select_title_txt.text = "您可以得到以下奖励：";
					if (dat.quest_award_select.length > 1)
					{
						this._award_select_title_txt.text = "你可以从下列奖励中选择一个：";
					}
					this._awardTitleBg_mc.visible = true;
					this._award_select_title_txt.y = nextY;
					nextY +=  this._award_select_title_txt.height;

					this._award_select_mc.visible = true;
					this._award_select_mc.y = nextY;					

										
					nextY +=  C_AwardItemHeight;//this._award_select_mc.height;

					for (i = 0; i < dat.quest_award_select.length; ++i)
					{
						if (i < this._award_select_icon_list.length)
						{
							awardDat = dat.quest_award_select[i] as QuestAwardIconData;
							if (awardDat != null)
							{
								this.fillAwardItemIcon(awardDat.item_index, _award_select_icon_list[i] as MovieClip, i, awardDat.item_template_id, awardDat.item_count, awardDat.item_name, awardDat.icon_img_name);
							}
						}
					}

					for (i = i; i < _award_select_icon_list.length; ++i)
					{
						this.fillAwardItemIcon(awardDat.item_index, _award_select_icon_list[i] as MovieClip, i, 0, 0, "", "");
					}
				}
				
				showAwardMoney(true);
				this._award_money_caption.text = dat.quest_award_money_caption;
				_award_money_caption.width = _award_money_caption.textWidth + 12;
				_award_money_caption.visible=true;
				if(dat.quest_award_money==""){
					this._award_money_caption.visible = false;
				}
				this._award_money_count.htmlText = dat.quest_award_money;
				
				this._award_money_count.x = this._award_money_caption.x +  this._award_money_caption.textWidth;
				
				this._award_money_caption_ex.text = dat.quest_award_money_caption_ex;
				_award_money_caption_ex.width = _award_money_caption_ex.textWidth + 12;
				this._award_money_count_ex.htmlText = dat.quest_award_money_ex;
				this._award_money_count_ex.x = this._award_money_caption_ex.x +  this._award_money_caption_ex.textWidth;
				
				_award_exp_caption.text = dat.quest_award_exp_caption;
				_award_exp_count.text = dat.quest_award_exp.toString();
				this._award_exp_count.x = this._award_exp_caption.x + _award_exp_caption.textWidth;
				nextY+=12;
				_award_exp_caption.y = nextY;
				_award_exp_count.y = nextY;
								
				_award_money_caption.y = nextY;
				_award_money_count.y = nextY ;
				_award_money_caption_ex.y = nextY;
				_award_money_count_ex.y = nextY ;
				
				nextY = _award_exp_caption.y + _award_exp_caption.height + 12;
				
				// 只算Y，X摆放时决定
				this._btn_accept.y = nextY;
				this._btn_reject.y = nextY;
				this._btn_submit.y = nextY;
				this._btn_abort.y = nextY;
				this._btn_close_diag.y = nextY;

				nextY +=  this._btn_accept.height;

				updatePageBtnVisible();
				updatePageBtnPos(nextY);
			}
			else
			{
				ExternalInterface.call("ASTrace", "---- [NPCDialogContent::updateQuestContent] quest data is null!");

			}
		}

		private function onActionClick(e:ButtonEvent):void
		{
			var btn:DialogOptionButton = e.target as DialogOptionButton;
			if (btn)
			{
				ExternalInterface.call("ASSelectDiagOption", btn._optionID);
			}
		}
		
		 public function PlayAnimation(timer:int):void
		 {
			 timer+=2000;
			 _btn_page_next.UCPlay(timer);
		 }
	}
}