package ActionScript3.Quest
{

	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.utils.getDefinitionByName;
	import flash.utils.setTimeout;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollBar;
	
	import scaleform.clik.interfaces.IScrollBar;
	import scaleform.clik.motion.Tween;

	public class QuestTracePanel extends MyPanel
	{
		public var quest_trace_accepted_tab_mc:MovieClip;
		public var quest_trace_available_tab_mc:MovieClip;
		public var quest_trace_list_mask_mc:MovieClip;
		public var quest_trace_list_mc:QuestTraceList;
		public var _traceScrollbar:MyScrollBar;
		public var quest_trace_list_bg_mc:MovieClip;
		public var quest_trace_caption_mc:MovieClip;
        public var taskArr:Array;
		public var taskItem:QuestTraceListItem;
		public var taskMc:MovieClip;
		public var newTaskItem:QuestTraceListItem;
		public var newQuestData:QuestTraceData;
		override protected function configUI():void
		{
			super.configUI();
			
			quest_trace_accepted_tab_mc.addEventListener(MouseEvent.CLICK, onTabClickAcceptedQuest);
			quest_trace_available_tab_mc.addEventListener(MouseEvent.CLICK, onTabClickAvailableQuest);
			
			// 关闭按钮要用来切换展开;
			btn_close.CloseTargetPanel = null;
			btn_close.RemoveAddedEventListener();
			btn_close.addEventListener(MouseEvent.CLICK, onExpandTracePanel);
			btn_close.selected = true;
			
			quest_trace_list_bg_mc.visible = true;
			
			quest_trace_list_bg_mc.alpha = 0.0;
			_traceScrollbar.alpha = 0.0;
			quest_trace_accepted_tab_mc.alpha = 0.0;
			quest_trace_available_tab_mc.alpha = 0.0;
			quest_trace_caption_mc.alpha = 0.0;
			btn_close.alpha = 0.0;
				
			quest_trace_list_mc.addEventListener(MouseEvent.MOUSE_OVER, onMouseOverPanel);
			quest_trace_list_mc.addEventListener(MouseEvent.MOUSE_OUT, onMouseOutPanel);
			//InfoDragButton_mc.addEventListener(MouseEvent.MOUSE_OVER, onMouseOverPanel);
			//InfoDragButton_mc.addEventListener(MouseEvent.MOUSE_OUT, onMouseOutPanel);
			quest_trace_list_bg_mc.addEventListener(MouseEvent.MOUSE_OVER, onMouseOverPanel);
			quest_trace_list_bg_mc.addEventListener(MouseEvent.MOUSE_OUT, onMouseOutPanel);
			
			quest_trace_accepted_tab_mc.addEventListener(MouseEvent.MOUSE_OVER, onMouseOverPanel);
			quest_trace_accepted_tab_mc.addEventListener(MouseEvent.MOUSE_OUT, onMouseOutPanel);
			
			quest_trace_available_tab_mc.addEventListener(MouseEvent.MOUSE_OVER, onMouseOverPanel);
			quest_trace_available_tab_mc.addEventListener(MouseEvent.MOUSE_OUT, onMouseOutPanel);
			
			btn_close.addEventListener(MouseEvent.MOUSE_OVER, onMouseOverPanel);
			btn_close.addEventListener(MouseEvent.MOUSE_OUT, onMouseOutPanel);
			
			if(_traceScrollbar)
			{	
				_traceScrollbar.addEventListener(MouseEvent.MOUSE_OVER, onMouseOverPanel);
				_traceScrollbar.addEventListener(MouseEvent.MOUSE_OUT, onMouseOutPanel);
				quest_trace_list_mc.setupScrollBar(_traceScrollbar);
			}
			
			// clear
			UCUpdateAcceptedQuestTraceList(new Array);
			UCUpdateAvailableQuestTraceList(new Array);
			
			quest_trace_accepted_tab_mc.visible = false;
			quest_trace_available_tab_mc.visible = false;
			quest_trace_caption_mc.visible = false;
			//btn_close.visible = false;
		
			onTabClickAcceptedQuest();
			
			this.focusable = false;
			quest_trace_list_mask_mc.focusable = false;
			quest_trace_list_mc.focusable = false;
			_traceScrollbar.focusable = false;
			//testData();
		}
		
/*        private function testData():void
		{
			var questList:Array = new Array();
			var i:int = 0;
			for (i = 1; i < 10; i ++)
			{
				var questData:QuestTraceData = new QuestTraceData;
				questData.quest_id = i;
				questData.quest_type = (i - 1) % 5;
				questData.quest_caption = "复仇复仇" + i;
				questData.quest_level = "20"
				questData.quest_is_new = i % 3 == 0;
				questData.quest_is_delay_complete = i % 2 == 0;
				questData.quest_failed = false;
				questData.quest_detail = "任务描述<a href=\"event:npc,1234\"><font color='#1C91D4' size='14'>测试</font></a>";
				questData.quest_time_limit = 100 + i;
				
				questData.quest_targets = new Array();
				var j:int = 0;
				for (j = 0; j < (i % 9); j ++)
				{
					var targetData:QuestTraceTargetData = new QuestTraceTargetData;
					targetData.quest_target_desc = "-杀15只<a href=\"event:npc,1234\"><font color='#1C91D4' size='14'>强壮的的平原蛮牛</font></a><font color='#F0E154' size='14'>(" + 0 + "/8)</font>";
					targetData.quest_target_progress_type = j % 3;
					targetData.quest_target_progress_cur = 5;
					targetData.quest_target_progress_max = 10;
					
					questData.quest_targets.push(targetData);
				}
				
				questList.push(questData);
			}
			quest_trace_accepted_tab_mc.alpha = 1.0;
			quest_trace_accepted_tab_mc.visible = true;
			UCUpdateAcceptedQuestTraceList(questList);
		}*/

		public function onTabClickAcceptedQuest()
		{
/*				var questData:QuestTraceData = new QuestTraceData;
				questData.quest_id = 12;
				questData.quest_type = (12 - 1) % 5;
				questData.quest_caption = "复仇复仇" + 12;
				questData.quest_level = "20"
				questData.quest_is_new = 12 % 3 == 0;
				questData.quest_is_delay_complete = 12 % 2 == 0;
				questData.quest_failed = false;
				questData.quest_detail = "任务描述<a href=\"event:npc,1234\"><font color='#1C91D4' size='14'>测试</font></a>";
				questData.quest_time_limit = 100 + 12;
				
				questData.quest_targets = new Array();*/
/*				var j:int = 0;
				for (j = 0; j < (12 % 9); j ++)
				{
					var targetData:QuestTraceTargetData = new QuestTraceTargetData;
					targetData.quest_target_desc = "-杀15只<a href=\"event:npc,1234\"><font color='#1C91D4' size='14'>强壮的的平原蛮牛</font></a><font color='#F0E154' size='14'>(" + 0 + "/8)</font>";
					targetData.quest_target_progress_type = j % 3;
		    		targetData.quest_target_progress_cur = 5;
		    		targetData.quest_target_progress_max = 10;
					
					questData.quest_targets.push(targetData);
				}*/
			//UCAddAcceptedQuest(questData,3);
			//UCRemoveAcceptedQuest(2);
			
			quest_trace_accepted_tab_mc.selected = true;
			quest_trace_available_tab_mc.selected = false;
			_traceScrollbar.position = 0;
			ExternalInterface.call("ASUpdateAcceptedQuestTraceList", this);
		}
		public function onTabClickAvailableQuest()
		{
			quest_trace_accepted_tab_mc.selected = false;
			quest_trace_available_tab_mc.selected = true;
			_traceScrollbar.position = 0;
			ExternalInterface.call("ASUpdateAvailableQuestTraceList", this);
		}
		
		function onExpandTracePanel()
		{
			//btn_close.selected = !btn_close.selected;
			
			quest_trace_list_bg_mc.alpha = 1.0;
			_traceScrollbar.alpha = 1.0;
			quest_trace_accepted_tab_mc.alpha = 1.0;
			quest_trace_available_tab_mc.alpha = 1.0;
			quest_trace_caption_mc.alpha = 1.0;
			//btn_close.alpha = 1.0;
			//btn_close.visible = true;
			
			quest_trace_list_mc.visible = btn_close.selected;
			_traceScrollbar.visible = btn_close.selected;
			quest_trace_accepted_tab_mc.visible = btn_close.selected;
			quest_trace_available_tab_mc.visible = btn_close.selected;
			quest_trace_caption_mc.visible = btn_close.selected;
			quest_trace_list_bg_mc.visible = btn_close.selected;
			
			playSound("MicroButton");
		}
		
		public function onMouseOverPanel(event:Event)
		{
			if (btn_close.selected)
			{
				quest_trace_list_bg_mc.alpha = 1.0;
				_traceScrollbar.alpha = 1.0;
				
				//quest_trace_accepted_tab_mc.alpha = 1.0;
				//quest_trace_available_tab_mc.alpha = 1.0;
				//quest_trace_caption_mc.alpha = 1.0;
				//btn_close.alpha = 1.0;
				
				quest_trace_list_mc.setExpandButtonAlpha(1.0);
			}
			
		}
		
		public function onMouseOutPanel(event:Event)
		{
			if (btn_close.selected)
			{
				quest_trace_list_bg_mc.alpha = 0.0;
				_traceScrollbar.alpha = 0.0;
				
				//quest_trace_accepted_tab_mc.alpha = 0.0;
				//quest_trace_available_tab_mc.alpha = 0.0;
				//quest_trace_caption_mc.alpha = 0.0;
				//btn_close.alpha = 0.0;
				
				quest_trace_list_mc.setExpandButtonAlpha(0.0);
			}
			
		}
		
		protected function handleMouseWheel(event:MouseEvent):void 
		{
			if(_traceScrollbar)
			{
				_traceScrollbar.position -= (event.delta > 0 ? 1 : -1) * 20;
			}
        }
		
		override public function UpdatePos(stageW:Number , stageH:Number)
		{
			this.x = stageW - 311;
		}
		
		// Event
		public function UCSetQuestTraceType(type:int):void
		{
			if (type == 0)
			{
				onTabClickAcceptedQuest();
			}
			else
			{
				onTabClickAvailableQuest();
			}
		}
		
		public function UCAddAcceptedQuest(dat:QuestTraceData,index:int):void
		{//你有新的任务
		     //在第几个位置显示
			newQuestData=dat;
			var i:int=0;
			var j:int=0;
			var l:int=quest_trace_list_mc.quest_trace_list.length;
			for(i=0;i<l;i++){
				taskItem=quest_trace_list_mc.quest_trace_list[i];
				if(index==i){
					newTaskItem=new QuestTraceListItem();
					newTaskItem.x=-400;
					newTaskItem.y=taskItem.y;
					newTaskItem.updateItemData(dat);
					this.addChild(newTaskItem);
					newTaskItem.hideMc(false);
					newTaskItem.scaleY=1;
					j=i;
					break;
				}
			}
			for(l;l>j;l--){
				var allItem:QuestTraceListItem=quest_trace_list_mc.quest_trace_list[l-1];
				var y:int=allItem.y;
				y+=newTaskItem.itemPos;
				allItem.scaleY=1;
				var tween1:Tween=new Tween(1000,allItem,{y:y});
			}
			var tween:Tween=new Tween(2000,newTaskItem,{x:0},{onComplete:onComplete1});
		}
		
		private function onComplete1():void
		{
			this.removeChild(newTaskItem);
			newTaskItem.updateItemData(newQuestData);
			quest_trace_list_mc.addChild(newTaskItem);
		}
		
		public function UCRemoveAcceptedQuest(id:int):void
		{
			if(taskArr && quest_trace_list_mc.quest_trace_list){
				var i:int=0;
				var l:int=taskArr.length;
				for(i=0;i<l;i++){
					var dat:QuestTraceData=taskArr[i];
					if(dat.quest_id==id){
						taskItem=quest_trace_list_mc.quest_trace_list[i];
						if(taskItem){
							taskItem.scaleY=1;
							var cl:Class=getDefinitionByName("taskEffect") as Class;
			                taskMc=new cl();
							taskMc.y=taskItem.y;
							taskMc.x=-246;
			                this.addChild(taskMc);
							taskArr.splice(i,1);
							setTimeout(playEffecf,1100);
							break;
						}
					}
				}
			}
		}
		
		private function playEffecf():void
		{
			if(taskMc && this.contains(taskMc))
			{
				this.removeChild(taskMc);
			}
			var tween:Tween=new Tween(2000,taskItem,{x:x+246},{onComplete:onComplete});
		}
		
		private function onComplete():void
		{
			if(taskItem){
				quest_trace_list_mc.quest_trace_list.splice(taskItem,1);
			    taskItem=null;
			}
			UCUpdateAcceptedQuestTraceList(taskArr);
		}
		
		public function UCUpdateAcceptedQuest(data:Object):void
		{
			quest_trace_list_mc.updateListItemData(data);
			quest_trace_list_bg_mc.height = quest_trace_list_mc.quest_trace_list_view_height;
		}
		
		public function UCUpdateAcceptedQuestTraceList(data:Array):void
		{
			taskArr=data as Array;
			quest_trace_list_mc.updateListData(data);
		}

		public function UCUpdateAvailableQuestTraceList(data:Array):void
		{
			quest_trace_list_mc.updateListData(data);
		}
		
		public function UCSetFocus():void
		{//只有TextField才需要有焦点，其他设置焦点管理接口将不在处理
			//FocusHandler.getInstance().setFocus(quest_trace_list_mc);
		}
	}
}