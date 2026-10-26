package ActionScript3.Quest
{
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextLineMetrics;
	import flash.utils.Timer;
	
	import ActionScript3.ItemSlotData;
	import ActionScript3.MyIcon;
	import ActionScript3.Common.DrawLine;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextEventEx;

	public class QuestTraceTarget extends UIComponent
	{
		public var quest_trace_target_data:QuestTraceTargetData;
		public var quest_trace_target_desc_tf:TextField;
		public var quest_trace_target_progress_mc:MovieClip;
        private var line:Sprite=new Sprite();
		public var isLine:Boolean=false;
		public var quest_id:int=0;//任务ID

		override protected function configUI():void
		{
			super.configUI();
			this.addChild(line);
			line.mouseChildren=false;
			line.mouseEnabled=false;
			isLine=false;
			this.mouseChildren = true;

			quest_trace_target_desc_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			quest_trace_target_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			quest_trace_target_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			quest_trace_target_desc_tf.styleSheet = new StyleSheet  ;
			quest_trace_target_desc_tf.autoSize = flash.text.TextFieldAutoSize.LEFT;// 自动高度
			quest_trace_target_desc_tf.wordWrap = true;
		}

		public function RemoveAll()
		{
			quest_trace_target_desc_tf.removeEventListener(TextEvent.LINK, onLinkCallBack);
			quest_trace_target_desc_tf.removeEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			quest_trace_target_desc_tf.removeEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
		}
		
		public function updateProgressData():void
		{//值更新进度条
			if(quest_trace_target_progress_mc.visible==true)
			{
				if (quest_trace_target_data.quest_target_progress_type == QuestTraceTargetData.quest_target_progress_type_count_progress)
				{
					quest_trace_target_progress_mc.setProgressPercent(0, quest_trace_target_data.quest_target_progress_cur, quest_trace_target_data.quest_target_progress_max);
				}
				else if (quest_trace_target_data.quest_target_progress_type == QuestTraceTargetData.quest_target_progress_type_hp_progress)
				{
					quest_trace_target_progress_mc.setProgressPercent(1, quest_trace_target_data.quest_target_progress_cur, quest_trace_target_data.quest_target_progress_max);
				}
			}
		}

		public function setQuestTraceTargetData(data:Object):void
		{
			quest_trace_target_data = data as QuestTraceTargetData;
			if (quest_trace_target_data != null)
			{
				var target_height:int = 0;
		   		quest_trace_target_desc_tf.htmlText = quest_trace_target_data.quest_target_desc;
				target_height += quest_trace_target_desc_tf.textHeight;
				
				quest_trace_target_progress_mc.visible = false;
				if (quest_trace_target_data.quest_target_progress_type == QuestTraceTargetData.quest_target_progress_type_count_progress)
				{
					quest_trace_target_progress_mc.y=target_height;
					quest_trace_target_progress_mc.visible = true;
					if (quest_trace_target_data.quest_target_progress_max == 0)
					{
						quest_trace_target_data.quest_target_progress_max = 1;
					}

					quest_trace_target_progress_mc.setProgressPercent(0, quest_trace_target_data.quest_target_progress_cur, quest_trace_target_data.quest_target_progress_max);
					target_height += quest_trace_target_progress_mc.height;
				}
				else if (quest_trace_target_data.quest_target_progress_type == QuestTraceTargetData.quest_target_progress_type_hp_progress)
				{
					quest_trace_target_progress_mc.visible = true;
					quest_trace_target_progress_mc.y=target_height;
					if (quest_trace_target_data.quest_target_progress_max == 0)
					{
						quest_trace_target_data.quest_target_progress_max = 1;
					}

					quest_trace_target_progress_mc.setProgressPercent(1, quest_trace_target_data.quest_target_progress_cur, quest_trace_target_data.quest_target_progress_max);
					target_height += quest_trace_target_progress_mc.height;
				}

				if (quest_trace_target_data.quest_target_complete)
				{
					clear();
					var i:int=0;
					var l:int=quest_trace_target_desc_tf.numLines;
					line.visible=true;
					for (i= 0; i < l; i++) 
					{
						var line_mc:DrawLine =new DrawLine();
						var hh:TextLineMetrics=quest_trace_target_desc_tf.getLineMetrics(i);
						line_mc.update(0, hh.width+8, (i*hh.height)+14, 500);
						line.addChild(line_mc);
					}
					isLine=true;
				}
				else
				{
					clear();
				}
				
				this.height = target_height;
			}
		}
		
		private function clear():void
		{
			var i:int=0;
			var l:int=line.numChildren;
			if (l>0) 
			{
				for (i= 0; i < l; i++) 
				{
					line.removeChildAt(0);
				}
			}
			line.visible=false;
			isLine=false;
		}

		function onLinkCallBack(e:TextEvent)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}

		function onLinkOverCallBack(e:TextEventEx)
		{
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
	}
}