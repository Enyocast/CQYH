package UI_ActivityWidget.ActivityAS3{
	
	import ActionScript3.MyPanel;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import flash.events.Event;

	public class ActivityFBView extends UIComponent
	{
		public var detailTitle0_tf:TextField;
		public var detailTitle1_tf:TextField;
		public var detailTitle2_tf:TextField;
		public var detailTitle3_tf:TextField;
		
		public var activity_Condition_tf:TextField;
		public var activity_Pos_tf:TextField;
		public var activity_Content_tf:TextField;
		public var activity_name_tf:TextField;
		public var bar:ScrollBar;
		
		override protected  function configUI():void 
		{		
			super.configUI();			
			//detailTitle0_tf.text = "";
			activity_Pos_tf.styleSheet = new StyleSheet  ;
			activity_Pos_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			activity_Pos_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
			activity_Pos_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
		}

		
		public function UpdateActivityDetailInfo(data:ActivityDetailInfo)
		{
			//ExternalInterface.call("ASTrace","---------ActivityFBView:UCUpdateActivityDetailInfo------");
			if(data)
			{
				activity_name_tf.text 		= 			data.activityName;
				activity_Condition_tf.text 	= 			data.conditionLimited;
				activity_Pos_tf.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				activity_Pos_tf.wordWrap 	= 			true;
				activity_Pos_tf.htmlText 	= 			data.activityPosition;
				activity_Pos_tf.height 		= 			activity_Pos_tf.textHeight;
				activity_Content_tf.text 	= 			data.describle;
				
				//detailTitle0_tf.text 		=            data.conditionTitle;(标题变短了)
				detailTitle1_tf.text 		=            data.positionTitle;
				detailTitle2_tf.text 		=            data.describleTitle;
				detailTitle3_tf.text 		=            data.rewardTitle;
			}
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

		function onLinkCallBack(e:TextEvent)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}
	}
}