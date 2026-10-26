package UI_Reputation.AS3
{
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.TreeDataProvider;
	import flash.external.ExternalInterface;
	import ActionScript3.Charactor.ReputationInfoBox;
	import flash.text.TextField;
	import ActionScript3.Common.CustomScrollBar;
	import scaleform.clik.controls.CheckBox;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.text.StyleSheet;
	import flash.events.TextEvent;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import ActionScript3.Slot.MySlot;
	import scaleform.clik.controls.Button;


	public class ReputationPanel extends MyPanel
	{

		public var list_mc:ScrollingList;
		public var tf_Message:TextField;
		public var sb_Message:CustomScrollBar;
		public var itemsData:Array = [];
		public var RelationBar_mc:RelationBar_base;
		public var TrackCheck_mc:CheckBox;
		public var curDatforceID:Number;

		public var mc_slot0:MySlot;
		public var mc_slot1:MySlot;
		public var mc_slot2:MySlot;
		public var mc_slot3:MySlot;
		public var mc_slot4:MySlot;

		public var mc_slot5:MySlot;
		public var mc_slot6:MySlot;
		public var mc_slot7:MySlot;
		public var mc_slot8:MySlot;
		public var mc_slot9:MySlot;

		public var btn_Receive:Button;


		override protected function configUI():void
		{
			super.configUI();

			this.ShowMode = "BC";
			ExternalInterface.call( "RegisterReputation", this );
			SetWindowTitle("声望");

			this.addEventListener(Event.REMOVED_FROM_STAGE, onRmoved );

			for (var i:int = 1; i < 28; i++)
			{
				itemsData.push({label:"Item " + i, index:i ,forceID:i, type:0, deepth:1, visible:true, curReputation:i*5, maxReputation:100,minReputation:0, txtReputation:"友好", tips:"eeeeeeeeee" ,info:"Item Info "+i  });
			}
			itemsData[0].type = 1;
			itemsData[0].deepth = 0;
			itemsData[3].type = 1;
			itemsData[3].deepth = 1;
			itemsData[6].type = 1;
			itemsData[6].deepth = 0;
			updateItemsData(itemsData);
			list_mc.selectedIndex = 0;
			list_mc.addEventListener(ListEvent.INDEX_CHANGE, handleListChange, false, 0, true);
			list_mc.addEventListener(ListEvent.ITEM_CLICK, handleListItemClick, false, 0, true);
			list_mc.addEventListener(ListEvent.ITEM_ROLL_OVER, handleListItemRollOver, false, 0, true);
			list_mc.addEventListener(ListEvent.ITEM_ROLL_OUT, handleListItemRollOut, false, 0, true);

			tf_Message.addEventListener(TextEvent.LINK, onLinkCallBack);
			tf_Message.addEventListener(TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			tf_Message.addEventListener(TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			tf_Message.styleSheet = new StyleSheet  ;
			sb_Message.scrollTarget = tf_Message;

			curDatforceID = -1;

			TrackCheck_mc.addEventListener("click", TrackClick);
			btn_Receive.addEventListener("click", AwardClick);

		}

		override public function onRmoved(e:Event)
		{
			super.onRmoved(e);
			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			tf_Message.removeEventListener(TextEvent.LINK, onLinkCallBack);
			tf_Message.removeEventListener(TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			tf_Message.removeEventListener(TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
		}

		function TrackClick(e:MouseEvent):void
		{
			if (visible)
			{
				if (curDatforceID>=0)
				{
					ExternalInterface.call( "ASSelectTrackForceID",curDatforceID );
				}
			}
		}

		function AwardClick(e:MouseEvent):void
		{
			if (curDatforceID>=0)
			{
				ExternalInterface.call( "ASAwardClick",curDatforceID );
			}
		}

		public function RelationPanel()
		{
		}

		public function SetSelectedItem( ForceID:Number ):void
		{
			var Provider:TreeDataProvider = list_mc.dataProvider as TreeDataProvider;
			for (var i=0; i<Provider.length; i++)
			{
				var obj:Object = Provider.requestItemAt(i);
				if (obj && ForceID == obj.forceID )
				{
					UpdateSelected(obj);
					list_mc.selectedIndex = i;
					list_mc.invalidateData();
					break;
				}
			}			
		}
		
		public function RefreshSelected():void
		{
			var Provider:TreeDataProvider = list_mc.dataProvider as TreeDataProvider;
			var index = list_mc.selectedIndex;
			var obj:Object = Provider.requestItemAt(index);
			if (obj && obj.type==0 && index>0 && obj.deepth>0)
			{
				UpdateSelected(obj);
			}
			else
			{
				UpdateSelected(null);
			}
		}		
		
		public function UpdateSelected(dat:Object)
		{
			if (dat)
			{
				tf_Message.htmlText = dat.info;
				TrackCheck_mc.enabled = true;
				curDatforceID = dat.forceID;
				if (dat.trackForceID == dat.forceID)
				{
					TrackCheck_mc.selected = true;
				}
				else
				{
					TrackCheck_mc.selected = false;
				}
				RelationBar_mc.UpdateData(dat);
				btn_Receive.visible = ! dat.awardState;
			}
			else
			{
				curDatforceID = -1;
				tf_Message.htmlText = "";
				TrackCheck_mc.enabled = false;
				RelationBar_mc.UpdateData(dat);
				btn_Receive.visible = false;
			}
			ExternalInterface.call( "ASUpdateRewordSlot",dat);
		}		
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public function updateItemsData( data:Array ):void
		{
			list_mc.dataProvider = new TreeDataProvider(data);
			list_mc.validateNow();
			list_mc.invalidateData();
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
				var obj:Object = Provider.requestItemAt(event.index);
				if (obj.type > 0)
				{

					ExternalInterface.call( "ASChangeReputationType",obj.ID, obj.type );
					UpdateSelected(null);
				}
				else
				{
					UpdateSelected(obj);
				}
				targetList.invalidateData();
			}
		}

		function handleListItemRollOver(event:ListEvent ):void
		{
			var itemRenderer:ListItemRenderer_Relation = event.itemRenderer as ListItemRenderer_Relation;
			if (itemRenderer != null)
			{
				itemRenderer.handleListItemRollOver();
			}
		}

		function handleListItemRollOut(event:ListEvent ):void
		{
			var itemRenderer:ListItemRenderer_Relation = event.itemRenderer as ListItemRenderer_Relation;
			if (itemRenderer != null)
			{
				itemRenderer.handleListItemRollOut();
			}
		}

		function onLinkOverCallBack(e:TextEventEx):void
		{
			trace("+++++++++++onLinkOverCallBack");
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		function onLinkOutCallBack(e:TextEventEx):void
		{
			trace("-----------onLinkOverCallBack");
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		function onLinkCallBack(e:TextEvent):void
		{
			trace("-----------onLinkCallBack");
			if ((e is TextEventEx))
			{
				var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
				var buttonIdx:int = (e as TextEventEx).buttonIdx;
				ExternalInterface.call( "ASLinkCallBack" , commandParameter , buttonIdx );
			}
		}

	}
}