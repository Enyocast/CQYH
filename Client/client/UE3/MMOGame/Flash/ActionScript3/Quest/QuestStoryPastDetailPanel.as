package ActionScript3.Quest
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButtonNew;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.gfx.Extensions;
	import ActionScript3.MyScrollBar;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	
	import scaleform.clik.motion.Tween;
	import fl.transitions.easing.*;

	public class QuestStoryPastDetailPanel extends MyPanel
	{
		public var dropDown:DropdownMenu;
		public var past:QuestStoryPast;
		public var dec:QuestStoryPastDetail;
		
		//public var quest_story_past_stage_list_mc:ScrollingList;
		
		//public var quest_story_past_stage_title_mc:TextField;
		//public var quest_story_past_stage_content_mc:TextField;
		//public var quest_story_past_back_mc:Button;
		//public var quest_story_past_sound_mc:Button;
		
		public function QuestStoryPastDetailPanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
			dropDown.dataProvider = new DataProvider();
			dropDown.addEventListener(Event.CHANGE, onChangeSelect);
			past.list_mc.selectedIndex = 0;

			past.list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			past.list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);
			past.list_mc.addEventListener(ListEvent.ITEM_ROLL_OVER, onListItemRollOver, false, 0, true);
			past.list_mc.addEventListener(ListEvent.ITEM_ROLL_OUT, onListItemRollOut, false, 0, true);
			
			dec.quest_story_past_back_mc.addEventListener(MouseEvent.CLICK, onBtClickBackStageList);
			dec.quest_story_past_sound_mc.addEventListener(MouseEvent.CLICK, onBtClickPlaySound);
			
		    dec.quest_story_past_stage_title_mc.text = "";
		    dec.quest_story_past_stage_title_mc.htmlText = "";
			
			dec.quest_story_past_stage_content_mc.styleSheet = new StyleSheet  ;
		    dec.quest_story_past_stage_content_mc.text = "";
		    dec.quest_story_past_stage_content_mc.htmlText = "";
			
			updateQuestStoryChapterList(new Array);
			updateQuestStoryStageList(new Array);
			/*
			// list test
			var i:int = 0;
			var quest_data:Object = null;
			var itemsData:Array =[];
	       
			// trunk
			for (i = 1; i < 20; i++)
			{
				quest_data = new Object ;
				quest_data.label = "";
				quest_data.index = i;
			    quest_data.type = 0;
			    quest_data.deepth = 0;
			    quest_data.visible = true;
				quest_data.quest_caption = "第" + i + "幕：牛轧糖日志（" + i + ")";
				quest_data.quest_stage_name="test"+i;
				quest_data.quest_chapter_list="test"+i;
				itemsData.push(quest_data);
			}
			
			updateQuestStoryChapterList(itemsData);
			updateQuestStoryStageList(itemsData);
			show();
			*/
		}
		
		private function onChangeSelect(e:Event):void
		{
			ExternalInterface.call("ASUpdateQuestStageList", dropDown.selectedIndex + 1);
		}
		
		private function onListItemChange( event:Event ):void
		{
			var scrolling:ScrollingList = event.target as ScrollingList;
			if (scrolling != null)
			{
				scrolling.invalidateData();
			}
		}
		
		private function onListItemClick(event:ListEvent):void
		{
			var scrolling:ScrollingList = event.target as ScrollingList;
			if (scrolling != null)
			{
				var provider:TreeDataProvider = scrolling.dataProvider as TreeDataProvider;
				if (provider!=null)
				{
					provider.handleListItemClick(event);
					var stage_data:Object = provider.requestItemAt(event.index);
					ExternalInterface.call("ASViewStoryQuestStageInfo", stage_data.quest_chapter, stage_data.quest_stage);
				}
				
				scrolling.invalidateData();
			}
			//updateQuestStoryStageInfo("test","test");
		}
		
		private function onListItemRollOver(event:ListEvent ):void
		{
		}

		private function onListItemRollOut(event:ListEvent ):void
		{
		}
		
		private function onBtClickBackStageList(evt:MouseEvent):void
		{
			ExternalInterface.call("ASUpdateQuestStageList", dropDown.selectedIndex + 1);
		}
		
		private function onBtClickPlaySound(evt:MouseEvent):void
		{
		}
		
		private function show():void
		{
			past.visible=true;
			dec.visible=false;
		}
		
		private function hide():void
		{
			past.visible = false;
			dec.visible=true;
		}
		
		public function updateQuestStoryChapterList(list:Array)
		{
			if (list.length > 0)
			{
				var data_list:Array = new Array;
				var i:int = 0;
				for (i = 0; i < list.length; i ++)
				{
					var obj:Object = list[i];
					if (obj)
					{
						data_list.push(String(obj.quest_chapter_name));
					}
				}
				
				//dropDown.datastring = dat.quest_chapter_list;
				dropDown.dataList = data_list;
				dropDown.SplitData();
				dropDown.selectedIndex = 0;
				//trace(dropDown.itemRenderer);
				dropDown.visible = true;
			}
			else
			{
				dropDown.visible = false;
			}
		}
		
		public function updateQuestStoryStageList(arr:Array)
		{
            show();
			past.list_mc.dataProvider = new TreeDataProvider(arr);
			past.list_mc.validateNow();
			past.list_mc.invalidateData();
			past.list_mc.selectedIndex = 0;
			past.list_mc.visible = arr.length > 0;
		}
		
		public function updateQuestStoryStageInfo(caption:String, desc:String)
		{
             hide();
		    dec.quest_story_past_stage_title_mc.htmlText = caption;
			dec.quest_story_past_stage_content_mc.autoSize =TextFieldAutoSize.LEFT;
			dec.quest_story_past_stage_content_mc.wordWrap = true;
		    dec.quest_story_past_stage_content_mc.htmlText = desc;
			
		}
	}
}