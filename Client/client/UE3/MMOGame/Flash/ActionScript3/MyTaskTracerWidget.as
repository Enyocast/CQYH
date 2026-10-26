
package ActionScript3 {

	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.display.Stage;
	import flash.display.Scene;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.Label;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.ItemSlotData;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.gfx.MouseEventEx;
	import ActionScript3.MyIconConponent;
	import flash.external.ExternalInterface;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyItemSlot;
	import ActionScript3.MyScrollBar;
	import ActionScript3.MyScrollPanel;
	import scaleform.clik.events.SliderEvent;
	import flash.events.TextEvent;
	
	public class MyTaskTracerWidget extends MyPanel
	{
		public var TaskTracerToggleButton:MovieClip;
		public var TaskTraceScrollPanel:MyScrollPanel;
		public var scrollBar_mc:MyScrollBar;
		public var TaskTraceUnit:MovieClip;
		
		public var TaskTrace:Array;

		override protected function configUI():void 
		{
			super.configUI();
			
			ExternalInterface.call("RegisterTaskTracer", this);
			
			TaskTraceUnit = TaskTraceScrollPanel["TaskTraceUnit"];
			
			TaskTracerToggleButton.addEventListener("click", onTaskTracerToggleButtonClickEvent);
		
			TaskTraceUnit.visible = false;
			
			TaskTrace = new Array;
			
			scrollBar_mc.scrollTarget = TaskTraceScrollPanel;
			TaskTraceScrollPanel.addEventListener(SliderEvent.VALUE_CHANGE, ScrollChange);
			scrollBar_mc.height = 300;
			scrollBar_mc.position = 0;
			
			scrollBar_mc.visible = false;
		}
		
		function ScrollChange(evt:SliderEvent)
		{
			var percent:Number = evt.value;
			TaskTraceScrollPanel.y = TaskTracerToggleButton.y + TaskTracerToggleButton.height - percent ;
		}
		
		static function duplicateMovieClip(source:MovieClip):MovieClip
		{
			var tClass:Class = Object(source).constructor;
			var ret:MovieClip = new tClass;
			
			ret.transform = source.transform;
			ret.filters = source.filters;
			ret.cacheAsBitmap = source.cacheAsBitmap;
			ret.opaqueBackground = source.opaqueBackground;
			
			if(source.parent)
				source.parent.addChild(ret);
				
			return ret;
		}
		
		function onTaskTracerToggleButtonClickEvent()
		{
			for(var i:Number = 0; i < TaskTrace.length; ++i)
			{
				var unit:MovieClip = TaskTrace[i];
				unit.visible = !unit.visible;
			}
			
			if(TaskTrace.length > 0)
				scrollBar_mc.visible = TaskTrace[0].visible;
			else
				scrollBar_mc.visible = false;
		}
		
		public function addTaskTraceWithQuest(questTitle:String, questDescription:String, questState:int)
		{
			var shouldBeSeen:Boolean = true;
			ExternalInterface.call("ASTrace", TaskTracerToggleButton.currentLabel);
			if(TaskTracerToggleButton.currentLabel != "out")
			{
				shouldBeSeen = false;
			}
			
			ExternalInterface.call("ASTrace", "addTaskTraceWithQuest");
			
			var newUnit:MovieClip = duplicateMovieClip(TaskTraceUnit);
			newUnit.visible = shouldBeSeen;
			newUnit.tF_taskTitle.text = questTitle;
			newUnit.tF_taskDetail.text = questDescription;
			
			for(var i:Number = 0; i < TaskTrace.length; ++i)
			{
				var unit:MovieClip = TaskTrace[i];
				unit.y += newUnit.height;
			}
			TaskTrace.push(newUnit);
			
			if(questState == 1)
			{
				ExternalInterface.call("ASTrace", "new add traced task ...");
				newUnit.hintTaskStatus_mc.text_mc.gotoAndStop(1);
				newUnit.hintTaskStatus_mc.gotoAndPlay(1);
				newUnit.taskStatus_mc.visible = false;
			}
			else if(questState == 2)
			{
				newUnit.hintTaskStatus_mc.visible = false;
				newUnit.taskStatus_mc.visible = false;
			}
			else if(questState == 3)
			{
				newUnit.hintTaskStatus_mc.text_mc.gotoAndStop(2);
				newUnit.hintTaskStatus_mc.gotoAndPlay(1);
				newUnit.taskStatus_mc.visible = true;
			}
			
			scrollBar_mc.visible = newUnit.visible;
		}
		
		public function removeTaskTraceWithQuest(questTitle:String, questDescription:String, questState:int)
		{
			for(var i:Number = 0; i < TaskTrace.length; ++i)
			{
				var unit:MovieClip = TaskTrace[i];
				if(unit.tF_taskTitle.text == questTitle)
				{
					removeTaskTraceWithQuestID(i);
					return;
				}
			}
		}
		
		function removeTaskTraceWithQuestID(idx:Number)
		{	
			if(TaskTrace.length > 1 )
			{
				for(var i:Number = idx; i < TaskTrace.length; ++i)
				{
					var nextIdx:Number = i + 1;
					if(nextIdx < TaskTrace.length)
					{
						TaskTrace[i].tF_taskTitle.text = TaskTrace[nextIdx].tF_taskTitle.text;
						TaskTrace[i].tF_taskDetail.text = TaskTrace[nextIdx].tF_taskDetail.text;
					}
				}
			}
			
			var mc:MovieClip = TaskTrace[TaskTrace.length - 1];
			TaskTrace.pop();
			TaskTraceScrollPanel.removeChild(mc);
			//mc.removeMovieClip();
		
			updateLayout();
		}
		
		public function UpdateTaskTracer(questTitle:String, questDescription:String, questState:int)
		{
			for(var i:Number = 0; i < TaskTrace.length; ++i)
			{
				var unit:MovieClip = TaskTrace[i];
				if(unit.tF_taskTitle.text == questTitle)
				{
					removeTaskTraceWithQuestID(i);
					return;
				}
			}
			
			addTaskTraceWithQuest(questTitle, questDescription, questState);
		}
		
		
		function updateLayout()
		{	
			if(TaskTrace.length >= 1)
			{
				TaskTrace[TaskTrace.length - 1].y = TaskTraceUnit.y;
				
				if(TaskTrace.length >= 2)
				{
					for(var i:Number = TaskTrace.length - 2; i >= 0; --i)
					{
						TaskTrace[i].y = TaskTrace[i + 1].y + TaskTrace[i + 1].height;
					}
				}
			}
		}
		
		public function IsThisTaskTraced(taskName:String):int
		{
			for(var i:Number = 0; i < TaskTrace.length; ++i)
			{
				var unit:MovieClip = TaskTrace[i];
				if(unit.tF_taskTitle.text == taskName)
				{
					return 1;
				}
			}

			return 0;
		}

	}
}