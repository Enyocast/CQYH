package UI_Journey.AS3
{
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	
	import ActionScript3.Quest.QuestTraceProgressBar;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextEventEx;

	public class JourneyTraceAchievementItem extends JourneyTraceItemContentDetail
	{
		private static const VIEW_TYPE_CHECK_BOX:int = 1;
		private static const VIEW_TYPE_PROGRESS_BAR:int = 2;
		private static const MARGIN:int = 8;
		private static const NUMBER_OF_CONDITION_CHECK_BOX:int = 6;
		private static const HEIGHT_OF_CONDITION_CHECK_BOX:Number = 22;
		
		public var achievement_trace_name_tf:TextField;
		public var achievement_trace_progress_mc:QuestTraceProgressBar;
		public var achievement_trace_condition_0_mc:Button;
		public var achievement_trace_condition_1_mc:Button;
		public var achievement_trace_condition_2_mc:Button;
		public var achievement_trace_condition_3_mc:Button;
		public var achievement_trace_condition_4_mc:Button;
		public var achievement_trace_condition_5_mc:Button;
		
		private var _viewType:int;
		private var _conditionAreaHeight:Number = 0;
		
		public function JourneyTraceAchievementItem()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			achievement_trace_condition_0_mc.mouseEnabled = false;
			achievement_trace_condition_1_mc.mouseEnabled = false;
			achievement_trace_condition_2_mc.mouseEnabled = false;
			achievement_trace_condition_3_mc.mouseEnabled = false;
			achievement_trace_condition_4_mc.mouseEnabled = false;
			achievement_trace_condition_5_mc.mouseEnabled = false;
			
			achievement_trace_name_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			achievement_trace_name_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			achievement_trace_name_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			achievement_trace_name_tf.styleSheet = new StyleSheet  ;
			achievement_trace_name_tf.autoSize = flash.text.TextFieldAutoSize.NONE;
			achievement_trace_name_tf.wordWrap = false;
			
			updateViewType(0);
		}
		
		private function onLinkCallBack(e:TextEvent)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			
			ExternalInterface.call( "ASTrace", "ASLinkCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}
		
		
		private function onLinkOverCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			
			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}
		
		private function onLinkOutCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			
			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}
		
		override public function get height():Number
		{
			if(_viewType == VIEW_TYPE_PROGRESS_BAR)
			{
				return achievement_trace_progress_mc.y + achievement_trace_progress_mc.height + MARGIN;
			}
			else if(_viewType == VIEW_TYPE_CHECK_BOX)
			{
				return achievement_trace_condition_0_mc.y + _conditionAreaHeight + MARGIN;
			}
			return achievement_trace_name_tf.height + MARGIN;
		}
		
		private function updateViewType(viewType:int):void
		{
			_viewType = viewType;
			achievement_trace_progress_mc.visible = (viewType == VIEW_TYPE_PROGRESS_BAR);
			achievement_trace_condition_0_mc.visible = (viewType == VIEW_TYPE_CHECK_BOX);
			achievement_trace_condition_1_mc.visible = (viewType == VIEW_TYPE_CHECK_BOX);
			achievement_trace_condition_2_mc.visible = (viewType == VIEW_TYPE_CHECK_BOX);
			achievement_trace_condition_3_mc.visible = (viewType == VIEW_TYPE_CHECK_BOX);
			achievement_trace_condition_4_mc.visible = (viewType == VIEW_TYPE_CHECK_BOX);
			achievement_trace_condition_5_mc.visible = (viewType == VIEW_TYPE_CHECK_BOX);
		}
		
		override public function updateItemData(data:Object, toUpdateParentLayout:Boolean = false):void
		{
			if(data == null)
			{
				return;
			}
			if(data.achievement_trace_name)
			{
				achievement_trace_name_tf.htmlText = data.achievement_trace_name;
				achievement_trace_name_tf.visible = true;
			}
			else 
			{
				achievement_trace_name_tf.visible = false;
			}
			updateViewType(data.achievement_detail);
			if(data.achievement_detail == VIEW_TYPE_PROGRESS_BAR)
			{
				achievement_trace_progress_mc.setProgressPercent(0, data.achievement_progress_cur, data.achievement_progress_max);
			}
			else if(data.achievement_detail == VIEW_TYPE_CHECK_BOX)
			{
				achievement_trace_condition_0_mc.label = data.achievement_condition_name0;
				achievement_trace_condition_1_mc.label = data.achievement_condition_name1;
				achievement_trace_condition_2_mc.label = data.achievement_condition_name2;
				achievement_trace_condition_3_mc.label = data.achievement_condition_name3;
				achievement_trace_condition_4_mc.label = data.achievement_condition_name4;
				achievement_trace_condition_5_mc.label = data.achievement_condition_name5;
				
				_conditionAreaHeight = 0;
				for(var i:int = 0; i < NUMBER_OF_CONDITION_CHECK_BOX; i++)
				{
					if(data['achievement_condition_name' + i] != null && data['achievement_condition_name' + i] != "")
					{
						(this['achievement_trace_condition_' + i + "_mc"] as Button).visible = true;
						_conditionAreaHeight = (Math.floor( i / 2 ) + 1 ) * HEIGHT_OF_CONDITION_CHECK_BOX;
					}
					else
					{
						(this['achievement_trace_condition_' + i + "_mc"] as Button).visible = false;
					}
				}
				
				achievement_trace_condition_0_mc.selected = data.achievement_condition_complete0;
				achievement_trace_condition_1_mc.selected = data.achievement_condition_complete1;
				achievement_trace_condition_2_mc.selected = data.achievement_condition_complete2;
				achievement_trace_condition_3_mc.selected = data.achievement_condition_complete3;
				achievement_trace_condition_4_mc.selected = data.achievement_condition_complete4;
				achievement_trace_condition_5_mc.selected = data.achievement_condition_complete5;
			}
		}
	}
}