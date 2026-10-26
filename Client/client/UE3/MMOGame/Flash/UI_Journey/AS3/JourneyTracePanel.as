package UI_Journey.AS3
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.filters.ColorMatrixFilter;
	import flash.filters.GlowFilter;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.utils.Dictionary;
	import flash.utils.clearTimeout;
	import flash.utils.setTimeout;
	
	import ActionScript3.GameDispathcher;
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Common.Utils.StyleType;
	import ActionScript3.Quest.QuestTraceData;
	import ActionScript3.Quest.QuestTraceTargetData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.events.ButtonEvent;
	
	public class JourneyTracePanel extends MyPanel
	{
		private static const PANEL_WIDTH:Number = 236;
		private static const HIDE_BUTTON_TOP_POS_Y:Number = 56;
		private static const HIDE_BUTTON_BOTTOM_POS_Y:Number = 373;
		
		public var bg_mask_mc:MovieClip;
		public var list_bg_mc:MovieClip;
		public var journey_trace_tips_mc:JourneyTraceTips;
		public var NPC_icon:UILoader;
		public var progressBar_fill_mc:JourneyProgressBarFill;
		public var btn_previous:Button;
		public var btn_next:Button;
		public var btn_expand:Button;
		public var btn_fold:Button;
		public var btn_hide:Button;
		public var btn_show:Button;
		public var FX_shine_mc:MovieClip;
		
		public var txt_chapter_title:TextField;
		public var btn_bonus:Button;
		public var scrolling_view_mc:ScrollingView;
		public var display_mc:JourneyTraceList;
		public var scroll_bar_mc:ScrollBar;
		public var guide_layer_mc:MovieClip;
		public var guide_award_mc:MovieClip;
		
		protected var _chapter:Array;
		protected var _chapterIndex:int = -1;
		
		private var _glowFilter:GlowFilter;
		private var _grayFilter:ColorMatrixFilter;
		
		private var _questTracelistItemDic:Dictionary = new Dictionary(false);
		private var _journeyTraceTips:Array;
		private var _listExpand:Boolean = false;
		private var _childVisibleData:Array = [];
		
		private var _localTest:Boolean = false;//true|false
		
		private var _awards_str:String;
		//don't update panel data when panel is invisible,store data and update data after reopen panel.
		private var _lastUpdateData:JourneyTraceData;
		private var _lastQuestTraceData:QuestTraceData;
		private var _isFolding:Boolean;
		
		public function JourneyTracePanel()
		{
			super();
		}
		
		override protected function configUI():void
		{
			ShowMode="TASK";
			super.configUI();
			btn_previous.addEventListener(ButtonEvent.CLICK, gotoPreChapter, false, 0, true);
			btn_next.addEventListener(ButtonEvent.CLICK, gotoNextChapter, false, 0, true);
			btn_bonus.addEventListener(ButtonEvent.CLICK, getChapterCompleteBonus, false, 0, true);
			btn_bonus.addEventListener("rollOver", onBonusRollOver);
			btn_bonus.addEventListener("rollOut", onBonusRollOut);
			
			_glowFilter = new GlowFilter(0xffffff,1,5,5,2,2,false,false);
			_grayFilter = StyleType.getInstance().getGrayFilter();
			
			NPC_icon.addEventListener(MouseEvent.MOUSE_OVER, onMouseOverIcon);
			NPC_icon.addEventListener(MouseEvent.MOUSE_OUT, onMouseOutIcon);
			NPC_icon.addEventListener(MouseEvent.CLICK, onShowNPCTips);
			
			addEventListener(MouseEvent.MOUSE_OVER, onMouseOverPanel);
			addEventListener(MouseEvent.MOUSE_OUT, onMouseOutPanel);
			//	btn_bonus.enabled =  btn_next.enabled = btn_previous.enabled = false;
			journey_trace_tips_mc.mouseEnabled = false;
			journey_trace_tips_mc.visible = false;
			onMouseOutPanel(null);
			
			guide_layer_mc.mouseEnabled = guide_layer_mc.mouseChildren = false;
			display_mc.setPanelDicReference(_questTracelistItemDic);
			display_mc.setGuideLayerReference(guide_layer_mc);
			scroll_bar_mc.addEventListener(Event.SCROLL, handleScroll, false, 0, true);
			scroll_bar_mc.addEventListener(Event.CHANGE, handleScroll, false, 0, true);
			
			guide_award_mc.mouseEnabled = guide_award_mc.mouseChildren = false;
			
			txt_chapter_title.mouseEnabled = true;
			txt_chapter_title.addEventListener(MouseEvent.CLICK, onExpandList, false, 0, true);
			
			btn_expand.addEventListener(MouseEvent.CLICK, onExpandList, false, 0, true);
			btn_fold.addEventListener(MouseEvent.CLICK, onExpandList, false, 0, true);
			btn_show.addEventListener(MouseEvent.CLICK, onShowTracePanel, false, 0, true);
			btn_hide.addEventListener(MouseEvent.CLICK, onHideTracePanel, false, 0, true);
			
			btn_show.visible = _isFolding = false;
			
			bg_mask_mc.visible = false;
			list_bg_mc.addEventListener(MouseEvent.CLICK, onClickListBg);

			btn_fold.visible = _listExpand = true;
			btn_expand.visible = !_listExpand;
			btn_hide.y = _listExpand ?  HIDE_BUTTON_BOTTOM_POS_Y : HIDE_BUTTON_TOP_POS_Y;
			FX_shine_mc.mouseChildren = FX_shine_mc.mouseEnabled = false;
			FX_shine_mc.visible = false;
			FX_shine_mc.gotoAndStop(1);
			
			if(_localTest)
			{
				UCSetChapterData(["第一章","第二章"]);
				UCSetTracePanelEnable(false);
			}
			_awards_str = "";
			
			progressBar_fill_mc.addEventListener("rollOver", onProgressRollOver);
			progressBar_fill_mc.addEventListener("rollOut", onProgressRollOut);
			stageChangeHandler(null);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x = this.cavasWidth - PANEL_WIDTH;
		}
		
		protected function handleScroll(event:Event):void
		{
			if(guide_layer_mc)
			{
				guide_layer_mc.y = display_mc.y;
			}
			checkGuidePosition();
		}
		
		private function onExpandList(evt:MouseEvent):void
		{
			if(_listExpand)
			{
				display_mc.visible = scroll_bar_mc.visible = false;
				guide_layer_mc.visible = false;
				bg_mask_mc.visible = true;
				list_bg_mc.mask = bg_mask_mc;
				_listExpand = false;
			}
			else
			{
				display_mc.visible = scroll_bar_mc.visible = true;
				guide_layer_mc.visible = true;
				bg_mask_mc.visible = false;
				list_bg_mc.mask = null;
				_listExpand = true;
			}
			btn_fold.visible = _listExpand;
			btn_expand.visible = !_listExpand;
			btn_hide.y = _listExpand ?  HIDE_BUTTON_BOTTOM_POS_Y : HIDE_BUTTON_TOP_POS_Y;
		}
		
		private function onMouseOverIcon(event:MouseEvent):void
		{
			NPC_icon.filters = [_glowFilter];
		}
		
		private function onMouseOutIcon(event:MouseEvent):void
		{
			NPC_icon.filters = null;
		}
		
		private function setIconGray(mc:MovieClip, gray:Boolean):void
		{
			if(! mc)
			{
				return;
			}
			
			if(gray)
			{
				mc.filters = [_grayFilter];
			}
			else
			{
				mc.filters = null;
			}
		}
		
		private function onShowNPCTips(event:MouseEvent):void
		{
			if(_journeyTraceTips && _journeyTraceTips.length > 0)
			{
				var idx:int = _journeyTraceTips.length * Math.random();
				var tipsInfo:String = _journeyTraceTips[idx];
				journey_trace_tips_mc.updateTips(tipsInfo);
				ExternalInterface.call("ASUpdateNPCTips", idx);
			}
			if(journey_trace_tips_mc.visible == false)
			{
				journey_trace_tips_mc.visible = true;
			}
		}
		
		public function onMouseOverPanel(event:MouseEvent):void
		{
			btn_expand.alpha = btn_fold.alpha = scroll_bar_mc.alpha = list_bg_mc.alpha = 1.0;
		}
		
		public function onMouseOutPanel(event:MouseEvent)
		{
			scroll_bar_mc.alpha = 0.0;
			btn_expand.alpha = btn_fold.alpha = 0.5;
			list_bg_mc.alpha = 0.3;
		}
		
		private function gotoPreChapter(evt:ButtonEvent):void
		{
			if(_chapterIndex - 1 >= 0)
			{
				_chapterIndex--;
				txt_chapter_title.text = _chapter[_chapterIndex];
				ExternalInterface.call("ASGotoChapter", _chapterIndex + 1);
				UCShowPreChapterHint(false, "");
				updateChapterButtonGroup();
			}
		}
		
		private function gotoNextChapter(evt:ButtonEvent):void
		{
			if(_chapter != null)
			{
				if(_chapterIndex + 1 < _chapter.length)
				{
					_chapterIndex++;
					txt_chapter_title.text = _chapter[_chapterIndex];
					ExternalInterface.call("ASGotoChapter", _chapterIndex + 1);
					updateChapterButtonGroup();
				}
			}
		}
		
		public function UCSetTracePanelEnable($enable:Boolean):void
		{
			if($enable)
			{
				if(_isFolding)
				{
					onShowTracePanel(null);
				}
			}
			else
			{
				if(!_isFolding)
				{
					onHideTracePanel(null);
				}
			}
		}
		
		private function onShowTracePanel(evt:MouseEvent):void
		{
			//ExternalInterface.call("ASShowJourneyTracePanle");
			var numChild:int = this.numChildren;
			var child:DisplayObject;
			for(var i:int = 0; i < numChild; i++)
			{
				child = getChildAt(i);
				child.visible = _childVisibleData[i];
			}
			btn_show.visible = _isFolding = false;
			_childVisibleData.length = 0;
			if(_lastUpdateData != null)
			{
				UCUpdateJourneyTraceInfo(_lastUpdateData);
				_lastUpdateData = null;
			}
			if(_lastQuestTraceData != null)
			{
				UCUpdateQuestTraceListItemData(_lastQuestTraceData);
				_lastQuestTraceData = null;
			}
			guide_award_mc.visible = true;
		}
		
		private function onHideTracePanel(evt:MouseEvent):void
		{
			//ExternalInterface.call("ASHideJourneyTracePanel");
			var numChild:int = this.numChildren;
			var child:DisplayObject;
			_childVisibleData.length = numChild;
			for(var i:int = 0; i < numChild; i++)
			{
				child = getChildAt(i);
				_childVisibleData[i] = child.visible;
				child.visible = false;
			}
			btn_show.visible = _isFolding = true;
			guide_award_mc.visible = false;
		}
		
		public function onClickListBg(e:MouseEvent)
		{
			e.stopImmediatePropagation();
			e.stopPropagation();
			e.preventDefault();
		}
		
		public function onBonusRollOver(e:Event)
		{
			var cur_mc:Button = e.currentTarget as Button;
			if (cur_mc)
			{
				ExternalInterface.call("ASShowTips_PlainText_WithString", cur_mc, _awards_str);
			}
		}
		
		public function onBonusRollOut(e:Event)
		{
			var cur_mc:Button = e.currentTarget as Button;
			if (cur_mc)
			{
				ExternalInterface.call("ASHideTips_Text", cur_mc);
			}
		}
		
		private function getChapterCompleteBonus(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASShowAwardsPanel", _chapterIndex + 1);
			if(_localTest)
			{
				//UCUpdateQuestTraceListItemData(testUpdateQuestData());
				UCUpdateJourneyTraceInfo(null);
			}
		}
		
		public function onProgressRollOver(e:Event)
		{
			var cur_mc:JourneyProgressBarFill = e.currentTarget as JourneyProgressBarFill;
			if (cur_mc)
			{
				ExternalInterface.call("ASShowTips_PlainText_WithString", cur_mc, cur_mc._progress_str);
			}
		}
		
		public function onProgressRollOut(e:Event)
		{
			var cur_mc:JourneyProgressBarFill = e.currentTarget as JourneyProgressBarFill;
			if (cur_mc)
			{
				ExternalInterface.call("ASHideTips_Text", cur_mc);
			}
		}
		
		public function UCSetChapterData(chapter:Array, curChapterIndex:int = 0):void
		{
			_chapter = chapter;
			if(_chapter == null)
			{
				return;
			}
			if(curChapterIndex <= 0 || curChapterIndex > _chapter.length)
			{
				curChapterIndex = _chapter.length;
			}
			_chapterIndex = curChapterIndex - 1;//different to UC
			txt_chapter_title.text = _chapter[_chapterIndex];
			ExternalInterface.call("ASGotoChapter", curChapterIndex);
			updateChapterButtonGroup();
			
			//test code
			if(_localTest)
			{
				UCUpdateJourneyTraceInfo(null);
				//UCUpdateJourneyTraceProgress(253,1000);
				//	UCShowGuideArrow(true, 0, "guide_mc");
			}
		}
		
		private function updateChapterButtonGroup():void
		{
			if(_chapter && _chapterIndex < _chapter.length - 1)
			{
				setIconGray(btn_next, false);
			}
			else
			{
				setIconGray(btn_next, true);
			}
			if(_chapter && _chapterIndex > 0)
			{
				setIconGray(btn_previous, false);
			}
			else
			{
				setIconGray(btn_previous, true);
			}
		}
		
		private var _testEmpty:Boolean = false;
		
		public function UCUpdateJourneyTraceInfo(data:JourneyTraceData):void
		{
			if(_isFolding)
			{
				_lastUpdateData = data;
				return;
			}
			if(_localTest)
			{
				data = getTestJourneyTraceData(_testEmpty);
				data.chapterComplete = false;
				_testEmpty = !_testEmpty;
			}
			NPC_icon.source = data.journeyTraceIcon;
			_journeyTraceTips = data.journeyTraceTips;
			
			if(data.chapterProgressData)
			{
				UCUpdateJourneyTraceProgress(data.chapterProgressData.curReputation, data.chapterProgressData.maxReputation, data.chapterProgressData.minReputation, data.chapterComplete, data.hasGetReward);
			}

			display_mc.updateAchievementAwardData(data.achievementRewardData);
			display_mc.updateListData(data.journeyTraceList);
			_awards_str = data.journeyAwardsStr;
		}
		
		//单独更新声望进度
		public function UCUpdateJourneyTraceProgress(curReputation:int, maxReputation:int, minReputation:int = 0, chapterComplete:Boolean = false, hasGetReward:Boolean = false):void
		{
			progressBar_fill_mc.UpdateData(curReputation, maxReputation, minReputation);
			// 按钮失效的时候，不接受悬停消息，所以屏蔽
			//	btn_bonus.enabled = data.chapterComplete;
			if(chapterComplete)
			{
				if(hasGetReward)
				{
					FX_shine_mc.visible = false;
					FX_shine_mc.gotoAndStop(1);
					setIconGray(btn_bonus, true);
				}
				else
				{
					FX_shine_mc.visible = true;
					if(FX_shine_mc.currentFrame == 1)
					{
						FX_shine_mc.gotoAndPlay(1);
					}
					setIconGray(btn_bonus, false);
				}
			}
			else
			{
				setIconGray(btn_bonus, true);
				FX_shine_mc.visible = false;
				FX_shine_mc.gotoAndStop(1);
			}
		}
		
		//set achievement trace reward data
		public function UCUpdateAchievementRewardData(data:Object):void
		{
			display_mc.updateAchievementAwardData(data);
			display_mc.updateLayout();
		}
		
		public function UCUpdateQuestTraceListItemData(data:Object):void
		{
			//
			if(_isFolding)
			{
				_lastQuestTraceData = data as QuestTraceData;
				return;
			}
			var quest_trace_data:QuestTraceData = data as QuestTraceData;
			if(quest_trace_data != null)
			{
				var questId:int = quest_trace_data.quest_id;
				if(_questTracelistItemDic[questId] != null)
				{
					var item:JourneyTraceQuestItem = _questTracelistItemDic[questId] as JourneyTraceQuestItem;
					if(item != null)
					{
						item.updateItemData(quest_trace_data, true);
					}
				}
			}
		}
		
		//追踪同步更新任务时间
		public function UCUpdateQuestTraceItemTimer(questId:int,timer:int):void
		{
			if(_questTracelistItemDic[questId])
			{
				var item:JourneyTraceQuestItem = _questTracelistItemDic[questId] as JourneyTraceQuestItem;
				if(item != null)
				{
					item.updateTimeLimit(timer);
				}
			}
		}
		
		public function updateScrollingView(toTop:Boolean = true, dataAvailable:Boolean = true):void
		{
			scrolling_view_mc.displayMc = display_mc;
			if(toTop)
			{
				scroll_bar_mc.position = 0;
			}
			if(!dataAvailable)
			{
				display_mc.visible = false;
				scroll_bar_mc.visible = false;
			}
			else
			{
				scroll_bar_mc.visible = display_mc.visible = _listExpand;
			}
		}
		
		public function checkGuidePosition():void
		{
			var numChild:int = guide_layer_mc.numChildren;
			var guideMC:MovieClip;
			var checkPosY:Number;
			var top:Number = scrolling_view_mc.y - 26;
			var bottom:Number = scrolling_view_mc.y + scrolling_view_mc.height;
			for(var i:int = 0; i < numChild; i++)
			{
				guideMC = guide_layer_mc.getChildAt(i) as MovieClip;
				if(guideMC)
				{
					checkPosY = guide_layer_mc.y  + guideMC.y + 9;
					guideMC.visible = (checkPosY > top	&& checkPosY < bottom);
				}
			}
		}
		
		//interface--------------------------------------------------------------------//
		public function UCShowPreChapterHint(bShow:Boolean, hintContent:String):void
		{
			if(_isFolding)//NPC Tips should not show when trace panel is invisible
			{
				return;
			}
			journey_trace_tips_mc.visible = bShow;
			if(bShow)
			{
				journey_trace_tips_mc.updateTips(hintContent);
				playHintAnimation();
			}
			else
			{
				clearTimeout(_hintAnimationTime);
				_hintAnimationTime = -1;
				btn_previous.filters = null;
			}
		}
		
		public function UCShowGuideArrow(bShow:Boolean, itemCategory:int, guideMCName:String):void
		{
			display_mc.UCShowGuideArrow(bShow, itemCategory, guideMCName);
			checkGuidePosition();
		}
		
		public function UCClearGuideArrow():void
		{
			while (guide_layer_mc.numChildren > 0)
			{
				guide_layer_mc.removeChildAt(0);
			}
		}
		
		private var _hintAnimationTime:int = -1;
		
		private function playHintAnimation():void
		{
			showHintFilter();
			
			function showHintFilter():void
			{
				if(_hintAnimationTime != -1)
				{
					clearTimeout(_hintAnimationTime);
				}
				btn_previous.filters = [_glowFilter];
				_hintAnimationTime = setTimeout(hideHintFilter, 300);
			}
			
			function hideHintFilter():void
			{
				if(_hintAnimationTime != -1)
				{
					clearTimeout(_hintAnimationTime);
				}
				btn_previous.filters = null;
				_hintAnimationTime = setTimeout(showHintFilter, 300);
			}
		}
		
		//---------------------------------------test code-----------------------------------------//
		private function getTestJourneyTraceData(testEmpty:Boolean = false):JourneyTraceData
		{
			var data:JourneyTraceData = new JourneyTraceData();
			data.journeyTraceIcon = "0.tga";
			data.journeyTraceTips = ["提示对话1,测试是否能正常地显示我们的所有内容测试是否能正常地显示我们的所有内容测试是否能正常地显示我们的所有内容。", "提示对话2,测试是否能正常地显示我测试是否能正常地显示我们的所有内容们的所有内容。","提示对话3,测试是否能正常地显示我们的所有内容。","提示对话4,测试是否能正常地显示我们的所有内容测试是否能正常地显示我们的所有内容测试是否能正常地显示我们的所有内容测试是否能正常地显示我们的所有内容。","提示对话5,测试是否能正常地显示我们的所有内容。"];
			data.chapterComplete = false;
			data.hasGetReward = true;
			data.journeyTraceList = getTestJourneyTraceListData(testEmpty);
			data.achievementRewardData = testEmpty ? null : getTestAchievementRewardData();
			return data;
		}
		
		private function getTestJourneyTraceListData(testEmpty:Boolean = false):Array
		{
			var listData:Array = [];
			var activatedKinds:int = 8;
			var expandIdx:int = activatedKinds * Math.random();
			var traceItemData:JourneyTraceItemData;
			for(var i:int = 0; i < activatedKinds; i++)
			{
				traceItemData = new JourneyTraceItemData();
				traceItemData.isComplete = (i == activatedKinds - 1);
				traceItemData.category = i + 1;
				traceItemData.isExpand = (i == expandIdx) &&  !testEmpty;
				traceItemData.recommandLevel = 1 + 5 * Math.random();
				traceItemData.hintText = "完成  <a href=\"event:storyQuest,1234\"><font color='#fbd671' size='14'>剧情任务</font></a> 获得经验提升,获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升获得经验提升";
				if(testEmpty)
				{
					traceItemData.questTraceData = [];
				}
				else
				{
					if(traceItemData.category == 0 || traceItemData.category == 3 || traceItemData.category == ConstantsDefine.CATEGORY_GUILD)
					{
						traceItemData.questTraceData = testQuestData();
					}
					else if(traceItemData.category == ConstantsDefine.CATEGORY_ACHIEVEMENT)
					{
						traceItemData.questTraceData = testAchievementData();
					}
				}
				listData.push(traceItemData);
			}
			return 	listData;
		}
		
		private function testQuestData():Array
		{
			var questList:Array = new Array();
			var i:int = 0;
			var questNum:int = 3;
			for (i = 1; i < questNum; i ++)
			{
				var questData:QuestTraceData = new QuestTraceData;
				questData.quest_id = i;
				questData.quest_type = (i - 1) % 5;
				questData.quest_caption = "复仇复仇" + i;
				questData.quest_level = "20"
				questData.quest_is_new = i % 3 == 0;
				questData.quest_is_delay_complete = i % 2 == 0;
				questData.quest_failed = false;
				questData.quest_detail = "任务描述<a href=\"event:npc,1234\"><font color='#fbd671' size='14'>测试</font></a>";
				questData.quest_time_limit = 100 + i;
				
				questData.quest_targets = new Array();
				var j:int = 0;
				for (j = 0; j < (i % 9); j ++)
				{
					var targetData:QuestTraceTargetData = new QuestTraceTargetData;
					targetData.quest_target_desc = "-杀15只<a href=\"event:npc,1234\"><font color='#fbd671' size='14'>强壮的的平原蛮牛</font></a><font color='#F0E154' size='14'>(" + 0 + "/8)</font>";
					targetData.quest_target_progress_type = j % 3;
					targetData.quest_target_progress_cur = 5;
					targetData.quest_target_progress_max = 10;
					
					questData.quest_targets.push(targetData);
				}
				
				questList.push(questData);
			}
			return questList;
		}
		
		private function testUpdateQuestData():QuestTraceData
		{
			var i:int = 1;
			var questData:QuestTraceData = new QuestTraceData;
			questData.quest_id = i;
			questData.quest_type = (i - 1) % 5;
			questData.quest_caption = "复仇复仇测试更新" + i;
			questData.quest_level = "30"
			questData.quest_is_new = i % 3 == 0;
			questData.quest_is_delay_complete = i % 2 == 0;
			questData.quest_failed = false;
			questData.quest_detail = "任务描述<a href=\"event:npc,1234\"><font color='#fbd671' size='14'>测试更新</font></a>";
			questData.quest_time_limit = 100 + i;
			
			questData.quest_targets = new Array();
			var j:int = 0;
			for (j = 0; j < (i % 9); j ++)
			{
				var targetData:QuestTraceTargetData = new QuestTraceTargetData;
				targetData.quest_target_desc = "-杀15只<a href=\"event:npc,1234\"><font color='#fbd671' size='14'>强壮的的平原蛮牛测试更新</font></a><font color='#F0E154' size='14'>(" + 0 + "/8)</font>";
				targetData.quest_target_progress_type = j % 3;
				targetData.quest_target_progress_cur = 5;
				targetData.quest_target_progress_max = 10;
				
				questData.quest_targets.push(targetData);
			}
			return questData;
		}
		
		private function testAchievementData():Array
		{
			var achievementList:Array = new Array();
			var i:int = 0;
			var questNum:int = 3;
			for (i = 1; i < questNum; i ++)
			{
				var data:Object = {};
				data.achievement_trace_name = "<a href=\"event:npc,1234\"><font color='#fbd671' size='14'>成就名称</font></a>";
				data.achievement_detail = (i % 2) + 1;
				if(data.achievement_detail == 2)
				{
					data.achievement_progress_cur = 50;
					data.achievement_progress_max = 100;
				}
				else if(data.achievement_detail == 1)
				{
					data.achievement_condition_name0 = "条件1";
					data.achievement_condition_name1 = "条件2";
					data.achievement_condition_name2 = "条件3";
//					data.achievement_condition_name3 = "条件4";
//					data.achievement_condition_name4 = "条件5";
//					data.achievement_condition_name5 = "条件6";
					
					data.achievement_condition_complete0 = true;
					data.achievement_condition_complete1 = false;
					data.achievement_condition_complete2 = true;
					data.achievement_condition_complete3 = false;
					data.achievement_condition_complete4 = true;
					data.achievement_condition_complete5 = true;
				}
				
				achievementList.push(data);
			}
			return achievementList;
		}
		
		private function getTestAchievementRewardData():Object
		{
			var rewardData:Object = {};
			rewardData.achievement_name = "<a href=\"event:npc,1234\"><font color='#fbd671' size='14'>成就名称A</font></a>";
			rewardData.achievement_reward_desc = "经验  9999999";
			rewardData.achievement_id = '201506010001';
			return rewardData;
		}
			
	}
}