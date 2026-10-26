package  UI_JourneyView.AS3
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.CustomScrollBar;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import UI_CharactorWidget.CharactorWidgetAS3.ListItemRenderer_Relation;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.gfx.TextEventEx;
	
	public class JourneyViewPanel extends MyPanel
	{
		public var NPC_icon:UILoader;
		public var get_awards_sign_mc:MovieClip;
		public var list_mc:ScrollingList;
		public var tf_NPC_name:TextField;
		public var tf_Message:TextField;
		//public var sb_Message:CustomScrollBar;
		public var itemsData:Array = [];
		public var journey_progress_bar_mc:JourneyProgressBar;
		
		public var mc_slot0:MyItemSlot;
		public var mc_slot1:MyItemSlot;
		public var mc_slot2:MyItemSlot;
		public var mc_slot3:MyItemSlot;
		public var mc_slot4:MyItemSlot;
		
		public var mc_slot5:MyItemSlot;
		public var mc_slot6:MyItemSlot;
		public var mc_slot7:MyItemSlot;
		public var mc_slot8:MyItemSlot;
		public var mc_slot9:MyItemSlot;
		
		public var award_bt:Button;
		public var _journey_view_data:JourneyViewData;
		
		private static const NUMBER_OF_REWARD_ITEMS:int = 10;
		
		public function JourneyViewPanel()
		{
			super();
		}
		
		override protected function configUI():void
		{
			this.ShowMode = "BC";
			super.configUI();
			SetWindowTitle("玛法传说");
			
			//test
			
/*			for (var i:int = 1; i < 28; i++)
			{
				itemsData.push({label:"Item " + i, index:i ,assistorIcon:"0.tga", chapterComplete : i % 2 == 0, forceID:i, type:0, deepth:1, visible:true, curReputation:i*5, maxReputation:100,minReputation:0, txtReputation:"友好", tips:"eeeeeeeeee" ,info:"Item Info "+i  });
			}
			itemsData[0].type = 1;
			itemsData[0].deepth = 0;
			itemsData[3].type = 1;
			itemsData[3].deepth = 1;
			itemsData[6].type = 1;
			itemsData[6].deepth = 0;
			updateItemsData(itemsData, 0);*/
			
			
			list_mc.selectedIndex = 0;
			list_mc.addEventListener(ListEvent.INDEX_CHANGE, handleListChange, false, 0, true);
			list_mc.addEventListener(ListEvent.ITEM_CLICK, handleListItemClick, false, 0, true);
			
			tf_NPC_name.htmlText = "";
			
			tf_Message.addEventListener(TextEvent.LINK, onLinkCallBack);
			tf_Message.addEventListener(TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			tf_Message.addEventListener(TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			tf_Message.styleSheet = new StyleSheet  ;
			//sb_Message.scrollTarget = tf_Message;
			
			get_awards_sign_mc.mouseEnabled = false;
			get_awards_sign_mc.visible = false;
			award_bt.enabled = false;
			award_bt.addEventListener(ButtonEvent.CLICK, getJourneyAwards, false, 0, true);
			_journey_view_data = null;
		}
		
//		override public function onRmoved(e:Event)
//		{
//			super.onRmoved(e);
//			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
//			tf_Message.removeEventListener(TextEvent.LINK, onLinkCallBack);
//			tf_Message.removeEventListener(TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
//			tf_Message.removeEventListener(TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
//		}
		
		public function UpdateSelected(data:JourneyViewData)
		{
			if (data)
			{
				_journey_view_data = data;
				if(data.journey_view_icon != null)
				{
					NPC_icon.source = data.journey_view_icon;
				}
				get_awards_sign_mc.visible = data.journey_view_get_awards;
				award_bt.enabled = data.journey_view_complete && !data.journey_view_get_awards;
				if(data.journey_view_title != null)
				{
					tf_NPC_name.htmlText = data.journey_view_title;
				}
				else
				{
					tf_NPC_name.htmlText = "";
				}
				tf_Message.htmlText = data.journey_view_desc;
				journey_progress_bar_mc.UpdateData(data.journey_view_progress);
				updateRewardItems(data.journey_view_rewards);
			}
			else
			{
				_journey_view_data = null;
				tf_NPC_name.htmlText = "";
				tf_Message.htmlText = "";
				get_awards_sign_mc.visible = false;
				award_bt.enabled = false;
				journey_progress_bar_mc.UpdateData(null);
			}
		}	
		
		private function updateRewardItems(items:Array):void
		{
			var item_num:int = 0;
			if(items)
			{
				item_num = items.length;
			}
			var item_data:Object;
			for(var i:int = 0; i < NUMBER_OF_REWARD_ITEMS; i++)
			{
				if(i < item_num)
				{
					(this['mc_slot' + i] as MyItemSlot).SetData(items[i].item_count, items[i].item_icon, items[i].item_id, "", 0, -1, -1);
					(this['mc_slot' + i] as MyItemSlot).visible = true;
				}
				else
				{
					(this['mc_slot' + i] as MyItemSlot).visible = false;
				}
			}
		}
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public function updateItemsData( data:Array, select:int ):void
		{
			list_mc.dataProvider = new TreeDataProvider(data);
			list_mc.validateNow();
			list_mc.invalidateData();
			list_mc.selectedIndex = select;
		}
		
		function handleListChange( event:ListEvent ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}
		
		function handleListItemClick( event:ListEvent ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				var Provider:TreeDataProvider = targetList.dataProvider as TreeDataProvider;
				Provider.handleListItemClick( event );
				var obj:JourneyViewData = Provider.requestItemAt(event.index) as JourneyViewData;
				if (obj)
				{
					ExternalInterface.call( "ASUpdateJourneyInfo", obj.journey_view_id );
				}
				else
				{
					UpdateSelected(null);
				}
				targetList.invalidateData();
			}
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
			if ((e is TextEventEx))
			{
				var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
				var buttonIdx:int = (e as TextEventEx).buttonIdx;
				ExternalInterface.call( "ASLinkCallBack" , commandParameter , buttonIdx );
			}
		}
		
		private function getJourneyAwards(evt:ButtonEvent):void
		{
			if (_journey_view_data)
			{
				ExternalInterface.call("ASGetCompleteAwards", _journey_view_data.journey_view_id);
			}
		}
	}
}