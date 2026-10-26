package ActionScript3.Helper
{
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import ActionScript3.MyScrollPanel;
	import flash.events.TextEvent;
	import flash.text.StyleSheet;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.ScrollBar;

	public class HelperDetailPage extends MyScrollPanel
	{
		public var _traceScrollbar:ScrollBar;
		public var _mouse_wheel_layer:MovieClip;
		
		//public var helper_title_tf:TextField
		public var helper_desc_tf:TextField;

		override protected function configUI():void
		{
			trace(">>>>>>>>>>>>>>> HelperDetailPage::configUI");
			super.configUI();

			helper_desc_tf.styleSheet = new StyleSheet  ;
			helper_desc_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			helper_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
			helper_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);

			trace("<<<<<<<<<<<<<<< HelperDetailPage::configUI");
		}
		
		function onWheel(e:MouseEvent):void
		{
			this._traceScrollbar.position -= e.delta * 4;
		}

		function onScrollChange(evt:SliderEvent):void
		{
			var percent:Number = evt.value;
			y = -percent + 100;
		}

		function onLinkOverCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		function onLinkOutCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		function onLinkCallBack(e:TextEvent):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}

		public function setupScrollBar(scrollBar:ScrollBar):void
		{
			_traceScrollbar = scrollBar;
			if (_traceScrollbar)
			{
				//_traceScrollbar.scrollTarget = this;
				//this.addEventListener(SliderEvent.VALUE_CHANGE, onScrollChange);
				//_traceScrollbar.height = 390;
				_traceScrollbar.position = 0;
			}
			else
			{
				ExternalInterface.call("ASTrace", "_traceScrollbar is null!");
			}
		}

		public function updateHelperDetailData(detail_data:Object):void
		{
			// 帮助标题
			//helper_title_tf.htmlText = detail_data.helper_title;
			
			// 帮助描述
			helper_desc_tf.autoSize = TextFieldAutoSize.LEFT;
			helper_desc_tf.wordWrap = true;
			helper_desc_tf.htmlText = detail_data.helper_desc;
			helper_desc_tf.height = helper_desc_tf.textHeight;

			var title_heigh = 29;
			var section_spacing = 10;

			// 任务标题
			//var next_pos:int = helper_title_tf.y + helper_title_tf.height + section_spacing;
			//next_pos += section_spacing * 2;

			// 任务描述
			//helper_desc_tf.y = next_pos + title_heigh;
			var next_pos:int = helper_desc_tf.y + helper_desc_tf.height;
			
			this.height = next_pos + 4;
           (this.parent.getChildByName("_scrollingView") as ScrollingView).displayMc= this.parent.getChildByName("helper_detail_mc");
		}
	}
}